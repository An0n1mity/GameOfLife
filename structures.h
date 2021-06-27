//
// Created by an0n1mity on 27/06/2021.
//

#ifndef CELLULARAUTOMATA_STRUCTURES_H
#define CELLULARAUTOMATA_STRUCTURES_H

typedef struct Cells{
    //Current state of the cell : Alive or dead
    bool alive;
    bool flag;
    //Right next neighbors of the cell
    struct Cells** neighbors;
    //The shape of the cell
    SDL_Rect shape;
}Cells;

typedef struct World{
    //Number of cells in a row
    int width;
    //Number of cells in a column
    int height;
    //The cells
    Cells** array;
}World;

#endif //CELLULARAUTOMATA_STRUCTURES_H
