#include <iostream>
#include <chrono>
#include <string_view>

///////////////////////////////////////////////////////////////////////////////

uint64_t fib_recurse(uint8_t x) noexcept {
        return x < 2 ? 1 : fib_recurse(x - 1) + fib_recurse(x - 2);
}

///////////////////////////////////////////////////////////////////////////////

uint64_t fib_loop(uint8_t x) noexcept {
    auto out = uint64_t{1};
    auto prev = uint64_t{1};

    for (auto i = uint8_t{2}; i <= x; ++i){
        auto tmp = out;
        out += prev;
        prev = tmp;
    }

    return out;
}

void time_function(std::string_view name, uint64_t(*fn)(uint8_t), uint8_t x){
    const auto start = std::chrono::steady_clock::now();
    const auto result = fn(x);
    const auto end = std::chrono::steady_clock::now();

    std::cout << name << "(" << static_cast<uint32_t>(x) << ") = " << result << ", in " << std::chrono::duration<double>{end - start}
              << std::endl;
}

///////////////////////////////////////////////////////////////////////////////

int main() {
    constexpr auto max_value = 45;

    for (auto value = 1u; value < max_value; ++value) {
        time_function("fib_recurse", fib_recurse, value);
        time_function("fib_loop", fib_loop, value);
    }

    return 0;
}

///////////////////////////////////////////////////////////////////////////////
