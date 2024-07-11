#include <cstdlib>

int randRange(int lowerLimit, int upperLimit)
{
    return rand() % (upperLimit - lowerLimit) + lowerLimit;
}
