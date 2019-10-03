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
                template <typename TElem, typename... TDims>
                void Redim(e::system::array<TElem> &arr, std::optional<bool> preserve, TDims... dims)
                {
                    arr.Redim(preserve.value_or(false), size_t(dims)...);
                }
                template <typename TElem>
                intptr_t GetSize(const e::system::array<TElem> &arr)
                {
                    return intptr_t(arr.GetSize());
                }
                template <typename TElem>
                intptr_t GetUBound(const e::system::array<TElem> &arr, std::optional<intptr_t> dimension = 1)
                {
                    return arr.GetUBound(size_t(dimension.value_or(1)));
                }
                template <typename TElem>
                void CopyTo(e::system::array<TElem> &dest, const e::system::array<TElem> &src)
                {
                    dest = src;
                }
                template <typename TElem>
                void Clear(e::system::array<TElem> &arr)
                {
                    arr = nullptr;
                }
                template <typename TElem>
                void Init(e::system::array<TElem> &arr)
                {
                    for (auto &item : arr)
                    {
                        item = TElem();
                    }
                }
                template <typename TElem, typename... TArgs>
                void Append(e::system::array<TElem> &arr, TArgs... args)
                {
                    arr.Append(std::forward<TArgs>(args)...);
                }
                template <typename TElem, typename TActualElem>
                void Insert(e::system::array<TElem> &arr, intptr_t pos, TActualElem newElem)
                {
                    if (pos <= 0)
                        return;
                    auto size = arr.GetSize();
                    if (size_t(pos) > size + 1)
                        return;
                    arr.Append(std::move(static_cast<TElem>(newElem)));
                    auto elem = arr.GetElemPtr();
                    TElem last = std::move(elem[size]);
                    for (size_t i = size; i >= size_t(pos); i--)
                    {
                        elem[i] = std::move(elem[i - 1]);
                    }
                    elem[pos - 1] = std::move(last);
                }
                template <typename TElem>
                void Remove(e::system::array<TElem> &arr, intptr_t start, std::optional<intptr_t> count = std::nullopt)
                {
                    auto count_v = count.value_or(1);
                    if (start <= 0 || count_v <= 0)
                        return;
                    auto size = arr.GetSize();
                    if (size_t(start) > size)
                        return;
                    if (size_t(start) + size_t(count_v) - 1 > size)
                        count_v = intptr_t(size) - start + 1;
                    auto numOfMoving = size - size_t(start) - size_t(count_v) + 1;
                    TElem *startMoving = &arr.GetElemPtr()[size_t(start) + size_t(count_v) - 1];
                    TElem *target = &arr.GetElemPtr()[start - 1];
                    for (size_t i = 0; i < numOfMoving; i++)
                    {
                        target[i] = std::move(startMoving[i]);
                    }
                    size -= count_v;
                    arr.Redim(true, size);
                }
                template <typename TElem>
                void Sort(e::system::array<TElem> &arr, std::optional<bool> asc = std::nullopt)
                {
                    if (asc.value_or(true))
                        std::sort(arr.begin(), arr.end(), std::less<TElem>());
                    else
                        std::sort(arr.begin(), arr.end(), std::greater<TElem>());
                }
            }
        }
    }
}