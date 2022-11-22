#include <iostream>

using namespace std;

class Pony {
    public:
        float height;
        string ras;
        float speed;
        int age;

        float calculatePrice(float marketPrice);
        void run();

        Pony(float aHeight, string aRas, float aSpeed, int aAge) {
            height = aHeight;
            ras = aRas;
            speed = aSpeed;
            age = aAge;
    };


    private:
        float price;

};