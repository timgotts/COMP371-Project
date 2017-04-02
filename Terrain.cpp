#include "Terrain.h"

TerrainChunk::TerrainChunk(int size, int posX, int posY) : size(size), posX(posX), posY(posY)
{
    
    heightMap = new float*[size];
    
    for(int x = 0; x < size; x++)
    {
        heightMap[x] = new float[size];
        
        for(int y = 0; y < size; y++)
        {
            heightMap[x][y] = 0.0f;
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

float TerrainChunk::getHeightAt(int x, int y)
{
    if(x < 0 || y < 0 || x >= size || y >= size)
    {
        return 0;
    }
    
    return heightMap[x][y];
}

void TerrainChunk::setHeightAt(int x, int y, float height)
{
    if(x < 0 || y < 0 || x >= size || y >= size)
    {
        return;
    }
    
    heightMap[x][y] = height;
    
}

void TerrainChunk::render(glm::mat4 vie, glm::mat4 proj)
{
    
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

float Terrain::getHeightAt(int x, int y)
{
    //chunk position
    int chunkX = x % pointsPerChunk;
    int chunkY = y % pointsPerChunk;
    
    TerrainChunk* chunk;
    if((chunk = getChunkAt(x,y)) != nullptr)
    {
        //position relative to the chunk
        int relX = x - chunkX * pointsPerChunk;
        int relY = y - chunkY * pointsPerChunk;
        
        return chunk->getHeightAt(relX, relY);
    }
    else
    {
        return 0;
    }
}

void Terrain::setHeightAt(int x, int y, float  height)
{
    //chunk position
    int chunkX = x % pointsPerChunk;
    int chunkY = y % pointsPerChunk;
    
    TerrainChunk* chunk;
    if((chunk = getChunkAt(x,y)) != nullptr)
    {
        //position relative to the chunk
        int relX = x - chunkX * pointsPerChunk;
        int relY = y - chunkY * pointsPerChunk;
        
        chunk->setHeightAt(relX, relY, height);
    }
    else
    {
        return;
    }
}

