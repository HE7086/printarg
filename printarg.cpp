#include <ranges>
#include <span>
#include <string_view>

#ifdef __cpp_lib_print
#include <print>
#define println (std::println)
#else
#include <fmt/core.h>
#define println (fmt::println)
#endif

int main(int argc, char *const *const argv) {
    if (argc == 1) {
        println("---- NO ARGS ----");
        return 0;
    }
    for (auto [index, arg] : std::span(argv + 1, argv + argc)
        | std::views::transform([](char* str) { return std::string_view(str); })
        | std::views::enumerate
    ) {
        println("{}:\t{:?}", index, arg);
    }
}
