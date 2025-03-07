#include <Arduino.h>

#include "Config.h"
#include "VelEstimator.h"
#include "Devices.h"
#include "Encoder.h"
#include "odometry.h"
#include "Battery.h"
#include "Motor.h"
#include "Switch.h"
#include "ASMR.h"
#include "Maze.h"
#include "MazeDrawer.h"
#include "Solver.h"

ASMR asmr;
Battery volts;
Maze maze;

void mazeTestCreate()
{
  maze.setWall(Vec2{1, 1}, Maze::CellWalls{.left = Maze::OPEN, .down = Maze::OPEN, .up = Maze::OPEN, .right = Maze::OPEN});
  maze.setWall(Vec2{3, 1}, Maze::CellWalls{.left = Maze::WALL, .down = Maze::WALL, .up = Maze::WALL, .right = Maze::WALL});
  maze.setWall(Vec2{1, 2}, Maze::CellWalls{.left = Maze::WALL, .down = Maze::WALL, .up = Maze::WALL, .right = Maze::WALL});
  maze.setWall(Vec2{2, 3}, Maze::CellWalls{.left = Maze::OPEN, .down = Maze::OPEN, .up = Maze::OPEN, .right = Maze::OPEN});
  maze.setWall(Vec2{4, 3}, Maze::CellWalls{.left = Maze::WALL, .down = Maze::WALL, .up = Maze::WALL, .right = Maze::WALL});

  Serial.println();

  drawMaze(maze, MAZE_WIDTH, MAZE_HEIGHT);
}

void solverVerifity()
{
  Solver solver;
  Vec2 start = {1,0};
  Vec2 end = {2,3};

  solver.findPath(start, end, &maze);

  Serial.println();
  drawMaze(maze, solver, MAZE_WIDTH, MAZE_HEIGHT);

}

void setup()
{
  ///////// INIT /////////
  Serial.begin(9600);
  mazeTestCreate();
  solverVerifity();
  while (1)
  {
  }
}

void loop()
{
  ///////// TIMER /////////
  // Задание постоянной частоты главного цикла прогааммы
  static uint32_t timer = micros();
  while (micros() - timer < Ts_us)
    ;
  timer = micros();

  ///////// SENSE /////////
  // Считывание датчиков
  leftEncoder.tick();
  rightEncoder.tick();

  ///////// PLAN /////////
  // Расчет управляющих воздействий
  coordinat();
  deltmath();
  decodeFunctionSwitch();
  volt.getBatteryVolts();

  ///////// ACT /////////
  asmr.exec();
}