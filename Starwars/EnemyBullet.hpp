#ifndef __EnemyBullet__
#define __EnemyBullet__
#include "src/rsdl.hpp"
using namespace std;

class EnemyBullet {
private:
    Point top_left_corner;
    int speed_y;
    int width;
    int height;
public:
    EnemyBullet(Point _point, int _width, int _height);
    Point get_location();
    int get_height();
    void update();
    void draw(Window* window, string bullet_image);
};

#endif
