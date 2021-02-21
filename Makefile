CXX=clang++
CXXFLAGS=-O2 -lbenchmark
COMPARE=python3 /usr/share/benchmark/compare.py

all: unique_benchmarks robinmap_benchmarks

%: %.cpp
	$(CXX) -o $@ $< $(CXXFLAGS)

test: unique_benchmarks robinmap_benchmarks
	$(COMPARE) benchmarks ./unique_benchmarks ./robinmap_benchmarks --benchmark_repetitions=10

clean:
	rm -f unique_benchmarks robinmap_benchmarks

