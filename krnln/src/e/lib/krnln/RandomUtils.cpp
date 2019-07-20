#include "RandomUtils.h"
#include <limits>
#include <random>

static std::default_random_engine thread_local RandomEngine;
void e::lib::krnln::RandomUtils::SetSeed(std::optional<int32_t> seed)
{
    if(seed.has_value())
    {
        RandomEngine.seed(seed.value());
    }
    else
    {
        std::random_device rd;
        RandomEngine.seed(rd());
    }
}

int32_t e::lib::krnln::RandomUtils::NextInt32(std::optional<int32_t> min, std::optional<int32_t> max)
{
    std::uniform_int_distribution<int32_t> distribution(min.value_or(0), max.value_or(std::numeric_limits<int32_t>::max()));
    return distribution(RandomEngine);
}
