#pragma once

#include <inttypes.h>
#include "Config.h"

struct Vec2
{
    int16_t x;
    int16_t y;

    bool operator == (const Vec2& other) const 
    {
        return  x == other.x && y == other.y;
    }
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
    CellStoreRaw map[MAZE_MEM_SIZE];

public:
    Maze()
    {
        for (int i = 0; i < MAZE_MEM_SIZE; i++)
        {
            map[i].lodown = UNKNOWN;
            map[i].loright = UNKNOWN;
            map[i].hidown = UNKNOWN;
            map[i].hiright = UNKNOWN;
        }
        for(int x = 0; x < MAZE_WIDTH; x++)
        {
            CellWalls cell = {.left = UNKNOWN, .down = WALL, .up = UNKNOWN, .right = UNKNOWN};
            Vec2 coord = {x, MAZE_HEIGHT - 1};
            setWall(coord, cell);
        }
        for(int y = 0; y < MAZE_HEIGHT; y++)
        {
            CellWalls cell = {.left = UNKNOWN, .down = UNKNOWN, .up = UNKNOWN, .right = WALL};
            Vec2 coord = {MAZE_WIDTH - 1, y};
            setWall(coord, cell);
        }
    }
    void setWall(Vec2 coord, CellWalls cell_walls)
    {
        int cell_id = coord.y * MAZE_WIDTH / 2 + coord.x / 2;
        int cell_offset = coord.x % 2;

        if (cell_offset == LO)
        {
            SET_WALL(map[cell_id].lodown, cell_walls.down);
            SET_WALL(map[cell_id].loright, cell_walls.right);
            SET_WALL(map[cell_id].hiright, cell_walls.left);
            if (cell_id >= MAZE_WIDTH / 2)
            {
                SET_WALL(map[cell_id - MAZE_WIDTH / 2].lodown, cell_walls.up);
            }
        }
        else
        {
            SET_WALL(map[cell_id].hidown, cell_walls.down);
            SET_WALL(map[cell_id].hiright, cell_walls.right);

            if (cell_id % (MAZE_WIDTH / 2) != 0)
            {
                SET_WALL(map[cell_id - 1].loright, cell_walls.left);
            }
            if (cell_id >= MAZE_WIDTH / 2)
            {
                SET_WALL(map[cell_id - MAZE_WIDTH / 2].hidown, cell_walls.up);
            }
        }
    }
    WallState getUpWall(int cell_id, int cell_offset)
    {
        if (cell_id >= MAZE_WIDTH / 2)
        {
            if (cell_offset == LO)
            {
                return map[cell_id - MAZE_WIDTH / 2].lodown;
            }
            return map[cell_id - MAZE_WIDTH / 2].hidown;
        }
        return WALL;
    }
    WallState getLeftWall(int cell_id, int cell_offset)
    {
        if (cell_offset == LO)
        {
            return map[cell_id].hiright;
        }

        if (cell_id % (MAZE_WIDTH / 2) == 0)
        {
            return WALL;
        }

        return map[cell_id - 1].loright;
    }

    WallState getDownWall(int cell_id, int cell_offset)
    {
        if (cell_offset == LO)
        {
            return map[cell_id].lodown;
        }
        return map[cell_id].hidown;
    }

    WallState getRightWall(int cell_id, int cell_offset)
    {
        if (cell_offset == LO)
        {
            return map[cell_id].loright;
        }
        return map[cell_id].hiright;
    }
  
    CellWalls getWalls(Vec2 coord)
    {
        int cell_id = coord.y * MAZE_WIDTH / 2 + coord.x / 2;
        int cell_offset = coord.x % 2;

        CellWalls cell =
        {
            .left  = getLeftWall(cell_id, cell_offset),
            .down  = getDownWall(cell_id, cell_offset),
            .up    = getUpWall(cell_id, cell_offset),
            .right = getRightWall(cell_id, cell_offset)
        };

        return cell;
    }
};