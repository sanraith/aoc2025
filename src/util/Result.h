// ReSharper disable CppNonExplicitConvertingConstructor
// ReSharper disable CppDFAConstantParameter

#pragma once
#include <string>
#include <iostream>
#include <concepts>
#include <utility>

namespace aoc::util {
    template<typename T>
    concept ResultIntegralType = std::same_as<T, int> || std::same_as<T, long> || std::same_as<T, long long> ||
                                 std::same_as<T, std::size_t>;

    template<typename T>
    concept ResultStringType = std::convertible_to<T, std::string_view>;

    struct Result {
        enum class State {
            Success,
            Failure,
            NotImplemented
        };

        const std::string value;
        const State state;

        // Forwarding constructor for string-like types
        template<ResultStringType T>
        constexpr Result(T&& val, const State state = State::Success) : value(std::forward<T>(val)), state(state) { // NOLINT(*-explicit-constructor)
        }

        // Integral constructor converts to string and delegates
        template<ResultIntegralType T>
        constexpr Result(T val) : Result(std::to_string(val), State::Success) { // NOLINT(*-explicit-constructor)
        }
    };

    inline std::ostream& operator<<(std::ostream& stream, const Result& r) {
        return stream << "Result{\"" << r.value << "\", State: " << static_cast<int>(r.state) << "}";
    }

    static constexpr Result NotImplementedResult{"???", Result::State::NotImplemented};
}
