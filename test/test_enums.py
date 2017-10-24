# #%L
# OME-FILES Python library for image IO.
# Copyright (c) 2017 University of Dundee
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

from __future__ import (
    absolute_import, division, print_function, unicode_literals
)

import sys
import unittest

import ome_files.enums as enums


class TestEnums(unittest.TestCase):

    def runTest(self):
        for cls_name in enums.__all__:
            cls = getattr(enums, cls_name)
            name_to_value = cls.strings()
            value_to_name = cls.values()
            for attr, value in cls.__members__.items():
                self.assertEqual(getattr(cls, attr), value)
                name = value_to_name[value]
                self.assertEqual(name_to_value[name], value)
                e = cls(value)
                self.assertEqual("%s" % e, name)
                self.assertEqual(e.value, value)
                self.assertEqual(cls(name), e)
                self.assertFalse(cls(name) != e)
                self.assertEqual(eval(e.__repr__(), {cls_name: cls}), e)


def load_tests(loader, tests, pattern):
    test_cases = (TestEnums,)
    suite = unittest.TestSuite()
    for tc in test_cases:
        suite.addTests(loader.loadTestsFromTestCase(tc))
    return suite


if __name__ == '__main__':
    suite = load_tests(unittest.defaultTestLoader, None, None)
    runner = unittest.TextTestRunner(verbosity=2)
    result = runner.run(suite)
    sys.exit(not result.wasSuccessful())
