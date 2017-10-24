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
#include <ome/xml/model/enums/UnitsPower.h>

#include "unitspower.h"


namespace py = pybind11;
using ome::xml::model::enums::UnitsPower;


void init_unitspower(py::module &m) {
  py::class_<UnitsPower> UnitsPowerWrapper(m, "UnitsPower");
  UnitsPowerWrapper
    .def(py::init<UnitsPower::enum_value>())
    .def(py::init<const std::string&, bool>(), "",
	 py::arg().noconvert(), py::arg("strict") = false)
    .def("__str__", [](const UnitsPower &t) {
	return static_cast<std::string>(t);
      })
    .def("__repr__", [](const UnitsPower &t) {
	return "UnitsPower('" + static_cast<std::string>(t) + "')";
      })
    .def(py::self == py::self)
    .def(py::self != py::self)
    .def_property_readonly("value", [](const UnitsPower &t) {
	return static_cast<UnitsPower::enum_value>(t);
      })
    .def_static("strings", []() { return UnitsPower::strings(); },
		"Get a map of valid string names and enum values.")
    .def_static("values", []() { return UnitsPower::values(); },
		"Get a map of valid enum values and string names.");
  py::enum_<UnitsPower::enum_value> EnumValue(UnitsPowerWrapper, "enum_value");
  EnumValue
    .value("YOTTAWATT", UnitsPower::enum_value::YOTTAWATT)
    .value("ZETTAWATT", UnitsPower::enum_value::ZETTAWATT)
    .value("EXAWATT", UnitsPower::enum_value::EXAWATT)
    .value("PETAWATT", UnitsPower::enum_value::PETAWATT)
    .value("TERAWATT", UnitsPower::enum_value::TERAWATT)
    .value("GIGAWATT", UnitsPower::enum_value::GIGAWATT)
    .value("MEGAWATT", UnitsPower::enum_value::MEGAWATT)
    .value("KILOWATT", UnitsPower::enum_value::KILOWATT)
    .value("HECTOWATT", UnitsPower::enum_value::HECTOWATT)
    .value("DECAWATT", UnitsPower::enum_value::DECAWATT)
    .value("WATT", UnitsPower::enum_value::WATT)
    .value("DECIWATT", UnitsPower::enum_value::DECIWATT)
    .value("CENTIWATT", UnitsPower::enum_value::CENTIWATT)
    .value("MILLIWATT", UnitsPower::enum_value::MILLIWATT)
    .value("MICROWATT", UnitsPower::enum_value::MICROWATT)
    .value("NANOWATT", UnitsPower::enum_value::NANOWATT)
    .value("PICOWATT", UnitsPower::enum_value::PICOWATT)
    .value("FEMTOWATT", UnitsPower::enum_value::FEMTOWATT)
    .value("ATTOWATT", UnitsPower::enum_value::ATTOWATT)
    .value("ZEPTOWATT", UnitsPower::enum_value::ZEPTOWATT)
    .value("YOCTOWATT", UnitsPower::enum_value::YOCTOWATT)
    .export_values();
  UnitsPowerWrapper.attr("__members__") = EnumValue.attr("__members__");
}
