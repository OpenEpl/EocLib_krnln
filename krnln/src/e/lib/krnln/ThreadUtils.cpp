#include "ThreadUtils.h"
#include <thread>
void e::lib::krnln::ThreadUtils::SleepFor(int32_t duration)
{
    std::this_thread::sleep_for(std::chrono::milliseconds(duration));
}