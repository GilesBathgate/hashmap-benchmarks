CXX=clang++
CXXFLAGS=-O2 -lbenchmark -labsl_raw_hash_set -labsl_hashtablez_sampler
COMPARE=python3 /usr/share/benchmark/compare.py

all: unique_benchmarks abseil_unordered_map_benchmarks

%: %.cpp
	$(CXX) -o $@ $< $(CXXFLAGS)

test: unique_benchmarks abseil_unordered_map_benchmarks
	$(COMPARE) benchmarks ./unique_benchmarks ./abseil_unordered_map_benchmarks --benchmark_repetitions=10

clean:
	rm -f unique_benchmarks abseil_unordered_map_benchmarks

