#pragma once
#include <assert.h>
#include <iostream>
#define ASSERT(x) do { std::cout << "Error!\n"; assert(x); } while(0)

#ifdef _MSC_VER
#define FORCE_INLINE __forceinline
#else
#define FORCE_INLINE __attribute__((always_inline))
#endif

#ifdef _MSC_VER
#include <optional>
template<class T>
using Optional = std::optional<T>;
#else
#include <experimental/optional>
template<class T>
using Optional = std::experimental::optional<T>;
namespace std
{
    template<typename T>
    using optional = std::experimental::optional<T>;
}
#endif

#include <memory>

template<class T>
using SharedPtr = std::shared_ptr<T>;