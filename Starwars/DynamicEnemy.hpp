#ifndef __DynamicEnemy__
#define __DynamicEnemy__
#include "src/rsdl.hpp"
#include "Enemy.hpp"
using namespace std;

class DynamicEnemy : public Enemy {
protected:
    int speed_x;
public:
    DynamicEnemy(Point _point, int _width, int _height);
    virtual void handle_movement(Window* window);
    virtual void update(Window* window);
    virtual void draw(Window* window);
};

#endif