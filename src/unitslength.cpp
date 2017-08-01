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
#include <ome/xml/model/enums/UnitsLength.h>

#include "unitslength.h"


namespace py = pybind11;
using ome::xml::model::enums::UnitsLength;


void init_unitslength(py::module &m) {
  py::class_<UnitsLength> UnitsLengthWrapper(m, "UnitsLength");
  UnitsLengthWrapper
    .def(py::init<UnitsLength::enum_value>())
    .def(py::init<const std::string&, bool>(), "",
	 py::arg().noconvert(), py::arg("strict") = false)
    .def("__str__", [](const UnitsLength &t) {
	return static_cast<std::string>(t);
      })
    .def("__repr__", [](const UnitsLength &t) {
	return "UnitsLength('" + static_cast<std::string>(t) + "')";
      })
    .def(py::self == py::self)
    .def(py::self != py::self)
    .def_property_readonly("value", [](const UnitsLength &t) {
	return static_cast<UnitsLength::enum_value>(t);
      })
    .def_static("strings", []() { return UnitsLength::strings(); },
		"Get a map of valid string names and enum values.")
    .def_static("values", []() { return UnitsLength::values(); },
		"Get a map of valid enum values and string names.");
  py::enum_<UnitsLength::enum_value> EnumValue(UnitsLengthWrapper, "enum_value");
  EnumValue
    .value("YOTTAMETER", UnitsLength::enum_value::YOTTAMETER)
    .value("ZETTAMETER", UnitsLength::enum_value::ZETTAMETER)
    .value("EXAMETER", UnitsLength::enum_value::EXAMETER)
    .value("PETAMETER", UnitsLength::enum_value::PETAMETER)
    .value("TERAMETER", UnitsLength::enum_value::TERAMETER)
    .value("GIGAMETER", UnitsLength::enum_value::GIGAMETER)
    .value("MEGAMETER", UnitsLength::enum_value::MEGAMETER)
    .value("KILOMETER", UnitsLength::enum_value::KILOMETER)
    .value("HECTOMETER", UnitsLength::enum_value::HECTOMETER)
    .value("DECAMETER", UnitsLength::enum_value::DECAMETER)
    .value("METER", UnitsLength::enum_value::METER)
    .value("DECIMETER", UnitsLength::enum_value::DECIMETER)
    .value("CENTIMETER", UnitsLength::enum_value::CENTIMETER)
    .value("MILLIMETER", UnitsLength::enum_value::MILLIMETER)
    .value("MICROMETER", UnitsLength::enum_value::MICROMETER)
    .value("NANOMETER", UnitsLength::enum_value::NANOMETER)
    .value("PICOMETER", UnitsLength::enum_value::PICOMETER)
    .value("FEMTOMETER", UnitsLength::enum_value::FEMTOMETER)
    .value("ATTOMETER", UnitsLength::enum_value::ATTOMETER)
    .value("ZEPTOMETER", UnitsLength::enum_value::ZEPTOMETER)
    .value("YOCTOMETER", UnitsLength::enum_value::YOCTOMETER)
    .value("ANGSTROM", UnitsLength::enum_value::ANGSTROM)
    .value("THOU", UnitsLength::enum_value::THOU)
    .value("LINE", UnitsLength::enum_value::LINE)
    .value("INCH", UnitsLength::enum_value::INCH)
    .value("FOOT", UnitsLength::enum_value::FOOT)
    .value("YARD", UnitsLength::enum_value::YARD)
    .value("MILE", UnitsLength::enum_value::MILE)
    .value("ASTRONOMICALUNIT", UnitsLength::enum_value::ASTRONOMICALUNIT)
    .value("LIGHTYEAR", UnitsLength::enum_value::LIGHTYEAR)
    .value("PARSEC", UnitsLength::enum_value::PARSEC)
    .value("POINT", UnitsLength::enum_value::POINT)
    .value("PIXEL", UnitsLength::enum_value::PIXEL)
    .value("REFERENCEFRAME", UnitsLength::enum_value::REFERENCEFRAME)
    .export_values();
  UnitsLengthWrapper.attr("__members__") = EnumValue.attr("__members__");
}
