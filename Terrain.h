#pragma once

#include "Renderable.h"

//Terrain Chunk, contains a heightmap
class TerrainChunk
{
    public:
    
    TerrainChunk(int size, int posX, int posY);
    
    int getSize();
    
    int** getHeightMap();
    
    int getPosX();
    
    int getPosY();
    
    private:
    //width and height of chunk
    const int size;
    
    //chunk position
    const int posX, posY;
    
    //heightmap grid
    int** heightMap;
    
    
    
};

class Terrain : public Renderable
{
    public:
    Terrain(int size);
    
    int getSize();
    
    //gets chunk at position, returns null pointer if out of bounds
    TerrainChunk* getChunkAt(int posX, int posY);
    
    int getHeightAt(int x, int y);
    
    private:
    
    //number of chunks on x,y
    const int size;
    
    const int pointsPerChunk = 9;
    
    //chunk grid
    TerrainChunk*** chunks;
    
};

