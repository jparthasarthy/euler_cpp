#include "Question17.h"

i64 Question17::Solve() {

    const std::string dig_str = "onetwothreefourfivesixseveneightnine";
    const std::string teen_str = "teneleventwelvethirteenfourteenfifteensixteenseventeeneighteennineteen";
    const std::string tens_str = "twentythirtyfortyfiftysixtyseventyeightyninety";
    const std::string prefix_str = "onetwothreefourfivesixseveneightnine";

    int count = 0;

    count += dig_str.length() * 9 * 10;
    count += teen_str.length() * 10;
    count += tens_str.length() * 10 * 10;
    count += prefix_str.length() * 10 * 10; // count 100s prefix

    count += 7 * 100 * 9; // count 100s
    count += 3 * 9 * 99; // count ands

    count += 3 + 8;

    return count;
}
