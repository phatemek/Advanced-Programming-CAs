#ifndef __StaticEnemy__
#define __StaticEnemy__
#include "src/rsdl.hpp"
#include "Enemy.hpp"
using namespace std;

class StaticEnemy : public Enemy {
public:
    StaticEnemy(Point _point, int width, int height);
    virtual void handle_movement(Window* window);
    virtual void update(Window* window);
    virtual void draw(Window* window);
};

#endif