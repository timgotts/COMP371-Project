#pragma once

#include "Renderable.h"

//Terrain Chunk, contains a heightmap
class TerrainChunk : public Renderable
{
    public:
    
    TerrainChunk(int size, int posX, int posY);
    
    int getSize();
    
    float** getHeightMap();
    
    int getPosX();
    
    int getPosY();
    
    float getHeightAt(int x, int y);
    void setHeightAt(int x, int y, float height);
    
    void render(glm::mat4 view, glm::mat4 proj);
    
    private:
    //width and height of chunk
    const int size;
    
    //chunk position
    const int posX, posY;
    
    //heightmap grid
    float** heightMap;
    
    
    
};

class Terrain
{
    public:
    Terrain(int size);
    
    int getSize();
    
    //gets chunk at position, returns null pointer if out of bounds
    TerrainChunk* getChunkAt(int posX, int posY);
    
    float getHeightAt(int x, int y);
    void setHeightAt(int x,int y,  float  height);
    
    
    private:
    
    //number of chunks on x,y
    const int size;
    
    const int pointsPerChunk = 9;
    
    //chunk grid
    TerrainChunk*** chunks;
    
};

