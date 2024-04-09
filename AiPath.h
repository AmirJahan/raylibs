#include <raylib.h>
#include <vector>

#include <string>

#ifndef AIPATH_H
#define AIPATH_H

using namespace std;

class AiPath
{
public:
#define ROWS 10
#define COLS 20

    // no border gap. perfect fit

    typedef struct Tile
    {
        int row, col;
        Vector2 position;
        Color fillColor, outlineColor;
        bool blocked = false;

        void Draw()
        {
            if (blocked)
                DrawRectangleV(position, Vector2{ 50, 50 }, fillColor);
            else
                DrawRectangleLines(position.x, position.y, 50, 50, outlineColor);
        }


        // Constructor for convenience
        Tile(int row = 0,
             int col = 0,
             Vector2 position = {},
             Color fillColor = BLACK,
             Color outlineColor = BLACK,
             bool blocked = false) : row(row), col(col), position(position), fillColor(fillColor), outlineColor(outlineColor), blocked(blocked)
        {
        }


        // A*
        float gCost = FLT_MAX; // ground cost from the start node to the current node,
        float hCost = FLT_MAX; // heuristic estimated cost from the current node to the end node
        float fCost = FLT_MAX; // final total cost (gCost + hCost)

        Tile* parent = nullptr;
        bool inOpenSet = false; // Add this flag to your Tile structure


    } Tile;



    vector<vector<Tile>> tiles;
    Tile src, dest;



    void Main();
    void Start();
    void Update();
    void MakeIntGrid();




    // A*

    // Path found, reconstruct and return
    vector<Tile*> tracedPath;
    vector<Tile*> visualPath; // just for demonstration

    float Heuristic(Tile* a, Tile* b);

    void AStarSearch(Tile* start, Tile* goal);

    vector<Tile*> GetNeighbors(Tile* tile);
};

#endif