#include <cstdlib>
#include <ranges>
#include <span>
#include <string_view>

#ifdef __cpp_lib_print
#include <print>
#define println (std::println)
#define print (std::print)
#else
#include <fmt/core.h>
#define println (fmt::println)
#define print (fmt::print)
#endif

[[gnu::always_inline]]
inline bool has_env(char const *const name) {
    const char* env = std::getenv(name);
    return env != nullptr && std::string_view{env} != "0";
}

int main(int argc, char** argv) {
    if (argc == 1) {
        println(stderr, "---- NO ARGS ----");
        return 0;
    }

    bool hex = false;
    if (std::string_view{argv[0]}.ends_with("printarg_hex")
        || has_env("PRINTARG_HEX")
    ) {
        hex = true;
        println(stderr, "---- PRINTARG HEX ----");
    }

    for (auto [index, arg] : std::span{argv, argv + argc}
        | std::views::transform([](char* str) { return std::string_view{str}; })
        | std::views::enumerate
        | std::views::drop(1)
    ) {
        if (!hex || arg.empty()) {
            println("{}:\t{:?}", index, arg);
            continue;
        }

        print("{}:\t{:X}", index, arg.front());
        for (auto c : arg | std::views::drop(1)) {
            print(" {:X}", c);
        }
        println("");
    }
}
