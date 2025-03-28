#pragma once

#include <Arduino.h>
#include "Maze.h"

#define ICON_WALL_VERTICAL "|"
#define ICON_WALL_HORIZONTAL "---"
#define ICON_UNKNOWN_HORIZONTAL " . "
#define ICON_UNKNOWN_VERTICAL "."
#define ICON_OPEN_HORIZONTAL "   "
#define ICON_OPEN_VERTICAL " "

void drawMaze(Maze &maze, int width, int height)
{
    for (int y = 0; y < height; y++)
    {
        for (int x = 0; x < width; x++)
        {
            Maze::CellWalls cell = maze.getWalls(Vec2{x, y});
            Serial.print("+");
            if (cell.up == Maze::WALL)
            {
                Serial.print(ICON_WALL_HORIZONTAL);
            }
            else if (cell.up == Maze::UNKNOWN)
            {
                Serial.print(ICON_UNKNOWN_HORIZONTAL);
            }
            else
            {
                Serial.print(ICON_OPEN_HORIZONTAL);
            }
        }
        Serial.println("+");


        for (int x = 0; x < width; x++)
        {
            Maze::CellWalls cell = maze.getWalls(Vec2{x, y});
            if (cell.left == Maze::WALL)
            {
                Serial.print(ICON_WALL_VERTICAL);
            }
            else if (cell.left == Maze::UNKNOWN)
            {
                Serial.print(ICON_UNKNOWN_VERTICAL);
            }
            else
            {
                Serial.print(ICON_OPEN_VERTICAL);
            }
            Serial.print(ICON_OPEN_HORIZONTAL); 
        }
       
        Maze::CellWalls lastCell = maze.getWalls(Vec2{width - 1, y});
        if (lastCell.right == Maze::WALL)
        {
            Serial.println(ICON_WALL_VERTICAL);
        }
        // else if (lastCell.right == Maze::UNKNOWN)
        // {
        //     Serial.println(ICON_UNKNOWN_VERTICAL);
        // }
        else
        {
            Serial.println(ICON_OPEN_VERTICAL);
        }
        
    }

  
    for (int x = 0; x < width; x++)
    {
        Maze::CellWalls cell = maze.getWalls(Vec2{x, height - 1});
        Serial.print("+");
        if (cell.down == Maze::WALL)
        {
            Serial.print(ICON_WALL_HORIZONTAL);
        }
        else if (cell.down == Maze::UNKNOWN)
        {
            Serial.print(ICON_UNKNOWN_HORIZONTAL);
        }
        else
        {
            Serial.print(ICON_OPEN_HORIZONTAL);
        }
    }
    Serial.println("+");
}

#include "Solver.h"


void drawMaze(Maze &maze, Solver &solver, int width, int height)
{
    
    for (int y = 0; y < height; y++)
    {
       
        for (int x = 0; x < width; x++)
        {
            Maze::CellWalls cell = maze.getWalls(Vec2{x, y});
            Serial.print("+");
            if (cell.up == Maze::WALL)
            {
                Serial.print(ICON_WALL_HORIZONTAL);
            }
            else if (cell.up == Maze::UNKNOWN)
            {
                Serial.print(ICON_UNKNOWN_HORIZONTAL);
            }
            else
            {
                Serial.print(ICON_OPEN_HORIZONTAL);
            }
        }
        Serial.println("+");

        
        for (int x = 0; x < width; x++)
        {
            Maze::CellWalls cell = maze.getWalls(Vec2{x, y});
            if (cell.left == Maze::WALL)
            {
                Serial.print(ICON_WALL_VERTICAL);
            }
            else if (cell.left == Maze::UNKNOWN)
            {
                Serial.print(ICON_UNKNOWN_VERTICAL);
            }
            else
            {
                Serial.print(ICON_OPEN_VERTICAL);
            }
            Serial.print(" ");
            Serial.print(solver.getWhereFrom(Vec2{x, y})); 
            Serial.print(" ");
        }
       
        Maze::CellWalls lastCell = maze.getWalls(Vec2{width - 1, y});
        if (lastCell.right == Maze::WALL)
        {
            Serial.println(ICON_WALL_VERTICAL);
        }
        else if (lastCell.right == Maze::UNKNOWN)
        {
            Serial.println(ICON_UNKNOWN_VERTICAL);
        }
        else
        {
            Serial.println(ICON_OPEN_VERTICAL);
        }
    }

   
    for (int x = 0; x < width; x++)
    {
        Maze::CellWalls cell = maze.getWalls(Vec2{x, height - 1});
        Serial.print("+");
        if (cell.down == Maze::WALL)
        {
            Serial.print(ICON_WALL_HORIZONTAL);
        }
        else if (cell.down == Maze::UNKNOWN)
        {
            Serial.print(ICON_UNKNOWN_HORIZONTAL);
        }
        else
        {
            Serial.print(ICON_OPEN_HORIZONTAL);
        }
    }
    Serial.println("+");
}