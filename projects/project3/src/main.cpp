#include <iostream>
#include <fstream>
#include <vector>
#include "main.h"
using namespace std;



Header readHeader(std::ifstream& file){
    Header headerObject;
    file.read(&headerObject.idLength, sizeof(headerObject.idLength));
    file.read(&headerObject.colorMapType, sizeof(headerObject.colorMapType));
    file.read(&headerObject.dataTypeCode, sizeof(headerObject.dataTypeCode));
    file.read(reinterpret_cast<char*>(&headerObject.colorMapOrigin), sizeof(headerObject.colorMapOrigin));
    file.read(reinterpret_cast<char*>(&headerObject.colorMapLength), sizeof(headerObject.colorMapLength));
    file.read(&headerObject.colorMapDepth, sizeof(headerObject.colorMapDepth));
    file.read(reinterpret_cast<char*>(&headerObject.xOrigin), sizeof(headerObject.xOrigin));
    file.read(reinterpret_cast<char*>(&headerObject.yOrigin), sizeof(headerObject.yOrigin));
    file.read(reinterpret_cast<char*>(&headerObject.width), sizeof(headerObject.width));
    file.read(reinterpret_cast<char*>(&headerObject.height), sizeof(headerObject.height));
    file.read(&headerObject.bitsPerPixel, sizeof(headerObject.bitsPerPixel));
    file.read(&headerObject.imageDescriptor, sizeof(headerObject.imageDescriptor));
    return headerObject;
}

void writeHeader(std::ofstream& file, const Header& headerObject){
    file.write(&headerObject.idLength, sizeof(headerObject.idLength));
    file.write(&headerObject.colorMapType, sizeof(headerObject.colorMapType));
    file.write(&headerObject.dataTypeCode, sizeof(headerObject.dataTypeCode));
    file.write(reinterpret_cast<const char*>(&headerObject.colorMapOrigin), sizeof(headerObject.colorMapOrigin));
    file.write(reinterpret_cast<const char*>(&headerObject.colorMapLength), sizeof(headerObject.colorMapLength));
    file.write(&headerObject.colorMapDepth, sizeof(headerObject.colorMapDepth));
    file.write(reinterpret_cast<const char*>(&headerObject.xOrigin), sizeof(headerObject.xOrigin));
    file.write(reinterpret_cast<const char*>(&headerObject.yOrigin), sizeof(headerObject.yOrigin));
    file.write(reinterpret_cast<const char*>(&headerObject.width), sizeof(headerObject.width));
    file.write(reinterpret_cast<const char*>(&headerObject.height), sizeof(headerObject.height));
    file.write(&headerObject.bitsPerPixel, sizeof(headerObject.bitsPerPixel));
    file.write(&headerObject.imageDescriptor, sizeof(headerObject.imageDescriptor));
}

void writePixels(std::ofstream& file, Pixel pixels[], int w, int h){
    for(int i=0; i < w*h; i++ ){
        file.put(pixels[i].blue);
        file.put(pixels[i].green);
        file.put(pixels[i].red);
    }
}

Pixel* loadPixels(std::ifstream& file, Header headerObject){
    Pixel* pixels = new Pixel[headerObject.width * headerObject.height];
    for(int i=0; i<headerObject.width*headerObject.height; i++){
        unsigned char bgr[3];
        file.read(reinterpret_cast<char*>(bgr),3);
        pixels[i].blue = bgr[0];
        pixels[i].green = bgr[1];
        pixels[i].red = bgr[2];
    }
    return pixels;

}


Pixel* Subtract(Pixel first[], Pixel second[], int w, int h){
    Pixel* pixels = new Pixel[w*h];
    for(int i=0; i < w*h; i++){
        pixels[i].blue=(unsigned char)(std::max(0,std::min(255,(int)first[i].blue-(int)second[i].blue)));
        pixels[i].green=(unsigned char)(std::max(0,std::min(255,(int)first[i].green-(int)second[i].green)));
        pixels[i].red=(unsigned char)(std::max(0,std::min(255,(int)first[i].red-(int)second[i].red)));
    }
    return pixels;
}

Pixel* Multiply(Pixel first[], Pixel second[], int w, int h){
    Pixel* pixels = new Pixel[w*h];
    for(int i=0; i < w*h; i++){
        pixels[i].blue=(unsigned char)std::min(255,std::max(0,(int)first[i].blue*(int)second[i].blue/255)); //possibly add 0.5
        pixels[i].green=(unsigned char)std::min(255,std::max(0,(int)first[i].green*(int)second[i].green/255));
        pixels[i].red=(unsigned char)std::min(255,std::max(0,(int)first[i].red*(int)second[i].red/255));
    }
    return pixels;
}

Pixel* Screen(Pixel first[], Pixel second[], int w, int h) {
    Pixel* pixels = new Pixel[w * h];
    for (int i = 0; i < w * h; i++) {
        pixels[i].blue=(unsigned char)std::min(255,255 -((255-(int)first[i].blue)*(255-(int)second[i].blue)/255));
        pixels[i].green=(unsigned char)std::min(255,255-((255-(int)first[i].green)*(255-(int)second[i].green)/255));
        pixels[i].red=(unsigned char)std::min(255,255-((255-(int)first[i].red)*(255-(int)second[i].red)/255));
    }
    return pixels;
}

int main() {
    std::ifstream file("../input/layer1.tga", std::ios::binary);
    std::ifstream file2("../input/pattern1.tga", std::ios::binary);


    //Test 1 (complete)
    Header headerObject = readHeader(file);
    Pixel* pixels = loadPixels(file,headerObject);
    Pixel* pixels2 = loadPixels(file2,headerObject);
    Pixel* result = Multiply(pixels,pixels2,headerObject.width,headerObject.height);
    std::ofstream outputFile("../output/part1.tga",std::ios::binary);
    writeHeader(outputFile,headerObject);
    writePixels(outputFile,result,headerObject.width,headerObject.height);
    outputFile.close();

    //Test 2 (complete)
    file = std::ifstream("../input/car.tga", std::ios::binary);
    file2 = std::ifstream("../input/layer2.tga", std::ios::binary);
    headerObject = readHeader(file);
    pixels = loadPixels(file,headerObject);
    pixels2 = loadPixels(file2,headerObject);
    result = Subtract(pixels,pixels2,headerObject.height,headerObject.width);
    outputFile = std::ofstream("../output/part2.tga",std::ios::binary);
    writeHeader(outputFile,headerObject);
    writePixels(outputFile,result,headerObject.width,headerObject.height);
    outputFile.close();

    //Test 3
    file = std::ifstream("../input/layer1.tga");
    file2 = std::ifstream("../input/pattern2.tga");
    headerObject = readHeader(file);
    pixels = loadPixels(file,headerObject);
    pixels2 = loadPixels(file2,headerObject);
    Pixel* temp_result = Multiply(pixels,pixels2,headerObject.width,headerObject.height);
    file = std::ifstream("../input/text.tga");
    headerObject = readHeader(file);
    pixels = loadPixels(file,headerObject);
    result = Screen(pixels,temp_result,headerObject.width,headerObject.height);
    outputFile = std::ofstream("../output/part3.tga",std::ios::binary);
    writeHeader(outputFile,headerObject);
    writePixels(outputFile,result,headerObject.width,headerObject.height);
    outputFile.close();


    //Test 6 (complete)
    file = std::ifstream("../input/car.tga", std::ios::binary);
    headerObject = readHeader(file);
    result = loadPixels(file,headerObject);
    for(int i=0; i < headerObject.height * headerObject.width; i++){
        int current = result[i].green;
        result[i].green = (unsigned char)std::min(255, std::max(0, current + 200));
    }
    outputFile = std::ofstream("../output/part6.tga",std::ios::binary);
    writeHeader(outputFile,headerObject);
    writePixels(outputFile,result,headerObject.width,headerObject.height);
    outputFile.close();

    //Test 9
    file = std::ifstream("../input/layer_red.tga", std::ios::binary);
    file2 = std::ifstream("../input/layer_green.tga", std::ios::binary);
    std::ifstream file3("../input/layer_blue.tga", std::ios::binary);
    headerObject = readHeader(file);
    cout << headerObject.width << ", " << headerObject.height << endl;
    result = loadPixels(file,headerObject);
    Pixel* result2 = loadPixels(file2,headerObject);
    Pixel* result3 = loadPixels(file3,headerObject);
    auto* true_result= new Pixel[headerObject.height*headerObject.width];

    for(int i=0; i < headerObject.height * headerObject.width; i++){
        true_result[i].red = (unsigned char)result[i].red;
        true_result[i].green = (unsigned char)result2[i].green;
        true_result[i].blue = (unsigned char)result3[i].blue;
    }
    outputFile = std::ofstream("../output/part9.tga");
    writeHeader(outputFile,headerObject);
    writePixels(outputFile,true_result,headerObject.width,headerObject.height);
    outputFile.close();
    return 0;
}
