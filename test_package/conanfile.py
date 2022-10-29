import os
from conan import ConanFile
from conan.tools.build import cross_building
from conan.tools.layout import basic_layout


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

    def test(self):
        if cross_building(self):
            return

        self.run("json_dictionary_parser help", env="conanrun")
        self.run("json_dictionary_parser ../test1_empty_input.json test1.output", env="conanrun")
        self.run("json_dictionary_parser ../test2_task_input.json  test2.output", env="conanrun")
        self.run("json_dictionary_parser ../test3_one_record.json  test3.output", env="conanrun")
