CXX=clang++
CXXFLAGS=-O2 -lbenchmark -std=c++17
COMPARE=python3 /usr/share/benchmark/compare.py

all: std_benchmarks robinhood_benchmarks

%: %.cpp
	$(CXX) -o $@ $< $(CXXFLAGS)

test: std_benchmarks robinhood_benchmarks
	$(COMPARE) benchmarks ./std_benchmarks ./robinhood_benchmarks --benchmark_repetitions=10

clean:
	rm -f std_benchmarks robinhood_benchmarks

