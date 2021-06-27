//
// Created by an0n1mity on 27/06/2021.
//

#include "headers.h"

void DrawWorld(World* world, SDL_Renderer* renderer)
{
    SDL_SetRenderDrawColor(renderer, 255, 255, 255, SDL_ALPHA_OPAQUE);
    for (int i = 0; i < world->height; ++i) {
        for (int j = 0; j < world->width; ++j) {
            SDL_RenderDrawRect(renderer, &world->array[i][j].shape);
        }
    }
}

World* CreateWorld(int width, int height)
{
    World* world = (World*)malloc(sizeof(World));
    world->width = width;
    world->height = height;
    world->array = (Cells**)malloc(height*sizeof(Cells*));
    for (int i = 0; i < height; ++i) {
        world->array[i] = (Cells*)malloc(width * sizeof(Cells));
    }

    for (int i = 0; i < height; ++i) {
        for (int j = 0; j < width; ++j) {
            world->array[i][j].flag = false;
            world->array[i][j].alive = false;
            world->array[i][j].shape.h = 10;
            world->array[i][j].shape.w = 10;
            world->array[i][j].shape.x = j * 10;
            world->array[i][j].shape.y = i * 10;
            world->array[i][j].neighbors = (Cells**)malloc(9*sizeof(Cells*));
            for (int k = 0; k < 9; ++k) {
                world->array[i][j].neighbors[k] = NULL;
            }
        }
    }
    return world;
}

void RandomizeWorld(World* world)
{
    for (int i = 0; i < world->height; ++i) {
        for (int j = 0; j < world->width; ++j) {
            if(rand()%2)
                world->array[i][j].alive = true ;
        }
    }
}

//Alive the cell that was clicked
void MakeAlive(World* world, int mouse_x, int mouse_y)
{
    world->array[mouse_y/10][mouse_x/10].alive = true;
}

void UpdateWorld(World* world)
{
    int nb_neighbors;
    for (int i = 0; i < world->height; ++i) {
        for (int j = 0; j < world->width; ++j) {

            nb_neighbors = 0;

            //Count the number of neighbors
            for (int k = 0; k < 9; ++k) {
                if(world->array[i][j].neighbors[k])
                    if(world->array[i][j].neighbors[k]->alive)
                        nb_neighbors++;
            }
            if(world->array[i][j].alive && (nb_neighbors < 2 || nb_neighbors > 3))
                world->array[i][j].flag = true;
            if(!(world->array[i][j].alive) && nb_neighbors == 3)
                world->array[i][j].flag = true;
        }
    }

    for (int i = 0; i < world->height; ++i) {
        for (int j = 0; j < world->width; ++j) {
            if (world->array[i][j].flag){
                if(world->array[i][j].alive)
                    world->array[i][j].alive = false;
                else
                    world->array[i][j].alive = true;
            }
        }
    }
}