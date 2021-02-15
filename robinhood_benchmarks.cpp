#include <benchmark/benchmark.h>
#include "robin_hood.h"
#include "Handle_hash_function.h"

class Data
{
};

using Handle = std::vector<Data>::iterator;

static std::vector<Handle> handles;

class Setup
{
public:
    Setup()
    {
        for(int i=0; i<50'000; ++i)
        {
            Handle h(new Data());
            handles.push_back(h);
        }
    }
};

Setup setup;

using Map = robin_hood::unordered_map<Handle,int,CGAL::Handle_hash_function>;

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
     for(int i=0; i<50'000; ++i) {
        const Handle& h=handles[i];
        map[h];
     }
     benchmark::DoNotOptimize(map.size());
  }
}

BENCHMARK(construction);
BENCHMARK(insert);

BENCHMARK_MAIN();
