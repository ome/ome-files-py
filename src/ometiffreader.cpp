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

#include <algorithm>
#include <string>
#include <vector>

#include <pybind11/pybind11.h>
#include <pybind11/numpy.h>
#include <pybind11/stl.h>

#include <ome/files/in/OMETIFFReader.h>
#include <ome/xml/meta/MetadataStore.h>
#include <ome/xml/meta/OMEXMLMetadata.h>
#include <ome/xml/model/enums/PixelType.h>

#include "ometiffreader.h"

namespace py = pybind11;
using ome::files::in::OMETIFFReader;
using ome::files::PixelBuffer;
using ome::files::PixelProperties;
using ome::files::VariantPixelBuffer;

namespace
{

  struct PBNumPyReadVisitor : public boost::static_visitor<py::array>
  {
    template<typename T>
    auto
    operator() (std::shared_ptr<PixelBuffer<T>>& v) const -> py::array
    {
      if (!v)
        throw std::runtime_error("Null pixel type");

      std::vector<size_t> shape(v->shape(), v->shape() + v->num_dimensions());
      std::vector<size_t> strides(v->num_dimensions());
      std::transform(v->strides(), v->strides() + v->num_dimensions(),
                     strides.begin(),
                     [](boost::multi_array_types::index s) -> size_t
                     {
                       if (s < 0)
                         throw std::runtime_error("Arrays with negative strides are unsupported with NumPy");
                       return s;
                     });
      py::array_t<T> py_array(shape, strides);
      std::copy(v->data(), v->data() + v->num_elements(),
                py_array.mutable_data());

      return py_array;
    }
  };

}


void init_ometiffreader(py::module &m) {
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
    .def("get_series", [](const OMETIFFReader &r) {
        return r.getSeries();
      }, "Get the active series.")
    .def("get_image_count", [](const OMETIFFReader &r) {
	return r.getImageCount();
      }, "Get the number of image planes in the current series.")
    .def("get_series_count", [](const OMETIFFReader &r) {
        return r.getSeriesCount();
      }, "Get the number of image series.")
    .def("get_size_x", [](const OMETIFFReader &r) {
	return r.getSizeX();
      }, "Get the size of the X dimension.")
    .def("get_size_y", [](const OMETIFFReader &r) {
        return r.getSizeY();
      }, "Get the size of the Y dimension.")
    .def("get_size_z", [](const OMETIFFReader &r) {
        return r.getSizeZ();
      }, "Get the size of the Z dimension.")
    .def("get_size_t", [](const OMETIFFReader &r) {
        return r.getSizeT();
      }, "Get the size of the T dimension.")
    .def("get_size_c", [](const OMETIFFReader &r) {
        return r.getSizeC();
      }, "Get the size of the C dimension.")
    .def("get_effective_size_c", [](const OMETIFFReader &r) {
        return r.getEffectiveSizeC();
      }, "Get the effective size of the C dimension.")
    .def("get_dimension_order", [](const OMETIFFReader &r) {
        return r.getDimensionOrder();
      }, "Get a five-character string representing the order in which "
      "planes will be returned.")
    .def("get_index", [](const OMETIFFReader &r, size_t z, size_t c, size_t t) {
	return r.getIndex(z, c, t);
      }, "Get the plane index corresponding to the given ZCT coordinates.")
    .def("get_zct_coords", [](const OMETIFFReader &r, size_t index) {
	return r.getZCTCoords(index);
      }, "Get the ZCT coordinates for the given plane index.")
    .def("get_rgb_channel_count", [](const OMETIFFReader &r, size_t channel) {
	return r.getRGBChannelCount(channel);
      }, "Get the number of sub-channels for the given channel.")
    .def("is_interleaved",
	 (bool (OMETIFFReader::*)(size_t) const) &OMETIFFReader::isInterleaved,
	 "Whether or not the given channel is interleaved")
    .def("is_interleaved",
	 (bool (OMETIFFReader::*)() const) &OMETIFFReader::isInterleaved,
	 "Whether or not the channels are interleaved")
    .def("get_pixel_dtype", [](const OMETIFFReader &r) {
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
	  return "?";
	default:
	  throw std::invalid_argument("unknown pixel type");
	}
      }, "Get the pixel type.")
    .def("open_bytes", [](const OMETIFFReader &r, size_t plane) {
	VariantPixelBuffer buf;
	r.openBytes(plane, buf);
        PBNumPyReadVisitor v;
        return boost::apply_visitor(v, buf.vbuffer());
      }, "Obtain the image plane for the given index.")
    .def("get_used_files", [](const OMETIFFReader &r, bool noPixels = false) {
	std::vector<std::string> fnames;
	for (const auto &f : r.getUsedFiles(noPixels)) {
	  fnames.push_back(f.string());
	}
	return fnames;
      }, "Get the files used by this dataset. "
      "If no_pixels is False, exclude pixel data files.",
      py::arg("no_pixels") = false)
    .def("get_ome_xml", [](const OMETIFFReader &r) {
	auto meta = std::dynamic_pointer_cast<ome::xml::meta::OMEXMLMetadata>(
          r.getMetadataStore()
        );
	return meta->dumpXML();
      }, "Get the OME XML metadata block.")
    .def("close", &OMETIFFReader::close, "Close the currently open file. "
	 "If file_only is False, also reset all internal state",
	 py::arg("file_only") = false);
}
