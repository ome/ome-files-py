/*
 * #%L
 * OME-FILES Python library for image IO.
 * Copyright (c) 2016 University of Dundee
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

#include <ome/compat/memory.h>
#include <ome/files/FormatReader.h>
#include <ome/files/in/OMETIFFReader.h>
#include <ome/files/PixelProperties.h>
#include <ome/xml/model/enums/PixelType.h>


static PyObject *Error;


typedef struct {
    PyObject_HEAD
    ome::compat::shared_ptr<ome::files::FormatReader> reader;
} PyOMETIFFReader;


static int
PyOMETIFFReader_init(PyOMETIFFReader *self, PyObject *args, PyObject *kwds) {
  self->reader = ome::compat::make_shared<ome::files::in::OMETIFFReader>();
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
    PyErr_SetString(Error, e.what());
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
    PyErr_SetString(Error, e.what());
    return NULL;
  }
  Py_RETURN_NONE;
}


static PyObject *
PyOMETIFFReader_getImageCount(PyOMETIFFReader *self) {
  try {
    return PyInt_FromSize_t(self->reader->getImageCount());
  } catch (const std::exception& e) {
    PyErr_SetString(Error, e.what());
    return NULL;
  }
}


static PyObject *
PyOMETIFFReader_getSizeX(PyOMETIFFReader *self) {
  try {
    return PyInt_FromSize_t(self->reader->getSizeX());
  } catch (const std::exception& e) {
    PyErr_SetString(Error, e.what());
    return NULL;
  }
}


static PyObject *
PyOMETIFFReader_getSizeY(PyOMETIFFReader *self) {
  try {
    return PyInt_FromSize_t(self->reader->getSizeY());
  } catch (const std::exception& e) {
    PyErr_SetString(Error, e.what());
    return NULL;
  }
}


static PyObject *
PyOMETIFFReader_getSizeZ(PyOMETIFFReader *self) {
  try {
    return PyInt_FromSize_t(self->reader->getSizeZ());
  } catch (const std::exception& e) {
    PyErr_SetString(Error, e.what());
    return NULL;
  }
}


static PyObject *
PyOMETIFFReader_getSizeT(PyOMETIFFReader *self) {
  try {
    return PyInt_FromSize_t(self->reader->getSizeT());
  } catch (const std::exception& e) {
    PyErr_SetString(Error, e.what());
    return NULL;
  }
}


static PyObject *
PyOMETIFFReader_getSizeC(PyOMETIFFReader *self) {
  try {
    return PyInt_FromSize_t(self->reader->getSizeC());
  } catch (const std::exception& e) {
    PyErr_SetString(Error, e.what());
    return NULL;
  }
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
      PyErr_SetString(Error, "unknown pixel type");
      return NULL;
    }
  } catch (const std::exception& e) {
    PyErr_SetString(Error, e.what());
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
    PyErr_SetString(Error, e.what());
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
    PyErr_SetString(Error, e.what());
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
    PyErr_SetString(Error, e.what());
    return NULL;
  }
  // buf.data() points to uint8_t, aka unsigned char
  return PyString_FromStringAndSize(
    reinterpret_cast<char*>(buf.data()),
    buf.num_elements() * ome::files::bytesPerPixel(buf.pixelType())
  );
}


static PyMethodDef PyOMETIFFReader_methods[] = {
  {"set_id", (PyCFunction)PyOMETIFFReader_setId, METH_VARARGS,
   "set_id(filename): set the current file name"},
  {"close", (PyCFunction)PyOMETIFFReader_close, METH_VARARGS | METH_KEYWORDS,
   "close(file_only=False): close the currently open file. "
   "If file_only is False, also reset all internal state"},
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
  {"get_pixel_type", (PyCFunction)PyOMETIFFReader_getPixelType, METH_NOARGS,
   "get_pixel_type(): get the pixel type"},
  {"get_rgb_channel_count", (PyCFunction)PyOMETIFFReader_getRGBChannelCount,
   METH_VARARGS, "get_rgb_channel_count(channel): "
   "get the number of sub-channels for the given channel"},
  {"is_interleaved", (PyCFunction)PyOMETIFFReader_isInterleaved, METH_VARARGS,
   "is_interleaved(channel): whether or not the given channel is interleaved"},
  {"open_bytes", (PyCFunction)PyOMETIFFReader_openBytes, METH_VARARGS,
   "open_bytes(plane): obtain the image plane for the given index"},
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


static PyMethodDef OMEFilesMethods[] = {
  {NULL}  /* Sentinel */
};


PyMODINIT_FUNC
initome_files(void) {
  PyObject *m;
  PyOMETIFFReaderType.tp_new = PyType_GenericNew;
  if (PyType_Ready(&PyOMETIFFReaderType) < 0) {
    return;
  }
  m = Py_InitModule3("ome_files", OMEFilesMethods, "OME Files wrapper");
  if (!m) {
    return;
  }
  Py_INCREF(&PyOMETIFFReaderType);
  PyModule_AddObject(m, "OMETIFFReader", (PyObject *)&PyOMETIFFReaderType);
  Error = PyErr_NewException(const_cast<char*>("ome_files.Error"), NULL, NULL);
  Py_INCREF(Error);
  PyModule_AddObject(m, "Error", Error);
}
