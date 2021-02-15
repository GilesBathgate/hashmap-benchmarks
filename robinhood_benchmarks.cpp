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

using Map = robin_hood::unordered_flat_map<Handle,int,CGAL::Handle_hash_function>;

static void construction(benchmark::State& state) {
  for (auto _ : state) {
     Map map;
     map.reserve(handles.size());
     benchmark::DoNotOptimize(map.size());
  }
}

static void insert(benchmark::State& state) {
  Map map;
  map.reserve(handles.size());
  for (auto _ : state) {
     for(const auto& h: handles) {
        map[h];
     }
     map.clear();
     benchmark::DoNotOptimize(map.size());
  }
}

static void update(benchmark::State& state) {
  Map map;
  map.reserve(handles.size());
  for(const auto& h: handles)
        map[h];

  for (auto _ : state) {
     for(const auto& h: handles) {
        map[h] = 987;
     }
     benchmark::DoNotOptimize(map.size());
  }
}

BENCHMARK(construction);
BENCHMARK(insert);
BENCHMARK(update);

BENCHMARK_MAIN();
