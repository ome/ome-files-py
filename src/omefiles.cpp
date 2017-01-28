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

#include "ometiffreader.h"
#include "errors.h"


PyObject *OMEFilesPyError;


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
  OMEFilesPyError = PyErr_NewException(const_cast<char*>("ome_files.Error"),
                                       NULL, NULL);
  if (OMEFilesPyError) {
    Py_INCREF(OMEFilesPyError);
    PyModule_AddObject(m, "Error", OMEFilesPyError);
  }
}
