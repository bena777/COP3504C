//
// Created by benad on 11/7/2024.
//

#ifndef PROJECT3_MAIN_H
#define PROJECT3_MAIN_H
#include <iostream>
#include <fstream>

using namespace std;

struct Header{
    char idLength;
    char colorMapType;
    char dataTypeCode;
    short colorMapOrigin;
    short colorMapLength;
    char colorMapDepth;
    short xOrigin;
    short yOrigin;
    short width;
    short height;
    char bitsPerPixel;
    char imageDescriptor;
};

struct Pixel{
    unsigned char blue;
    unsigned char green;
    unsigned char red;
};
Header readHeader(std::ifstream& file);
void writeHeader(std::ofstream& file, const Header& headerObject);
void writePixels(std::ofstream& file, Pixel pixels[], int w, int h);
Pixel* Subtract(Pixel first[], Pixel second[], int w, int h);

#endif //PROJECT3_MAIN_H
