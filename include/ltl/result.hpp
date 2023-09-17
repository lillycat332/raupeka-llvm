//
// Created by Lilly Cham on 17/09/2023.
//
#pragma once
#include <cstdlib>
#include <string>
#include <type_traits>
#include <variant>
#include <iostream>

/// @brief A concept representing Errors.
template <typename T>
concept Error = requires(T e) { e.str()->std::string; };

/// @brief An implementation of a monadic result type.
/// @tparam T The type of the result.
/// @tparam E The type of the error.
template <typename T, typename E>
  requires Error<E> && std::is_copy_constructible_v<T> &&
           std::is_copy_constructible_v<E> && std::equality_comparable<T> &&
           std::equality_comparable<E>
class Result {
public:
  /// @brief Construct a new Okay Result object.
  /// @param value The value to wrap.
  auto okay(T value) -> Result<T, E> { return Result<T, E>(value); }

  /// @brief Construct a new Error Result object.
  /// @param value The error to wrap.
  auto error(E value) -> Result<T, E> { return Result<T, E>(value); }

  /// @brief force unwrap the result, returning the value if it is Ok, or
  /// printing the error and exiting if it is Err.
  /// It is recommended to avoid using this function, and instead use
  /// `map`, `map_err`, `and_then`, or `or_else`.
  /// @return T The value if it is Ok.
  auto unwrap() -> T {
    if (is_ok()) {
      return std::get<T>(value);
    } else {
      std::cerr << std::get<E>(value).str() << std::endl;
      std::abort();
    }
  }

  auto operator==(const Result<T, E> &other) const -> bool {
    return value == other.value;
  }

  auto operator!=(const Result<T, E> &other) const -> bool {
    return value != other.value;
  }

  /// @brief Returns true if the result is Ok.
  const bool is_ok() const { return std::holds_alternative<T>(this->value); }

  /// @brief Returns true if the result is Err.
  const bool is_err() const { return std::holds_alternative<E>(this->value); }

  /// @brief Map a function over the result, returning a new result.
  /// @tparam F The type of the function.
  template <typename F>
  auto map(F f) -> Result<decltype(f(std::get<T>(this->value))), E> {
    if (is_ok()) {
      return Result<decltype(f(std::get<T>(this->value))), E>(f(std::get<T>(this->value)));
    } else {
      return Result<decltype(f(std::get<T>(this->value))), E>(std::get<E>(this->value));
    }
  }

  template <typename F>
  auto map_err(F f) -> Result<T, decltype(f(std::get<E>(this->value)))> {
    if (is_ok()) {
      return Result<T, decltype(f(std::get<E>(this->value)))>(std::get<T>(this->value));
    } else {
      return Result<T, decltype(f(std::get<E>(this->value)))>(f(std::get<E>(this->value)));
    }
  }

private:
  std::variant<T, E> value;
};
