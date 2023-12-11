#include "DynamicEnemy.hpp"
using namespace std;
const int DYNAMIC_ENEMY_SPEED = -4;

DynamicEnemy::DynamicEnemy(Point _point, int _width, int _height) : Enemy(_point, _width, _height) {
    speed_x = DYNAMIC_ENEMY_SPEED;
}

void DynamicEnemy::handle_movement(Window* window) {
    if(top_left_corner.x + speed_x <= 0 || top_left_corner.x + speed_x >= window->get_width() - width)
        speed_x = -speed_x;
}

void DynamicEnemy::update(Window* window) {
    top_left_corner.x += speed_x;
}

void DynamicEnemy::draw(Window* window) {
    window->draw_img("images/dynamicenemy.png", Rectangle(top_left_corner, width, height));
}
