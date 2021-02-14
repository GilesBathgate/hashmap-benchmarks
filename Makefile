CXX=clang++
CXXFLAGS=-lbenchmark
COMPARE=python3 /usr/share/benchmark/compare.py

all: unique_benchmarks robinhood_benchmarks

%: %.cpp
	$(CXX) -o $@ $< $(CXXFLAGS)

test: unique_benchmarks robinhood_benchmarks
	$(COMPARE) benchmarks ./unique_benchmarks ./robinhood_benchmarks --benchmark_repetitions=10

clean:
	rm -f unique_benchmarks robinhood_benchmarks

