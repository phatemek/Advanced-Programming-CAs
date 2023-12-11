#include "EnemyBullet.hpp"
using namespace std;
const int ENEMY_BULLET_SPEED = 8;

EnemyBullet::EnemyBullet(Point _point, int _width, int _height) {
    top_left_corner = _point;
    width = _width;
    height = _height;
    speed_y = ENEMY_BULLET_SPEED;
}

Point EnemyBullet::get_location() {
    return top_left_corner;
}

int EnemyBullet::get_height() {
    return height;
}

void EnemyBullet::update() {
    top_left_corner.y += speed_y;
}

void EnemyBullet::draw(Window* window, string bullet_image) {
    window->draw_img(bullet_image, Rectangle(top_left_corner, width, height));
}
