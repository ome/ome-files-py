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

#include <string>
#include <pybind11/operators.h>
#include <pybind11/stl.h>
#include <ome/xml/model/enums/Correction.h>

#include "correction.h"


namespace py = pybind11;
using ome::xml::model::enums::Correction;


void init_correction(py::module &m) {
  py::class_<Correction> CorrectionWrapper(m, "Correction");
  CorrectionWrapper
    .def(py::init<Correction::enum_value>())
    .def(py::init<const std::string&, bool>(), "",
	 py::arg().noconvert(), py::arg("strict") = false)
    .def("__str__", [](const Correction &t) {
	return static_cast<std::string>(t);
      })
    .def("__repr__", [](const Correction &t) {
	return "Correction('" + static_cast<std::string>(t) + "')";
      })
    .def(py::self == py::self)
    .def(py::self != py::self)
    .def_property_readonly("value", [](const Correction &t) {
	return static_cast<Correction::enum_value>(t);
      })
    .def_static("strings", []() { return Correction::strings(); },
		"Get a map of valid string names and enum values.")
    .def_static("values", []() { return Correction::values(); },
		"Get a map of valid enum values and string names.");
  py::enum_<Correction::enum_value> EnumValue(CorrectionWrapper, "enum_value");
  EnumValue
    .value("UV", Correction::enum_value::UV)
    .value("PLANAPO", Correction::enum_value::PLANAPO)
    .value("PLANFLUOR", Correction::enum_value::PLANFLUOR)
    .value("SUPERFLUOR", Correction::enum_value::SUPERFLUOR)
    .value("VIOLETCORRECTED", Correction::enum_value::VIOLETCORRECTED)
    .value("ACHRO", Correction::enum_value::ACHRO)
    .value("ACHROMAT", Correction::enum_value::ACHROMAT)
    .value("FLUOR", Correction::enum_value::FLUOR)
    .value("FL", Correction::enum_value::FL)
    .value("FLUAR", Correction::enum_value::FLUAR)
    .value("NEOFLUAR", Correction::enum_value::NEOFLUAR)
    .value("FLUOTAR", Correction::enum_value::FLUOTAR)
    .value("APO", Correction::enum_value::APO)
    .value("PLANNEOFLUAR", Correction::enum_value::PLANNEOFLUAR)
    .value("OTHER", Correction::enum_value::OTHER)
    .export_values();
  CorrectionWrapper.attr("__members__") = EnumValue.attr("__members__");
}
