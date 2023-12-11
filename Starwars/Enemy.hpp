#ifndef __Enemy__
#define __Enemy__
#include "src/rsdl.hpp"
#include "EnemyBullet.hpp"
#include "SpaceshipBullet.hpp"
#include <vector>
using namespace std;

class Enemy {
protected:
    Point top_left_corner;
    int width;
    int height;
public:
    Enemy(Point _point, int _width, int _height);
    vector<EnemyBullet*> enemy_bullets;
    int get_width();
    int get_height();
    Point get_location();
    void shoot();
    bool is_hit_by(SpaceshipBullet* bullet);
    bool is_alive(vector<SpaceshipBullet*>& spaceship_bullets);
    virtual void handle_movement(Window* window) = 0;
    virtual void update(Window* window) = 0;
    virtual void draw(Window* window) = 0;
};

#endif