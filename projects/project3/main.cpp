#include <iostream>
#include <fstream>
#include <vector>

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


int main() {
    std::ifstream inStream("input/car.tga", std::ios::binary);
    inStream.open("../input/car.tga");
    inStream.seekg(12);
    unsigned char heightBytes[2];
    inStream.read(reinterpret_cast<char*>(heightBytes), sizeof(heightBytes));
    short height = (static_cast<short>(heightBytes[1]) << 8) | heightBytes[0];
    std::cout << "Height: " << height << std::endl;

    unsigned char widthBytes[2];
    inStream.read(reinterpret_cast<char*>(widthBytes), sizeof(widthBytes));
    short width = (static_cast<short>(widthBytes[1]) << 8) | widthBytes[0];
    std::cout << "Width: " << width << std::endl;

    int pixels = width*height;
    inStream.seekg(18);
    for(int i=0; i<pixels;i+=1){
        Pixel pixel;
        inStream.read(reinterpret_cast<char*>(red), sizeof(red));
        std::cout << "Red: " << red << std::endl;
    }
    return 0;
}
