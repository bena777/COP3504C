#include <iostream>
#include "ConsoleGfx.h"
using namespace std;

int main()
{
    cout<< "Welcome to the Image Scaler!" << endl;
    cout<< "\nDisplaying Spectrum Image:" << endl;
    ConsoleGfx* gfx = ConsoleGfx::getInstance();
    gfx->displayImage(gfx->testRainbow);
    cout<< "\nScaler Menu" << endl;
    cout<< "--------------" << endl;
    cout<< "0. Exit" << endl;
    cout<< "1. Load File" << endl;
    cout<< "2. Load Test Image" << endl;
    cout<< "3. Display Image" << endl;
    cout<< "4. Enlarge Image" << endl;
    cout<< "5. Shrink Image" << endl;
    cout<< "6. Show Image Properties" << endl;
    char option;
    cout<< "Select a Menu Option: ";
    cin>>option;
    cout<<option;
    unsigned char image
    if(option == '1'){
       string file;
       cout << "Enter name of file to load: ";
       cin >> file;
       try{
           gfx->loadFile(file);
           cout << "File loaded." << endl;
       } catch(...){
           cout << "Error: could not load file" << endl;
       }
    } else if(option == '2'){
        return 0;
    } else if(option == '3'){

    }
}