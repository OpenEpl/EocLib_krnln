#include <e/system/basic_type.h>
namespace e
{
    namespace lib
    {
        namespace krnln
        {
            namespace LogicUtils
            {
                template <typename TResult = e::system::any, typename TA, typename TB>
                TResult IIf(bool x, TA a, TB b)
                {
                    return x ? static_cast<TResult>(a) : static_cast<TResult>(b);
                }

                template <typename TResult = e::system::any, typename... TArgs>
                TResult Choose(intptr_t x, TArgs... item)
                {
                    TResult items[] = {static_cast<TResult>(item)...};
                    if (x < 1 || x > sizeof...(item))
                        throw std::out_of_range("Choose IndexCheck");
                    return items[x - 1];
                }
            }
        }
    }
}