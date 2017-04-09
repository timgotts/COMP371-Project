#include "TerrainGenerator.h"

PerlinNoiseGenerator::PerlinNoiseGenerator(double persistence, double frequency, double amplitude, int octaves, int seed): persistence(persistence), frequency(frequency), amplitude(amplitude), octaves(octaves), seed(2+seed*seed)
{
    
}

double PerlinNoiseGenerator::getHeightAt(double x, double y)
{
    return amplitude * total(x,y);
}

double PerlinNoiseGenerator::total(double i, double j)
{
    double total = 0.0f;
    double octaveAmplitude = 1;
    double octaveFrequency = frequency;
    
    //add each octave to the total value
    for(int octaveIndex = 0; octaveIndex < octaves; octaveIndex++)
    {
        total += getValue(j * octaveFrequency + seed, i * octaveFrequency + seed) * octaveAmplitude;
        
        octaveAmplitude *= persistence;
        octaveFrequency *= 2;
    }
    
    return total;
}

double PerlinNoiseGenerator::getValue(double realX, double realY)
{
    int x = (int)realX;
    int y = (int)realY;
    
    double xRemainder = realX - x;
    double yRemainder = realY - y;
    
    double n01 = noise(x-1, y-1);
    double n02 = noise(x+1, y-1);
    double n03 = noise(x-1, y+1);
    double n04 = noise(x+1, y+1);
    double n05 = noise(x-1, y);
    double n06 = noise(x+1, y);
    double n07 = noise(x, y-1);
    double n08 = noise(x, y+1);
    double n09 = noise(x, y);
    
    double n12 = noise(x+2, y-1);
    double n14 = noise(x+2, y+1);
    double n16 = noise(x+2, y);
    
    double n23 = noise(x-1, y+2);
    double n24 = noise(x+1, y+2);
    double n28 = noise(x, y+2);
    
    double n34 = noise(x+2, y+2);
    
    //find the noise values of the four corners
    double x0y0 = 0.0625*(n01+n02+n03+n04) + 0.125*(n05+n06+n07+n08) + 0.25*(n09);
    double x1y0 = 0.0625*(n07+n12+n08+n14) + 0.125*(n09+n16+n02+n04) + 0.25*(n06);
    double x0y1 = 0.0625*(n05+n06+n23+n24) + 0.125*(n03+n04+n09+n28) + 0.25*(n08);
    double x1y1 = 0.0625*(n09+n16+n28+n34) + 0.125*(n08+n14+n06+n24) + 0.25*(n04);
    
    //interpolate between those values according to the x and y fractions
    double v1 = interpolate(x0y0, x1y0, xRemainder); //interpolate in x direction (y)
    double v2 = interpolate(x0y1, x1y1, yRemainder); //interpolate in x direction (y+1)
    
    double finalValue = interpolate(v1, v2, yRemainder);  //interpolate in y direction
    
    return finalValue;
    
    
}

double PerlinNoiseGenerator::interpolate(double x, double y, double a)
{
    double aSquare = a * a;
    double aInverse = 1.0 - a;
    double aInverseSquare = aInverse * aInverse;
    
    double fac1 = 3.0 * (aInverseSquare) - 2.0 * (aInverseSquare * aInverse);
    double fac2 = 3.0 * aSquare - 2.0 * (aSquare * a);
    
    double result = x * fac1 + y * fac2;
    return result;
}

double PerlinNoiseGenerator::noise(int x, int y)
{
    int n = x + y * 57;
    n  = (n << 13) ^ n;
    int t = (n * (n * n * 15731 + 789221) + 1376312589) & 0x7fffffff;
    return 1.0 - double(t) * 0.931322574615478515625e-9;
}
    