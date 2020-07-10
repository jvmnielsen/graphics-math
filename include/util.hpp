#pragma once

#define REQUIRES(...) typename std::enable_if<(__VA_ARGS__), int>::type = 0