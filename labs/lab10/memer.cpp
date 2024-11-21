#include <iostream>
#include <SFML/Graphics.hpp>

sf::Image generateMeme(sf::Image base, sf::String topText, sf::String bottomText = "", int topX = -1, int topY = -1, int bottomX = -1, int bottomY = -1){
    sf::Texture tex;
    tex.loadFromImage(base);
    sf::Sprite sprite(tex);
    sf::RenderTexture render_tex;
    render_tex.create(base.getSize().x,base.getSize().y);
    render_tex.clear();
    render_tex.draw(sprite);
    render_tex.display();
    std::cout << topX << " " << topY << " " << bottomX << " " << bottomY << std::endl;
    sf::Font font;
    font.loadFromFile("C:/Users/benad/CLionProjects/lab10/resources/Cave-Story.ttf");
    sf::Text top(sf::String(topText),font,30);
    if (topX == -1 && topY == -1){
        top.setPosition(base.getSize().x/3, base.getSize().y/3);
    } else{
        top.setPosition(topX,topY);
    }
    sf::Text bottom(sf::String(bottomText),font,30); //what font size do we use?
    if (bottomX == -1 && bottomY == -1){
        bottom.setPosition(base.getSize().x/3, base.getSize().y*2/3);
    } else{
        bottom.setPosition(bottomX,bottomY);
    }

    render_tex.draw(top);
    render_tex.draw(bottom);
    render_tex.display();

    sf::Image final = render_tex.getTexture().copyToImage();

    return final;
}