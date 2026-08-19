#include "build.h"
#include <boost/process/v1/child.hpp>
#include <boost/process/v1/search_path.hpp>
#include <print>
#include <iostream>
#include <format>

namespace cproj_core {
	void handleBuild(std::filesystem::path path) {
		namespace process = boost::process::v1;
		if (!std::filesystem::exists(path / "CMakeLists.txt")) {
			std::println(std::cerr, "Could not find CMakeLists.txt in provided path {}", path.string());
			return;
		}

		if (!std::filesystem::is_empty(path)) {
			std::println("Configuring with CMake...");
			process::child cmake(process::search_path("cmake"), "-S", path.string(), "-B", (path / "bin").string(), "-G", "Ninja");
			cmake.wait();
			if (cmake.exit_code() != 0) {
				std::println(std::cerr, "Failed to configure with CMake");
				return;
			}
		}

		std::println("Building project...");
		process::child cmake(process::search_path("cmake"), "--build", (path / "bin").string());
		cmake.wait();
		if (cmake.exit_code() != 0) {
			std::println(std::cerr, "Failed to build project");
			return;
		}
	}
}