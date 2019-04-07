#pragma once
#include <e/system/basic_type.h>
#include <e/system/func.h>
namespace e
{
	namespace lib
	{
		namespace krnln
		{
			namespace ArrayUtils
			{
				template <typename TElem, typename... TDims> void Redim(e::system::array<TElem> &arr, std::optional<bool> preserve, TDims... dims)
				{
					arr.Redim(preserve.value_or(false), size_t(dims)...);
				}
				template <typename TElem> intptr_t GetSize(const e::system::array<TElem> &arr)
				{
					return intptr_t(arr.GetSize());
				}
				template <typename TElem> intptr_t GetUBound(const e::system::array<TElem> &arr, std::optional<intptr_t> dimension = 1)
				{
					return arr.GetUBound(size_t(dimension.value_or(1)));
				}
				template <typename TElem> void CopyTo(e::system::array<TElem> &dest, const e::system::array<TElem> &src)
				{
					dest = src;
				}
				template <typename TElem> void Clear(e::system::array<TElem> &arr)
				{
					arr = nullptr;
				}
			}
		}
	}
}