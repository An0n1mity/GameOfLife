//
// Created by an0n1mity on 27/06/2021.
//

#include "headers.h"

void DrawCells(World* world, SDL_Renderer* renderer)
{
    for (int i = 0; i < world->height; ++i) {
        for (int j = 0; j < world->width; ++j) {
            if(world->array[i][j].flag){
                if(world->array[i][j].alive)
                    SDL_SetRenderDrawColor(renderer, 255, 255, 255, SDL_ALPHA_OPAQUE);
                else
                    SDL_SetRenderDrawColor(renderer, 0, 0, 0, SDL_ALPHA_OPAQUE);
                SDL_RenderFillRect(renderer, &world->array[i][j].shape);
            }
            world->array[i][j].flag = false;
        }
    }
}

void DrawCell(Cells* cell, SDL_Renderer* renderer)
{
    SDL_SetRenderDrawColor(renderer, 255, 255, 255, SDL_ALPHA_OPAQUE);
    SDL_RenderFillRect(renderer, &cell->shape);
}

void DrawNeighbors(World* world, SDL_Renderer* renderer)
{
    SDL_SetRenderDrawColor(renderer, 255, 0, 0, SDL_ALPHA_OPAQUE);
    for (int i = 0; i < world->height; ++i) {
        for (int j = 0; j < world->width; ++j) {
            if(world->array[i][j].alive)
                for (int k = 0; k < 9; ++k) {
                    if(world->array[i][j].neighbors[k])
                        SDL_RenderFillRect(renderer, &world->array[i][j].neighbors[k]->shape);
                }
        }
    }
}

void DetectNeighbors(World* world)
{
    int idx = 0;
    for (int y = 0; y < world->height; ++y) {
        for (int x = 0; x < world->width; ++x) {
            idx = 0;
            for (int i = y-1; i <= y+1; ++i) {
                for (int j = x-1; j <= x+1; ++j) {
                    if((i >= 0 && i < world->height) && (j >= 0 && j < world->width) && (!((i == y) && (j == x))) && (world->array[i][j].alive))
                        world->array[y][x].neighbors[idx] = &world->array[i][j];
                    idx++;
                }
            }
        }
    }
}
