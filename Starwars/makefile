CC := g++ --std=c++11
CCFLAGS += -l SDL2 -l SDL2_image -l SDL2_ttf -l SDL2_mixer

all: starwars.out

starwars.out: main.o SpaceshipBullet.o EnemyBullet.o Spaceship.o HostageSpaceship.o Enemy.o StaticEnemy.o DynamicEnemy.o Starwars.o rsdl.o
	$(CC) main.o SpaceshipBullet.o EnemyBullet.o Spaceship.o HostageSpaceship.o Enemy.o StaticEnemy.o DynamicEnemy.o Starwars.o rsdl.o $(CCFLAGS) -o starwars.out

main.o: src/rsdl.hpp SpaceshipBullet.hpp EnemyBullet.hpp Spaceship.hpp HostageSpaceship.hpp Enemy.hpp StaticEnemy.hpp DynamicEnemy.hpp Starwars.hpp main.cpp
	$(CC) -c main.cpp -o main.o

SpaceshipBullet.o: SpaceshipBullet.hpp src/rsdl.hpp SpaceshipBullet.cpp
	$(CC) -c SpaceshipBullet.cpp -o SpaceshipBullet.o

EnemyBullet.o: EnemyBullet.hpp src/rsdl.hpp EnemyBullet.cpp
	$(CC) -c EnemyBullet.cpp -o EnemyBullet.o

Spaceship.o: Spaceship.hpp src/rsdl.hpp HostageSpaceship.hpp Enemy.hpp Spaceship.cpp
	$(CC) -c Spaceship.cpp -o Spaceship.o

HostageSpaceship.o: HostageSpaceship.hpp src/rsdl.hpp SpaceshipBullet.hpp HostageSpaceship.cpp
	$(CC) -c HostageSpaceship.cpp -o HostageSpaceship.o

Enemy.o: Enemy.hpp src/rsdl.hpp EnemyBullet.hpp SpaceshipBullet.hpp Enemy.cpp
	$(CC) -c Enemy.cpp -o Enemy.o

StaticEnemy.o: StaticEnemy.hpp src/rsdl.hpp Enemy.hpp StaticEnemy.cpp
	$(CC) -c StaticEnemy.cpp -o StaticEnemy.o

DynamicEnemy.o: DynamicEnemy.hpp src/rsdl.hpp Enemy.hpp DynamicEnemy.cpp
	$(CC) -c DynamicEnemy.cpp -o DynamicEnemy.o

Starwars.o: Starwars.hpp src/rsdl.hpp HostageSpaceship.hpp Enemy.hpp Spaceship.hpp StaticEnemy.hpp DynamicEnemy.hpp Starwars.cpp
	$(CC) -c Starwars.cpp -o Starwars.o

rsdl.o: src/rsdl.hpp src/rsdl.cpp
	$(CC) -c src/rsdl.cpp -o rsdl.o

.PHONY: clean
clean:
	rm -r *.o
