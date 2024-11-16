#include <iostream>
#include "Cow.h"
#include <string>
#include <vector>
#include "HeiferGenerator.h"
using namespace std;

void list_cows(const vector<Cow*>& cows){
    cout << "Cows available: ";
    for(int i=0; i < cows.size(); i++){
        cout << cows.at(i)->getName();
        if(i != cows.size()-1){
            cout << " ";
        } else{
            cout << "\n";
        }
    }
}

Cow* find_cow(const std::string& name, const vector<Cow*>& cows){
    for(Cow *cow: cows){
        if (cow->getName() == name){
            return cow;
        }
    }
    return nullptr;
}


int main(int argc, const char* argv[]) {
    vector<Cow*> cows = HeiferGenerator::getCows();
    if (argc <= 1){
        std::exit(1);
    }
    else if (argc <= 3){
        if (std::string(argv[1]) == "-l") {
            list_cows(cows);
            cout << endl;
        } else {
            cout << endl;
            auto cow = find_cow("heifer",cows);
            for (int i = 1; i < argc; i++){
                cout << argv[i];
                if (i != argc-1){
                    cout << " ";
                } else{
                    cout << endl;
                }
            }
            cout << cow -> getImage() << endl;
        }
    }else if (std::string(argv[1]) == "-n"){
        if (std::string(argv[1]).length() < 1){
            cout << "Error: Invalid Response" << endl;
        }
        try {
            auto cow = find_cow(argv[2], cows);
            if(cow == nullptr){
                string error = "Could not find ";
                error.append(argv[2]);
                error.append(" cow!");
                cout << error << endl;
                cout << "\n";
                std::exit(1);
            }
            cout << endl;
            for (int i = 3; i < argc; i++) {
                cout << argv[i];
                if (i != argc - 1) {
                    cout << " ";
                }
            }
            cout << endl;
            cout << cow->getImage() << endl;
            Dragon* dragon = HeiferGenerator::getDragonPointer(cow);
            if (dragon != nullptr) {
                if (dragon->canBreatheFire()) {
                    cout << "This dragon can breathe fire.\n" << endl;
                } else {
                    cout << "This dragon cannot breathe fire.\n" << endl;
                }
            }
        } catch(...) {
            string error = "Could not find ";
            error.append(argv[2]);
            error.append(" cow!");
        }
    } else if (argc == 4){
        cout << "\n";
        auto cow = find_cow("heifer",cows);
        for (int i = 1; i < argc; i++){
            cout << argv[i];
            if (i != argc-1){
                cout << " ";
            } else{
                cout << endl;
            }
        }
        cout << cow -> getImage() << endl;
    }
    return 0;
}
