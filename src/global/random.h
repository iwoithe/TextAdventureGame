#ifndef GLOBAL_RANDOM_H
#define GLOBAL_RANDOM_H

#include <cstdlib>

inline int randRange(int lowerLimit, int upperLimit)
{
    if (lowerLimit == upperLimit) {
        return lowerLimit;
    }

    return rand() % (upperLimit - lowerLimit) + lowerLimit;
}

#endif // GLOBAL_RANDOM_H
