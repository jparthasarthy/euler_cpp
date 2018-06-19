#include "Question14.h"

i64 Question14::Solve() {

    int longest_count = 0;
    i64 longest_starting = 1;

    for (i64 i = 1; i < 1000000; i += 2) {
        i64 j = i;
        int count = 0;

        while (j > 1) {
            j = (j % 2 == 0) ? j / 2 : 3 * j + 1;
            count++;
        }

        if (count > longest_count) {
            longest_count = count;
            longest_starting = i;
        }
    }

    return longest_starting;
}
