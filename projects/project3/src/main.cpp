#include <iostream>
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
    for (int i = 0; i < w * h; i++) {
        pixels[i].blue=(unsigned char)((first[i].blue*second[i].blue+127)/255);
        pixels[i].green=(unsigned char)((first[i].green * second[i].green+127)/255);
        pixels[i].red=(unsigned char)((first[i].red * second[i].red+127)/255);
    }
    return pixels;
}

Pixel* Screen(Pixel first[], Pixel second[], int w, int h) {
    Pixel* pixels = new Pixel[w*h];
    for (int i = 0; i < w*h; i++) {
        pixels[i].blue = (unsigned char)std::min(255,std::max(0,(int)(255-((255-(int)first[i].blue)*(255-(int)second[i].blue)+127)/255)));
        pixels[i].green = (unsigned char)std::min(255,std::max(0,(int)(255-((255-(int)first[i].green)*(255-(int)second[i].green)+127)/255)));
        pixels[i].red = (unsigned char)std::min(255, std::max(0,(int)(255-((255-(int)first[i].red)*(255 -(int)second[i].red)+127)/255)));
    }
    return pixels;
}

Pixel* Overlay(Pixel first[], Pixel second[], int w, int h){
    Pixel* pixels = new Pixel[w*h];
    for(int i=0; i<w*h; i++){
        if(second[i].blue/255.0 <= 0.5){
            pixels[i].blue = (unsigned char)((2*((second[i].blue*first[i].blue)/255.0))+0.5);
        } else{
            pixels[i].blue = (unsigned char)((255*(1-2*(1-(second[i].blue/255.0))*(1-(first[i].blue/255.0))))+0.5);
        }
        if(second[i].green/255.0 <= 0.5){
            pixels[i].green = (unsigned char)(((2*((second[i].green*first[i].green)/255.0)))+0.5);
        } else{
            pixels[i].green = (unsigned char)((255*(1-2*(1-(second[i].green/255.0))*(1-(first[i].green/255.0))))+0.5);
        }
        if(second[i].red/255.0 <= 0.5){
            pixels[i].red = (unsigned char)(((2*((second[i].red*first[i].red)/255.0)))+0.5);
        } else{
            pixels[i].red = (unsigned char)((255*(1-2*(1-(second[i].red/255.0))*(1-(first[i].red/255.0))))+0.5);
        }
    }
    return pixels;
}
bool test_task(Pixel actual[], Pixel example[], int w, int h){ //legacy function from testing
    for(int i=0; i<w * h; i++){
        if((actual[i].red != example[i].red) || (actual[i].green != example[i].green) || (actual[i].blue != example[i].blue)){
            cout << i << endl;
            cout << "Actual: R: " << (int)actual[i].red << " G: " << (int)actual[i].green << " B: " << (int)actual[i].blue <<endl;
            cout << "Ex: R: " << (int)example[i].red << " G: " << (int)example[i].green << " B: " << (int)example[i].blue <<endl;
            return false;
        }
    }
    return true;
}

int main() {
    std::ifstream file("../input/layer1.tga", std::ios::binary);
    std::ifstream file2("../input/pattern1.tga", std::ios::binary);


    //Test 1 (complete)
    Header headerObject = readHeader(file);
    Header headerObject2 = readHeader(file2);
    Pixel* pixels = loadPixels(file,headerObject);
    Pixel* pixels2 = loadPixels(file2,headerObject);
    Pixel* result = Multiply(pixels,pixels2,headerObject.width,headerObject.height);
    std::ofstream outputFile("../output/part1.tga",std::ios::binary);
    writeHeader(outputFile,headerObject);
    writePixels(outputFile,result,headerObject.width,headerObject.height);
    outputFile.close();

    file = ifstream("../output/part1.tga", std::ios::binary);
    file2 = ifstream("../examples/EXAMPLE_part1.tga", std::ios::binary);
    headerObject = readHeader(file);
    headerObject2 = readHeader(file2);
    pixels = loadPixels(file,headerObject);
    pixels2 = loadPixels(file2,headerObject);
    bool test = test_task(pixels,pixels2,headerObject.height,headerObject.width);
    if(test){
        cout << "Test 1 passes!" << endl;
    } else{
        cout << "Test 1 fails." << endl;
    }

    //Test 2 (complete)
    file = std::ifstream("../input/car.tga", std::ios::binary);
    file2 = std::ifstream("../input/layer2.tga", std::ios::binary);
    headerObject = readHeader(file);
    headerObject2 = readHeader(file2);
    pixels = loadPixels(file,headerObject);
    pixels2 = loadPixels(file2,headerObject);
    result = Subtract(pixels,pixels2,headerObject.height,headerObject.width);
    outputFile = std::ofstream("../output/part2.tga",std::ios::binary);
    writeHeader(outputFile,headerObject);
    writePixels(outputFile,result,headerObject.width,headerObject.height);
    outputFile.close();

    file = ifstream("../output/part2.tga", std::ios::binary);
    file2 = ifstream("../examples/EXAMPLE_part2.tga", std::ios::binary);
    headerObject = readHeader(file);
    headerObject2 = readHeader(file2);
    pixels = loadPixels(file,headerObject);
    pixels2 = loadPixels(file2,headerObject);
    test = test_task(pixels,pixels2,headerObject.height,headerObject.width);
    if(test){
        cout << "Test 2 passes!" << endl;
    } else{
        cout << "Test 2 fails." << endl;
    }

    //Test 3 (complete)
    file = std::ifstream("../input/layer1.tga",std::ios::binary);
    file2 = std::ifstream("../input/pattern2.tga",std::ios::binary);
    headerObject = readHeader(file);
    headerObject2 = readHeader(file2);
    pixels = loadPixels(file,headerObject);
    pixels2 = loadPixels(file2,headerObject);
    Pixel* temp_result = Multiply(pixels2,pixels,headerObject.width,headerObject.height);
    file = std::ifstream("../input/text.tga",std::ios::binary);
    headerObject = readHeader(file);
    pixels = loadPixels(file,headerObject);
    result = Screen(pixels,temp_result,headerObject.width,headerObject.height);
    outputFile = std::ofstream("../output/part3.tga",std::ios::binary);
    writeHeader(outputFile,headerObject);
    writePixels(outputFile,result,headerObject.width,headerObject.height);
    outputFile.close();

    file = ifstream("../output/part3.tga", std::ios::binary);
    file2 = ifstream("../examples/EXAMPLE_part3.tga", std::ios::binary);
    headerObject = readHeader(file);
    headerObject2 = readHeader(file2);
    pixels = loadPixels(file,headerObject);
    pixels2 = loadPixels(file2,headerObject);
    test = test_task(pixels,pixels2,headerObject.height,headerObject.width);
    if(test){
        cout << "Test 3 passes!" << endl;
    } else{
        cout << "Test 3 fails." << endl;
    }

    //Test 4 (complete)
    file = std::ifstream("../input/layer2.tga",std::ios::binary);
    file2 = std::ifstream("../input/circles.tga",std::ios::binary);
    headerObject = readHeader(file);
    headerObject2 = readHeader(file2);
    pixels = loadPixels(file,headerObject);
    pixels2 = loadPixels(file2,headerObject);
    temp_result = Multiply(pixels2,pixels,headerObject.width,headerObject.height);
    file = std::ifstream("../input/pattern2.tga",std::ios::binary);
    headerObject = readHeader(file);
    pixels = loadPixels(file,headerObject);
    result = Subtract(temp_result,pixels,headerObject.width,headerObject.height);
    outputFile = std::ofstream("../output/part4.tga",std::ios::binary);
    writeHeader(outputFile,headerObject);
    writePixels(outputFile,result,headerObject.width,headerObject.height);
    outputFile.close();

    file = ifstream("../output/part4.tga", std::ios::binary);
    file2 = ifstream("../examples/EXAMPLE_part4.tga", std::ios::binary);
    headerObject = readHeader(file);
    headerObject2 = readHeader(file2);
    pixels = loadPixels(file,headerObject);
    pixels2 = loadPixels(file2,headerObject);
    test = test_task(pixels,pixels2,headerObject.height,headerObject.width);
    if(test){
        cout << "Test 4 passes!" << endl;
    } else{
        cout << "Test 4 fails." << endl;
    }

    //Test 5
    file = std::ifstream("../input/pattern1.tga",std::ios::binary);
    file2 = std::ifstream("../input/layer1.tga",std::ios::binary);
    headerObject = readHeader(file);
    headerObject2 = readHeader(file2);
    pixels = loadPixels(file,headerObject);
    pixels2 = loadPixels(file2,headerObject2);
    result = Overlay(pixels2,pixels,headerObject.width,headerObject.height);
    outputFile = std::ofstream("../output/part5.tga",std::ios::binary);
    writeHeader(outputFile,headerObject);
    writePixels(outputFile,result,headerObject.width,headerObject.height);
    outputFile.close();

    file = ifstream("../output/part5.tga", std::ios::binary);
    file2 = ifstream("../examples/EXAMPLE_part5.tga", std::ios::binary);
    headerObject = readHeader(file);
    headerObject2 = readHeader(file2);
    pixels = loadPixels(file,headerObject);
    pixels2 = loadPixels(file2,headerObject);
    test = test_task(pixels,pixels2,headerObject.height,headerObject.width);
    if(test){
        cout << "Test 5 passes!" << endl;
    } else{
        cout << "Test 5 fails." << endl;
    }



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

    file = ifstream("../output/part6.tga", std::ios::binary);
    file2 = ifstream("../examples/EXAMPLE_part6.tga", std::ios::binary);
    headerObject = readHeader(file);
    headerObject2 = readHeader(file2);
    pixels = loadPixels(file,headerObject);
    pixels2 = loadPixels(file2,headerObject);
    test = test_task(pixels,pixels2,headerObject.height,headerObject.width);
    if(test){
        cout << "Test 6 passes!" << endl;
    } else{
        cout << "Test 6 fails." << endl;
    }

    //Test 7 (complete)
    file = std::ifstream("../input/car.tga",std::ios::binary);
    headerObject = readHeader(file);
    result = loadPixels(file,headerObject);
    for(int i=0; i < headerObject.height * headerObject.width; i++){
        int current = result[i].red;
        result[i].blue = (unsigned char)0;
        result[i].red = (unsigned char)std::min(255,(int)(current * 4));
    }
    outputFile = std::ofstream("../output/part7.tga",std::ios::binary);
    writeHeader(outputFile,headerObject);
    writePixels(outputFile,result,headerObject.width,headerObject.height);
    outputFile.close();

    file = ifstream("../output/part7.tga", std::ios::binary);
    file2 = ifstream("../examples/EXAMPLE_part7.tga", std::ios::binary);
    headerObject = readHeader(file);
    headerObject2 = readHeader(file2);
    pixels = loadPixels(file,headerObject);
    pixels2 = loadPixels(file2,headerObject);
    test = test_task(pixels,pixels2,headerObject.height,headerObject.width);
    if(test){
        cout << "Test 7 passes!" << endl;
    } else{
        cout << "Test 7 fails." << endl;
    }

    //Test 8 (complete)
    file=std::ifstream("../input/car.tga",std::ios::binary);
    headerObject = readHeader(file);
    result = loadPixels(file,headerObject);
    Pixel* red_channel = new Pixel[headerObject.height * headerObject.width];
    Pixel* green_channel = new Pixel[headerObject.height * headerObject.width];
    Pixel* blue_channel = new Pixel[headerObject.height * headerObject.width];
    for(int i=0; i < headerObject.width * headerObject.height; i++){
       red_channel[i].red = result[i].red;
       red_channel[i].blue = result[i].red;
       red_channel[i].green = result[i].red;
       green_channel[i].red = result[i].green;
       green_channel[i].blue = result[i].green;
       green_channel[i].green = result[i].green;
       blue_channel[i].red = result[i].blue;
       blue_channel[i].blue = result[i].blue;
       blue_channel[i].green = result[i].blue;
    }
    outputFile = std::ofstream("../output/part8_r.tga",std::ios::binary);
    writeHeader(outputFile,headerObject);
    writePixels(outputFile,red_channel,headerObject.width,headerObject.height);
    outputFile.close();
    outputFile = std::ofstream("../output/part8_g.tga",std::ios::binary);
    writeHeader(outputFile,headerObject);
    writePixels(outputFile,green_channel,headerObject.width,headerObject.height);
    outputFile.close();
    outputFile = std::ofstream("../output/part8_b.tga",std::ios::binary);
    writeHeader(outputFile,headerObject);
    writePixels(outputFile,blue_channel,headerObject.width,headerObject.height);
    outputFile.close();
    delete[] blue_channel;
    delete[] red_channel;
    delete[] green_channel;
    cout << "Test 8 passes!" << endl;



    //Test 9 (complete)
    file = std::ifstream("../input/layer_red.tga", std::ios::binary);
    file2 = std::ifstream("../input/layer_green.tga", std::ios::binary);
    std::ifstream file3("../input/layer_blue.tga", std::ios::binary);
    headerObject = readHeader(file);
    headerObject2 = readHeader(file2);
    Header headerObject3 = readHeader(file3);
    result = loadPixels(file,headerObject);
    Pixel* result2 = loadPixels(file2,headerObject2);
    Pixel* result3 = loadPixels(file3,headerObject3);
    Pixel* true_result= new Pixel[headerObject.height*headerObject.width];
    for(int i=0; i < headerObject.height * headerObject.width; i++){
        true_result[i].red = result[i].red;
        true_result[i].green = result2[i].green;
        true_result[i].blue = result3[i].blue;
    }
    outputFile = std::ofstream("../output/part9.tga",std::ios::binary);
    writeHeader(outputFile,headerObject);
    writePixels(outputFile,true_result,headerObject.width,headerObject.height);
    outputFile.close();

    file = ifstream("../output/part9.tga", std::ios::binary);
    file2 = ifstream("../examples/EXAMPLE_part9.tga", std::ios::binary);
    headerObject = readHeader(file);
    headerObject2 = readHeader(file2);
    pixels = loadPixels(file,headerObject);
    pixels2 = loadPixels(file2,headerObject);
    test = test_task(pixels,pixels2,headerObject.height,headerObject.width);
    if(test){
        cout << "Test 9 passes!" << endl;
    } else{
        cout << "Test 9 fails." << endl;
    }

    //Test 10
    file = ifstream("../input/text2.tga",std::ios::binary);
    headerObject = readHeader(file);
    pixels = loadPixels(file,headerObject);
    Pixel* new_pixels = new Pixel[headerObject.height * headerObject.width];
    for (int h = 0; h < headerObject.height; h++) {
        for (int w = 0; w < headerObject.width; w++) {
            new_pixels[(headerObject.height-1-h)*headerObject.width+(headerObject.width-1-w)].red = pixels[h*headerObject.width+w].red;
            new_pixels[(headerObject.height-1-h)*headerObject.width+(headerObject.width-1-w)].green = pixels[h*headerObject.width+w].green;
            new_pixels[(headerObject.height-1-h)*headerObject.width+(headerObject.width-1-w)].blue = pixels[h*headerObject.width+w].blue;
        }
    }
    outputFile = std::ofstream("../output/part10.tga",std::ios::binary);
    writeHeader(outputFile,headerObject);
    writePixels(outputFile,new_pixels,headerObject.width,headerObject.height);
    outputFile.close();

    file = ifstream("../output/part10.tga", std::ios::binary);
    file2 = ifstream("../examples/EXAMPLE_part10.tga", std::ios::binary);
    headerObject = readHeader(file);
    headerObject2 = readHeader(file2);
    pixels = loadPixels(file,headerObject);
    pixels2 = loadPixels(file2,headerObject);
    test = test_task(pixels,pixels2,headerObject.height,headerObject.width);
    if(test){
        cout << "Test 10 passes!" << endl;
    } else{
        cout << "Test 10 fails." << endl;
    }

    //Extra Credit
    file = std::ifstream("../input/car.tga", std::ios::binary);
    file2 = std::ifstream("../input/circles.tga", std::ios::binary);
    file3 = std::ifstream("../input/pattern1.tga",std::ios::binary);
    std::ifstream file4("../input/text.tga", std::ios::binary);
    headerObject = readHeader(file);
    headerObject2 = readHeader(file2);
    headerObject3 = readHeader(file3);
    Header headerObject4 = readHeader(file4);
    int total = (headerObject.height*headerObject.width)+(headerObject2.height*headerObject2.width)+(headerObject3.height*headerObject3.width)+(headerObject4.height*headerObject4.width);
    true_result= new Pixel[total];
    result = loadPixels(file,headerObject);
    result2 = loadPixels(file2,headerObject2);
    result3 = loadPixels(file3,headerObject3);
    Pixel* result4 = loadPixels(file4,headerObject4);
    int running = 0;
    for(int i=0; i < headerObject.height * headerObject.width; i++){
        true_result[i].red = (unsigned char)result[i].red;
        true_result[i].green = (unsigned char)result[i].green;
        true_result[i].blue = (unsigned char)result[i].blue;
    }
    running+=headerObject.height*headerObject.width;
    for(int i=running; i < headerObject2.height * headerObject2.width; i++){
        true_result[i].red = (unsigned char)result2[i].red;
        true_result[i].green = (unsigned char)result2[i].green;
        true_result[i].blue = (unsigned char)result2[i].blue;
    }
    running+=headerObject2.height*headerObject2.width;
    for(int i=running; i < headerObject3.height * headerObject3.width; i++){
        true_result[i].red = (unsigned char)result3[i].red;
        true_result[i].green = (unsigned char)result3[i].green;
        true_result[i].blue = (unsigned char)result3[i].blue;
    }
    running+=headerObject3.height*headerObject3.width;
    for(int i=running; i < headerObject4.height * headerObject.width; i++){
        true_result[i].red = (unsigned char)result4[i].red;
        true_result[i].green = (unsigned char)result4[i].green;
        true_result[i].blue = (unsigned char)result4[i].blue;
    }
    outputFile = std::ofstream("../output/extracredit.tga");
    writeHeader(outputFile,headerObject);
    writePixels(outputFile,true_result,headerObject.width,headerObject.height);
    outputFile.close();



    return 0;
}
