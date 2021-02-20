CXX=clang++
CXXFLAGS=-O2 -lbenchmark -std=c++17
COMPARE=python3 /usr/share/benchmark/compare.py

all: unique_benchmarks unordered_map_benchmarks

%: %.cpp
	$(CXX) -o $@ $< $(CXXFLAGS)

test: unique_benchmarks unordered_map_benchmarks
	$(COMPARE) benchmarks ./unique_benchmarks ./unordered_map_benchmarks --benchmark_repetitions=10

clean:
	rm -f unique_benchmarks unordered_map_benchmarks

