# #%L
# OME-FILES Python library for image IO.
# Copyright (c) 2016-2017 University of Dundee
# %%
# Redistribution and use in source and binary forms, with or without
# modification, are permitted provided that the following conditions are met:
#
# 1. Redistributions of source code must retain the above copyright notice,
#    this list of conditions and the following disclaimer.
# 2. Redistributions in binary form must reproduce the above copyright notice,
#    this list of conditions and the following disclaimer in the documentation
#    and/or other materials provided with the distribution.
#
# THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
# AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
# IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
# ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDERS OR CONTRIBUTORS BE
# LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
# CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
# SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
# INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
# CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
# ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
# POSSIBILITY OF SUCH DAMAGE.
# #L%

import numpy as np

import _core
from _core import Error
try:
    from ome_files.version import version as __version__
except ImportError:
    __version__ = None


__all__ = ["OMETIFFReader", "Error"]


class OMETIFFReader(_core.OMETIFFReader):

    def open_array(self, plane):
        """\
        Obtain the image plane for the given index as a numpy array, or a
        list of numpy arrays in the RGB case.
        """
        H, W = self.get_size_y(), self.get_size_x()
        dtype = np.dtype(self.get_pixel_type())
        rgb = self.get_rgb_channel_count(0)  # TODO: use actual channel
        interleaved = self.is_interleaved(0)
        raw = self.open_bytes(plane)
        pixels = np.fromstring(raw, dtype=dtype)
        N = H * W
        assert pixels.size == N * rgb
        if rgb <= 1:
            pixels = pixels.reshape((H, W))
        else:
            if interleaved:
                pixels = [pixels[j: j+N*rgb: rgb].reshape((H, W))
                          for j in xrange(rgb)]
            else:
                pixels = [pixels[N*j: N*(j+1)].reshape((H, W))
                          for j in xrange(rgb)]
        return pixels
