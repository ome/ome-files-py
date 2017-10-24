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
#include <ome/xml/model/enums/AcquisitionMode.h>

#include "acquisitionmode.h"


namespace py = pybind11;
using ome::xml::model::enums::AcquisitionMode;


void init_acquisitionmode(py::module &m) {
  py::class_<AcquisitionMode> AcquisitionModeWrapper(m, "AcquisitionMode");
  AcquisitionModeWrapper
    .def(py::init<AcquisitionMode::enum_value>())
    .def(py::init<const std::string&, bool>(), "",
	 py::arg().noconvert(), py::arg("strict") = false)
    .def("__str__", [](const AcquisitionMode &t) {
	return static_cast<std::string>(t);
      })
    .def("__repr__", [](const AcquisitionMode &t) {
	return "AcquisitionMode('" + static_cast<std::string>(t) + "')";
      })
    .def(py::self == py::self)
    .def(py::self != py::self)
    .def_property_readonly("value", [](const AcquisitionMode &t) {
	return static_cast<AcquisitionMode::enum_value>(t);
      })
    .def_static("strings", []() { return AcquisitionMode::strings(); },
		"Get a map of valid string names and enum values.")
    .def_static("values", []() { return AcquisitionMode::values(); },
		"Get a map of valid enum values and string names.");
  py::enum_<AcquisitionMode::enum_value> EnumValue(AcquisitionModeWrapper, "enum_value");
  EnumValue
    .value("WIDEFIELD", AcquisitionMode::enum_value::WIDEFIELD)
    .value("LASERSCANNINGCONFOCALMICROSCOPY", AcquisitionMode::enum_value::LASERSCANNINGCONFOCALMICROSCOPY)
    .value("SPINNINGDISKCONFOCAL", AcquisitionMode::enum_value::SPINNINGDISKCONFOCAL)
    .value("SLITSCANCONFOCAL", AcquisitionMode::enum_value::SLITSCANCONFOCAL)
    .value("MULTIPHOTONMICROSCOPY", AcquisitionMode::enum_value::MULTIPHOTONMICROSCOPY)
    .value("STRUCTUREDILLUMINATION", AcquisitionMode::enum_value::STRUCTUREDILLUMINATION)
    .value("SINGLEMOLECULEIMAGING", AcquisitionMode::enum_value::SINGLEMOLECULEIMAGING)
    .value("TOTALINTERNALREFLECTION", AcquisitionMode::enum_value::TOTALINTERNALREFLECTION)
    .value("FLUORESCENCELIFETIME", AcquisitionMode::enum_value::FLUORESCENCELIFETIME)
    .value("SPECTRALIMAGING", AcquisitionMode::enum_value::SPECTRALIMAGING)
    .value("FLUORESCENCECORRELATIONSPECTROSCOPY", AcquisitionMode::enum_value::FLUORESCENCECORRELATIONSPECTROSCOPY)
    .value("NEARFIELDSCANNINGOPTICALMICROSCOPY", AcquisitionMode::enum_value::NEARFIELDSCANNINGOPTICALMICROSCOPY)
    .value("SECONDHARMONICGENERATIONIMAGING", AcquisitionMode::enum_value::SECONDHARMONICGENERATIONIMAGING)
    .value("PALM", AcquisitionMode::enum_value::PALM)
    .value("STORM", AcquisitionMode::enum_value::STORM)
    .value("STED", AcquisitionMode::enum_value::STED)
    .value("TIRF", AcquisitionMode::enum_value::TIRF)
    .value("FSM", AcquisitionMode::enum_value::FSM)
    .value("LCM", AcquisitionMode::enum_value::LCM)
    .value("OTHER", AcquisitionMode::enum_value::OTHER)
    .value("BRIGHTFIELD", AcquisitionMode::enum_value::BRIGHTFIELD)
    .value("SWEPTFIELDCONFOCAL", AcquisitionMode::enum_value::SWEPTFIELDCONFOCAL)
    .value("SPIM", AcquisitionMode::enum_value::SPIM)
    .export_values();
  AcquisitionModeWrapper.attr("__members__") = EnumValue.attr("__members__");
}
