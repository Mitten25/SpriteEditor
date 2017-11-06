#include "frame.h"

using namespace std;

Frame::Frame()
{
    currLayer = 0;
}

tuple<int, int, int, int> Frame::getPixel() {
    //To be implemented, may not be using result variable, placed there just as filled to compile.
    tuple<int, int, int, int> result;
    return result;
}

void Frame::setPixel(tuple <int, int, int, int>) {
    //To be implemented
}

int Frame::deleteLayer() {
    //To be implemented
}

int Frame::addLayer() {
    //To be implemented
}
