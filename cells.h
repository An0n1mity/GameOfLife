//
// Created by an0n1mity on 27/06/2021.
//

#ifndef CELLULARAUTOMATA_CELLS_H
#define CELLULARAUTOMATA_CELLS_H

#include <stdbool.h>
#include <SDL2/SDL.h>
#include "structures.h"

void RandomCells(World* world);
void DrawCells(World* world, SDL_Renderer* renderer);
void DrawNeighbors(World* world, SDL_Renderer* renderer);
void DetectNeighbors(World* world);
void DrawCell(Cells* cell, SDL_Renderer* renderer);
#endif //CELLULARAUTOMATA_CELLS_H
