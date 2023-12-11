#include "src/rsdl.hpp"
#include "SpaceshipBullet.hpp"
#include "EnemyBullet.hpp"
#include "Spaceship.hpp"
#include "HostageSpaceship.hpp"
#include "Enemy.hpp"
#include "StaticEnemy.hpp"
#include "DynamicEnemy.hpp"
#include "Starwars.hpp"
#include <vector>
#include <string>

using namespace std;

int main() {
    Starwars starwars;
    starwars.run_game();
    return 0;
}
