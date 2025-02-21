#pragma once

#include <inttypes.h>
#include "Config.h"

#define MAZE_WIDTH 8


struct Vec2
{
    int16_t x;
    int16_t y;
};

class Maze
{
public:
enum WallState
{
    UNKNOWN,
    WALL,
    OPEN
};
struct CellWalls
{
    WallState left : 2;
    WallState down : 2;
    WallState up : 2;
    WallState right : 2;
};

private:
struct CellStoreRaw
{
    WallState hidown : 2;
    WallState hiright : 2;
    WallState lodown : 2;
    WallState loright : 2;
};
enum LoHi
{
    LO = 1,
    HI = 0
};
CellWalls getWalls(Vec2 coord){

}

};