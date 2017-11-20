# #%L
# OME-FILES Python library for image IO.
# Copyright (c) 2017 University of Dundee
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

import ome_files


class TestVersion(object):

    def test_upstream_version(self):
        v = ome_files.upstream_version_info
        for a in "major", "minor", "patch", "extra":
            assert hasattr(v, a)
        assert len(v) == 4
        assert v[:1] == (v.major,)
        assert v[:2] == (v.major, v.minor)
        assert v[:3] == (v.major, v.minor, v.patch)
        assert v[:4] == (v.major, v.minor, v.patch, v.extra)
        exp_str = "%d.%d.%d%s" % (v.major, v.minor, v.patch, v.extra)
        assert str(v) == exp_str
        assert ome_files.upstream_version == exp_str
