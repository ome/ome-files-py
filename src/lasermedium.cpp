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
#include <ome/xml/model/enums/LaserMedium.h>

#include "lasermedium.h"


namespace py = pybind11;
using ome::xml::model::enums::LaserMedium;


void init_lasermedium(py::module &m) {
  py::class_<LaserMedium> LaserMediumWrapper(m, "LaserMedium");
  LaserMediumWrapper
    .def(py::init<LaserMedium::enum_value>())
    .def(py::init<const std::string&, bool>(), "",
	 py::arg().noconvert(), py::arg("strict") = false)
    .def("__str__", [](const LaserMedium &t) {
	return static_cast<std::string>(t);
      })
    .def("__repr__", [](const LaserMedium &t) {
	return "LaserMedium('" + static_cast<std::string>(t) + "')";
      })
    .def(py::self == py::self)
    .def(py::self != py::self)
    .def_property_readonly("value", [](const LaserMedium &t) {
	return static_cast<LaserMedium::enum_value>(t);
      })
    .def_static("strings", []() { return LaserMedium::strings(); },
		"Get a map of valid string names and enum values.")
    .def_static("values", []() { return LaserMedium::values(); },
		"Get a map of valid enum values and string names.");
  py::enum_<LaserMedium::enum_value> EnumValue(LaserMediumWrapper, "enum_value");
  EnumValue
    .value("CU", LaserMedium::enum_value::CU)
    .value("AG", LaserMedium::enum_value::AG)
    .value("ARFL", LaserMedium::enum_value::ARFL)
    .value("ARCL", LaserMedium::enum_value::ARCL)
    .value("KRFL", LaserMedium::enum_value::KRFL)
    .value("KRCL", LaserMedium::enum_value::KRCL)
    .value("XEFL", LaserMedium::enum_value::XEFL)
    .value("XECL", LaserMedium::enum_value::XECL)
    .value("XEBR", LaserMedium::enum_value::XEBR)
    .value("N", LaserMedium::enum_value::N)
    .value("AR", LaserMedium::enum_value::AR)
    .value("KR", LaserMedium::enum_value::KR)
    .value("XE", LaserMedium::enum_value::XE)
    .value("HENE", LaserMedium::enum_value::HENE)
    .value("HECD", LaserMedium::enum_value::HECD)
    .value("CO", LaserMedium::enum_value::CO)
    .value("CO2", LaserMedium::enum_value::CO2)
    .value("H2O", LaserMedium::enum_value::H2O)
    .value("HFL", LaserMedium::enum_value::HFL)
    .value("NDGLASS", LaserMedium::enum_value::NDGLASS)
    .value("NDYAG", LaserMedium::enum_value::NDYAG)
    .value("ERGLASS", LaserMedium::enum_value::ERGLASS)
    .value("ERYAG", LaserMedium::enum_value::ERYAG)
    .value("HOYLF", LaserMedium::enum_value::HOYLF)
    .value("HOYAG", LaserMedium::enum_value::HOYAG)
    .value("RUBY", LaserMedium::enum_value::RUBY)
    .value("TISAPPHIRE", LaserMedium::enum_value::TISAPPHIRE)
    .value("ALEXANDRITE", LaserMedium::enum_value::ALEXANDRITE)
    .value("RHODAMINE6G", LaserMedium::enum_value::RHODAMINE6G)
    .value("COUMARINC30", LaserMedium::enum_value::COUMARINC30)
    .value("GAAS", LaserMedium::enum_value::GAAS)
    .value("GAALAS", LaserMedium::enum_value::GAALAS)
    .value("EMINUS", LaserMedium::enum_value::EMINUS)
    .value("OTHER", LaserMedium::enum_value::OTHER)
    .export_values();
  LaserMediumWrapper.attr("__members__") = EnumValue.attr("__members__");
}
