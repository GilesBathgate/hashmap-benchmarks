#include <benchmark/benchmark.h>
#include "Handle_hash_map.h"

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

using Map = CGAL::internal::Handle_hash_map<Handle,int>;

static void construction(benchmark::State& state) {
  for (auto _ : state) {
     Map map(0,handles.size());
     benchmark::DoNotOptimize(map.size());
  }
}

static void insert(benchmark::State& state) {
  Map map(0,handles.size());
  for (auto _ : state) {
     for(const auto& h: handles) {
        map[h];
     }
     map.clear();
     benchmark::DoNotOptimize(map.size());
  }
}

static void update(benchmark::State& state) {
  Map map(0,handles.size());
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
