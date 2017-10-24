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
#include <ome/xml/model/enums/UnitsElectricPotential.h>

#include "unitselectricpotential.h"


namespace py = pybind11;
using ome::xml::model::enums::UnitsElectricPotential;


void init_unitselectricpotential(py::module &m) {
  py::class_<UnitsElectricPotential> UnitsElectricPotentialWrapper(m, "UnitsElectricPotential");
  UnitsElectricPotentialWrapper
    .def(py::init<UnitsElectricPotential::enum_value>())
    .def(py::init<const std::string&, bool>(), "",
	 py::arg().noconvert(), py::arg("strict") = false)
    .def("__str__", [](const UnitsElectricPotential &t) {
	return static_cast<std::string>(t);
      })
    .def("__repr__", [](const UnitsElectricPotential &t) {
	return "UnitsElectricPotential('" + static_cast<std::string>(t) + "')";
      })
    .def(py::self == py::self)
    .def(py::self != py::self)
    .def_property_readonly("value", [](const UnitsElectricPotential &t) {
	return static_cast<UnitsElectricPotential::enum_value>(t);
      })
    .def_static("strings", []() { return UnitsElectricPotential::strings(); },
		"Get a map of valid string names and enum values.")
    .def_static("values", []() { return UnitsElectricPotential::values(); },
		"Get a map of valid enum values and string names.");
  py::enum_<UnitsElectricPotential::enum_value> EnumValue(UnitsElectricPotentialWrapper, "enum_value");
  EnumValue
    .value("YOTTAVOLT", UnitsElectricPotential::enum_value::YOTTAVOLT)
    .value("ZETTAVOLT", UnitsElectricPotential::enum_value::ZETTAVOLT)
    .value("EXAVOLT", UnitsElectricPotential::enum_value::EXAVOLT)
    .value("PETAVOLT", UnitsElectricPotential::enum_value::PETAVOLT)
    .value("TERAVOLT", UnitsElectricPotential::enum_value::TERAVOLT)
    .value("GIGAVOLT", UnitsElectricPotential::enum_value::GIGAVOLT)
    .value("MEGAVOLT", UnitsElectricPotential::enum_value::MEGAVOLT)
    .value("KILOVOLT", UnitsElectricPotential::enum_value::KILOVOLT)
    .value("HECTOVOLT", UnitsElectricPotential::enum_value::HECTOVOLT)
    .value("DECAVOLT", UnitsElectricPotential::enum_value::DECAVOLT)
    .value("VOLT", UnitsElectricPotential::enum_value::VOLT)
    .value("DECIVOLT", UnitsElectricPotential::enum_value::DECIVOLT)
    .value("CENTIVOLT", UnitsElectricPotential::enum_value::CENTIVOLT)
    .value("MILLIVOLT", UnitsElectricPotential::enum_value::MILLIVOLT)
    .value("MICROVOLT", UnitsElectricPotential::enum_value::MICROVOLT)
    .value("NANOVOLT", UnitsElectricPotential::enum_value::NANOVOLT)
    .value("PICOVOLT", UnitsElectricPotential::enum_value::PICOVOLT)
    .value("FEMTOVOLT", UnitsElectricPotential::enum_value::FEMTOVOLT)
    .value("ATTOVOLT", UnitsElectricPotential::enum_value::ATTOVOLT)
    .value("ZEPTOVOLT", UnitsElectricPotential::enum_value::ZEPTOVOLT)
    .value("YOCTOVOLT", UnitsElectricPotential::enum_value::YOCTOVOLT)
    .export_values();
  UnitsElectricPotentialWrapper.attr("__members__") = EnumValue.attr("__members__");
}
