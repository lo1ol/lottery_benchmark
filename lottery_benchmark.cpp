#include <vector>
#include <random>
#include <utility>
#include <algorithm>

#include <benchmark/benchmark.h>

#include "lottery.h"

std::vector<uint64_t> GetRandomVector(const uint64_t cnt, const uint64_t seed)
{
    std::mt19937 gen(seed);
    std::uniform_int_distribution<uint64_t> dis(0);
    std::vector<uint64_t> vec;
    vec.reserve(cnt); // выделяем память сразу под нужное кол-во элементов

    for (uint64_t i=0; i < cnt; ++i) {
        vec.push_back(dis(gen));
    }

    return vec;
}

template <class LotteryImpl>
void BM_Lottery(benchmark::State& state) {
    const uint64_t r = uint64_t(-1) / (2*(state.range(0) + 1)); // берем радиус в 2 раза меньше среднего растояия между объектами
    std::vector<uint64_t> centers = GetRandomVector(state.range(0), 0); // генерируем нужное кол-во центров
    std::sort(centers.begin(), centers.end()); // необходимо для ускорения вставки в flat_set, чтобы не перемещать в памяти большие объемы данных при вставке

    LotteryImpl lot(std::move(centers), r);
    std::vector<uint64_t> points = GetRandomVector(1000, 1); // генерируем 1000 точек, от которых будем считать "испытывать удачу"

    for (auto _ : state) {
        for (auto point : points) {
            lot.GetWinAmount(point);
        }
    }

}
// тесты на 2^10, 2^12, 2^15, 2^20, 2^24 элементов. Т.к. каждый лист дерева занимает примерно 3 элемента (значение, указатель на левый и на правый лист) и все занимают 8 байт.
// то занимаемая память примерно составляет 24кб, 96кб, 768кб, 24мб, 384 мб
BENCHMARK_TEMPLATE(BM_Lottery, lottery::LotterySet)->Arg(1<<10)->Arg(1<<12)->Arg(1<<15)->Arg(1<<20)->Arg(1<<24);
// тесты на 2^10, 2^12, 2^15, 2^20, 2^24 элементов. т.к. Занимает в памяти столько же места, сколько и кол-во элементв*8.
// то занимаемая память примерно составляет 8кб, 32кб, 256кб, 8мб, 128 мб
BENCHMARK_TEMPLATE(BM_Lottery, lottery::LotteryFlatSet)->Arg(1<<10)->Arg(1<<12)->Arg(1<<15)->Arg(1<<20)->Arg(1<<24);

BENCHMARK_MAIN();
