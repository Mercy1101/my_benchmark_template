#include <queue>

#include "benchmark.h"


// Define a function that executes the code to be measured a
// specified number of times:
static void BM_StringCreation(benchmark::State& state) {
  for (auto _ : state) std::string empty_string;
}

// Register the function as a benchmark
BENCHMARK(BM_StringCreation);

// Define another benchmark
static void BM_StringCopy(benchmark::State& state) {
  std::string x = "hello";
  for (auto _ : state) std::string copy(x);
}
BENCHMARK(BM_StringCopy);

// Augment the main() program to invoke benchmarks if specified
// via the --benchmarks command line flag.  E.g.,
//       my_unittest --benchmark_filter=all
//       my_unittest --benchmark_filter=BM_StringCreation
//       my_unittest --benchmark_filter=String
//       my_unittest --benchmark_filter='Copy|Creation'
int main(int argc, char** argv) {
  benchmark::Initialize(&argc, argv);
  benchmark::RunSpecifiedBenchmarks();
  return 0;
}

// Sometimes a family of microbenchmarks can be implemented with
// just one routine that takes an extra argument to specify which
// one of the family of benchmarks to run.  For example, the following
// code defines a family of microbenchmarks for measuring the speed
// of memcpy() calls of different lengths:

static void BM_memcpy(benchmark::State& state) {
  char* src = new char[state.range(0)];
  char* dst = new char[state.range(0)];
  memset(src, 'x', state.range(0));
  for (auto _ : state) memcpy(dst, src, state.range(0));
  state.SetBytesProcessed(state.iterations() * state.range(0));
  delete[] src;
  delete[] dst;
}
BENCHMARK(BM_memcpy)->Arg(8)->Arg(64)->Arg(512)->Arg(1 << 10)->Arg(8 << 10);

// The preceding code is quite repetitive, and can be replaced with the
// following short-hand.  The following invocation will pick a few
// appropriate arguments in the specified range and will generate a
// microbenchmark for each such argument.
BENCHMARK(BM_memcpy)->Range(8, 8 << 10);

// You might have a microbenchmark that depends on two inputs.  For
// example, the following code defines a family of microbenchmarks for
// measuring the speed of set insertion.
static void BM_SetInsert(benchmark::State& state) {
  std::set<int> data;
  for (auto _ : state) {
    state.PauseTiming();
    /// data = ConstructRandomSet(state.range(0));
    state.ResumeTiming();
    for (int j = 0; j < state.range(1); ++j) data.insert(j);
  }
}
BENCHMARK(BM_SetInsert)
    ->Args({1 << 10, 128})
    ->Args({2 << 10, 128})
    ->Args({4 << 10, 128})
    ->Args({8 << 10, 128})
    ->Args({1 << 10, 512})
    ->Args({2 << 10, 512})
    ->Args({4 << 10, 512})
    ->Args({8 << 10, 512});

// The preceding code is quite repetitive, and can be replaced with
// the following short-hand.  The following macro will pick a few
// appropriate arguments in the product of the two specified ranges
// and will generate a microbenchmark for each such pair.
BENCHMARK(BM_SetInsert)->Ranges({{1 << 10, 8 << 10}, {128, 512}});

// For more complex patterns of inputs, passing a custom function
// to Apply allows programmatic specification of an
// arbitrary set of arguments to run the microbenchmark on.
// The following example enumerates a dense range on
// one parameter, and a sparse range on the second.
static void CustomArguments(benchmark::internal::Benchmark* b) {
  for (int i = 0; i <= 10; ++i)
    for (int j = 32; j <= 1024 * 1024; j *= 8) b->Args({i, j});
}
BENCHMARK(BM_SetInsert)->Apply(CustomArguments);

/// Use `Benchmark::MinTime(double t)` to set the minimum time used to run the
///     benchmark.This option overrides the `benchmark_min_time` flag
///         .

void BM_test(benchmark::State& state) {
  /// Do Somthing
}
BENCHMARK(BM_test)->MinTime(2.0);  // Run for at least 2 seconds.

/// In a multithreaded test,
///     it is guaranteed that none of the threads will start until all have
///     reached
///         the loop start,
///     and all will have finished before any thread exits the loop body.As
///     such, any global setup or teardown you want to do can be wrapped in a
///     check
///                             against the thread index :

static void BM_MultiThreaded(benchmark::State& state) {
  if (state.thread_index == 0) {
    // Setup code here.
  }
  for (auto _ : state) {
    // Run the test as normal.
  }
  if (state.thread_index == 0) {
    // Teardown code here.
  }
}
BENCHMARK(BM_MultiThreaded)->Threads(4);

/// If a benchmark runs a few milliseconds it may be hard to visually compare
/// the measured times, since the output data is given in nanoseconds per
/// default. In order to manually set the time unit, you can specify it
/// manually:

BENCHMARK(BM_test)->Unit(benchmark::kMillisecond);