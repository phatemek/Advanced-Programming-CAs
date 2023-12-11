#ifndef __Spaceship__
#define __Spaceship__
#include "src/rsdl.hpp"
#include "Enemy.hpp"
#include "HostageSpaceship.hpp"
#include <vector>
using namespace std;

class Spaceship {
private:
    Point top_left_corner;
    int width;
    int height;
    int speed_x;
    int speed_y;
public:
    Spaceship(Point _point, int _width, int _height);
    vector<SpaceshipBullet*> spaceship_bullets;
    bool is_inside_x(Window* window);
    bool is_inside_y(Window* window);
    void update(Window* window);
    void shoot();
    void handle_key_press(char key);
    void handle_key_release(char key);
    void draw(Window* window);
    bool is_hit_by_bullet(EnemyBullet* bullet);
    bool is_hit_by_enemy(Enemy* enemy);
    bool is_shot_by(vector<Enemy*> enemies);
    bool crashed_into(vector<Enemy*> enemies);
    bool hit_hostage(HostageSpaceship* hostage);
    bool is_alive(vector<Enemy*> static_enemies, vector<Enemy*> dynamic_enemies, HostageSpaceship* hostage);
};


#endif