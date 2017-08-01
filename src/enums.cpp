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

/*─────────────────────────────────────────────────────────────────────────────
 *
 * THIS IS AUTOMATICALLY GENERATED CODE.  DO NOT MODIFY.
 *
 *─────────────────────────────────────────────────────────────────────────────
 */

#include "enums.h"


namespace py = pybind11;


void init_enums(py::module &m) {
  py::module subm = m.def_submodule("enums");
  init_acquisitionmode(subm);
  init_arctype(subm);
  init_binning(subm);
  init_compression(subm);
  init_contrastmethod(subm);
  init_correction(subm);
  init_detectortype(subm);
  init_dimensionorder(subm);
  init_experimenttype(subm);
  init_filamenttype(subm);
  init_fillrule(subm);
  init_filtertype(subm);
  init_fontfamily(subm);
  init_fontstyle(subm);
  init_illuminationtype(subm);
  init_immersion(subm);
  init_lasermedium(subm);
  init_lasertype(subm);
  init_marker(subm);
  init_medium(subm);
  init_microbeammanipulationtype(subm);
  init_microscopetype(subm);
  init_namingconvention(subm);
  init_pixeltype(subm);
  init_pulse(subm);
  init_unitselectricpotential(subm);
  init_unitsfrequency(subm);
  init_unitslength(subm);
  init_unitspower(subm);
  init_unitspressure(subm);
  init_unitstemperature(subm);
  init_unitstime(subm);
}
