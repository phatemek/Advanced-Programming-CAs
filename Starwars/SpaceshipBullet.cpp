#include "SpaceshipBullet.hpp"
using namespace std;
const int SPACESHIP_BULLET_SPEED = 8;

SpaceshipBullet::SpaceshipBullet(Point _point, int _width, int _height) {
    top_left_corner = _point;
    width = _width;
    height = _height;
    speed_y = -SPACESHIP_BULLET_SPEED;
}

Point SpaceshipBullet::get_location() {
    return top_left_corner;
}

void SpaceshipBullet::update() {
    top_left_corner.y += speed_y;
}

void SpaceshipBullet::draw(Window* window) {
    window->draw_img("images/spaceshipbullet.png", Rectangle(top_left_corner, width, height));
}
