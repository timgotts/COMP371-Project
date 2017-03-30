#include "Terrain.h"

TerrainChunk::TerrainChunk(int size, int posX, int posY) : size(size), posX(posX), posY(posY)
{
    
    heightMap = new int*[size];
    
    for(int x = 0; x < size; x++)
    {
        heightMap[x] = new int[size];
        
        for(int y = 0; y < size; y++)
        {
            heightMap[x][y] = 0;
        }
    }
    
}

int TerrainChunk::getPosX()
{
    return posX;
}


int TerrainChunk::getPosY()
{
    return posY;
}

Terrain::Terrain(int size) : size(size)
{
    
    chunks = new TerrainChunk**[size];
    
    for(int x = 0; x < size; x++)
    {
        chunks[x] = new TerrainChunk*[size];
        
        for(int y = 0; y < size; y++)
        {
            chunks[x][y] = new TerrainChunk(pointsPerChunk, x, y);
        }
    }
    
}


int Terrain::getSize()
{
    return size;
}

TerrainChunk* Terrain::getChunkAt(int posX, int posY)
{
    if(posX < 0 || posY < 0 || posX >= size || posY >= size)
    {
        return nullptr;
    }
    
    return chunks[posX][posY];
}

int Terrain::getHeightAt(int x, int y)
{
    int chunkX = x % pointsPerChunk;
    int chunkY = y % pointsPerChunk;
    TerrainChunk* chunk;
    if((chunk = getChunkAt(x,y)) != nullptr)
    {
        //TODO return real height
        return 0;
    }
    else
    {
        return 0;
    }
}