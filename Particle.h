#include <raylib.h>

#include <vector>

#include <math.h>

#include <iostream>
#include <ostream>
// update the center of the circle
#include <algorithm>

#include "Extensions.h"

// test.h
#ifndef PARTICLES_H
#define PARTICLES_H






class Particle
{
public:

    std::vector<Circle> circles;

    void Main();
    void Start();
    void EvalCurFrame();
    void DrawCurFrame();
    void Update();




};

#endif
