#pragma once

#include "Renderable.h"
#include "TerrainGenerator.h"
#include "Config.h"
#include "Seaweed.h"
#include <GL\glew.h>
#include <GLM\glm.hpp>
#include <GLM\gtc\matrix_transform.hpp>
#include <GLM\gtc\type_ptr.hpp>

//Terrain Chunk, contains a heightmap
class TerrainChunk : public Renderable
{
    public:
    
    TerrainChunk(int size, int posX, int posY, float offset, PerlinNoiseGenerator* pn);
    
    int getSize();
    
    float** getHeightMap();
    
    int getPosX();
    
    int getPosY();
    
    std::vector<Renderable*>& getEntities()
    {
        return entities;
    }
    
    float getHeightAt(int x, int y);
    void setHeightAt(int x, int y, float height);
    
    void render(glm::mat4 view, glm::mat4 proj);
    
    private:
    //width and height of chunk
    const int size;
    
    std::vector<Renderable*> entities;;
    
    //chunk position
    const int posX, posY;
    
    //heightmap grid
    float** heightMap;
    
    
    
};

class Terrain
{
    public:
    Terrain();
    
    
    void render(glm::vec3 position, glm::mat4 view, glm::mat4 proj);
    
    
    int getSize();
    
    int getPointsPerChunk();
    
    //gets chunk at position, returns null pointer if out of bounds
    TerrainChunk* getChunkAt(int posX, int posY);
    
    TerrainChunk* getChunkAtReal(int posX, int posY);
    
    float getHeightAt(int x, int y);
    void setHeightAt(int x,int y,  float  height);
    
    
    private:
    
    //number of chunks on x,y
    int size;
    
    int renderDistance;
    
    int pointsPerChunk;
    
    //chunk grid
    TerrainChunk*** chunks;
    
};

