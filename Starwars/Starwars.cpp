#include "Starwars.hpp"

using namespace std;

const int STATIC_ENEMIES_FRAME_GAP = 0;
const int DYNAMIC_ENEMIES_FRAME_GAP = 50;

const int WINDOW_WIDTH = 1000;
const int WINDOW_HEIGHT = 700;
const int SPACESHIP_WIDTH = 60;
const int SPACESHIP_HEIGHT = 100;
const int ENEMY_WIDTH = 80;
const int ENEMY_HEIGHT = 65;

Starwars::Starwars() {
    vector<Enemy*> static_enemies;
    vector<Enemy*> dynamic_enemies;
    window = new Window(WINDOW_WIDTH, WINDOW_HEIGHT, "RSDL");
    spaceship_pointer = new Spaceship(Point(500, 600), SPACESHIP_WIDTH, SPACESHIP_HEIGHT);
    hostage_spaceship_pointer = new HostageSpaceship(Point(600, 10), SPACESHIP_WIDTH, SPACESHIP_HEIGHT);
    past_frames = 0;
    game_is_over = false;
}

void Starwars::make_enemies() {
    for(int i = 0; i < 5; i++) {
        Enemy* static_enemy_pointer = new StaticEnemy(Point(200*i+50, 100), ENEMY_WIDTH, ENEMY_HEIGHT);
        static_enemies.push_back(static_enemy_pointer);
    }

    for(int i = 0; i < 4; i++) {
        Enemy* dynamic_enemy_pointer = new DynamicEnemy(Point(200*i+100, 200), ENEMY_WIDTH, ENEMY_HEIGHT);
        dynamic_enemies.push_back(dynamic_enemy_pointer);
    }
}

void Starwars::handle_events() {
    while(window->has_pending_event()) {
        Event event = window->poll_for_event();
        char key;
        switch (event.get_type())
        {
        case Event::EventType::QUIT:
            game_is_over = true;
            break;
        case Event::EventType::KEY_PRESS:
            key = event.get_pressed_key();
            spaceship_pointer->handle_key_press(key);
            break;
        case Event::EventType::KEY_RELEASE:
            key = event.get_pressed_key();
            spaceship_pointer->handle_key_release(key);
            break;
        }
    }
} 

void Starwars::move_dynamic_enemies() {
    for(int enemy = 0; enemy < dynamic_enemies.size(); enemy++) {
        dynamic_enemies[enemy]->handle_movement(window);
        dynamic_enemies[enemy]->update(window);
    }
}

void Starwars::move_spaceship_bullets() {
    for(int bullet = 0; bullet < spaceship_pointer->spaceship_bullets.size(); bullet++) {
        spaceship_pointer->spaceship_bullets[bullet]->update();
        if(spaceship_pointer->spaceship_bullets[0]->get_location().y <= 0) {
            spaceship_pointer->spaceship_bullets.erase(spaceship_pointer->spaceship_bullets.begin());
        }
    }
}

void Starwars::handle_enemy_bullets(vector<Enemy*>& enemies, int frame_gap) {
    if((past_frames + frame_gap) % 100 == 0) {
        for(int enemy = 0; enemy < enemies.size(); enemy++) {
            enemies[enemy]->shoot();
        }
    }

    for(int enemy = 0; enemy < enemies.size(); enemy++) {
        for(int bullet = 0; bullet < enemies[enemy]->enemy_bullets.size(); bullet++) {
            enemies[enemy]->enemy_bullets[bullet]->update();
            if(enemies[enemy]->enemy_bullets[0]->get_location().y >= window->get_height()) {
                enemies[enemy]->enemy_bullets.erase(enemies[enemy]->enemy_bullets.begin());
            }
        }
    }
}

void Starwars::handle_spaceship_death() {
    if(!spaceship_pointer->is_alive(static_enemies, dynamic_enemies, hostage_spaceship_pointer)
    || !hostage_spaceship_pointer->is_alive(spaceship_pointer->spaceship_bullets))
        game_is_over = true;
}

void Starwars::handle_enemies_death(vector<Enemy*>& enemies) {
    for(int enemy = 0; enemy < enemies.size(); enemy++) {
        if(!enemies[enemy]->is_alive(spaceship_pointer->spaceship_bullets)) {
            enemies.erase(enemies.begin() + enemy);
        }
    }
}

void Starwars::handle_deaths() {
    handle_spaceship_death();
    handle_enemies_death(static_enemies);
    handle_enemies_death(dynamic_enemies);
}

void Starwars::update_window() {
    handle_events();
    spaceship_pointer->update(window);
    move_dynamic_enemies();
    move_spaceship_bullets();
    handle_enemy_bullets(static_enemies, STATIC_ENEMIES_FRAME_GAP);
    handle_enemy_bullets(dynamic_enemies, DYNAMIC_ENEMIES_FRAME_GAP);
    handle_deaths();
    past_frames++;
}

void Starwars::draw_enemies(vector<Enemy*> enemies) {
    for(int enemy = 0; enemy < enemies.size(); enemy++) {
        enemies[enemy]->draw(window);
    }
}

void Starwars::draw_spaceship_bullets(vector<SpaceshipBullet*> spaceship_bullets) {
    for(int bullet = 0; bullet < spaceship_bullets.size(); bullet++) {
        spaceship_bullets[bullet]->draw(window);
    }
}

void Starwars::draw_enemies_bullets(vector<Enemy*> enemies, string bullet_image) {
    for(int enemy = 0; enemy < enemies.size(); enemy++) {
        for(int bullet = 0; bullet < enemies[enemy]->enemy_bullets.size(); bullet++) {
            enemies[enemy]->enemy_bullets[bullet]->draw(window, bullet_image);
        }
    }
}

void Starwars::draw_bullets() {
    draw_spaceship_bullets(spaceship_pointer->spaceship_bullets);
    draw_enemies_bullets(static_enemies, "images/staticenemybullet.png");
    draw_enemies_bullets(dynamic_enemies, "images/dynamicenemybullet.png");
}

void Starwars::draw_spaceships() {
    spaceship_pointer->draw(window);
    hostage_spaceship_pointer->draw(window);
}

void Starwars::draw_window() {
    window->clear();
    window->draw_img("images/space.png");
    draw_spaceships();
    draw_enemies(static_enemies);
    draw_enemies(dynamic_enemies);
    draw_bullets();
    window->update_screen();
}

void Starwars::game_over() {
    window->clear();
    if(!enemies_are_alive()) {
        window->draw_img("images/youwin.png");
    }
    else {
        window->draw_img("images/gameover.jpg");
    }
    window->update_screen();
    delay(2000);
}

bool Starwars::enemies_are_alive() {
    return !(static_enemies.size() == 0 && dynamic_enemies.size() == 0);
}

void Starwars::run_game() {
    make_enemies();
    while(!game_is_over && enemies_are_alive()){
        window->play_music("images/tetris.mp3");
        update_window();
        draw_window();
        delay(15);
    }
    game_over();
}
