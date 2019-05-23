#include <vector>
#include <random>
#include <utility>
#include <algorithm>

#include <benchmark/benchmark.h>

#include "lottery.h"

std::vector<uint64_t> GetRandomVector(const uint64_t cnt, const uint64_t seed)
{
    std::mt19937 gen(seed); //Standard mersenne_twister_engine seeded with rd()
    std::uniform_int_distribution<uint64_t> dis(0);
    std::vector<uint64_t> vec;
    vec.reserve(cnt);

    for (uint64_t i=0; i < cnt; ++i) {
        vec.push_back(dis(gen));
    }

    return vec;
}

template <class LotteryImpl>
void BM_Lottery(benchmark::State& state) {
    const uint64_t r = uint64_t(-1) / (2*(state.range(0) + 1));
    std::vector<uint64_t> centers = GetRandomVector(state.range(0), 0);
    std::sort(centers.begin(), centers.end()); // sort to boost filling of lot when it is implemented as FlatSet

    LotteryImpl lot(centers, r);
    std::vector<uint64_t> points = GetRandomVector(1000, 1);

    for (auto _ : state) {
        for (auto point : points) {
            lot.GetWinAmount(point);
        }
    }

}

BENCHMARK_TEMPLATE(BM_Lottery, lottery::LotterySet)->Arg(1<<10)->Arg(1<<12)->Arg(1<<15)->Arg(1<<20)->Arg(1<<24);
BENCHMARK_TEMPLATE(BM_Lottery, lottery::LotteryFlatSet)->Arg(1<<10)->Arg(1<<12)->Arg(1<<15)->Arg(1<<20)->Arg(1<<24);

BENCHMARK_MAIN();
