#include <e/system/basic_type.h>
#include <vector>
namespace e
{
    namespace lib
    {
        namespace krnln
        {
            template <typename TData, typename TSearcher>
            std::vector<TData *> findAllSubData(TData *startPtr, TData *endPtr, TData *target, size_t targetLength, size_t limit, TSearcher searcher)
            {
                std::vector<TData *> positions;
                while (positions.size() < limit)
                {
                    if (startPtr >= endPtr)
                        break;
                    startPtr = searcher(startPtr, target);
                    if (startPtr == nullptr)
                        break;
                    positions.push_back(startPtr);
                    startPtr += targetLength;
                }
                return positions;
            }
        }
    }
}
