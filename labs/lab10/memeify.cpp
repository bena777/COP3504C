#include <SFML/Graphics.hpp>
#include <iostream>
#include "memer.h"

int main(int argc, char* argv[]){
    std::string path = argv[1];
    std::string top_text = argv[2];
    std::string bottom_text = argv[3];
    int top_x,top_y,bottom_x,bottom_y = -1;
    std::cout << argv[7] << std::endl;
    if(argc >= 4){
        top_x = std::stoi(argv[4]); //method i found online to convert char* type to int
        if(argc >= 5){
            top_y = std::stoi(argv[5]);
        } if(argc >=6){
            bottom_x = std::stoi(argv[6]);
            if(argc >=7){
                bottom_y = std::stoi(argv[7]);
            }
        }
    }
    std::cout << top_x << " " << top_y << " " << bottom_x << " " << bottom_y << std::endl;
    sf::Image image;
    image.loadFromFile("C:/Users/benad/CLionProjects/lab10/resources/doge.jpg");
    sf::Image meme = generateMeme(image,top_text,bottom_text,top_x,top_y,bottom_x,bottom_y);
    sf::Texture tex;
    tex.loadFromImage(meme);
    sf:: Sprite sprite(tex);
    sf::RenderWindow window(sf::VideoMode(meme.getSize().x, meme.getSize().y), "Meme Gen");
    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
            }
        }
        window.clear();
        window.draw(sprite);
        window.display();
    }
    std::string outputPath = path.substr(0, path.find_last_of('.')) + "-meme" + path.substr(path.find_last_of('.'));
    meme.saveToFile(outputPath);
    return 0;
}
