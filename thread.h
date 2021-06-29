#ifndef THREAD_H
#define THREAD_H

#include "structures.h"

extern World* world;
extern bool thread;

void* AcessWorld();
void RandomCells(World* world);

#endif
