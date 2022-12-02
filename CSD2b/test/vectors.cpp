#include <iostream>
#include <vector>
#include <ctime>
#include <cmath>

#include "timer.h"
using namespace std;






int main() 
{
    vector<int> notes;
    for(int i = 0; i <= 7; i++)
    {
        notes.push_back(i);
    }

    int readPointer = 0;


    Timer timer1;

    bool running = true;
    timer1.start();
    while (running) {
        if (fmod(timer1.getTime(), 500) == 0) {
            cout << "Time: " << timer1.getTime() << endl;
            cout << "Note: " << notes[readPointer++] << endl;
            if (readPointer >= int(notes.size()))
            {
                readPointer = 0;
                running = false;
            }
        }
    }



    cout << "Vector length: " << notes.size() << endl;

    return 0;
}


//C++ Code to Visualize Use of Iterators in C++
// #include <iostream> 
// #include <vector> 
// using namespace std;   
// int main() 
// { 
//     vector<int> a; //Declaration of vector in C++
   
//    //Initializing vector ‘a’ with values from 1 to 7
//     for (int i = 1; i <=7 ; i++) 
//         a.push_back(i); 

//     //Printing the Output of vector ‘a’ using iterators  begin() and end()  
//     cout << "Output of begin and end Function: "; 
//     for (auto i = a.begin(); i != a.end(); ++i) 
//         cout << *i << " "; 
    
//     return 0;
// }