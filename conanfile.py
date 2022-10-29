from conan import ConanFile
from conans import CMake

required_conan_version = ">=1.52.0"

class JsonDictionaryParserConan(ConanFile):
    name = "json_dictionary_parser"
    version = "0.0.0"

    # Optional metadata
    license = "<Put the package license here>"
    author = "andrei.malashkin@reactivereality.com"
    url = "<Package recipe repository url here, for issues about the package>"
    description = "<Description of JsonDictionaryParser here>"
    topics = ("json", "parsing")
    generators = "cmake_find_package_multi", "cmake"
    cmake = None
    version = "1.0.0"

    # Binary configuration
    settings = "os", "compiler", "build_type", "arch"

    # Sources are located in the same place as this recipe, copy them to the recipe
    exports_sources = "CMakeLists.txt", "src/*", "include/*", "3rd_party/*"

    def requirements(self):
        self.requires('rapidjson/cci.20220822')

    def getCmake(self):
        if self.cmake is None:
            self.cmake = CMake(self)
            self.cmake.configure()
        return self.cmake

    def build(self):
        cmake = self.getCmake()
        cmake.build()

    def package(self):
        cmake = self.getCmake()
        cmake.install()
