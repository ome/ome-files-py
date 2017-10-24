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
#include <ome/xml/model/enums/UnitsTime.h>

#include "unitstime.h"


namespace py = pybind11;
using ome::xml::model::enums::UnitsTime;


void init_unitstime(py::module &m) {
  py::class_<UnitsTime> UnitsTimeWrapper(m, "UnitsTime");
  UnitsTimeWrapper
    .def(py::init<UnitsTime::enum_value>())
    .def(py::init<const std::string&, bool>(), "",
	 py::arg().noconvert(), py::arg("strict") = false)
    .def("__str__", [](const UnitsTime &t) {
	return static_cast<std::string>(t);
      })
    .def("__repr__", [](const UnitsTime &t) {
	return "UnitsTime('" + static_cast<std::string>(t) + "')";
      })
    .def(py::self == py::self)
    .def(py::self != py::self)
    .def_property_readonly("value", [](const UnitsTime &t) {
	return static_cast<UnitsTime::enum_value>(t);
      })
    .def_static("strings", []() { return UnitsTime::strings(); },
		"Get a map of valid string names and enum values.")
    .def_static("values", []() { return UnitsTime::values(); },
		"Get a map of valid enum values and string names.");
  py::enum_<UnitsTime::enum_value> EnumValue(UnitsTimeWrapper, "enum_value");
  EnumValue
    .value("YOTTASECOND", UnitsTime::enum_value::YOTTASECOND)
    .value("ZETTASECOND", UnitsTime::enum_value::ZETTASECOND)
    .value("EXASECOND", UnitsTime::enum_value::EXASECOND)
    .value("PETASECOND", UnitsTime::enum_value::PETASECOND)
    .value("TERASECOND", UnitsTime::enum_value::TERASECOND)
    .value("GIGASECOND", UnitsTime::enum_value::GIGASECOND)
    .value("MEGASECOND", UnitsTime::enum_value::MEGASECOND)
    .value("KILOSECOND", UnitsTime::enum_value::KILOSECOND)
    .value("HECTOSECOND", UnitsTime::enum_value::HECTOSECOND)
    .value("DECASECOND", UnitsTime::enum_value::DECASECOND)
    .value("SECOND", UnitsTime::enum_value::SECOND)
    .value("DECISECOND", UnitsTime::enum_value::DECISECOND)
    .value("CENTISECOND", UnitsTime::enum_value::CENTISECOND)
    .value("MILLISECOND", UnitsTime::enum_value::MILLISECOND)
    .value("MICROSECOND", UnitsTime::enum_value::MICROSECOND)
    .value("NANOSECOND", UnitsTime::enum_value::NANOSECOND)
    .value("PICOSECOND", UnitsTime::enum_value::PICOSECOND)
    .value("FEMTOSECOND", UnitsTime::enum_value::FEMTOSECOND)
    .value("ATTOSECOND", UnitsTime::enum_value::ATTOSECOND)
    .value("ZEPTOSECOND", UnitsTime::enum_value::ZEPTOSECOND)
    .value("YOCTOSECOND", UnitsTime::enum_value::YOCTOSECOND)
    .value("MINUTE", UnitsTime::enum_value::MINUTE)
    .value("HOUR", UnitsTime::enum_value::HOUR)
    .value("DAY", UnitsTime::enum_value::DAY)
    .export_values();
  UnitsTimeWrapper.attr("__members__") = EnumValue.attr("__members__");
}
