#pragma once

#include <cstddef>  // size_t
#include <cmath>
#include <random>
#include <algorithm>
#include <numeric>

//Simplex noise generator
class SimplexNoise {
    public:
    //get noise for x/y coordinate
    static float noise(float x, float y);
    
    //create fractal for x/y coordinates and number of octaves
    float fractal(size_t octaves, float x, float y) const;
    
    //default constructor
    explicit SimplexNoise(float frequency = 1.0f,
                          float amplitude = 1.0f,
                          float lacunarity = 2.0f,
                          float persistence = 0.5f) :
    mFrequency(frequency),
    mAmplitude(amplitude),
    mLacunarity(lacunarity),
    mPersistence(persistence) {
    }
    
    private:
    
    float mFrequency;   
    float mAmplitude;   
    float mLacunarity;  
    float mPersistence; 
};
