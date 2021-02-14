#include <benchmark/benchmark.h>
#include "robin_hood.h"
struct Int_hash_function
{
    template <typename H>
    std::size_t operator()(const H& h) const
    {
        return h;
    }
};

using Map = robin_hood::unordered_map<int,int,Int_hash_function>;

static void construction(benchmark::State& state) {
  for (auto _ : state) {
     Map map;
     map.reserve(512);
     benchmark::DoNotOptimize(map.size());
  }
}

static void insert(benchmark::State& state) {
  Map map;
  map.reserve(512);
  for (auto _ : state) {
     for(int i=0; i<50'000; ++i)
        map[i];
     benchmark::DoNotOptimize(map.size());
  }
}


BENCHMARK(construction);
BENCHMARK(insert);

BENCHMARK_MAIN();
