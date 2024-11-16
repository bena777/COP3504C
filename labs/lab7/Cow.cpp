#include "Cow.h"
Cow::Cow(const std::string& _name) : name(_name) {}

std::string& Cow::getName() {
    return name;
}

std::string& Cow::getImage() {
    return image;
}

void Cow::setImage(const std::string& _image) {
    image = _image;
}