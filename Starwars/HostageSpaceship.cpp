#include "HostageSpaceship.hpp"
using namespace std;

HostageSpaceship::HostageSpaceship(Point _top_left_corner, int _width, int _height) {
    top_left_corner = _top_left_corner;
    width = _width;
    height = _height;
}

Point HostageSpaceship::get_location() {
    return top_left_corner;
}

int HostageSpaceship::get_width() {
    return width;
}

int HostageSpaceship::get_height() {
    return height;
}

void HostageSpaceship::draw(Window* window) {
    window->draw_img("images/hostage.png", Rectangle(top_left_corner, width, height));
}

bool HostageSpaceship::is_hit_by(SpaceshipBullet* bullet) {
    return (bullet->get_location().x > top_left_corner.x
         && bullet->get_location().x < top_left_corner.x + width
         && bullet->get_location().y > top_left_corner.y
         && bullet->get_location().y < top_left_corner.y + height);
}

bool HostageSpaceship::is_alive(vector<SpaceshipBullet*> spaceship_bullets) {
    for(int bullet = 0; bullet < spaceship_bullets.size(); bullet++) {
        if(is_hit_by(spaceship_bullets[bullet]))
            return false;
    }
    return true;
}