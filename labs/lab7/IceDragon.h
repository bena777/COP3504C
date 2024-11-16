
#ifndef LAB7_ICEDRAGON_H
#define LAB7_ICEDRAGON_H
#include "Dragon.h"
#include "string"

class IceDragon : public Dragon {
    public:
        IceDragon(const std::string& _name, const std::string& _image);
        bool canBreatheFire() override;

};


#endif //LAB7_ICEDRAGON_H
