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

import pytest

import numpy as np
import ome_files

THIS_DIR = os.path.dirname(os.path.abspath(__file__))


class NotABool(object):
    def __nonzero__(self):
        raise NotImplementedError("truth value is undefined")

    def __bool__(self):
        raise NotImplementedError("truth value is undefined")


def rgb_pixeldata(self):
    pixels = [np.ndarray(shape=[64, 128], dtype=np.dtype('u1'), order='C'),
              np.ndarray(shape=[64, 128], dtype=np.dtype('u1'), order='C'),
              np.ndarray(shape=[64, 128], dtype=np.dtype('u1'), order='C')]
    for s in range(0, len(pixels)):
        for (y, x), value in np.ndenumerate(pixels[s]):
            if s == 0:
                value = (x * 255) / 128
            if s == 1:
                value = (y * 255) / 64
            if s == 2:
                value = 255 - ((y * 255) / 64)
            pixels[s].itemset((y, x), value)
    return pixels


def grey_pixeldata(self):
    pixels = np.ndarray(shape=[64, 128], dtype=np.dtype('f4'), order='C')
    for (y, x), value in np.ndenumerate(pixels):
        value = x/128.0 + y/64.0
        pixels.itemset((y, x), value)
    return pixels


@pytest.fixture(scope='class',
                params=[
                    ('rgb',
                     {
                         'filename': 'rgb.ome.tiff',
                         'xml': """<?xml version="1.0" encoding="UTF-8"?>
<OME xmlns="http://www.openmicroscopy.org/Schemas/OME/2016-06"
     xmlns:xsi="http://www.w3.org/2001/XMLSchema-instance"
     Creator="OME Bio-Formats 5.7.2-SNAPSHOT"
     UUID="urn:uuid:fbca7579-37b6-4bc6-a216-4a7b2dfad2eb"
     xsi:schemaLocation="http://www.openmicroscopy.org/Schemas/OME/2016-06 \
http://www.openmicroscopy.org/Schemas/OME/2016-06/ome.xsd">
  <Image ID="Image:0" Name="rgb.png">
    <Pixels BigEndian="true" DimensionOrder="XYCTZ" ID="Pixels:0"
     Interleaved="true" SignificantBits="8" SizeC="3" SizeT="1"
     SizeX="128" SizeY="64" SizeZ="1" Type="uint8">
      <Channel ID="Channel:0:0" SamplesPerPixel="3"><LightPath/></Channel>
      <TiffData FirstC="0" FirstT="0" FirstZ="0" IFD="0" PlaneCount="1">
        <UUID FileName="rgb.ome.tiff">\
urn:uuid:fbca7579-37b6-4bc6-a216-4a7b2dfad2eb</UUID>
      </TiffData>
    </Pixels>
  </Image>
</OME>""",
                         'pixeldata': rgb_pixeldata
                     }),
                    ('grey',
                     {
                         'filename': 'grey.ome.tiff',
                         'xml': """<?xml version="1.0" encoding="UTF-8"?>
<OME xmlns="http://www.openmicroscopy.org/Schemas/OME/2016-06"
     xmlns:xsi="http://www.w3.org/2001/XMLSchema-instance"
     Creator="OME Bio-Formats 5.7.2-SNAPSHOT"
     UUID="urn:uuid:fbda7579-37b6-4bc6-a216-4a7b2dfad2eb"
     xsi:schemaLocation="http://www.openmicroscopy.org/Schemas/OME/2016-06 \
http://www.openmicroscopy.org/Schemas/OME/2016-06/ome.xsd">
  <Image ID="Image:0" Name="grey.png">
    <Pixels BigEndian="true" DimensionOrder="XYCTZ" ID="Pixels:0"
     Interleaved="true" SignificantBits="8" SizeC="1" SizeT="1"
     SizeX="128" SizeY="64" SizeZ="1" Type="float">
      <Channel ID="Channel:0:0" SamplesPerPixel="1"><LightPath/></Channel>
      <TiffData FirstC="0" FirstT="0" FirstZ="0" IFD="0" PlaneCount="1">
        <UUID FileName="grey.ome.tiff">\
urn:uuid:fbda7579-37b6-4bc6-a216-4a7b2dfad2eb</UUID></TiffData>
    </Pixels>
  </Image>
</OME>""",
                         'pixeldata': grey_pixeldata
                     })
                ])
def ome_tiff_writer_testcases(request):
    request.cls.filename = request.param[1]['filename']
    request.cls.xml = request.param[1]['xml']
    request.cls.pixeldata = request.param[1]['pixeldata']
    request.cls.data = request.param[1]
    yield


@pytest.mark.usefixtures('ome_tiff_writer_testcases')
class TestOMETiffWriter(object):
    def setup_method(self):
        self.writer = ome_files.OMETIFFWriter()

    def test_open(self):
        self.writer.set_ome_xml(self.xml)
        self.writer.set_id(self.filename)

        # Error raised if no pixeldata written.
        with pytest.raises(RuntimeError):
            self.writer.close()

    def test_save_bytes(self):
        self.writer.set_ome_xml(self.xml)
        self.writer.set_id(self.filename)

        self.writer.save_bytes_simple(0, self.pixeldata())

        self.writer.close()
