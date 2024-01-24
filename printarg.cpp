#include <cstdlib>
#include <ranges>
#include <span>
#include <string_view>

#include <fmt/core.h>
#include <fmt/ranges.h>

[[gnu::always_inline]]
inline bool has_env(char const *const name) {
    const char* env = std::getenv(name);
    return env != nullptr && std::string_view{env} != "0";
}

int main(int argc, char** argv) {
    if (argc <= 1) {
        fmt::println(stderr, "---- NO ARGS (argc={}) ----", argc);
        return 0;
    }

    bool hex = false;
    if (std::string_view{argv[0]}.ends_with("printarg_hex")
        || has_env("PRINTARG_HEX")
    ) {
        hex = true;
        fmt::println(stderr, "---- PRINTARG HEX ----");
    }

    for (auto [index, arg] : std::span{argv, argv + argc}
        | std::views::transform([](char* str) { return std::string_view{str}; })
        | std::views::enumerate
        | std::views::drop(1)
    ) {
        if (!hex) {
            fmt::println("{}:\t{:?}", index, arg);
            continue;
        }

        fmt::println("{}:\t{:X}", index, fmt::join(arg, " "));
    }
}
