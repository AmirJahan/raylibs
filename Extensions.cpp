#include "Extensions.h"

#include <raylib.h>
#include <raymath.h>
#include <string>
#include <math.h>
#include <tuple>

#include <stdlib.h> // rand
#include <algorithm>

#include <iostream>
#include <ostream>

using namespace std;

Color RandomColor(void)
{
    int r = 50;


        // return a random Color
        return CLITERAL(Color) {
            static_cast<unsigned char> (rand() % 255), 
            static_cast<unsigned char> (rand() % 255),
            static_cast<unsigned char>(rand() % 255),
            255 };
    
}
