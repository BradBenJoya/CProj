#include "build.h"
#include "run.h"

#include <boost/process/v1/child.hpp>
#include <cstdlib>
#include <filesystem>
#include <format>
#include <print>
#include <iostream>

namespace cproj_core {
	void handleRun(std::filesystem::path path) {
		handleBuild(path);

		const std::string name = path.filename().string();

#ifdef _WIN32
		const std::filesystem::path executable = path / "bin" / (name + ".exe");
#else
		const std::filesystem::path executable = path / "bin" / name;
#endif

		boost::process::v1::child program(executable.string());
		program.wait();
		if (program.exit_code() != 0) {
			std::println(std::cerr, "Failed to run project");
		}
	}
}