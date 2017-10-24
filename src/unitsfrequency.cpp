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
#include <ome/xml/model/enums/UnitsFrequency.h>

#include "unitsfrequency.h"


namespace py = pybind11;
using ome::xml::model::enums::UnitsFrequency;


void init_unitsfrequency(py::module &m) {
  py::class_<UnitsFrequency> UnitsFrequencyWrapper(m, "UnitsFrequency");
  UnitsFrequencyWrapper
    .def(py::init<UnitsFrequency::enum_value>())
    .def(py::init<const std::string&, bool>(), "",
	 py::arg().noconvert(), py::arg("strict") = false)
    .def("__str__", [](const UnitsFrequency &t) {
	return static_cast<std::string>(t);
      })
    .def("__repr__", [](const UnitsFrequency &t) {
	return "UnitsFrequency('" + static_cast<std::string>(t) + "')";
      })
    .def(py::self == py::self)
    .def(py::self != py::self)
    .def_property_readonly("value", [](const UnitsFrequency &t) {
	return static_cast<UnitsFrequency::enum_value>(t);
      })
    .def_static("strings", []() { return UnitsFrequency::strings(); },
		"Get a map of valid string names and enum values.")
    .def_static("values", []() { return UnitsFrequency::values(); },
		"Get a map of valid enum values and string names.");
  py::enum_<UnitsFrequency::enum_value> EnumValue(UnitsFrequencyWrapper, "enum_value");
  EnumValue
    .value("YOTTAHERTZ", UnitsFrequency::enum_value::YOTTAHERTZ)
    .value("ZETTAHERTZ", UnitsFrequency::enum_value::ZETTAHERTZ)
    .value("EXAHERTZ", UnitsFrequency::enum_value::EXAHERTZ)
    .value("PETAHERTZ", UnitsFrequency::enum_value::PETAHERTZ)
    .value("TERAHERTZ", UnitsFrequency::enum_value::TERAHERTZ)
    .value("GIGAHERTZ", UnitsFrequency::enum_value::GIGAHERTZ)
    .value("MEGAHERTZ", UnitsFrequency::enum_value::MEGAHERTZ)
    .value("KILOHERTZ", UnitsFrequency::enum_value::KILOHERTZ)
    .value("HECTOHERTZ", UnitsFrequency::enum_value::HECTOHERTZ)
    .value("DECAHERTZ", UnitsFrequency::enum_value::DECAHERTZ)
    .value("HERTZ", UnitsFrequency::enum_value::HERTZ)
    .value("DECIHERTZ", UnitsFrequency::enum_value::DECIHERTZ)
    .value("CENTIHERTZ", UnitsFrequency::enum_value::CENTIHERTZ)
    .value("MILLIHERTZ", UnitsFrequency::enum_value::MILLIHERTZ)
    .value("MICROHERTZ", UnitsFrequency::enum_value::MICROHERTZ)
    .value("NANOHERTZ", UnitsFrequency::enum_value::NANOHERTZ)
    .value("PICOHERTZ", UnitsFrequency::enum_value::PICOHERTZ)
    .value("FEMTOHERTZ", UnitsFrequency::enum_value::FEMTOHERTZ)
    .value("ATTOHERTZ", UnitsFrequency::enum_value::ATTOHERTZ)
    .value("ZEPTOHERTZ", UnitsFrequency::enum_value::ZEPTOHERTZ)
    .value("YOCTOHERTZ", UnitsFrequency::enum_value::YOCTOHERTZ)
    .export_values();
  UnitsFrequencyWrapper.attr("__members__") = EnumValue.attr("__members__");
}
