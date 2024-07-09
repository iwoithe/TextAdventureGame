#ifndef GLOBAL_ALGORITHMS_H
#define GLOBAL_ALGORITHMS_H

#include <vector>

template<typename T>
int binarySearch(std::vector<T> items, T key)
{
    // Only works on sorted lists
    int l = 0;
    int r = items.size() - 1;

    while (l <= r) {
        int m = (int)((l + r) / 2);
        if (items[m] == key) {
            return m;
        }

        if (items[m] < key) {
            l = m + 1;
        }

        if (items[m] > key) {
            r = m - 1;
        }
    }

    return -1;
}

template<typename A, typename B>
int binarySearch(std::vector<A> items, B key)
{
    // Only works on sorted lists
    int l = 0;
    int r = items.size() - 1;

    while (l <= r) {
        int m = (int)((l + r) / 2);
        if (items[m] == key) {
            return m;
        }

        if (items[m] < key) {
            l = m + 1;
        }

        if (items[m] > key) {
            r = m - 1;
        }
    }

    return -1;
}

#endif // GLOBAL_ALGORITHMS_H
