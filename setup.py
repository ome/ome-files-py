# #%L
# OME-FILES Python library for image IO.
# Copyright (c) 2016-2017 University of Dundee
# %%
# Redistribution and use in source and binary forms, with or without
# modification, are permitted provided that the following conditions are met:
#
# 1. Redistributions of source code must retain the above copyright notice,
#    this list of conditions and the following disclaimer.
# 2. Redistributions in binary form must reproduce the above copyright notice,
#    this list of conditions and the following disclaimer in the documentation
#    and/or other materials provided with the distribution.
#
# THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
# AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
# IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
# ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDERS OR CONTRIBUTORS BE
# LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
# CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
# SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
# INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
# CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
# ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
# POSSIBILITY OF SUCH DAMAGE.
# #L%

import sys
import os
import platform
from distutils.core import setup, Extension
from distutils.command.build_ext import build_ext as BaseBuildExt
from distutils.command.build import build as BaseBuild
from distutils.unixccompiler import UnixCCompiler
from distutils.util import get_platform
from distutils.sysconfig import customize_compiler
from distutils.errors import DistutilsSetupError
from distutils.dep_util import newer


EXTRA_COMPILE_ARGS = ['-std=c++11'] if platform.system != "Windows" else []
VERSION_FILE = "VERSION"
PY_VERSION_FILE = "ome_files/version.py"


def get_version_string():
    try:
        with open(VERSION_FILE) as f:
            return f.read().strip()
    except IOError:
        raise DistutilsSetupError("failed to read version info")


def write_version():
    if newer(VERSION_FILE, PY_VERSION_FILE):
        with open(PY_VERSION_FILE, "w") as f:
            f.write("# GENERATED BY setup.py\n")
            f.write("version = '%s'\n" % (get_version_string()))


# On Darwin, UnixCCompiler uses "-L" for runtime lib paths
class DarwinCompiler(UnixCCompiler):

    def runtime_library_dir_option(self, dir):
        return ["-rpath", dir]


class BuildExt(BaseBuildExt):

    # Copied from the base class, except for the Darwin workaround
    def run(self):
        from distutils.ccompiler import new_compiler
        if not self.extensions:
            return
        if self.distribution.has_c_libraries():
            build_clib = self.get_finalized_command('build_clib')
            self.libraries.extend(build_clib.get_library_names() or [])
            self.library_dirs.append(build_clib.build_clib)
        if sys.platform[:6] == "darwin":
            self.compiler = DarwinCompiler(None, self.dry_run, self.force)
        else:
            self.compiler = new_compiler(compiler=self.compiler,
                                         verbose=self.verbose,
                                         dry_run=self.dry_run,
                                         force=self.force)
        customize_compiler(self.compiler)
        if os.name == 'nt' and self.plat_name != get_platform():
            self.compiler.initialize(self.plat_name)
        if self.include_dirs is not None:
            self.compiler.set_include_dirs(self.include_dirs)
        if self.define is not None:
            for (name, value) in self.define:
                self.compiler.define_macro(name, value)
        if self.undef is not None:
            for macro in self.undef:
                self.compiler.undefine_macro(macro)
        if self.libraries is not None:
            self.compiler.set_libraries(self.libraries)
        if self.library_dirs is not None:
            self.compiler.set_library_dirs(self.library_dirs)
        if self.rpath is not None:
            self.compiler.set_runtime_library_dirs(self.rpath)
        if self.link_objects is not None:
            self.compiler.set_link_objects(self.link_objects)
        self.build_extensions()


class Build(BaseBuild):

    def run(self):
        write_version()
        BaseBuild.run(self)


ext = Extension(
    "ome_files._core",
    sources=["src/omefiles.cpp", "src/ometiffreader.cpp"],
    libraries=["ome-common", "ome-files", "ome-xml"],
    extra_compile_args=EXTRA_COMPILE_ARGS,
)

setup(
    name="ome_files",
    version=get_version_string(),
    packages=["ome_files"],
    cmdclass={"build_ext": BuildExt, "build": Build},
    ext_modules=[ext]
)
