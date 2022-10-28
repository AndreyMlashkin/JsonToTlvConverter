from conan import ConanFile
from conans import CMake
from conan.tools.scm import Git

required_conan_version = ">=1.53.0"

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

    # Binary configuration
    settings = "os", "compiler", "build_type", "arch"

    # Sources are located in the same place as this recipe, copy them to the recipe
    exports_sources = "CMakeLists.txt", "src/*", "include/*", "3rd_party/*"

    def set_version(self):
        git = Git(self, folder=self.recipe_folder)
        self.version = git.run("describe --always --tags --abbrev=9")

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
