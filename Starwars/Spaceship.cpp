#include "Spaceship.hpp"
using namespace std;
const int INITIAL_SPACESHIP_SPEED = 0;
const int SPACESHIP_SPEED = 7;
const int BULLET_WIDTH = 7;
const int BULLET_HEIGHT = 30;

Spaceship::Spaceship(Point _point, int _width, int _height) {
    top_left_corner = _point;
    width = _width;
    height = _height;
    speed_x = INITIAL_SPACESHIP_SPEED;
    speed_y = INITIAL_SPACESHIP_SPEED;
}

void Spaceship::draw(Window* window) {
    window->draw_img("images/spaceship.png", Rectangle(top_left_corner, width, height));
}

void Spaceship::handle_key_press(char key) {
    switch (key)
    {
    case 'd':
        speed_x = SPACESHIP_SPEED;
        break;
    case 'a':
        speed_x = -SPACESHIP_SPEED;
        break;
    case 'w':
        speed_y = -SPACESHIP_SPEED;
        break;
    case 's':
        speed_y = SPACESHIP_SPEED;
        break;
    case ' ':
        shoot();
        break;
    }
}

void Spaceship::handle_key_release(char key) {
    switch (key)
    {
    case 'd':
        speed_x = INITIAL_SPACESHIP_SPEED;
        break;
    case 'a':
        speed_x = INITIAL_SPACESHIP_SPEED;
        break;
    case 'w':
        speed_y = INITIAL_SPACESHIP_SPEED;
        break;
    case 's':
        speed_y = INITIAL_SPACESHIP_SPEED;
        break;
    }
}

bool Spaceship::is_inside_x(Window* window) {
    return (top_left_corner.x + speed_x <= window->get_width() - width) && (top_left_corner.x + speed_x >= 0);
}

bool Spaceship::is_inside_y(Window* window) {
    return (top_left_corner.y + speed_y <= window->get_height() - height) && (top_left_corner.y + speed_y >= 0);
}

void Spaceship::update(Window* window) {
    if(is_inside_x(window)) {
        top_left_corner.x += speed_x;
    }
    if(is_inside_y(window)) {
        top_left_corner.y += speed_y;
    }
}

void Spaceship::shoot() {
    Point bullet_location((top_left_corner.x + width/2 - 5), (top_left_corner.y - 50));
    SpaceshipBullet* bullet = new SpaceshipBullet(bullet_location, BULLET_WIDTH, BULLET_HEIGHT);
    spaceship_bullets.push_back(bullet);
}

bool Spaceship::is_hit_by_bullet(EnemyBullet* bullet) {
    return (bullet->get_location().x > top_left_corner.x
         && bullet->get_location().x < top_left_corner.x + width
         && bullet->get_location().y + bullet->get_height() > top_left_corner.y
         && bullet->get_location().y + bullet->get_height() < top_left_corner.y + height);
}

bool Spaceship::is_shot_by(vector<Enemy*> enemies) {
    for(int enemy = 0; enemy < enemies.size(); enemy++) {
        for(int bullet = 0; bullet < enemies[enemy]->enemy_bullets.size(); bullet++) {
            if(is_hit_by_bullet(enemies[enemy]->enemy_bullets[bullet])) {
                return true;
            }
        }
    }
    return false;
}

bool Spaceship::is_hit_by_enemy(Enemy* enemy) {
    return (top_left_corner.x + width > enemy->get_location().x
         && top_left_corner.x < enemy->get_location().x + enemy->get_width()
         && top_left_corner.y + height > enemy->get_location().y
         && top_left_corner.y < enemy->get_location().y + enemy->get_height());
}

bool Spaceship::crashed_into(vector<Enemy*> enemies) {
    for(int enemy = 0; enemy < enemies.size(); enemy++) {
        if(is_hit_by_enemy(enemies[enemy]))
            return true;
    }
    return false;
}

bool Spaceship::hit_hostage(HostageSpaceship* hostage) {
    return (top_left_corner.x + width > hostage->get_location().x
         && top_left_corner.x < hostage->get_location().x + hostage->get_width()
         && top_left_corner.y + height > hostage->get_location().y
         && top_left_corner.y < hostage->get_location().y + hostage->get_height());
}

bool Spaceship::is_alive(vector<Enemy*> static_enemies, vector<Enemy*> dynamic_enemies, HostageSpaceship* hostage) {
    if(is_shot_by(static_enemies) || is_shot_by(dynamic_enemies)
    || crashed_into(static_enemies) || crashed_into(dynamic_enemies)
    || hit_hostage(hostage))
        return false;
    return true;
}
