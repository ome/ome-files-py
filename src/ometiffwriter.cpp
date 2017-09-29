/*
 * #%L
 * OME-FILES Python library for image IO.
 * Copyright (c) 2017 University of Dundee
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

#include <ome/files/out/OMETIFFWriter.h>
#include <ome/files/MetadataTools.h>
#include <ome/files/PixelProperties.h>
#include <ome/files/VariantPixelBuffer.h>
#include <ome/xml/meta/MetadataStore.h>
#include <ome/xml/meta/OMEXMLMetadata.h>
#include <ome/xml/model/enums/DimensionOrder.h>
#include <ome/xml/model/enums/PixelType.h>

#include <boost/preprocessor.hpp>

#include "ometiffwriter.h"


namespace py = pybind11;
using ome::files::out::OMETIFFWriter;
using ome::files::PixelBufferBase;
using ome::files::PixelBuffer;
using ome::files::PixelProperties;
using ome::files::VariantPixelBuffer;
using ome::xml::model::enums::DimensionOrder;
using ome::xml::model::enums::PixelType;

namespace pybind11 { namespace detail {
    template <typename T>
    struct type_caster<boost::optional<T>> : optional_caster<boost::optional<T>> {};
}}

namespace
{

  template<typename T>
  void
  transfer_buffer (py::array           src,
                   VariantPixelBuffer& dest,
                   PixelType           pixeltype,
                   bool                interleaved)
  {
    py::array_t<T> tsrc = py::array_t<T>::ensure(src);
    if (!tsrc)
      throw std::runtime_error("Unsupported NumPy datatype");

    if (PixelBufferBase::dimensions != src.ndim())
      throw std::runtime_error("NumPy array has an invalid dimension count");

    std::vector<size_t> shape(src.shape(), src.shape() + src.ndim());
    std::vector<size_t> strides(src.strides(), src.strides() + src.ndim());
    auto storage_order = PixelBufferBase::make_storage_order(DimensionOrder::XYZTC, interleaved);

    dest.setBuffer(shape, pixeltype, storage_order);
    auto tdest = dest.array<T>();
    for(typename decltype(tdest)::index x = 0; x < src.shape()[ome::files::DIM_SPATIAL_X]; x++)
      {
        for(typename decltype(tdest)::index y = 0; y < src.shape()[ome::files::DIM_SPATIAL_Y]; y++)
          {
            for(typename decltype(tdest)::index s = 0; s < src.shape()[ome::files::DIM_SUBCHANNEL]; s++)
              {
                tdest[x][y][0][0][0][s][0][0][0] = tsrc.at(x, y, 0, 0, 0, s, 0, 0, 0);
              }
          }
      }
  }

}

void init_ometiffwriter(py::module &m) {
  py::class_<OMETIFFWriter>(m, "OMETIFFWriter")
    .def("__init__", [](OMETIFFWriter &r) {
	new (&r) OMETIFFWriter();
      })
    .def("set_ome_xml", [](OMETIFFWriter &r, std::string ome_xml) {
        std::shared_ptr<ome::xml::meta::MetadataRetrieve> metadata = ome::files::createOMEXMLMetadata(ome_xml);
	r.setMetadataRetrieve(metadata);
      }, "Set the OME XML metadata block.")
    .def("set_id", [](OMETIFFWriter &r, std::string id) {
	r.setId(id);
      }, "Set the current file name.")
    .def("set_series", [](OMETIFFWriter &r, size_t series) {
        r.setSeries(series);
      }, "Set the active series.")
    .def("get_series", [](const OMETIFFWriter &r) {
        return r.getSeries();
      }, "Get the active series.")
    .def("get_image_count", [](const OMETIFFWriter &r) {
	return r.getImageCount();
      }, "Get the number of image planes in the current series.")
    .def("get_series_count", [](const OMETIFFWriter &r) {
        return r.getSeriesCount();
      }, "Get the number of image series.")
    .def("get_size_x", [](const OMETIFFWriter &r) {
	return r.getSizeX();
      }, "Get the size of the X dimension.")
    .def("get_size_y", [](const OMETIFFWriter &r) {
        return r.getSizeY();
      }, "Get the size of the Y dimension.")
    .def("get_size_z", [](const OMETIFFWriter &r) {
        return r.getSizeZ();
      }, "Get the size of the Z dimension.")
    .def("get_size_t", [](const OMETIFFWriter &r) {
        return r.getSizeT();
      }, "Get the size of the T dimension.")
    .def("get_size_c", [](const OMETIFFWriter &r) {
        return r.getSizeC();
      }, "Get the size of the C dimension.")
    .def("get_dimension_order", [](const OMETIFFWriter &r) {
        return r.getDimensionOrder();
      }, "Get a five-character string representing the order in which "
      "planes will be returned.")
    .def("get_index", [](const OMETIFFWriter &r, size_t z, size_t c, size_t t) {
	return r.getIndex(z, c, t);
      }, "Get the plane index corresponding to the given ZCT coordinates.")
    .def("get_zct_coords", [](const OMETIFFWriter &r, size_t index) {
	return r.getZCTCoords(index);
      }, "Get the ZCT coordinates for the given plane index.")
    .def("get_rgb_channel_count", [](const OMETIFFWriter &r, size_t channel) {
	return r.getRGBChannelCount(channel);
      }, "Get the number of sub-channels for the given channel.")
    .def("set_interleaved",
	 (void (OMETIFFWriter::*)(bool) const) &OMETIFFWriter::setInterleaved,
	 "Enable or disable sub-channel interleaving")
    .def("get_interleaved",
	 (boost::optional<bool> (OMETIFFWriter::*)() const) &OMETIFFWriter::getInterleaved,
	 "Whether or not the channels are interleaved")
    .def("get_pixel_type", [](const OMETIFFWriter &r) {
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
    .def("save_bytes", [](OMETIFFWriter &w, size_t plane, const py::array& buf) {
	VariantPixelBuffer vbuf; // set pixel type for visit?
        const boost::optional<bool>& interleaved = w.getInterleaved();

        if (buf.dtype().is(py::dtype::of<uint8_t>()))
          {
            transfer_buffer<uint8_t>(buf, vbuf, PixelType::UINT8,
                                     interleaved && *interleaved);
          }
        else if (buf.dtype().is(py::dtype::of<uint16_t>()))
          {
            transfer_buffer<uint16_t>(buf, vbuf, PixelType::UINT16,
                                      interleaved && *interleaved);
          }
        else if (buf.dtype().is(py::dtype::of<uint32_t>()))
          {
            transfer_buffer<uint32_t>(buf, vbuf, PixelType::UINT32,
                                      interleaved && *interleaved);
          }
        else if (buf.dtype().is(py::dtype::of<int8_t>()))
          {
            transfer_buffer<int8_t>(buf, vbuf, PixelType::INT8,
                                    interleaved && *interleaved);
          }
        else if (buf.dtype().is(py::dtype::of<int16_t>()))
          {
            transfer_buffer<int16_t>(buf, vbuf, PixelType::INT16,
                                     interleaved && *interleaved);
          }
        else if (buf.dtype().is(py::dtype::of<int32_t>()))
          {
            transfer_buffer<int32_t>(buf, vbuf, PixelType::INT32,
                                     interleaved && *interleaved);
          }
        else if (buf.dtype().is(py::dtype::of<float>()))
          {
            transfer_buffer<float>(buf, vbuf, PixelType::FLOAT,
                                   interleaved && *interleaved);
          }
        else if (buf.dtype().is(py::dtype::of<double>()))
          {
            transfer_buffer<double>(buf, vbuf, PixelType::DOUBLE,
                                    interleaved && *interleaved);
          }
        else if (buf.dtype().is(py::dtype::of<std::complex<float>>()))
          {
            transfer_buffer<std::complex<float>>(buf, vbuf, PixelType::COMPLEXFLOAT,
                                                 interleaved && *interleaved);
          }
        else if (buf.dtype().is(py::dtype::of<std::complex<double>>()))
          {
            transfer_buffer<std::complex<double>>(buf, vbuf, PixelType::COMPLEXDOUBLE,
                                                  interleaved && *interleaved);
          }
        else if (buf.dtype().is(py::dtype::of<bool>()))
          {
            transfer_buffer<bool>(buf, vbuf, PixelType::BIT,
                                  interleaved && *interleaved);
          }
        else
          {
            throw std::runtime_error("NumPy array using unsupported pixel type");
          }

	w.saveBytes(plane, vbuf);
      }, "Provide the image plane for the given index.")
    .def("close", &OMETIFFWriter::close, "Close the currently open file. "
	 "If file_only is False, also reset all internal state",
	 py::arg("file_only") = false);
}
