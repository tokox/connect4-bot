#ifndef CONN4_BOT_TYPES
#define CONN4_BOT_TYPES

#include <cstdint>
#include <cstddef>
#include <concepts>
#include <string_view>

using int128_t = __int128_t;
using uint128_t = __uint128_t;

using u8 = uint8_t;
using u16 = uint16_t;
using u32 = uint32_t;
using u64 = uint64_t;
using u128 = uint128_t;
using usz = size_t;


template<usz N>
struct uint_leastN
{
	using type = std::conditional_t<N <= 8, u8,
		std::conditional_t<N <= 16, u16,
		std::conditional_t<N <= 32, u32,
		std::conditional_t<N <= 64, u64,
		u128>>>>;
};
template<usz N>
using uint_leastN_t = typename uint_leastN<N>::type;

template<usz L, usz C, uint_leastN_t<L> V, typename T = uint_leastN_t<L* C>, usz I = 0>
struct repeat_pattern
{
	static constexpr T value = (repeat_pattern<L, C, V, T, I + 1>::value << L) | V;
};

template<usz L, usz C, uint_leastN_t<L> V, typename T>
struct repeat_pattern<L, C, V, T, C>
{
	static constexpr T value = 0;
};

template<usz L, usz C, uint_leastN_t<L> V, typename T = uint_leastN_t<L* C>>
constexpr T repeat_pattern_v = repeat_pattern<L, C, V, T>::value;

#define REPB(pattern, count, ...) repeat_pattern_v<std::string_view(#pattern).size(), count, 0b0##pattern, ##__VA_ARGS__>

#endif
