
#include "IceDragon.h"

IceDragon::IceDragon(const std::string& _name, const std::string& _image) : Dragon(_name,_image) {
    setImage(_image);
}
bool IceDragon::canBreatheFire() {
    return false;
}
