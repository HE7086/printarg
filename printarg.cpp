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

int main(int argc, char *const *const argv) {
    if (argc == 1) {
        println(stderr, "---- NO ARGS ----");
        return 0;
    }

    bool hex = false;
    if (std::string_view{argv[0]}.ends_with("printarg_hex")
        || std::getenv("PRINTARG_HEX") != nullptr
    ) {
        hex = true;
        println(stderr, "---- PRINTARG HEX ----");
    }

    for (auto [index, arg] : std::span{argv, argv + argc}
        | std::views::transform([](char* str) { return std::string_view{str}; })
        | std::views::enumerate
        | std::views::drop(1)
    ) {
        if (!hex) {
            println("{}:\t{:?}", index, arg);
            return 0;
        }

        print("{}:\t", index);
        if (!arg.empty()) {
            print("{:X}", arg.front());
            for (auto c : arg | std::views::drop(1)) {
                print(" {:X}", c);
            }
        }
        println("");
    }
}
