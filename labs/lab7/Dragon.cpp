
#include "Dragon.h"
Dragon::Dragon(const std::string& _name, const std::string& _image) : Cow(_name) {
    setImage(_image);
}
bool Dragon::canBreatheFire() {
    return true;
}