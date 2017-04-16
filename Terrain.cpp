#include "Terrain.h"

TerrainChunk::TerrainChunk(int size, int posX, int posY, float offset,  SimplexNoise* pn, int finalSize) : size(size), posX(posX), posY(posY)
{
    //create new heightmap
    heightMap = new float*[size];
    
    //keep track of indices
    int currentIndice = 0;
    
    for(int x = 0; x < size; x++)
    {
        heightMap[x] = new float[size];
        
        for(int y = 0; y < size; y++)
        {
            
            //get coordinates of chunk point in real world
            float coordX = (posX * (size-1) + x);
            float coordY = (posY * (size-1) + y);
            
            //generate height at coordinates
            float height = 50 * pn->noise(coordX/(size*size), coordY/(size*size));
            
            heightMap[x][y] = height;
            
            //std::cout << height << std::endl;
            
            vertices.push_back({coordX, height, coordY });
            
            //add triangles to vertice list in order to render terrain alter
            if(x > 0 && y > 0)
            {
                //triangle one
                glm::vec3 t1v1 = vertices.at(currentIndice);
                glm::vec3 t1v2 = vertices.at(currentIndice-1);
                glm::vec3 t1v3 = vertices.at(currentIndice-size-1);
                
                //triangle two
                glm::vec3 t2v1 = vertices.at(currentIndice);
                glm::vec3 t2v2 = vertices.at(currentIndice-size);
                glm::vec3 t2v3 = vertices.at(currentIndice-size-1);
                
                //edges
                glm::vec3 t1e1 = t1v2-t1v1;
                glm::vec3 t1e2 = t1v3-t1v1;
                
                glm::vec3 t2e1 = t2v2-t2v1;
                glm::vec3 t2e2 = t2v3-t2v1;
                
                //normals
                glm::vec3 t1n = glm::normalize(glm::cross(t1e1,t1e2));
                glm::vec3 t2n = glm::normalize(glm::cross(t2e2,t2e1));
                
                //store data
                finalVertices.push_back(t1v1);
                finalVertices.push_back(t1n);
                finalVertices.push_back(t1v2);
                finalVertices.push_back(t1n);
                finalVertices.push_back(t1v3);
                finalVertices.push_back(t1n);
                
                finalVertices.push_back(t2v1);
                finalVertices.push_back(t2n);
                finalVertices.push_back(t2v2);
                finalVertices.push_back(t2n);
                finalVertices.push_back(t2v3);
                finalVertices.push_back(t2n);
            }
            
            currentIndice++;
        }
    }
    vertices.clear();
    
    //Assign material
    material = Material(glm::vec3(0.65f, 0.4f, 0.31f), glm::vec3(0.76f, 0.7f, 0.5f), glm::vec3(0.5f, 0.5f, 0.5f), 4.0f);
    
}

void TerrainChunk::addEntity(Renderable* r)
{
    entities.push_back(r);
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
bool TerrainChunk::load()
{
    if(VAO == 0)
    {
        
        // Generate buffers
        glGenVertexArrays(1, &VAO);
        glGenBuffers(1, &VBO);
        
        // Buffer object data
        glBindVertexArray(VAO);
        glBindBuffer(GL_ARRAY_BUFFER, VBO);
        glBufferData(GL_ARRAY_BUFFER, sizeof(glm::vec3) * finalVertices.size(), finalVertices.data(), GL_STATIC_DRAW);
        
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), (GLvoid*)0);
        glEnableVertexAttribArray(0);
        
        glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), (GLvoid*)(3 * sizeof(GLfloat)));
        glEnableVertexAttribArray(1);
        
        glBindBuffer(GL_ARRAY_BUFFER, 0);
        glBindVertexArray(0);
        
        return true;
    }
    return false;
}

void TerrainChunk::unload()
{
    glDeleteBuffers(1, &VBO);
    glDeleteVertexArrays(1, &VAO);
    
    VBO = 0;
    VAO = 0;
}
void TerrainChunk::render(Shader* shader)
{
    
    //shader->use();
    glm::mat3 normalMatrix = glm::transpose(glm::inverse(model));
    
    // Broadcast the uniform values to the shaders
    GLuint modelLoc = glGetUniformLocation(shader->program, "model");
    GLint normalMatrixLoc = glGetUniformLocation(shader->program, "normalMatrix");
    GLint matAmbientLoc = glGetUniformLocation(shader->program, "material.ambient");
    GLint matDiffuseLoc = glGetUniformLocation(shader->program, "material.diffuse");
    GLint matSpecularLoc = glGetUniformLocation(shader->program, "material.specular");
    GLint matShineLoc = glGetUniformLocation(shader->program, "material.shininess");
    
    glUniform3f(matAmbientLoc, material.ambient.x, material.ambient.y, material.ambient.z);
    glUniform3f(matDiffuseLoc, material.diffuse.x, material.diffuse.y, material.diffuse.z);
    glUniform3f(matSpecularLoc, material.specular.x, material.specular.y, material.specular.z);
    glUniform1f(matShineLoc, material.shininess);
    glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
    glUniformMatrix3fv(normalMatrixLoc, 1, GL_FALSE, glm::value_ptr(normalMatrix));
    
    
    // Draw object
    glBindVertexArray(VAO);
    glDrawArrays(GL_TRIANGLES, 0, finalVertices.size()/2);
    glBindVertexArray(0);
    
    //render all the entities contained in the chunk
    for(auto entity : entities)
    {
        entity->render(shader);
    }
    
}

Terrain::Terrain()
{
    //load terrain config
    Config config("res/config/Terrain.config");
    
    size = config.getConfig()->getInt("size");
    renderDistance = config.getConfig()->getInt("renderDistance");
    
    chunks = new TerrainChunk**[size];
    
    ConfigSection* generatorConfig = config.getConfig()->getSection("generator");
    
    double persistence = generatorConfig->getDouble("persistence");
    double frequency = generatorConfig->getDouble("frequency");
    double amplitude = generatorConfig->getDouble("amplitude");
    int octaves = generatorConfig->getInt("octaves");
    
    //noise generator for heightmap
    SimplexNoise* perlin = new SimplexNoise(frequency, amplitude, 1.0f, persistence);
    
    ConfigSection* chunkConfig = config.getConfig()->getSection("chunk");
    
    pointsPerChunk = chunkConfig->getInt("pointsPerChunk");
    
    int finalSize = size * (pointsPerChunk-1);
    
    //generate chunks and store in chunk array
    for(int x = 0; x < size; x++)
    {
        chunks[x] = new TerrainChunk*[size];
        
        for(int y = 0; y < size; y++)
        {
            chunks[x][y] = new TerrainChunk(pointsPerChunk, x, y, (float)size/2.0f ,perlin, finalSize);
        }
    }
}


int Terrain::getSize()
{
    return size;
}

int Terrain::getPointsPerChunk()
{
    return pointsPerChunk;
}

TerrainChunk* Terrain::getChunkAt(int posX, int posY)
{
    if(posX < 0 || posY < 0 || posX >= size || posY >= size)
    {
        return nullptr;
    }
    
    return chunks[posX][posY];
}
TerrainChunk* Terrain::getChunkAtReal(int posX, int posY)
{
    return getChunkAt(posX/(pointsPerChunk-1), posY / (pointsPerChunk-1));
}

float Terrain::getHeightAt(int x, int y)
{
    //relative coordinate for chunk
    int relX = x % (pointsPerChunk - 1);
    int relY = y % (pointsPerChunk - 1);
    
    
    //chunk position
    int chunkX = x / (pointsPerChunk-1);
    int chunkY = y / (pointsPerChunk-1);
    
    TerrainChunk* chunk;
    if((chunk = getChunkAt(chunkX,chunkY)) != nullptr)
    {
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
void Terrain::updateChunks(glm::vec3 position)
{
    
    //render from position outwards in all directions
    TerrainChunk* chunk = getChunkAt(-position.x/(pointsPerChunk-1), -position.z/(pointsPerChunk-1));
    if(chunk != nullptr)
    {
        if(loadedChunks.size() > (renderDistance*renderDistance)*2)
            for(int i=0; i < loadedChunks.size(); i++)
        {
            TerrainChunk* loadedChunk = loadedChunks.at(i);
            
            int dx = abs(chunk->getPosX() - loadedChunk->getPosX());
            int dy = abs(chunk->getPosX() - loadedChunk->getPosY());
            
            if(dx > renderDistance || dy > renderDistance)
            {
                loadedChunk->unload();
                loadedChunks.erase (loadedChunks.begin()+i);
                i--;
            }
            
        }
        
        //make sure draw distance is contained within terrain size
        int minX = chunk->getPosX()-renderDistance;
        int minY = chunk->getPosY()-renderDistance;
        
        int maxX = chunk->getPosX()+renderDistance;
        int maxY = chunk->getPosY()+renderDistance;
        
        if(minX < 0)
        {
            minX = 0;
        }
        if(minY < 0)
        {
            minY = 0;
        }
        
        if(maxX > size-1)
        {
            maxX = size-1;
        }
        
        if(maxY > size-1)
        {
            maxY = size-1;
        }
        
        
        for(int x = minX; x <= maxX; x++)
        {
            for(int y = minY; y <= maxY; y++)
            {
                TerrainChunk* chunkToLoad = getChunkAt(x,y);
                if(chunkToLoad->load())
                {
                    loadedChunks.push_back(chunkToLoad);
                }
            }
        }
        
    }
    else //if out of bounds, render everything, mainly for debug purposes
    {
        for(int x = 0; x < size; x++)
        {
            for(int y = 0; y < size; y++)
            {
                getChunkAt(x,y)->load();
            }
        }
    }
    
}

void Terrain::render(glm::vec3 position, Shader* shader)
{
    //render from position outwards in all directions
    TerrainChunk* chunk = getChunkAt(-position.x/(pointsPerChunk-1), -position.z/(pointsPerChunk-1));
    if(chunk != nullptr)
    {
        //make sure draw distance is contained within terrain size
        int minX = chunk->getPosX()-renderDistance;
        int minY = chunk->getPosY()-renderDistance;
        
        int maxX = chunk->getPosX()+renderDistance;
        int maxY = chunk->getPosY()+renderDistance;
        
        if(minX < 0)
        {
            minX = 0;
        }
        if(minY < 0)
        {
            minY = 0;
        }
        
        if(maxX > size-1)
        {
            maxX = size-1;
        }
        
        if(maxY > size-1)
        {
            maxY = size-1;
        }
        
        
        for(int x = minX; x <= maxX; x++)
        {
            for(int y = minY; y <= maxY; y++)
            {
                getChunkAt(x,y)->render(shader);
            }
        }
        
    }
    else //if out of bounds, render everything, mainly for debug purposes
    {
        for(int x = 0; x < size; x++)
        {
            for(int y = 0; y < size; y++)
            {
                getChunkAt(x,y)->render(shader);
            }
        }
    }
    
}