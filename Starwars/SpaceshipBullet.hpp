#ifndef __SpaceshipBullet__
#define __SpaceshipBullet__
#include "src/rsdl.hpp"
using namespace std;

class SpaceshipBullet {
private:
    Point top_left_corner;
    int speed_y;
    int width;
    int height;
public:
    SpaceshipBullet(Point _point, int _width, int _height);
    Point get_location();
    void update();
    void draw(Window* window);
};

#endif
