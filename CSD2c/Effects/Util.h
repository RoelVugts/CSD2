
namespace Util
{
    template <typename T> T mapInRange(T value, T inputMin, T inputMax, T outputMin, T outputMax)
    {
        T inputRange = inputMax - inputMin;
        T outputRange = outputMax - outputMin;
        T valueScaled = (value-inputMin)/inputRange;
        T output = valueScaled * outputRange + outputMin;
        return output;
    }

    template <typename T> T linearMap(T factor, T min, T max)
    {
        T output = mapInRange(factor, 0.0, 1.0, min, max);
        return output;
    }


}// Util