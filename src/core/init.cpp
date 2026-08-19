#include "init.h"

#include <boost/process/v1/child.hpp>
#include <boost/process/v1/search_path.hpp>
#include <cstdlib>
#include <filesystem>
#include <format>
#include <fstream>
#include <iostream>
#include <print>
#include <string_view>

namespace cproj_core {

	constexpr std::string_view mainCpp =
		"#include \"core/hello.h\"\n"
		"\n"
		"int main() {\n"
		"\tcore::hello();\n"
		"}\n";

	constexpr std::string_view helloH =
		"#pragma once\n"
		"\n"
		"namespace core {\n"
		"\n"
		"\tvoid hello();\n"
		"\n"
		"}\n";

	constexpr std::string_view helloCpp =
		"#include \"hello.h\"\n"
		"\n"
		"#include <print>\n"
		"\n"
		"namespace core {\n"
		"\n"
		"\tvoid hello() {\n"
		"\t\tstd::println(\"Hello, world!\");\n"
		"\t}\n"
		"\n"
		"}\n";

	constexpr std::string_view cmake =
		"cmake_minimum_required(VERSION 3.25)\n"
		"\n"
		"project({} LANGUAGES CXX)\n"
		"\n"
		"set(CMAKE_CXX_STANDARD 23)\n"
		"set(CMAKE_CXX_STANDARD_REQUIRED ON)\n"
		"set(CMAKE_CXX_EXTENSIONS OFF)\n"
		"\n"
		"file(\n"
		"\tGLOB_RECURSE\n"
		"\tSOURCES\n"
		"\tCONFIGURE_DEPENDS\n"
		"\t\"${{CMAKE_CURRENT_SOURCE_DIR}}/src/*.cpp\"\n"
		")\n"
		"\n"
		"add_executable(\n"
		"\t${{PROJECT_NAME}}\n"
		"\t${{SOURCES}}\n"
		")\n"
		"\n"
		"if(MSVC)\n"
		"\ttarget_compile_options(${{PROJECT_NAME}} PRIVATE\n"
		"\t\t/W4\n"
		"\t\t/permissive-\n"
		"\t)\n"
		"else()\n"
		"\ttarget_compile_options(${{PROJECT_NAME}} PRIVATE\n"
		"\t\t-Wall\n"
		"\t\t-Wextra\n"
		"\t\t-Wpedantic\n"
		"\t\t-Wconversion\n"
		"\t\t-Wsign-conversion\n"
		"\t\t-Wshadow\n"
		"\t\t-Wformat=2\n"
		"\t\t-Wnull-dereference\n"
		"\t\t-Wdouble-promotion\n"
		"\t\t-Wimplicit-fallthrough\n"
		"\t\t-Woverloaded-virtual\n"
		"\t\t-Wnon-virtual-dtor\n"
		"\t\t-Wold-style-cast\n"
		"\t\t-Wcast-align\n"
		"\t\t-Wunused\n"
		"\t\t-Werror=return-type\n"
		"\t)\n"
		"endif()\n"
		"\n"
		"target_include_directories(\n"
		"\t${{PROJECT_NAME}}\n"
		"\tPRIVATE\n"
		"\t\t\"${{CMAKE_CURRENT_SOURCE_DIR}}/src\"\n"
		")\n";

	void handleInit(std::string_view name) {
		std::println("Creating project: {}", name);

		const std::filesystem::path root{ name };
		const std::filesystem::path src = root / "src";
		const std::filesystem::path core = src / "core";

		std::filesystem::create_directories(core);

		boost::process::v1::child git(boost::process::v1::search_path("git"), "init", root.string());
		git.wait();
		if (git.exit_code() != 0) {
			std::println(std::cerr, "Failed to initialize Git repository");
		}

		std::ofstream mainFile{ src / "main.cpp" };
		mainFile << mainCpp;

		std::ofstream helloHeader{ core / "hello.h" };
		helloHeader << helloH;

		std::ofstream helloSource{ core / "hello.cpp" };
		helloSource << helloCpp;

		std::ofstream cmakeFile{ root / "CMakeLists.txt" };
		cmakeFile << std::format(cmake, name);

		std::println("Project created successfully!");
	}

} // namespace cproj_core