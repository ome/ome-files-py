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
#include <ome/xml/model/enums/Binning.h>

#include "binning.h"


namespace py = pybind11;
using ome::xml::model::enums::Binning;


void init_binning(py::module &m) {
  py::class_<Binning> BinningWrapper(m, "Binning");
  BinningWrapper
    .def(py::init<Binning::enum_value>())
    .def(py::init<const std::string&, bool>(), "",
	 py::arg().noconvert(), py::arg("strict") = false)
    .def("__str__", [](const Binning &t) {
	return static_cast<std::string>(t);
      })
    .def("__repr__", [](const Binning &t) {
	return "Binning('" + static_cast<std::string>(t) + "')";
      })
    .def(py::self == py::self)
    .def(py::self != py::self)
    .def_property_readonly("value", [](const Binning &t) {
	return static_cast<Binning::enum_value>(t);
      })
    .def_static("strings", []() { return Binning::strings(); },
		"Get a map of valid string names and enum values.")
    .def_static("values", []() { return Binning::values(); },
		"Get a map of valid enum values and string names.");
  py::enum_<Binning::enum_value> EnumValue(BinningWrapper, "enum_value");
  EnumValue
    .value("ONEBYONE", Binning::enum_value::ONEBYONE)
    .value("TWOBYTWO", Binning::enum_value::TWOBYTWO)
    .value("FOURBYFOUR", Binning::enum_value::FOURBYFOUR)
    .value("EIGHTBYEIGHT", Binning::enum_value::EIGHTBYEIGHT)
    .value("OTHER", Binning::enum_value::OTHER)
    .export_values();
  BinningWrapper.attr("__members__") = EnumValue.attr("__members__");
}
