from conan import ConanFile
from conan.tools.cmake import CMake, cmake_layout

class FishingConan(ConanFile):
    name = "fishing"
    version = "0.0.0"
    settings = "os", "compiler", "build_type", "arch"
    generators = "CMakeDeps", "CMakeToolchain"

    def requirements(self):
        # self.requires("glfw/3.4")  # OpenGL API library
        # self.requires("glm/1.0.1") # Math library
        pass

    def layout(self):
        cmake_layout(self)

    def build(self):
        cmake = CMake(self)
        cmake.configure()
        cmake.build()
