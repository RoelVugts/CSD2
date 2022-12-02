#include <iostream>

using namespace std;

int main() {

    int a = 5;

    int *aPtr = &a;
    int **aPtrPtr = &aPtr;
    int *bPtrPtr = &aPtr;



    cout << "Adress: " << aPtr << endl;
    cout << "Value: " << *aPtr << endl;
    cout << "PtrPtr Address: " << aPtrPtr << endl;
    out << "Ptr Address: " << bPtrPtr << endl;
    return 0;
}


