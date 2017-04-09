#pragma once

class PerlinNoiseGenerator
{
    public:
    PerlinNoiseGenerator(double persistence, double frequency, double amplitude, int octaves, int seed);
    
    double getHeightAt(double x, double y);
    
    private:
    double total(double i, double j);
    double getValue(double realX, double realY);
    double interpolate(double x, double y, double a);
    double noise(int x, int y);
    
    //determines how persistent the amplitude is for each passing octave
    double persistence;
    
    double frequency; 
    
    //Height multiplier
    double amplitude;
    int octaves, seed;
    
};