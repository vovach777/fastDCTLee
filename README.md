# fastDCTLee

## resize by DCT sample 8x8 -> 32x32
```
#include <iostream>
#include <iomanip>
#include <algorithm>
#include "dct.hpp"

int main() {

    float inout[32][32]{};
    inout[0][0] = 10;
    inout[0][7] = 10;
    inout[7][0] = 10;
    inout[7][7] = 10;
    inout[4][4] = 10;




    for (int y = 0; y < 8; ++y, std::cout << std::endl)
    for (int x = 0; x < 8; ++x)
    {
        std::cout << std::fixed << std::setprecision(1) << std::setw(5) << inout[y][x];
    }
    std::cout << std::endl;

    DCT2D<float,float>([&](int x, int y) -> float& {
        return inout[y][x];
    },8,8);


    iDCT2D<float,float>([&](int x, int y) -> float& {
        return inout[y][x];
    },32,32);

    for (int y = 0; y < 32; ++y, std::cout << std::endl)
    for (int x = 0; x < 32; ++x)
    {
        std::cout << std::fixed << std::setprecision(1) << std::setw(5) << inout[y][x];
    }
    std::cout << std::endl;

}```
