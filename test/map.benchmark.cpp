#include <benchmark/benchmark.h>

#include "data.hpp"

int main(int argc, char* argv[]) {
    benchmark::Initialize(&argc, argv);
    benchmark::RunSpecifiedBenchmarks();
    return 0;
}

const char* aliceblue = "aliceblue";
const char* missing = "missing";
const char* mediumorchid = "mediumorchid";

////////////////////////////////////////////////////////////////////////////////
// mapbox::eternal::map

MAPBOX_ETERNAL_CONSTEXPR const auto colors = mapbox::eternal::map<mapbox::eternal::string, Color>({
    COLORS
});

#if MAPBOX_ETERNAL_IS_CONSTEXPR
static void EternalMap_ConstexprLookup(benchmark::State& state) {
    while (state.KeepRunning()) {
        constexpr auto it = colors.find("aliceblue");
        benchmark::DoNotOptimize(it);
    }
}
#endif

static void EternalMap_Lookup(benchmark::State& state) {
    while (state.KeepRunning()) {
        benchmark::DoNotOptimize(colors.find(aliceblue));
    }
}

static void EternalMap_LookupMissing(benchmark::State& state) {
    while (state.KeepRunning()) {
        benchmark::DoNotOptimize(colors.find(missing));
    }
}

static void EternalMap_LookupEqualRange(benchmark::State& state) {
    while (state.KeepRunning()) {
        benchmark::DoNotOptimize(colors.equal_range(mediumorchid));
    }
}

#if MAPBOX_ETERNAL_IS_CONSTEXPR
BENCHMARK(EternalMap_ConstexprLookup);
#endif
BENCHMARK(EternalMap_Lookup);
BENCHMARK(EternalMap_LookupMissing);
BENCHMARK(EternalMap_LookupEqualRange);


////////////////////////////////////////////////////////////////////////////////
// mapbox::eternal::hash_map

MAPBOX_ETERNAL_CONSTEXPR const auto colorsHashMap = mapbox::eternal::hash_map<mapbox::eternal::string, Color>({
    COLORS
});

#if MAPBOX_ETERNAL_IS_CONSTEXPR
static void EternalHashMap_ConstexprLookup(benchmark::State& state) {
    while (state.KeepRunning()) {
        constexpr auto it = colorsHashMap.find("aliceblue");
        benchmark::DoNotOptimize(it);
    }
}
#endif

static void EternalHashMap_Lookup(benchmark::State& state) {
    while (state.KeepRunning()) {
        benchmark::DoNotOptimize(colorsHashMap.find(aliceblue));
    }
}

static void EternalHashMap_LookupMissing(benchmark::State& state) {
    while (state.KeepRunning()) {
        benchmark::DoNotOptimize(colorsHashMap.find(missing));
    }
}

static void EternalHashMap_LookupEqualRange(benchmark::State& state) {
    while (state.KeepRunning()) {
        benchmark::DoNotOptimize(colorsHashMap.equal_range(mediumorchid));
    }
}

#if MAPBOX_ETERNAL_IS_CONSTEXPR
BENCHMARK(EternalHashMap_ConstexprLookup);
#endif
BENCHMARK(EternalHashMap_Lookup);
BENCHMARK(EternalHashMap_LookupMissing);
BENCHMARK(EternalHashMap_LookupEqualRange);


////////////////////////////////////////////////////////////////////////////////
// std::map

const std::map<std::string, Color> namedColors = {
    COLORS
};

static void StdMap_Lookup(benchmark::State& state) {
    while (state.KeepRunning()) {
        benchmark::DoNotOptimize(namedColors.find(aliceblue));
    }
}

static void StdMap_LookupMissing(benchmark::State& state) {
    while (state.KeepRunning()) {
        benchmark::DoNotOptimize(namedColors.find(missing));
    }
}

static void StdMap_LookupEqualRange(benchmark::State& state) {
    while (state.KeepRunning()) {
        benchmark::DoNotOptimize(namedColors.equal_range(mediumorchid));
    }
}

BENCHMARK(StdMap_Lookup);
BENCHMARK(StdMap_LookupMissing);
BENCHMARK(StdMap_LookupEqualRange);

////////////////////////////////////////////////////////////////////////////////
// std::multimap

const std::multimap<std::string, Color> namedColorsMultimap = {
    COLORS
};

static void StdMultimap_Lookup(benchmark::State& state) {
    while (state.KeepRunning()) {
        benchmark::DoNotOptimize(namedColorsMultimap.find(aliceblue));
    }
}

static void StdMultimap_LookupMissing(benchmark::State& state) {
    while (state.KeepRunning()) {
        benchmark::DoNotOptimize(namedColorsMultimap.find(missing));
    }
}

static void StdMultimap_LookupEqualRange(benchmark::State& state) {
    while (state.KeepRunning()) {
        benchmark::DoNotOptimize(namedColorsMultimap.equal_range(mediumorchid));
    }
}

BENCHMARK(StdMultimap_Lookup);
BENCHMARK(StdMultimap_LookupMissing);
BENCHMARK(StdMultimap_LookupEqualRange);

////////////////////////////////////////////////////////////////////////////////
// std::unordered_map

const std::unordered_map<std::string, Color> namedColorsHashMap = {
    COLORS
};

static void StdUnorderedMap_Lookup(benchmark::State& state) {
    while (state.KeepRunning()) {
        benchmark::DoNotOptimize(namedColorsHashMap.find(aliceblue));
    }
}

static void StdUnorderedMap_LookupMissing(benchmark::State& state) {
    while (state.KeepRunning()) {
        benchmark::DoNotOptimize(namedColorsHashMap.find(missing));
    }
}

static void StdUnorderedMap_LookupEqualRange(benchmark::State& state) {
    while (state.KeepRunning()) {
        benchmark::DoNotOptimize(namedColorsHashMap.equal_range(mediumorchid));
    }
}

BENCHMARK(StdUnorderedMap_Lookup);
BENCHMARK(StdUnorderedMap_LookupMissing);
BENCHMARK(StdUnorderedMap_LookupEqualRange);

////////////////////////////////////////////////////////////////////////////////
// std::unordered_multimap

const std::unordered_multimap<std::string, Color> namedColorsHashMultimap = {
    COLORS
};

static void StdUnorderedMultimap_Lookup(benchmark::State& state) {
    while (state.KeepRunning()) {
        benchmark::DoNotOptimize(namedColorsHashMultimap.find(aliceblue));
    }
}

static void StdUnorderedMultimap_LookupMissing(benchmark::State& state) {
    while (state.KeepRunning()) {
        benchmark::DoNotOptimize(namedColorsHashMultimap.find(missing));
    }
}

static void StdUnorderedMultimap_LookupEqualRange(benchmark::State& state) {
    while (state.KeepRunning()) {
        benchmark::DoNotOptimize(namedColorsHashMultimap.equal_range(mediumorchid));
    }
}

BENCHMARK(StdUnorderedMultimap_Lookup);
BENCHMARK(StdUnorderedMultimap_LookupMissing);
BENCHMARK(StdUnorderedMultimap_LookupEqualRange);

