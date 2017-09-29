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

from __future__ import (
    absolute_import, division, print_function, unicode_literals
)

import os
import uuid

import pytest

import numpy as np
import ome_files

THIS_DIR = os.path.dirname(os.path.abspath(__file__))


class NotABool(object):
    def __nonzero__(self):
        raise NotImplementedError("truth value is undefined")

    def __bool__(self):
        raise NotImplementedError("truth value is undefined")


@pytest.fixture(scope='class',
                params=[
                    {
                        'image': os.path.join(THIS_DIR, 'data',
                                              'multi-channel-4D-series'
                                              '.companion.ome'),
                        'series-count': 1,
                        'image-count': 60,
                        'size-x': 128,
                        'size-y': 64,
                        'size-z': 5,
                        'size-t': 4,
                        'size-c': 3,
                        'effective-size-c': 3,
                        'dimension-order': 'XYZCT',
                        'bytes-per-pixel': 2,
                        'pixel-type': 'u2',
                        'rgb-channel-count': 1,
                        'interleaved': True,
                        'used-files': [
                            os.path.join(THIS_DIR, 'data',
                                         'multi-channel-4D-series'
                                         '.companion.ome'),
                            os.path.join(THIS_DIR, 'data',
                                         'plane.ome.tiff')
                        ]
                    },
                    {
                        'image': os.path.join(THIS_DIR, 'data',
                                              'rgb.ome.tiff'),
                        'series-count': 1,
                        'image-count': 1,
                        'size-x': 128,
                        'size-y': 64,
                        'size-z': 1,
                        'size-t': 1,
                        'size-c': 3,
                        'effective-size-c': 1,
                        'dimension-order': 'XYCTZ',
                        'bytes-per-pixel': 2,
                        'pixel-type': 'u1',
                        'rgb-channel-count': 3,
                        'interleaved': True,
                        'used-files': [
                            os.path.join(THIS_DIR, 'data',
                                         'rgb.ome.tiff')
                        ]
                    },
                    {
                        'image': os.path.join(THIS_DIR, 'data',
                                              'grey.ome.tiff'),
                        'series-count': 1,
                        'image-count': 1,
                        'size-x': 128,
                        'size-y': 64,
                        'size-z': 1,
                        'size-t': 1,
                        'size-c': 1,
                        'effective-size-c': 1,
                        'dimension-order': 'XYCTZ',
                        'bytes-per-pixel': 2,
                        'pixel-type': 'u1',
                        'rgb-channel-count': 1,
                        'interleaved': True,
                        'used-files': [
                            os.path.join(THIS_DIR, 'data',
                                         'grey.ome.tiff')
                        ]
                    }
                ])
def ome_tiff_testcases(request):
    request.cls.image = request.param['image']
    request.cls.results = request.param
    yield


def test_bad_id():
    reader = ome_files.OMETIFFReader()
    filename = str(uuid.uuid4())
    with pytest.raises(RuntimeError):
        reader.set_id(filename)
    with pytest.raises(TypeError):
        reader.set_id(0)


@pytest.mark.usefixtures('ome_tiff_testcases')
class TestOMETiffReader(object):
    def setup_method(self):
        self.reader = ome_files.OMETIFFReader()

    def assertPathsEqualNoOrder(self, paths1, paths2, msg=None):
        self.assertEqual(sorted(os.path.realpath(_) for _ in paths1),
                         sorted(os.path.realpath(_) for _ in paths2), msg=msg)

    def test_image_count(self):
        with pytest.raises(RuntimeError):
            self.reader.get_image_count()
        self.reader.set_id(self.image)
        assert self.reader.get_image_count() == self.results['image-count']
        self.reader.close(file_only=True)
        assert self.reader.get_image_count() == self.results['image-count']
        self.reader.close()
        with pytest.raises(RuntimeError):
            self.reader.get_image_count()

    def test_series_count(self):
        with pytest.raises(RuntimeError):
            self.reader.get_series_count()
        self.reader.set_id(self.image)
        assert self.reader.get_series_count() == self.results['series-count']
        self.reader.close()
        with pytest.raises(RuntimeError):
            self.reader.get_series_count()

    def test_series(self):
        with pytest.raises(RuntimeError):
            self.reader.set_series(0)
        self.reader.set_id(self.image)
        with pytest.raises(TypeError):
            self.reader.set_series(0.)
        self.reader.set_series(0)
        assert self.reader.get_series() == 0
        self.reader.close()
        with pytest.raises(RuntimeError):
            self.reader.set_series(0)

    def test_dimensions(self):
        for dim in "xyztc":
            meth = getattr(self.reader, "get_size_%s" % dim)
            with pytest.raises(RuntimeError):
                meth()
        self.reader.set_id(self.image)
        assert self.reader.get_size_x() == self.results['size-x']
        assert self.reader.get_size_y() == self.results['size-y']
        assert self.reader.get_size_z() == self.results['size-z']
        assert self.reader.get_size_t() == self.results['size-t']
        assert self.reader.get_size_c() == self.results['size-c']
        assert self.reader.get_effective_size_c() == \
            self.results['effective-size-c']
        self.reader.close()
        for dim in "xyztc":
            meth = getattr(self.reader, "get_size_%s" % dim)
            with pytest.raises(RuntimeError):
                meth()

    def test_dimension_order(self):
        with pytest.raises(RuntimeError):
            self.reader.get_dimension_order()
        self.reader.set_id(self.image)
        assert self.reader.get_dimension_order() == \
            self.results['dimension-order']
        self.reader.close()
        with pytest.raises(RuntimeError):
            self.reader.get_dimension_order()

    def test_index(self):
        with pytest.raises(RuntimeError):
            self.reader.get_index(0, 0, 0)
        self.reader.set_id(self.image)
        assert self.reader.get_index(0, 0, 0) == 0
        with pytest.raises(IndexError):
            self.reader.get_index(self.results['size-z'], 0, 0)
        with pytest.raises(IndexError):
            self.reader.get_index(0, self.results['effective-size-c'], 0)
        with pytest.raises(IndexError):
            self.reader.get_index(0, 0, self.results['size-t'])
        self.reader.close()
        with pytest.raises(RuntimeError):
            self.reader.get_index(0, 0, 0)

    def test_zct_coords(self):
        with pytest.raises(RuntimeError):
            self.reader.get_zct_coords(0)
        self.reader.set_id(self.image)
        assert self.reader.get_zct_coords(0) == [0, 0, 0]
        self.reader.close()
        with pytest.raises(RuntimeError):
            self.reader.get_zct_coords(0)

    def test_all_coords(self):
        self.reader.set_id(self.image)
        for z in range(self.results['size-z']):
            for c in range(self.results['effective-size-c']):
                for t in range(self.results['size-t']):
                    index = self.reader.get_index(z, c, t)
                    zct = self.reader.get_zct_coords(index)
                    assert zct == [z, c, t]
        self.reader.close()

    def test_pixel_dtype(self):
        with pytest.raises(RuntimeError):
            self.reader.get_pixel_dtype()
        self.reader.set_id(self.image)
        assert self.reader.get_pixel_dtype() == self.results['pixel-type']
        self.reader.close()
        with pytest.raises(RuntimeError):
            self.reader.get_pixel_dtype()

    def test_bad_close(self):
        self.reader.set_id(self.image)
        with pytest.raises(TypeError):
            self.reader.close(NotABool())
        self.reader.close()

    def test_rgb_channel_count(self):
        with pytest.raises(RuntimeError):
            self.reader.get_rgb_channel_count(0)
        self.reader.set_id(self.image)
        with pytest.raises(TypeError):
            self.reader.get_rgb_channel_count(0.)
        assert self.reader.get_rgb_channel_count(0) == \
            self.results['rgb-channel-count']
        self.reader.close()
        with pytest.raises(RuntimeError):
            self.reader.get_rgb_channel_count(0)

    def test_interleaved(self):
        with pytest.raises(RuntimeError):
            self.reader.is_interleaved(0)
        self.reader.set_id(self.image)
        with pytest.raises(TypeError):
            self.reader.is_interleaved(0.)
            assert self.reader.is_interleaved(0) == \
                self.results['interleaved']
        self.reader.close()
        with pytest.raises(RuntimeError):
            self.reader.is_interleaved(0)

    def test_open_bytes(self):
        with pytest.raises(RuntimeError):
            self.reader.open_bytes(0)
        self.reader.set_id(self.image)
        with pytest.raises(TypeError):
            self.reader.open_bytes(0.)
        raw = self.reader.open_bytes(0)
        assert raw.size == \
            self.results['size-x'] * \
            self.results['size-y'] * \
            self.results['rgb-channel-count']
        self.reader.close()
        with pytest.raises(RuntimeError):
            self.reader.open_bytes(0)

    def test_used_files(self):
        with pytest.raises(RuntimeError):
            self.reader.get_used_files()
        self.reader.set_id(self.image)
        with pytest.raises(TypeError):
            self.reader.get_used_files(NotABool())
        fnames = self.reader.get_used_files()
        assert len(fnames) == len(self.results['used-files'])
        assert sorted(fnames) == sorted(self.results['used-files'])
        assert len(self.reader.get_used_files(no_pixels=True)) == 0
        self.reader.close()
        with pytest.raises(RuntimeError):
            self.reader.get_used_files()

    def test_metadata(self):
        self.reader.set_id(self.image)
        assert self.reader.get_ome_xml().strip().startswith("<?xml")
        self.reader.close()

    def test_open_bytes_simple(self):
        self.reader.set_id(self.image)
        img = self.reader.open_bytes_simple(0)
        if type(img) is list:
            assert self.reader.get_rgb_channel_count(0) > 1
            assert len(img) == self.reader.get_rgb_channel_count(0)
            for rgb_plane in img:
                assert hasattr(rgb_plane, "shape")
                assert rgb_plane.shape == \
                    (self.results['size-y'], self.results['size-x'])
                assert hasattr(rgb_plane, "dtype")
                assert rgb_plane.dtype == np.dtype(self.results['pixel-type'])
        else:
            assert hasattr(img, "shape")
            assert img.shape == \
                (self.results['size-y'], self.results['size-x'])
            assert hasattr(img, "dtype")
            assert img.dtype == np.dtype(self.results['pixel-type'])
        self.reader.close()
