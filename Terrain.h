#pragma once

#include "Renderable.h"
#include "TerrainGenerator.h"
#include "Config.h"
#include "Seaweed.h"
#include "Rock.h"
#include <GL\glew.h>
#include <GLM\glm.hpp>
#include <GLM\gtc\matrix_transform.hpp>
#include <GLM\gtc\type_ptr.hpp>

//Terrain Chunk, contains a heightmap and entity list
class TerrainChunk : public Renderable
{
    public:
    //constructor specifies chunk size, position, offset in world, noise generator and the final terrain size
    TerrainChunk(int size, int posX, int posY, float offset, SimplexNoise* pn, int finalSize);
    //get the size of the chunk
    int getSize();
    
    //height map as a float 2d array of dimension  [size][size]
    float** getHeightMap();
    
    //get the chunk position
    int getPosX();
    int getPosY();
    
    //return a list of entities
    std::vector<Renderable*>& getEntities()
    {
        return entities;
    }
    
    //height accessors
    float getHeightAt(int x, int y);
    void setHeightAt(int x, int y, float height);
    
    //render chunk using specified shader
    void render(Shader* shader, float deltaTime);
    
    //add entity to chunk
    void addEntity(Renderable* r);
    
    bool load();
    void unload();
    
    private:
    //width and height of chunk
    const int size;
    
    std::vector<Renderable*> entities;;
    
    //chunk position
    const int posX, posY;
    
    //heightmap grid
    float** heightMap;
    
    
    std::vector<glm::vec3> finalVertices;
    
    
};

//conttains all terrain info
class Terrain
{
    public:
    Terrain();
    
    //render terrain using a position and shader
    void render(glm::vec3 position, Shader* shader, float deltaTime);
    
    //get terrain size in chunks
    int getSize();
    
    //get heightmap points per chunk
    int getPointsPerChunk();
    
    //gets chunk at position, returns null pointer if out of bounds
    TerrainChunk* getChunkAt(int posX, int posY);
    
    TerrainChunk* getChunkAtReal(int posX, int posY);
    
    float getHeightAt(int x, int y);
    void setHeightAt(int x,int y,  float  height);
    
    void updateChunks(glm::vec3 position);
    
    int getRenderDistance();
    
    bool isPositionValid(glm::vec3 position);
    
    private:
    
    //number of chunks on x,y
    int size;
    
    int renderDistance;
    
    int pointsPerChunk;
    
    std::vector<TerrainChunk*> loadedChunks;
    
    //chunk grid
    TerrainChunk*** chunks;
    
    
    
};

