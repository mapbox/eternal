#include "data.hpp"

#include <cassert>


MAPBOX_ETERNAL_CONSTEXPR const auto colors = mapbox::eternal::map<mapbox::eternal::string, Color>({
    COLORS
});

MAPBOX_ETERNAL_CONSTEXPR const auto multi_colors = mapbox::eternal::map<mapbox::eternal::string, Color>({
    { "red", { 255, 0, 0, 1 } },
    { "yellow", { 255, 255, 0, 1 } },
    { "white", { 255, 255, 255, 1 } }, // comes before yellow!
    { "yellow", { 255, 220, 0, 1 } },  // a darker yellow
});

MAPBOX_ETERNAL_CONSTEXPR const auto hash_colors = mapbox::eternal::hash_map<mapbox::eternal::string, Color>({
    { "red", { 255, 0, 0, 1 } },
    { "yellow", { 255, 255, 0, 1 } },
    { "yellow", { 255, 220, 0, 1 } },  // a darker yellow
    { "white", { 255, 255, 255, 1 } },
});

// GCC 4.9 compatibility
#if MAPBOX_ETERNAL_IS_CONSTEXPR
#define CONSTEXPR_ASSERT(value, str) static_assert(value, str)
#else
#define CONSTEXPR_ASSERT(value, str) assert(value)
#endif

static void test() {
    CONSTEXPR_ASSERT(colors.unique(), "multi_colors are not unique");
    CONSTEXPR_ASSERT(colors.find("beige") != colors.end(), "colors contains beige");
    CONSTEXPR_ASSERT(colors.find("beige")->second == Color(245, 245, 220, 1),
                  "beige returns the correct color");
    CONSTEXPR_ASSERT(colors.find("blackquoise") == colors.end(), "blackquoise is not a color");
    CONSTEXPR_ASSERT(colors.count("beige") == 1, "beige is found once");
    CONSTEXPR_ASSERT(colors.count("blackquoise") == 0, "blackquoise is not found");
    CONSTEXPR_ASSERT(colors.contains("beige") == true, "beige is not found");
    CONSTEXPR_ASSERT(colors.contains("blackquoise") == false, "blackquoise is not found");

    CONSTEXPR_ASSERT(!multi_colors.unique(), "multi_colors are not unique");
    CONSTEXPR_ASSERT(multi_colors.find("yellow") != multi_colors.end(), "colors contains yellow");
    CONSTEXPR_ASSERT(multi_colors.find("yellow")->second == Color(255, 255, 0, 1), "yellow returns the correct color");
    CONSTEXPR_ASSERT((++multi_colors.find("yellow"))->second == Color(255, 220, 0, 1), "yellow returns the correct color");
    CONSTEXPR_ASSERT(multi_colors.equal_range("white").first == multi_colors.find("white"), "white range returns the correct begin");
    CONSTEXPR_ASSERT(multi_colors.equal_range("white").second == multi_colors.find("yellow"), "white range end is the next color");
    CONSTEXPR_ASSERT(multi_colors.equal_range("yellow").first == multi_colors.find("yellow"), "yellow range returns the correct begin");
    CONSTEXPR_ASSERT(multi_colors.equal_range("yellow").second == multi_colors.end(), "yellow range end returns end");
    CONSTEXPR_ASSERT(multi_colors.count("yellow") == 2, "has 2 yellows");

    CONSTEXPR_ASSERT(hash_colors.size() == 4, "hash_colors has 4 elements");
    CONSTEXPR_ASSERT(!hash_colors.unique(), "hash_colors are not unique");
    CONSTEXPR_ASSERT(hash_colors.find("yellow") != hash_colors.end(), "colors contains yellow");
    CONSTEXPR_ASSERT(hash_colors.find("yellow")->second == Color(255, 255, 0, 1), "yellow returns the correct color");
    CONSTEXPR_ASSERT((++hash_colors.find("yellow"))->second == Color(255, 220, 0, 1), "yellow returns the correct color");
    CONSTEXPR_ASSERT(hash_colors.equal_range("white").first == hash_colors.find("white"), "white range returns the correct begin");
    CONSTEXPR_ASSERT(hash_colors.equal_range("yellow").first == hash_colors.find("yellow"), "yellow range returns the correct begin");
    CONSTEXPR_ASSERT(hash_colors.count("yellow") == 2, "has 2 yellows");

    // Can use range-for
    for (auto& x : colors) {
        (void)x;
    }

    // Can use range-for over equal_range
    for (auto range = multi_colors.equal_range("yellow"); range.first != range.second; ++range.first) {
        (void)range;
    }
}

int main(int argc, char* argv[]) {
#if MAPBOX_ETERNAL_IS_CONSTEXPR
    fprintf(stderr, "using constexpr implementation\n");
#else
    fprintf(stderr, "using non-constexpr implementation\n");
#endif
    test();

    if (argc < 2) {
        fprintf(stderr, "please specify a color name\n");
        exit(1);
    }
    const auto color = colors.find(argv[1]);
    if (color != colors.end()) {
        fprintf(stderr, "%s = (%u, %u, %u, %.2f)\n", argv[1], color->second.r, color->second.g, color->second.b,
                static_cast<double>(color->second.a));
    } else {
        fprintf(stderr, "color could not be found\n");
    }

    return 0;
}
