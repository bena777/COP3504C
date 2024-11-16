
#ifndef LAB7_DRAGON_H
#define LAB7_DRAGON_H
#include "Cow.h"
#include <string>

class Dragon : public Cow{
    public:
        Dragon(const std::string& _name, const std::string& _image);
        virtual bool canBreatheFire();
};


#endif //LAB7_DRAGON_H
