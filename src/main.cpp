#include "core/init.h"
#include "core/build.h"
#include "core/run.h"

#include <cstring>
#include <iostream>
#include <print>

int main(int argc, char** argv) {
	if (argc < 2) {
		std::println(std::cerr, "Usage: cproj [command] <options>");
		return 1;
	}

	if (argc == 2) {
		if (std::strcmp(argv[1], "build") == 0) {
			cproj_core::handleBuild(std::filesystem::current_path());
		}
		else if (std::strcmp(argv[1], "run") == 0) {
			cproj_core::handleRun(std::filesystem::current_path());
		}
	}
	else if (argc == 3) {
		if (std::strcmp(argv[1], "init") == 0) {
			cproj_core::handleInit(argv[2]);
		}
		else if (std::strcmp(argv[1], "build") == 0) {
			cproj_core::handleBuild(argv[2]);
		}
		else if (std::strcmp(argv[1], "run") == 0) {
			cproj_core::handleRun(argv[2]);
		}
	}
}