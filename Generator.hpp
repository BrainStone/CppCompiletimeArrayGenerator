#pragma once

#include <cstddef>

template <size_t N, typename T, T (*F)(size_t)>
struct Generator {
  static_assert(N > 0, "N must be greater than 0");

 private:
  template <int M, int... Rest>
  struct Generator_impl {
    static constexpr const T (&value)[N] = Generator_impl<M - 1, F(M), Rest...>::value;
  };

  template <int... Rest>
  struct Generator_impl<0, Rest...> {
    static constexpr const T value[N] = {F(0), Rest...};
  };

 public:
  static constexpr const T (&value)[N] = Generator_impl<N - 1>::value;

  Generator() = delete;
  Generator(const Generator&) = delete;
  Generator(Generator&&) = delete;
};

template <size_t N, typename T, T (*F)(size_t)>
template <int... Rest>
constexpr const T Generator<N, T, F>::Generator_impl<0, Rest...>::value[];
