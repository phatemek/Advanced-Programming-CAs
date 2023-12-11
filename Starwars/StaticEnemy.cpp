#include "StaticEnemy.hpp"
using namespace std;

StaticEnemy::StaticEnemy(Point _point, int _width, int _height) : Enemy(_point, _width, _height) {}

void StaticEnemy::handle_movement(Window* window) {}

void StaticEnemy::update(Window* window) {}

void StaticEnemy::draw(Window* window) {
    window->draw_img("images/staticenemy.png", Rectangle(top_left_corner, width, height));
}
