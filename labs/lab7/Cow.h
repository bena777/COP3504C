#include <string>

#ifndef LAB7_COW_H
#define LAB7_COW_H

class Cow {
private:
    std::string name;
    std::string image;

public:
    Cow(const std::string& _name);
    std::string& getName();
    std::string& getImage();
    virtual void setImage(const std::string& _image);
};

#endif