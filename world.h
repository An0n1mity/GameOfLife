//
// Created by an0n1mity on 27/06/2021.
//

#ifndef CELLULARAUTOMATA_WORLD_H
#define CELLULARAUTOMATA_WORLD_H

#include "headers.h"
#include "structures.h"
#include "SDL2/SDL.h"

void DrawWorld(World* world, SDL_Renderer* renderer);
World* CreateWorld(int width, int height);
void MakeAlive(World* world, int mouse_x, int mouse_y);
void UpdateWorld(World* world);
void RandomizeWorld(World* world);

#endif //CELLULARAUTOMATA_WORLD_H
