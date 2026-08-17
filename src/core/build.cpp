#include "build.h"
#include <print>
#include <iostream>
#include <format>

namespace cproj_core {
	void handleBuild(std::filesystem::path path) {
		if (!std::filesystem::exists(path / "CMakeLists.txt")) {
			std::println(std::cerr, "Could not find CMakeLists.txt in provided path {}", path.string());
			return;
		}

		if (!std::filesystem::is_empty(path)) {
			std::println("Configuring with CMake...");
			if (std::system(std::format("cmake -S \"{}\" -B \"{}/bin\" -G Ninja", path.string(), path.string()).c_str()) != 0) {
				std::println(std::cerr, "Failed to configure with CMake");
				return;
			}
		}

		std::println("Building project...");
		if (std::system(std::format("cmake --build \"{}/bin\"", path.string()).c_str()) != 0) {
			std::println(std::cerr, "Failed to build project");
			return;
		}
	}
}