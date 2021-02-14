#include <benchmark/benchmark.h>
#include "Unique_hash_map.h"

struct Int_hash_function
{
    template <typename H>
    std::size_t operator()(const H& h) const
    {
        return h;
    }
};

using Map = CGAL::Unique_hash_map<int,int,Int_hash_function>;

static void construction(benchmark::State& state) {
  for (auto _ : state) {
     Map map(0,512);
     benchmark::DoNotOptimize(map.size());
  }
}

static void insert(benchmark::State& state) {
  Map map(0,512);
  for (auto _ : state) {
     for(int i=0; i<50'000; ++i)
        map[i];
     benchmark::DoNotOptimize(map.size());
  }
}

BENCHMARK(construction);
BENCHMARK(insert);

BENCHMARK_MAIN();
