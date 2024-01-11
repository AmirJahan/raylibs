#pragma once

#include "raylib.h"
#include <vector>
#include <string>

#include "tile.h"



#ifndef MEMORY_H
#define MEMORY_H



class Memory 
{

public:
#define GAP 8
#define WAIT_TIME 0.5


    static const int screenWidth = 1280;
    static const int screenHeight = 720;

    // array of tiles
    std::vector<Tile> tilesArr;
    std::vector<int> numbers;


    int tile_1_index = -1;
    int tile_2_index = -1;
    bool gameOver = false;

    int gridSize = 4;
   


    bool compareMode = false; // this might seem redundant, but a good idea
    float timeOfSecondClick = -1.0;

    bool canClick = true;






    void Main();
    void Start();
    void EvalCurFrame();
    void DrawCurFrame();
    void Update();




};

#endif 
