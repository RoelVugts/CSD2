#include <iostream>


float mapInRange(float value, float inputMin, float inputMax, float outputMin, float outputMax)
{
    float inputRange = inputMax - inputMin;
    float outputRange = outputMax - outputMin;
    float valueScaled = (value-inputMin)/inputRange;
    float output = valueScaled * outputRange + outputMin;
    return output;
}

float linearMap(float factor, float min, float max)
{
    const float output = mapInRange(factor, 0.0f, 1.0f, min, max);
    return output;
}




int main ()
{
    std::cout << mapInRange(100, 50, 100, 1000, 2000) << std::endl;
    std::cout << linearMap(0.4, 50, 100) << std::endl;

    return 0;
}