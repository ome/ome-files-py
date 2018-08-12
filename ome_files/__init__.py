# #%L
# OME-FILES Python library for image IO.
# Copyright © 2016-2017 University of Dundee
# Copyright © 2018 Quantitative Imaging Systems, LLC
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

from __future__ import (
    absolute_import, division, print_function, unicode_literals
)
from collections import namedtuple

import numpy as np

from . import _core
try:
    from ome_files.version import version as __version__
except ImportError:
    __version__ = None


__all__ = [
    "OMETIFFReader"
    "OMETIFFWriter"
    "Version",
    "upstream_version",
    "upstream_version_info",
]


class Version(namedtuple("Version", ["major", "minor", "patch", "extra"])):

    __slots__ = ()

    def __str__(self):
        return "%d.%d.%d%s" % self


upstream_version_info = Version(
    _core.version_info.major,
    _core.version_info.minor,
    _core.version_info.patch,
    _core.version_info.extra,
)
upstream_version = str(upstream_version_info)


class OMETIFFReader(_core.OMETIFFReader):

    def open_bytes_simple(self, plane):
        """\
        Obtain the image plane for the given index as a numpy array, or a
        list of numpy arrays in the RGB case.
        """

        # Fetch 4D array
        a = self.open_bytes(plane)
        # Drop all unused dimensions
        s = np.squeeze(a, axis=(2))
        # Swap x,y to y,x
        s = np.swapaxes(s, 0, 1)
        # Split RGB samples into separate arrays
        if s.shape[2] == 1:
            return np.squeeze(s, axis=2)
        else:
            return [s[:, :, i] for i in range(0, s.shape[2])]


class OMETIFFWriter(_core.OMETIFFWriter):

    def save_bytes_simple(self, plane, buf):
        """\
        Obtain the image plane for the given index as a numpy array, or a
        list of numpy arrays in the RGB case.
        """

        copy = None
        # Recombine RGB samples into single array
        if type(buf) is list:
            shape = None
            dtype = None
            for planebuf in buf:
                if planebuf.ndim != 2:
                    raise RuntimeError(
                        "Invalid number of dimensions for RGB plane")
                if shape is None:
                    shape = planebuf.shape
                else:
                    if shape != planebuf.shape:
                        raise RuntimeError(
                            "Inconsistent dimension shapes for RGB planes")
                if dtype is None:
                    dtype = planebuf.dtype
                else:
                    if dtype != planebuf.dtype:
                        raise RuntimeError(
                            "Inconsistent datatypes for RGB planes")

            copy = np.ndarray(shape=(shape[0], shape[1], len(buf)),
                              dtype=dtype, order='C')
            for i in range(0, len(buf)):
                copy[:, :, i] = buf[i]
        else:
            # Take a copy to preserve the original, since we will alter it
            if buf.ndim != 2:
                raise RuntimeError("Invalid number of dimensions for plane")
            copy = np.array(buf, copy=True)
            # Add subchannel dimension
            copy = np.expand_dims(copy, axis=2)

        # Swap y,x to x,y
        copy = np.swapaxes(copy, 0, 1)

        # Add missing unused dimensions
        copy = np.expand_dims(copy, axis=2)

        # Save 4D array
        self.save_bytes(plane, copy)
