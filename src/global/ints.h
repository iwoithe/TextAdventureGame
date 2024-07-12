#ifndef GLOBAL_INTS_H
#define GLOBAL_INTS_H

int concatenateInts(int i, int j) {
    return (i * 10) + j;
}

template <class T>
int numDigitsInNum(T number)
{
    int digits = 0;
    if (number < 0) {
        digits = 1;
    }

    while (number) {
        number /= 10;
        digits++;
    }

    return digits;
}

#endif // GLOBAL_INTS_H
