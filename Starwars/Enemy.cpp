#include "Enemy.hpp"
using namespace std;
const int BULLET_WIDTH = 7;
const int BULLET_HEIGHT = 30;

Enemy::Enemy(Point _point, int _width, int _height) {
    top_left_corner = _point;
    width = _width;
    height = _height;
}

int Enemy::get_width() {
    return width;
}

int Enemy::get_height() {
    return height;
}

Point Enemy::get_location() {
    return top_left_corner;
}

void Enemy::shoot() {
    Point bullet_location((top_left_corner.x + width/2 - BULLET_WIDTH/2), (top_left_corner.y + height));
    EnemyBullet* bullet = new EnemyBullet(bullet_location, BULLET_WIDTH, BULLET_HEIGHT);
    enemy_bullets.push_back(bullet);
}

bool Enemy::is_hit_by(SpaceshipBullet* bullet) {
    return (bullet->get_location().x > top_left_corner.x
        && bullet->get_location().x < top_left_corner.x + width
        && bullet->get_location().y > top_left_corner.y
        && bullet->get_location().y < top_left_corner.y + height);
}

bool Enemy::is_alive(vector<SpaceshipBullet*>& spaceship_bullets) {
    for(int bullet = 0; bullet < spaceship_bullets.size(); bullet++) {
        if(is_hit_by(spaceship_bullets[bullet])){
            spaceship_bullets.erase(spaceship_bullets.begin() + bullet);
            return false;
        }
    }
    return true;
}
