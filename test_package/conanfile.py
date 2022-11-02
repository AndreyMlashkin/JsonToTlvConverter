import os, sys, filecmp
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
        
    def _run_test_case(self, test_name):
        input = "../{}.json".format(test_name)
        output = "{}.tlv".format(test_name)
        expected_output = "../{}.tlv".format(test_name)

        assert os.path.isfile(input)
        assert os.path.isfile(expected_output)

        self.run("json_dictionary_parser {} {}".format(input, output), env="conanrun")
        assert os.path.isfile(output)

        print("\n\n\n\nExpected output:\n")
        expected_output_file = open(expected_output, 'rb')
        assert expected_output_file.closed == False
        print(expected_output_file.read())

        print("\n\n\n\nOutput:\n")
        output_file = open(output, 'rb')
        assert output_file.closed == False
        print(output_file.read())

        equal = filecmp.cmp(output, expected_output, shallow=False)
        if equal:
            print("Test {} succeeded".format(test_name))
        else:
            print("Files are different, test {} failed".format(test_name), file=sys.stderr)
            assert False

    def test(self):
        if cross_building(self):
            return

        self.run("json_dictionary_parser help", env="conanrun")

        self._run_test_case("test1_empty_input")
        self._run_test_case("test2_task_input")
        self._run_test_case("test3_one_record")
        self._run_test_case("test4_maxint")
        self._run_test_case("test5_long_record")
