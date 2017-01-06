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


// This currently returns a raw byte string. At the Python level,
// numpy.fromstring can be used (together with info on shape, bytes
// per pixel, etc.) to get an array. By using the Numpy C API here, we
// could return an array directly, e.g., via PyArray_NewFromDescr.
static PyObject *
PyOMETIFFReader_openBytes(PyOMETIFFReader *self, PyObject *args) {
  //uint8_t *data;
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
  // do we need to multiply by the n. of bytes per pixel?
  return PyString_FromStringAndSize(reinterpret_cast<char*>(buf.data()),
				    buf.num_elements());
}


static PyMethodDef PyOMETIFFReader_methods[] = {
  {"set_id", (PyCFunction)PyOMETIFFReader_setId, METH_VARARGS,
   "set_id(filename): set the current file name"},
  {"close", (PyCFunction)PyOMETIFFReader_close, METH_VARARGS | METH_KEYWORDS,
   "close(file_only=False): close the currently open file. "
   "If file_only is False, also reset all internal state"},
  {"get_image_count", (PyCFunction)PyOMETIFFReader_getImageCount, METH_NOARGS,
   "get_image_count(): get the number of image planes in the current series"},
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
