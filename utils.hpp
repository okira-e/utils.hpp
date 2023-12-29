#pragma once

#include <iostream>
#include <string>
#include <optional>
#include <random>


//
// Utility Macros
//


// Syntax sugar for shared and unique pointers.
#define RC          std::shared_ptr
#define RC_NEW      std::make_shared
#define BOX         std::unique_ptr
#define BOX_NEW     std::make_unique

// The defer macro definition.
// Source: https://stackoverflow.com/questions/32432450/what-is-standard-defer-finalizer-implementation-in-c
#ifndef defer
struct defer_dummy {};
template <class F> struct deferrer { F f; ~deferrer() { f(); } };
template <class F> deferrer<F> operator*(defer_dummy, F f) { return {f}; }
#define DEFER_(LINE) zz_defer##LINE
#define DEFER(LINE) DEFER_(LINE)
#define defer auto DEFER(__LINE__) = defer_dummy{} *[&]()
#endif // defer


//
// Utility Functions
//

// Utility class
class Utils {
public:
    /**
     * @brief panic takes a message and prints it to the standard error.
     * @param msg
     * @param exit_code
     */
    static auto panic(const std::string& msg, size_t exit_code = 1) -> void {
        std::cerr << msg << std::endl;
        exit(exit_code);
    }

    /**
     * @brief expect takes an optional value and exists the program with an error message if it is not set.
     * @tparam T
     * @param opt
     * @param msg
     * @return the value of the optional if it is not empty.
     */
    template <typename T>
    static auto expect(const std::optional<T>& opt, const std::string& msg) -> const T& {
        if (!opt.has_value()) {
            std::cerr << ("ERROR: " + msg) << std::endl;
            exit(1);
        }

        return opt.value();
    }

    /**
     * @brief free_if_set takes an optional raw pointer and deletes it if it is set.
     * @tparam T
     * @param ptr
     */
    template <typename T>
    static auto free_if_set(std::optional<T*>& ptr) -> void {
        if (ptr.has_value() && ptr.value() != nullptr) {
            delete ptr.value();
        }
    }

    /**
     * @brief randomInt generates a random integer between min and max.
     * @param min
     * @param max
     * @return a random integer.
     */
    static auto randomInt(int min, int max) -> int {
        auto rd = std::random_device{};
        auto mt = std::mt19937(rd());
        auto dist = std::uniform_int_distribution<int>(min, max);

        return dist(mt);
    }

    /**
     * @brief randomFloat generates a random float between min and max.
     * @param min
     * @param max
     * @return a random float.
     */
     template <typename T>
    static auto randomReal(T min, T max) -> T {
        auto rd = std::random_device{};
        auto mt = std::mt19937(rd());
        auto dist = std::uniform_real_distribution<T>(min, max);

        return dist(mt);
    }
};
