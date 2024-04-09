#include "AiPath.h"
#include <queue>
#include <unordered_map>
#include <vector>
#include <functional>

using namespace std;


// isTileAt function for comparing is a tile is at a position of another one
bool isTileAt(AiPath::Tile* a, AiPath::Tile* b)
{
    return a->row == b->row && a->col == b->col;
}

// compare two tiles for equalit based on their col and row values
bool operator==(const AiPath::Tile& a, const AiPath::Tile& b)
{
    return a.row == b.row && a.col == b.col;
}

void AiPath::AStarSearch(Tile* start, Tile* goal)
{
    /*
    a lambda for comparing two Tile* based on their fCost and, if those are equal, their hCost.
    This is a good approach for ensuring that the tile with the lowest cost is prioritized*/
    // the return here is a boolean
    auto Compare = [](Tile* a, Tile* b)
    {
        return a->fCost > b->fCost || (a->fCost == b->fCost && a->hCost > b->hCost);
    };

    //  The decltype(Compare) part specifies the type of the comparison function to use for ordering the elements in the queue
    priority_queue<Tile*, vector<Tile*>, decltype(Compare)> openSet(Compare);
    //  The Compare function is passed as an argument to the priority_queue constructor to initialize the queue with this custom ordering logic.
    // It doesn't store elements as key-value pairs and doesn't provide direct access to elements other than the one at the top.


    //  keep track of the path from start to goal
    // un -ordered, because we use the relationship between tiles and their parents
    unordered_map<Tile*, Tile*> cameFrom;

    //  keep track of the cost of the cheapest path from start to each node,
    //  initialized to infinity for all nodes initially
    unordered_map<Tile*, float> gScore;

    // Initialize gScore for all tiles
    for (auto& row : tiles)
        for (auto& tile : row)
            gScore[&tile] = INFINITY;



    gScore[start] = 0;
    start->hCost = Heuristic(start, goal);
    start->fCost = start->hCost;
    start->inOpenSet = true; // Set flag

    openSet.push(start);


    while (!openSet.empty())
    {
        Tile* current = openSet.top();
        openSet.pop();
        current->inOpenSet = false; // Clear flag since it's being processed

        // if (current->col == goal->col && current->row == goal->row) // if (current
        if (isTileAt(current, goal)) // if (current
        {
            // Path found, reconstruct and return
            while (current != start)
            {
                tracedPath.push_back(current);
                current = cameFrom[current];
            }
            tracedPath.push_back(start);
            std::reverse(tracedPath.begin(), tracedPath.end());
            // Use path for your purpose

            return;
        }

        visualPath.push_back(current); // just for demonstration

        vector<Tile*> neighbors = GetNeighbors(current);
        for (Tile* neighbor : neighbors)
        {
            float tentative_gScore = gScore[current] + 1; // assuming a uniform cost of 1 for moving from the current tile to the neighbor
            if (tentative_gScore < gScore[neighbor]) // a cheaper path to this neighbor has been found
            {
                cameFrom[neighbor] = current; // the best path to this neighbor (so far) comes through the current tile
                gScore[neighbor] = tentative_gScore;
                neighbor->hCost = Heuristic(neighbor, goal);
                neighbor->fCost = gScore[neighbor] + neighbor->hCost;

                if (!neighbor->inOpenSet) //  it hasn't yet been queued for exploration
                {
                    neighbor->inOpenSet = true; // Set flag
                    openSet.push(neighbor);
                }
            }
        }
    }
}

vector<AiPath::Tile*> AiPath::GetNeighbors(Tile* tile)
{
    vector<Tile*> neighbors;

    // Helper lambda to check if a given position is within the grid and the tile is not blocked
    auto isValidAndNotBlocked = [&](int row, int col) -> bool
    {
        return  row >= 0 &&
            row < (int)(tiles.size()) &&
            col >= 0 &&
            col < (int)(tiles[0].size()) &&
            !tiles[row][col].blocked;
    };

    // Check North
    if (isValidAndNotBlocked(tile->row - 1, tile->col))
    {
        neighbors.push_back(&tiles[tile->row - 1][tile->col]);
    }

    // Check South
    if (isValidAndNotBlocked(tile->row + 1, tile->col))
    {
        neighbors.push_back(&tiles[tile->row + 1][tile->col]);
    }

    // Check East
    if (isValidAndNotBlocked(tile->row, tile->col + 1))
    {
        neighbors.push_back(&tiles[tile->row][tile->col + 1]);
    }

    // Check West
    if (isValidAndNotBlocked(tile->row, tile->col - 1))
    {
        neighbors.push_back(&tiles[tile->row][tile->col - 1]);
    }

    return neighbors;
}

// The heuristic function estimates the cost to reach the goal from a specific tile.
// Since you're only moving horizontally and vertically, you can use Manhattan distance:
float AiPath::Heuristic(Tile* a, Tile* b)
{
    return abs(a->row - b->row) + abs(a->col - b->col);
}





void AiPath::Main()
{
    InitWindow(1000, 500, "classic game: snake");

    Start();

    SetTargetFPS(120);
    while (!WindowShouldClose())
    {
        BeginDrawing();
        ClearBackground(RAYWHITE);

        Update();

        EndDrawing();
    }

    CloseWindow();
}

void AiPath::Start()
{

    // find all squares
    // Draw grid lines
    tiles.clear();
    for (int row = 0; row < ROWS; row++)
    {
        float y = 50 * row;

        vector<Tile> rowTiles;
        for (int col = 0; col < COLS; col++)
        {
            float x = 50 * col;

            Tile tile = { row, col, Vector2{x, y}, DARKGRAY, DARKGRAY };

            rowTiles.push_back(tile);
        }

        tiles.push_back(rowTiles);
    }

    // take 20 from sqaures randomly and put in blocks
    for (int i = 0; i < 20; i++)
    {
        int randRow = GetRandomValue(0, (int)(tiles.size()) - 1);
        int randCol = GetRandomValue(0, (int)(tiles[randRow].size()) - 1);
        tiles[randRow][randCol].blocked = true;
    }

    // choose a random home and dest from squares
    int randRow = GetRandomValue(0, (int)(tiles.size()) - 1);
    int randCol = GetRandomValue(0, (int)(tiles[randRow].size()) - 1);
    src = tiles[randRow][randCol];
    src.fillColor = GREEN;
    src.blocked = true; // this just so the color renders

    randRow = GetRandomValue(0, (int)(tiles.size()) - 1);
    randCol = GetRandomValue(0, (int)(tiles[randRow].size()) - 1);
    dest = tiles[randRow][randCol];
    dest.fillColor = BLUE;
    dest.blocked = true; // this just so the color renders

    // calculate the path between home and dest
    // use A* algorithm
    // https://en.wikipedia.org/wiki/A*_search_algorithm

    // A* code for home to target
    // https://www.geeksforgeeks.org/a-search-algorithm/

    AStarSearch(&src, &dest);
}

void AiPath::Update()
{
    for (int i = 0; i < (int)(tiles.size()); i++)
        for (int j = 0; j < (int)(tiles[i].size()); j++)
            tiles[i][j].Draw();

    // draw home and dest
    src.Draw();
    dest.Draw();


    for (Tile* tile : tracedPath)
        DrawRectangleV(tile->position, Vector2{ 50, 50 }, Color{ 255, 255, 0, 100 });

    // for (Tile* tile : demoPath)
    //     DrawRectangleV(tile->position, Vector2{50, 50}, Color{255, 255, 255, 100});
}
