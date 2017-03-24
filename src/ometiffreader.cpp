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

#include <Python.h>

#include <string>
#include <memory>
#include <array>

#include <boost/filesystem/path.hpp>

#include <ome/files/in/OMETIFFReader.h>
#include <ome/files/PixelProperties.h>
#include <ome/xml/model/enums/PixelType.h>
#include <ome/xml/meta/MetadataStore.h>
#include <ome/xml/meta/OMEXMLMetadata.h>

#include "ometiffreader.h"
#include "errors.h"


static int
PyOMETIFFReader_init(PyOMETIFFReader *self, PyObject *args, PyObject *kwds) {
  self->reader = std::make_shared<ome::files::in::OMETIFFReader>();
  try {
    std::shared_ptr<ome::xml::meta::MetadataStore> store(
      std::make_shared<ome::xml::meta::OMEXMLMetadata>());
    self->reader->setMetadataStore(store);
  } catch (const std::exception& e) {
    PyErr_SetString(OMEFilesPyError, e.what());
    return -1;
  }
  return 0;
}


static PyObject *
PyOMETIFFReader_setId(PyOMETIFFReader *self, PyObject *args) {
  const char *filename;
  if (!PyArg_ParseTuple(args, "s", &filename)) {
    return NULL;
  }
  try {
    self->reader->setId(std::string(filename));
  } catch (const std::exception& e) {
    PyErr_SetString(OMEFilesPyError, e.what());
    return NULL;
  }
  Py_RETURN_NONE;
}


static PyObject *
PyOMETIFFReader_close(PyOMETIFFReader *self, PyObject *args, PyObject *kwds) {
  PyObject *file_only = Py_False;
  static const char *kwlist[] = {"file_only", NULL};
  int fileOnly;
  if (!PyArg_ParseTupleAndKeywords(
        args, kwds, "|O", const_cast<char**>(kwlist), &file_only)) {
    return NULL;
  }
  fileOnly = PyObject_IsTrue(file_only);
  if (fileOnly < 0) {
    return PyErr_Format(PyExc_TypeError, "could not convert argument to bool");
  }
  try {
    self->reader->close(fileOnly);
  } catch (const std::exception& e) {
    PyErr_SetString(OMEFilesPyError, e.what());
    return NULL;
  }
  Py_RETURN_NONE;
}


static PyObject *
PyOMETIFFReader_setSeries(PyOMETIFFReader *self, PyObject *args) {
  size_t series;
  if (!PyArg_ParseTuple(args, "n", &series)) {
    return NULL;
  }
  try {
    self->reader->setSeries(series);
  } catch (const std::exception& e) {
    PyErr_SetString(OMEFilesPyError, e.what());
    return NULL;
  }
  Py_RETURN_NONE;
}


static PyObject *
PyOMETIFFReader_getSeries(PyOMETIFFReader *self) {
  try {
    return PyInt_FromSize_t(self->reader->getSeries());
  } catch (const std::exception& e) {
    PyErr_SetString(OMEFilesPyError, e.what());
    return NULL;
  }
}


static PyObject *
PyOMETIFFReader_getSeriesCount(PyOMETIFFReader *self) {
  try {
    return PyInt_FromSize_t(self->reader->getSeriesCount());
  } catch (const std::exception& e) {
    PyErr_SetString(OMEFilesPyError, e.what());
    return NULL;
  }
}


static PyObject *
PyOMETIFFReader_getImageCount(PyOMETIFFReader *self) {
  try {
    return PyInt_FromSize_t(self->reader->getImageCount());
  } catch (const std::exception& e) {
    PyErr_SetString(OMEFilesPyError, e.what());
    return NULL;
  }
}


static PyObject *
PyOMETIFFReader_getSizeX(PyOMETIFFReader *self) {
  try {
    return PyInt_FromSize_t(self->reader->getSizeX());
  } catch (const std::exception& e) {
    PyErr_SetString(OMEFilesPyError, e.what());
    return NULL;
  }
}


static PyObject *
PyOMETIFFReader_getSizeY(PyOMETIFFReader *self) {
  try {
    return PyInt_FromSize_t(self->reader->getSizeY());
  } catch (const std::exception& e) {
    PyErr_SetString(OMEFilesPyError, e.what());
    return NULL;
  }
}


static PyObject *
PyOMETIFFReader_getSizeZ(PyOMETIFFReader *self) {
  try {
    return PyInt_FromSize_t(self->reader->getSizeZ());
  } catch (const std::exception& e) {
    PyErr_SetString(OMEFilesPyError, e.what());
    return NULL;
  }
}


static PyObject *
PyOMETIFFReader_getSizeT(PyOMETIFFReader *self) {
  try {
    return PyInt_FromSize_t(self->reader->getSizeT());
  } catch (const std::exception& e) {
    PyErr_SetString(OMEFilesPyError, e.what());
    return NULL;
  }
}


static PyObject *
PyOMETIFFReader_getSizeC(PyOMETIFFReader *self) {
  try {
    return PyInt_FromSize_t(self->reader->getSizeC());
  } catch (const std::exception& e) {
    PyErr_SetString(OMEFilesPyError, e.what());
    return NULL;
  }
}


static PyObject *
PyOMETIFFReader_getDimensionOrder(PyOMETIFFReader *self) {
  try {
    return PyString_FromString(self->reader->getDimensionOrder().c_str());
  } catch (const std::exception& e) {
    PyErr_SetString(OMEFilesPyError, e.what());
    return NULL;
  }
}


static PyObject *
PyOMETIFFReader_getIndex(PyOMETIFFReader *self, PyObject *args) {
  size_t z, c, t;
  if (!PyArg_ParseTuple(args, "nnn", &z, &c, &t)) {
    return NULL;
  }
  try {
    return PyInt_FromSize_t(self->reader->getIndex(z, c, t));
  } catch (const std::exception& e) {
    PyErr_SetString(OMEFilesPyError, e.what());
    return NULL;
  }
}


static PyObject *
PyOMETIFFReader_getZCTCoords(PyOMETIFFReader *self, PyObject *args) {
  std::array<size_t, 3> zct;
  size_t index;
  if (!PyArg_ParseTuple(args, "n", &index)) {
    return NULL;
  }
  try {
    zct = self->reader->getZCTCoords(index);
  } catch (const std::exception& e) {
    PyErr_SetString(OMEFilesPyError, e.what());
    return NULL;
  }
  PyObject* ret = PyList_New(0);
  if (ret == NULL) {
    return NULL;
  }
  for (const auto &coord : zct) {
    if (PyList_Append(ret, PyInt_FromSize_t(coord)) < 0) {
      Py_DECREF(ret);
      return NULL;
    }
  }
  return ret;
}


static PyObject *
PyOMETIFFReader_getPixelType(PyOMETIFFReader *self) {
  const char *numpy_pt;
  try {
    switch(self->reader->getPixelType()) {
    case ome::xml::model::enums::PixelType::INT8:
      numpy_pt = "i1"; break;
    case ome::xml::model::enums::PixelType::INT16:
      numpy_pt = "i2"; break;
    case ome::xml::model::enums::PixelType::INT32:
      numpy_pt = "i4"; break;
    case ome::xml::model::enums::PixelType::UINT8:
      numpy_pt = "u1"; break;
    case ome::xml::model::enums::PixelType::UINT16:
      numpy_pt = "u2"; break;
    case ome::xml::model::enums::PixelType::UINT32:
      numpy_pt = "u4"; break;
    case ome::xml::model::enums::PixelType::FLOAT:
      numpy_pt = "f4"; break;
    case ome::xml::model::enums::PixelType::DOUBLE:
      numpy_pt = "f8"; break;
    case ome::xml::model::enums::PixelType::COMPLEXFLOAT:
      numpy_pt = "c8"; break;
    case ome::xml::model::enums::PixelType::COMPLEXDOUBLE:
      numpy_pt = "c16"; break;
    case ome::xml::model::enums::PixelType::BIT:
      numpy_pt = "b1"; break;
    default:
      PyErr_SetString(OMEFilesPyError, "unknown pixel type");
      return NULL;
    }
  } catch (const std::exception& e) {
    PyErr_SetString(OMEFilesPyError, e.what());
    return NULL;
  }
  return PyString_FromString(numpy_pt);
}


static PyObject *
PyOMETIFFReader_getRGBChannelCount(PyOMETIFFReader *self, PyObject *args) {
  size_t channel;
  if (!PyArg_ParseTuple(args, "n", &channel)) {
    return NULL;
  }
  try {
    return PyInt_FromSize_t(self->reader->getRGBChannelCount(channel));
  } catch (const std::exception& e) {
    PyErr_SetString(OMEFilesPyError, e.what());
    return NULL;
  }
}


static PyObject *
PyOMETIFFReader_isInterleaved(PyOMETIFFReader *self, PyObject *args) {
  size_t channel;
  if (!PyArg_ParseTuple(args, "n", &channel)) {
    return NULL;
  }
  try {
    return PyBool_FromLong(self->reader->isInterleaved(channel));
  } catch (const std::exception& e) {
    PyErr_SetString(OMEFilesPyError, e.what());
    return NULL;
  }
}


// This currently returns a raw byte string. At the Python level,
// numpy.fromstring can be used (together with info on shape, bytes
// per pixel, etc.) to get an array. By using the Numpy C API here, we
// could return an array directly, e.g., via PyArray_NewFromDescr.
static PyObject *
PyOMETIFFReader_openBytes(PyOMETIFFReader *self, PyObject *args) {
  ome::files::VariantPixelBuffer buf;
  size_t plane;
  if (!PyArg_ParseTuple(args, "n", &plane)) {
    return NULL;
  }
  try {
    self->reader->openBytes(plane, buf);
  } catch (const std::exception& e) {
    PyErr_SetString(OMEFilesPyError, e.what());
    return NULL;
  }
  // buf.data() points to uint8_t, aka unsigned char
  return PyString_FromStringAndSize(
    reinterpret_cast<char*>(buf.data()),
    buf.num_elements() * ome::files::bytesPerPixel(buf.pixelType())
  );
}


static PyObject *
PyOMETIFFReader_getUsedFiles(PyOMETIFFReader *self, PyObject *args,
    PyObject *kwds) {
  std::vector<boost::filesystem::path> files;
  PyObject *file_list;
  PyObject *no_pixels = Py_False;
  static const char *kwlist[] = {"no_pixels", NULL};
  int noPixels;
  if (!PyArg_ParseTupleAndKeywords(
        args, kwds, "|O", const_cast<char**>(kwlist), &no_pixels)) {
    return NULL;
  }
  noPixels = PyObject_IsTrue(no_pixels);
  if (noPixels < 0) {
    return PyErr_Format(PyExc_TypeError, "could not convert argument to bool");
  }
  try {
    files = self->reader->getUsedFiles(noPixels);
  } catch (const std::exception& e) {
    PyErr_SetString(OMEFilesPyError, e.what());
    return NULL;
  }
  file_list = PyList_New(0);
  if (file_list == NULL) {
    PyErr_SetString(PyExc_RuntimeError, "list creation failed");
    return NULL;
  }
  PyObject *fname;
  for (const auto &f : files) {
    fname = PyString_FromString(f.string().c_str());
    if (fname == NULL) {
      PyErr_SetString(PyExc_RuntimeError, "string creation failed");
      Py_DECREF(file_list);
      return NULL;
    }
    if (PyList_Append(file_list, fname) < 0) {
      PyErr_SetString(PyExc_RuntimeError, "list append failed");
      Py_DECREF(file_list);
      return NULL;
    }
  }
  return file_list;
}


static PyObject *
PyOMETIFFReader_getOMEXML(PyOMETIFFReader *self) {
  try {
    auto meta =
      std::dynamic_pointer_cast<ome::xml::meta::OMEXMLMetadata>(
        self->reader->getMetadataStore());
    if (!meta) {
      Py_RETURN_NONE;
    }
    return PyString_FromString(meta->dumpXML().c_str());
  } catch (const std::exception& e) {
    PyErr_SetString(OMEFilesPyError, e.what());
    return NULL;
  }
}


static PyMethodDef PyOMETIFFReader_methods[] = {
  {"set_id", (PyCFunction)PyOMETIFFReader_setId, METH_VARARGS,
   "set_id(filename): set the current file name"},
  {"close", (PyCFunction)PyOMETIFFReader_close, METH_VARARGS | METH_KEYWORDS,
   "close(file_only=False): close the currently open file. "
   "If file_only is False, also reset all internal state"},
  {"set_series", (PyCFunction)PyOMETIFFReader_setSeries, METH_VARARGS,
   "set_series(series): set the active series"},
  {"get_series", (PyCFunction)PyOMETIFFReader_getSeries, METH_NOARGS,
   "get_series(): get the active series"},
  {"get_series_count", (PyCFunction)PyOMETIFFReader_getSeriesCount,
   METH_NOARGS, "get_series_count(): get the number of image series"},
  {"get_image_count", (PyCFunction)PyOMETIFFReader_getImageCount, METH_NOARGS,
   "get_image_count(): get the number of image planes in the current series"},
  {"get_size_x", (PyCFunction)PyOMETIFFReader_getSizeX, METH_NOARGS,
   "get_size_x(): get the size of the X dimension"},
  {"get_size_y", (PyCFunction)PyOMETIFFReader_getSizeY, METH_NOARGS,
   "get_size_y(): get the size of the Y dimension"},
  {"get_size_z", (PyCFunction)PyOMETIFFReader_getSizeZ, METH_NOARGS,
   "get_size_z(): get the size of the Z dimension"},
  {"get_size_t", (PyCFunction)PyOMETIFFReader_getSizeT, METH_NOARGS,
   "get_size_t(): get the size of the T dimension"},
  {"get_size_c", (PyCFunction)PyOMETIFFReader_getSizeC, METH_NOARGS,
   "get_size_c(): get the size of the C dimension"},
  {"get_dimension_order", (PyCFunction)PyOMETIFFReader_getDimensionOrder,
   METH_NOARGS, "get_dimension_order(): get a five-character string "
   "representing the order in which planes will be returned"},
  {"get_index", (PyCFunction)PyOMETIFFReader_getIndex,
   METH_VARARGS, "get_index(z, c, t): "
   "get the plane index corresponding to the given ZCT coordinates"},
  {"get_zct_coords", (PyCFunction)PyOMETIFFReader_getZCTCoords,
   METH_VARARGS, "get_zct_coords(index): "
   "get the ZCT coordinates for the given plane index"
   "get the plane index corresponding to the given ZCT coordinates"},
  {"get_pixel_type", (PyCFunction)PyOMETIFFReader_getPixelType, METH_NOARGS,
   "get_pixel_type(): get the pixel type"},
  {"get_rgb_channel_count", (PyCFunction)PyOMETIFFReader_getRGBChannelCount,
   METH_VARARGS, "get_rgb_channel_count(channel): "
   "get the number of sub-channels for the given channel"},
  {"is_interleaved", (PyCFunction)PyOMETIFFReader_isInterleaved, METH_VARARGS,
   "is_interleaved(channel): whether or not the given channel is interleaved"},
  {"open_bytes", (PyCFunction)PyOMETIFFReader_openBytes, METH_VARARGS,
   "open_bytes(plane): obtain the image plane for the given index"},
  {"get_used_files", (PyCFunction)PyOMETIFFReader_getUsedFiles,
   METH_VARARGS | METH_KEYWORDS,
   "get_used_files(no_pixels=False): get the files used by this dataset. "
   "If no_pixels is False, exclude pixel data files"},
  {"get_ome_xml", (PyCFunction)PyOMETIFFReader_getOMEXML, METH_NOARGS,
   "get_ome_xml(): get the OME XML metadata block"},
  {NULL}  /* Sentinel */
};


PyTypeObject PyOMETIFFReaderType = {
    PyObject_HEAD_INIT(NULL)
    0,                                                /* ob_size */
    "ome_files.OMETIFFReader",                        /* tp_name */
    sizeof(PyOMETIFFReader),                          /* tp_basicsize */
    0,                                                /* tp_itemsize */
    0,                                                /* tp_dealloc */
    0,                                                /* tp_print */
    0,                                                /* tp_getattr */
    0,                                                /* tp_setattr */
    0,                                                /* tp_compare */
    0,                                                /* tp_repr */
    0,                                                /* tp_as_number */
    0,                                                /* tp_as_sequence */
    0,                                                /* tp_as_mapping */
    0,                                                /* tp_hash */
    0,                                                /* tp_call */
    0,                                                /* tp_str */
    0,                                                /* tp_getattro */
    0,                                                /* tp_setattro */
    0,                                                /* tp_as_buffer */
    Py_TPFLAGS_DEFAULT | Py_TPFLAGS_BASETYPE,         /* tp_flags */
    "TIFF reader with support for OME-XML metadata",  /* tp_doc */
    0,                                                /* tp_traverse */
    0,                                                /* tp_clear */
    0,                                                /* tp_richcompare */
    0,                                                /* tp_weaklistoffset */
    0,                                                /* tp_iter */
    0,                                                /* tp_iternext */
    PyOMETIFFReader_methods,                          /* tp_methods */
    0,                                                /* tp_members */
    0,                                                /* tp_getset */
    0,                                                /* tp_base */
    0,                                                /* tp_dict */
    0,                                                /* tp_descr_get */
    0,                                                /* tp_descr_set */
    0,                                                /* tp_dictoffset */
    (initproc)PyOMETIFFReader_init,                   /* tp_init */
    0,                                                /* tp_alloc */
    0,                                                /* tp_new */
};
