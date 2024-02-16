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


    Tile* tile_1 = nullptr;
    Tile* tile_2 = nullptr;

    bool gameOver = false;

    int gridSize = 6;
   


    bool compareMode = false; 

    // used to calculate the time for compare
    float timeOfSecondClick = -1.0;

    bool canClick = true;






    void Main();
    void Start();
    void EvalCurFrame();



    void DrawCurFrame();
    void Update();
};

#endif 
