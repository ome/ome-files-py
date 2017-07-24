/*
 * #%L
 * OME-FILES Python library for image IO.
 * Copyright (c) 2016-2017 University of Dundee
 * %%
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are met:
 *
 * 1. Redistributions of source code must retain the above copyright notice,
 *    this list of conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright notice,
 *    this list of conditions and the following disclaimer in the documentation
 *    and/or other materials provided with the distribution.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
 * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 * ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDERS OR CONTRIBUTORS BE
 * LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
 * CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
 * SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
 * INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
 * CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
 * ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
 * POSSIBILITY OF SUCH DAMAGE.
 * #L%
 */

#include <pybind11/pybind11.h>
#include <pybind11/stl.h>
#include <string>
#include <vector>
#include <ome/files/in/OMETIFFReader.h>
#include <ome/xml/meta/MetadataStore.h>
#include <ome/xml/meta/OMEXMLMetadata.h>
#include <ome/xml/model/enums/PixelType.h>

namespace py = pybind11;
using ome::files::in::OMETIFFReader;

PYBIND11_PLUGIN(_core) {
  py::module m("_core");
  py::class_<OMETIFFReader>(m, "OMETIFFReader")
    .def("__init__", [](OMETIFFReader &r) {
	new (&r) OMETIFFReader();
	std::shared_ptr<ome::xml::meta::MetadataStore> store(
          std::make_shared<ome::xml::meta::OMEXMLMetadata>()
        );
	r.setMetadataStore(store);
      })
    .def("set_id", [](OMETIFFReader &r, std::string id) {
	r.setId(id);
      }, "Set the current file name.")
    .def("set_series", [](OMETIFFReader &r, size_t series) {
        r.setSeries(series);
      }, "Set the active series.")
    .def("get_series", [](OMETIFFReader &r) {
        return r.getSeries();
      }, "Get the active series.")
    .def("get_image_count", [](OMETIFFReader &r) {
	return r.getImageCount();
      }, "Get the number of image planes in the current series.")
    .def("get_series_count", [](OMETIFFReader &r) {
        return r.getSeriesCount();
      }, "Get the number of image series.")
    .def("get_size_x", [](OMETIFFReader &r) {
	return r.getSizeX();
      }, "Get the size of the X dimension.")
    .def("get_size_y", [](OMETIFFReader &r) {
        return r.getSizeY();
      }, "Get the size of the Y dimension.")
    .def("get_size_z", [](OMETIFFReader &r) {
        return r.getSizeZ();
      }, "Get the size of the Z dimension.")
    .def("get_size_t", [](OMETIFFReader &r) {
        return r.getSizeT();
      }, "Get the size of the T dimension.")
    .def("get_size_c", [](OMETIFFReader &r) {
        return r.getSizeC();
      }, "Get the size of the C dimension.")
    .def("get_dimension_order", [](OMETIFFReader &r) {
        return r.getDimensionOrder();
      }, "Get a five-character string representing the order in which "
      "planes will be returned.")
    .def("get_index", [](OMETIFFReader &r, size_t z, size_t c, size_t t) {
	return r.getIndex(z, c, t);
      }, "Get the plane index corresponding to the given ZCT coordinates.")
    .def("get_zct_coords", [](OMETIFFReader &r, size_t index) {
	return r.getZCTCoords(index);
      }, "Get the ZCT coordinates for the given plane index.")
    .def("get_rgb_channel_count", [](OMETIFFReader &r, size_t channel) {
	return r.getRGBChannelCount(channel);
      }, "Get the number of sub-channels for the given channel.")
    .def("is_interleaved",
	 (bool (OMETIFFReader::*)(size_t) const) &OMETIFFReader::isInterleaved,
	 "Whether or not the given channel is interleaved")
    .def("is_interleaved",
	 (bool (OMETIFFReader::*)() const) &OMETIFFReader::isInterleaved,
	 "Whether or not the channels are interleaved")
    .def("get_pixel_type", [](OMETIFFReader &r) {
	switch(r.getPixelType()) {
	case ome::xml::model::enums::PixelType::INT8:
	  return "i1";
	case ome::xml::model::enums::PixelType::INT16:
	  return "i2";
	case ome::xml::model::enums::PixelType::INT32:
	  return "i4";
	case ome::xml::model::enums::PixelType::UINT8:
	  return "u1";
	case ome::xml::model::enums::PixelType::UINT16:
	  return "u2";
	case ome::xml::model::enums::PixelType::UINT32:
	  return "u4";
	case ome::xml::model::enums::PixelType::FLOAT:
	  return "f4";
	case ome::xml::model::enums::PixelType::DOUBLE:
	  return "f8";
	case ome::xml::model::enums::PixelType::COMPLEXFLOAT:
	  return "c8";
	case ome::xml::model::enums::PixelType::COMPLEXDOUBLE:
	  return "c16";
	case ome::xml::model::enums::PixelType::BIT:
	  return "b1";
	default:
	  throw std::invalid_argument("unknown pixel type");
	}
      }, "Get the pixel type.")
    .def("open_bytes", [](OMETIFFReader &r, size_t plane) {
	ome::files::VariantPixelBuffer buf;
	r.openBytes(plane, buf);
	return py::bytes(std::string(
          reinterpret_cast<char*>(buf.data()),
          buf.num_elements() * ome::files::bytesPerPixel(buf.pixelType())
	));
      }, "Obtain the image plane for the given index.")
    .def("get_used_files", [](OMETIFFReader &r, bool noPixels = false) {
	std::vector<std::string> fnames;
	for (const auto &f : r.getUsedFiles(noPixels)) {
	  fnames.push_back(f.string());
	}
	return fnames;
      }, "Get the files used by this dataset. "
      "If no_pixels is False, exclude pixel data files.",
      py::arg("no_pixels") = false)
    .def("get_ome_xml", [](OMETIFFReader &r) {
	auto meta = std::dynamic_pointer_cast<ome::xml::meta::OMEXMLMetadata>(
          r.getMetadataStore()
        );
	return meta->dumpXML();
      }, "Get the OME XML metadata block.")
    .def("close", &OMETIFFReader::close, "Close the currently open file. "
	 "If file_only is False, also reset all internal state",
	 py::arg("file_only") = false);
  return m.ptr();
}
