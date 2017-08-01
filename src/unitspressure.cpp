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
#include <ome/xml/model/enums/UnitsPressure.h>

#include "unitspressure.h"


namespace py = pybind11;
using ome::xml::model::enums::UnitsPressure;


void init_unitspressure(py::module &m) {
  py::class_<UnitsPressure> UnitsPressureWrapper(m, "UnitsPressure");
  UnitsPressureWrapper
    .def(py::init<UnitsPressure::enum_value>())
    .def(py::init<const std::string&, bool>(), "",
	 py::arg().noconvert(), py::arg("strict") = false)
    .def("__str__", [](const UnitsPressure &t) {
	return static_cast<std::string>(t);
      })
    .def("__repr__", [](const UnitsPressure &t) {
	return "UnitsPressure('" + static_cast<std::string>(t) + "')";
      })
    .def(py::self == py::self)
    .def(py::self != py::self)
    .def_property_readonly("value", [](const UnitsPressure &t) {
	return static_cast<UnitsPressure::enum_value>(t);
      })
    .def_static("strings", []() { return UnitsPressure::strings(); },
		"Get a map of valid string names and enum values.")
    .def_static("values", []() { return UnitsPressure::values(); },
		"Get a map of valid enum values and string names.");
  py::enum_<UnitsPressure::enum_value> EnumValue(UnitsPressureWrapper, "enum_value");
  EnumValue
    .value("YOTTAPASCAL", UnitsPressure::enum_value::YOTTAPASCAL)
    .value("ZETTAPASCAL", UnitsPressure::enum_value::ZETTAPASCAL)
    .value("EXAPASCAL", UnitsPressure::enum_value::EXAPASCAL)
    .value("PETAPASCAL", UnitsPressure::enum_value::PETAPASCAL)
    .value("TERAPASCAL", UnitsPressure::enum_value::TERAPASCAL)
    .value("GIGAPASCAL", UnitsPressure::enum_value::GIGAPASCAL)
    .value("MEGAPASCAL", UnitsPressure::enum_value::MEGAPASCAL)
    .value("KILOPASCAL", UnitsPressure::enum_value::KILOPASCAL)
    .value("HECTOPASCAL", UnitsPressure::enum_value::HECTOPASCAL)
    .value("DECAPASCAL", UnitsPressure::enum_value::DECAPASCAL)
    .value("PASCAL", UnitsPressure::enum_value::PASCAL)
    .value("DECIPASCAL", UnitsPressure::enum_value::DECIPASCAL)
    .value("CENTIPASCAL", UnitsPressure::enum_value::CENTIPASCAL)
    .value("MILLIPASCAL", UnitsPressure::enum_value::MILLIPASCAL)
    .value("MICROPASCAL", UnitsPressure::enum_value::MICROPASCAL)
    .value("NANOPASCAL", UnitsPressure::enum_value::NANOPASCAL)
    .value("PICOPASCAL", UnitsPressure::enum_value::PICOPASCAL)
    .value("FEMTOPASCAL", UnitsPressure::enum_value::FEMTOPASCAL)
    .value("ATTOPASCAL", UnitsPressure::enum_value::ATTOPASCAL)
    .value("ZEPTOPASCAL", UnitsPressure::enum_value::ZEPTOPASCAL)
    .value("YOCTOPASCAL", UnitsPressure::enum_value::YOCTOPASCAL)
    .value("BAR", UnitsPressure::enum_value::BAR)
    .value("MEGABAR", UnitsPressure::enum_value::MEGABAR)
    .value("KILOBAR", UnitsPressure::enum_value::KILOBAR)
    .value("DECIBAR", UnitsPressure::enum_value::DECIBAR)
    .value("CENTIBAR", UnitsPressure::enum_value::CENTIBAR)
    .value("MILLIBAR", UnitsPressure::enum_value::MILLIBAR)
    .value("ATMOSPHERE", UnitsPressure::enum_value::ATMOSPHERE)
    .value("PSI", UnitsPressure::enum_value::PSI)
    .value("TORR", UnitsPressure::enum_value::TORR)
    .value("MILLITORR", UnitsPressure::enum_value::MILLITORR)
    .value("MMHG", UnitsPressure::enum_value::MMHG)
    .export_values();
  UnitsPressureWrapper.attr("__members__") = EnumValue.attr("__members__");
}
