import os
from conan import ConanFile
from conan.tools.build import cross_building
from conan.tools.layout import basic_layout
import numpy as np
import filecmp

class JsonDictionaryParserTestConan(ConanFile):
    settings = "os", "compiler", "build_type", "arch"
    # VirtualRunEnv can be avoided if "tools.env.virtualenv:auto_use" is defined
    # (it will be defined in Conan 2.0)
    generators = "VirtualRunEnv"
    apply_env = False
    test_type = "explicit"

    def requirements(self):
        self.requires(self.tested_reference_str)

    def layout(self):
        basic_layout(self)
        
    def _run_test_case(self, test_name):
        input = "../{}.tlv".format(test_name)
        output = "{}.tlv".format(test_name)
        
        self.run("json_dictionary_parser {} {}".format(input, output), env="conanrun")
        same = filecmp.cmp(input, output, shallow=False)
        if same:
            print("Files are different, test {} failed".format(test_name), file=sys.stderr)
        else:
            print("Test {} succeeded".format(test_name))

    def test(self):
        if cross_building(self):
            return

        self.run("json_dictionary_parser help", env="conanrun")

        self._run_test_case("test1_empty_input")
        self._run_test_case("test2_task_input")
        self._run_test_case("test3_one_record")
        self._run_test_case("test4_maxint")
        self._run_test_case("test5_long_record")
