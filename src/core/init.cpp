#include "init.h"
#include <print>

namespace cproj_core {
void handleInit(std::string_view name) { std::println("{}", name); }
} // namespace cproj_core
