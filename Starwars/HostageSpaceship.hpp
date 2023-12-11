#ifndef __HostageSpaceship__
#define __HostageSpaceship__
#include "src/rsdl.hpp"
#include "SpaceshipBullet.hpp"
#include <vector>
using namespace std;

class HostageSpaceship {
private:
    Point top_left_corner;
    int width;
    int height;
public:
    HostageSpaceship(Point _top_left_corner, int _width, int _height);
    Point get_location();
    int get_width();
    int get_height();
    void draw(Window* window);
    bool is_hit_by(SpaceshipBullet* bullet);
    bool is_alive(vector<SpaceshipBullet*> spaceship_bullets);
};

#endif