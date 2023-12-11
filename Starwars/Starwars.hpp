#ifndef __Starwars__
#define __Starwars__
#include "src/rsdl.hpp"
#include "Enemy.hpp"
#include "HostageSpaceship.hpp"
#include "Spaceship.hpp"
#include "StaticEnemy.hpp"
#include "DynamicEnemy.hpp"
#include <vector>
using namespace std;

class Starwars {
private:
    Window* window;
    Spaceship* spaceship_pointer;
    HostageSpaceship* hostage_spaceship_pointer;
    vector<Enemy*> static_enemies;
    vector<Enemy*> dynamic_enemies;
    long past_frames;
    bool game_is_over;
public:
    Starwars();
    void make_enemies();
    void handle_events();
    void move_dynamic_enemies();
    void move_spaceship_bullets();
    void handle_enemy_bullets(vector<Enemy*>& enemies, int frame_gap);
    void handle_spaceship_death();
    void handle_enemies_death(vector<Enemy*>& enemies);
    void handle_deaths();
    void update_window();
    void draw_spaceships();
    void draw_enemies(vector<Enemy*> enemies);
    void draw_spaceship_bullets(vector<SpaceshipBullet*> spaceship_bullets);
    void draw_enemies_bullets(vector<Enemy*> enemies, string bullet_image);
    void draw_bullets();
    void draw_window();
    void run_game();
    bool enemies_are_alive();
    void game_over();
};

#endif