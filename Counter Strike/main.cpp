#include <iostream>
#include <vector>
#include <algorithm>
#define HEAVY_PRICE 3000
#define HEAVY_DAMAGE 45
#define HEAVY_REWARD_MONEY 100
#define PISTOL_PRICE 400
#define PISTOL_DAMAGE 20
#define PISTOL_REWARD_MONEY 200
#define KNIFE_PRICE 0
#define KNIFE_DAMAGE 35
#define KNIFE_REWARD_MONEY 500
#define INITIAL_PLAYER_HEALTH 100
#define INITIAL_PLAYER_MONEY 1000
#define INITIAL_PLAYER_PLACE "atk"
#define WINNER_TEAM_PRIZE 2700
#define LOSER_TEAM_PRIZE 2400
#define MAX_PLAYER_MONEY 10000

using namespace std;

class Weapon {
    public:
    Weapon(string Name, long Price, int Damage, int RewardMoney) {
        name = Name;
        price = Price;
        damage = Damage;
        rewardMoney = RewardMoney;
    }
    string getName() { return name; }
    long getPrice() { return price; }
    int getDamage() { return damage; }
    int getRewardMoney() {return rewardMoney; }

    private:
    string name;
    long price;
    int damage;
    int rewardMoney;
};

class Player {
    public:
    Player(string Username, string Team, int Health, bool IsAlive, long Money, string Place,
            vector<Weapon> Weapons, int Kills, int Deaths){
        username = Username;
        team = Team;
        health = Health;
        isAlive = IsAlive;
        money = Money;
        place = Place;
        weapons = Weapons;
        kills = Kills;
        deaths = Deaths;
    }

    void setHealth(int Health) { health = Health; }
    void decreaseHealth(int Damage) { health -= Damage; }
    void setIsAlive(bool IsAlive) { isAlive = IsAlive; }
    void setMoney(long Money);
    void addRewardMoney(long RewardMoney);
    void decreaseMoney(long Price) { money -= Price; }
    void setPlace(string Place) { place = Place; }
    void addWeapon(Weapon NewWeapon) { weapons.push_back(NewWeapon); }
    void setWeapons(vector<Weapon> Weapons) { weapons = Weapons; }
    void addToKills() { kills++; }
    void addToDeaths() { deaths++; }

    string getUsername() { return username; }
    string getTeam() { return team; }
    int getHealth() { return health; }
    bool getIsAlive() { return isAlive; }
    long getMoney() { return money; }
    string getPlace() { return place; }
    vector<Weapon> getWeapons() { return weapons; }
    int getKills() { return kills; }
    int getDeaths() { return deaths; }

    private:
    string username;
    string team;
    int health;
    bool isAlive;
    long money;
    string place;
    vector<Weapon> weapons;
    int kills;
    int deaths;
};

void Player::setMoney(long Money) {
    if(Money <= MAX_PLAYER_MONEY)
        money = Money;
    else
        money = MAX_PLAYER_MONEY;
}

void Player:: addRewardMoney(long RewardMoney) {
    if(money + RewardMoney <= MAX_PLAYER_MONEY)
        money += RewardMoney;
    else
        money = MAX_PLAYER_MONEY;
}

void startGame(bool& gameHasStarted) {
    gameHasStarted = true;
    cout << "fight!" << endl;
}

void addUser(bool gameHasStarted, vector<Player>& players, Weapon Knife) {
    vector<Weapon> initial_player_weapons;
    initial_player_weapons.push_back(Knife);
    string Username;
    string Team;
    cin >> Username;
    cin >> Team;

    if(gameHasStarted)
        cout << "you can't add users anymore" << endl;
    else {
        Player Player(Username, Team, INITIAL_PLAYER_HEALTH, true, INITIAL_PLAYER_MONEY,
                      INITIAL_PLAYER_PLACE, initial_player_weapons, 0, 0);
        players.push_back(Player);
        cout << "ok" << endl;
    }
}

void printMoney(vector<Player>& players) {
    string Username;
    cin >> Username;
    for(int player = 0; player < players.size(); player++) {
        if(players[player].getUsername() == Username) {
            cout << players[player].getMoney() << endl;
            break;
        }
    }
}

void printHealth(vector<Player>& players) {
    string Username;
    cin >> Username;
    for(int player = 0; player < players.size(); player++) {
        if(players[player].getUsername() == Username) {
            cout << players[player].getHealth() << endl;
            break;
        }
    }
}

void goAfk(vector<Player>& players) {
    string Username;
    cin >> Username;
    for(int player = 0; player < players.size(); player++) {
        if(players[player].getUsername() == Username) {
            players[player].setPlace("afk");
            cout << "ok" << endl;
            break;
        }
    }
}

void goAtk(vector<Player>& players) {
    string Username;
    cin >> Username;
    for(int player = 0; player < players.size(); player++) {
        if(players[player].getUsername() == Username) {
            players[player].setPlace("atk");
            cout << "ok" << endl;
            break;
        }
    }
}

bool wrongUsername(string playerUsername, vector<Player>& players) {
    for(int player = 0; player < players.size(); player++) {
        if(players[player].getUsername() == playerUsername)
            return false;
    }
    return true;
}

bool playerIsAfk(string playerUsername, vector<Player>& players) {
    for(int player = 0; player < players.size(); player++) {
        if(players[player].getUsername() == playerUsername && players[player].getPlace() == "afk")
            return true;
    }
    return false;
}

bool isDead(string playerUsername, vector<Player>& players) {
    for(int player = 0; player < players.size(); player++) {
        if(players[player].getUsername() == playerUsername && !players[player].getIsAlive())
            return true;
    }
    return false;
}

bool hasWeapon(string username, string attackerWeapon, vector<Player>& players) {
    for(int player = 0; player < players.size(); player++) {
        if(players[player].getUsername() == username) {
            for(int weapon = 0; weapon < players[player].getWeapons().size(); weapon++) {
                if(players[player].getWeapons()[weapon].getName() == attackerWeapon)
                    return true;
            }
            return false;
        }
    }
    return false;
}

bool sameTeam(string attackerUsername, string attackedUsername, vector<Player>& players) {
    string attackerTeam;
    string attackedTeam;
    for(int player = 0; player < players.size(); player++) {
        if(players[player].getUsername() == attackerUsername)
            attackerTeam = players[player].getTeam();
        else if(players[player].getUsername() == attackedUsername)
            attackedTeam = players[player].getTeam();
    }
    if(attackerTeam == attackedTeam)
        return true;
    else
        return false;
}

void shoot(string attackerUsername, string attackedUsername, string attackerWeapon, vector<Player>& players,
           vector<Weapon>& gameWeapons) {
    bool attackedDied = false;
    int weaponDamage;
    int weaponRewardMoney;

    for(int weapon = 0; weapon < gameWeapons.size(); weapon++) {
        if(gameWeapons[weapon].getName() == attackerWeapon) {
            weaponDamage = gameWeapons[weapon].getDamage();
            weaponRewardMoney = gameWeapons[weapon].getRewardMoney();
        break;
        }
    }

    for(int player = 0; player < players.size(); player++) {
        if(players[player].getUsername() == attackedUsername) {
            if(players[player].getHealth() - weaponDamage <= 0)
                attackedDied = true;
        }
    }

    for(int player = 0; player < players.size(); player++) {
        if(players[player].getUsername() == attackerUsername) {
            if(attackedDied) {
                players[player].addToKills();
                players[player].addRewardMoney(weaponRewardMoney);
            }
        }
        else if(players[player].getUsername() == attackedUsername) {
            if(attackedDied) {
                players[player].setHealth(0);
                players[player].setIsAlive(false);
                players[player].addToDeaths();
            }
            else
                players[player].decreaseHealth(weaponDamage);
        }
    }
}

void checkShot(bool gameHasStarted, vector<Player>& players, vector<Weapon>& gameWeapons) {
    string attacker;
    string attacked;
    string attackerWeapon;
    cin >> attacker;
    cin >> attacked;
    cin >> attackerWeapon;

    if(!gameHasStarted)
        cout << "The game hasn't started yet" << endl;

    else if(wrongUsername(attacker, players) || wrongUsername(attacked, players) || playerIsAfk(attacker, players)
            || playerIsAfk(attacked, players))
        cout << "user not available" << endl;

    else if(isDead(attacker, players))
        cout << "attacker is dead" << endl;

    else if(isDead(attacked, players))
        cout << "attacked is dead" << endl;

    else if(!hasWeapon(attacker, attackerWeapon, players))
        cout << "attacker doesn't have this gun" << endl;

    else if(sameTeam(attacker, attacked, players))
        cout << "you can't shoot this player" << endl;
    
    else {
        shoot(attacker, attacked, attackerWeapon, players, gameWeapons);
        cout << "nice shot" << endl;
    }
}

bool wrongWeaponName(string weaponName) {
    return !(weaponName == "heavy" || weaponName == "pistol" || weaponName == "knife");
}

bool alreadyHasWeapon(string playerUsername, string weaponName, vector<Player>& players) {
    for(int player = 0; player < players.size(); player++) {
        if(players[player].getUsername() == playerUsername) {
            for(int weapon = 0; weapon < players[player].getWeapons().size(); weapon++) {
                if(players[player].getWeapons()[weapon].getName() == weaponName)
                    return true;
            }
            return false;
        }
    }
    return false;
}

bool insufficientMoney(string playerUsername, string weaponName, vector<Player>& players, vector<Weapon>& gameWeapons) {
    int weaponPrice;
    int playerMoney;

    for(int weapon = 0; weapon < gameWeapons.size(); weapon++) {
        if(gameWeapons[weapon].getName() == weaponName) {
            weaponPrice = gameWeapons[weapon].getPrice();
            break;
        }
    }

    for(int player = 0; player < players.size(); player++) {
        if(players[player].getUsername() == playerUsername) {
            playerMoney = players[player].getMoney();
            break;
        }
    }

    return (playerMoney < weaponPrice);
}

void buyWeapon(string playerUsername, string weaponName, vector<Player>& players, vector<Weapon>& gameWeapons) {
    for(int player = 0; player < players.size(); player++) {
        if(players[player].getUsername() == playerUsername) {
            for(int weapon = 0; weapon < gameWeapons.size(); weapon++) {
                if(gameWeapons[weapon].getName() == weaponName) {
                    players[player].decreaseMoney(gameWeapons[weapon].getPrice());
                    players[player].addWeapon(gameWeapons[weapon]);
                }
            }
            break;
        }
    }
}

void checkBuy(bool gameHasStarted, vector<Player>& players, vector<Weapon>& gameWeapons) {
    string playerUsername;
    string weaponName;
    cin >> playerUsername;
    cin >> weaponName;

    if(wrongUsername(playerUsername, players) || playerIsAfk(playerUsername, players))
        cout << "user not available" << endl;

    else if(gameHasStarted)
        cout << "you can't buy weapons anymore" << endl;

    else if(wrongWeaponName(weaponName))
        cout << "weapon not available" << endl;

    else if(alreadyHasWeapon(playerUsername, weaponName, players)) 
        cout << "you already have this weapon" << endl;

    else if(insufficientMoney(playerUsername, weaponName, players, gameWeapons))
        cout << "insufficient money" << endl;

    else {
        buyWeapon(playerUsername, weaponName, players, gameWeapons);
        cout << "weapon bought successfully" << endl;
    }
}

bool playerSorter(Player& firstPlayer, Player& secondPlayer) {
    if(firstPlayer.getKills() != secondPlayer.getKills())
        return firstPlayer.getKills() > secondPlayer.getKills();

    if(firstPlayer.getDeaths() != secondPlayer.getDeaths())
        return firstPlayer.getDeaths() < secondPlayer.getDeaths();

    return firstPlayer.getUsername() < secondPlayer.getUsername();
}

void printScoreBoard(vector<Player>& players) {
    vector<Player> terroristPlayers;
    vector<Player> counterPlayers;
    for(int player = 0; player < players.size(); player++) {
        if(players[player].getTeam() == "terrorist") 
            terroristPlayers.push_back(players[player]);
        else
            counterPlayers.push_back(players[player]);
    }
    sort(terroristPlayers.begin(), terroristPlayers.end(), &playerSorter);
    sort(counterPlayers.begin(), counterPlayers.end(), &playerSorter);

    cout << "counter-terrorist players:" << endl;
    for(int counter = 0; counter < counterPlayers.size(); counter++) {
        cout << counterPlayers[counter].getUsername() << ' ' << counterPlayers[counter].getKills() << ' ' <<
                counterPlayers[counter].getDeaths() << endl;
    }
    cout << "terrorist players:" << endl;
    for(int terrorist = 0; terrorist < terroristPlayers.size(); terrorist++) {
        cout << terroristPlayers[terrorist].getUsername() << ' ' << terroristPlayers[terrorist].getKills() << ' ' <<
                terroristPlayers[terrorist].getDeaths() << endl;
    }
}

void perform(string command, bool& gameHasStarted, vector<Player>& players, vector<Weapon>& gameWeapons) {
    if(command == "start")
        startGame(gameHasStarted);

    else if(command == "add-user")
        addUser(gameHasStarted, players, gameWeapons[2]);

    else if(command == "get-money")
        printMoney(players);

    else if(command == "get-health")
        printHealth(players);

    else if(command == "go-afk")
        goAfk(players);

    else if(command == "go-atk")
        goAtk(players);

    else if(command == "shoot")
        checkShot(gameHasStarted, players, gameWeapons);

    else if(command == "buy")
        checkBuy(gameHasStarted, players, gameWeapons);

    else if(command == "score-board")
        printScoreBoard(players);
    
    else {
        string etc;
        cin >> etc;
    }
}

string calculateWinnerTeam(vector<Player>& players) {
    bool counterTerroristsWin = false;
    for(int player = 0; player < players.size(); player++) {
        if(players[player].getTeam() == "counter-terrorist" && players[player].getIsAlive() == true)
            counterTerroristsWin = true;
    }
    if(counterTerroristsWin)
        return "counter-terrorist";
    else
        return "terrorist";
}

void resetPlayers(vector<Player>& players, vector<Weapon> gameWeapons, string winnerTeam) {
    vector<Weapon> initial_player_weapons;
    initial_player_weapons.push_back(gameWeapons[2]);
    for(int player = 0; player < players.size(); player++) {
        players[player].setHealth(INITIAL_PLAYER_HEALTH);
        if(!players[player].getIsAlive()) 
            players[player].setWeapons(initial_player_weapons);
        players[player].setIsAlive(true);
        if(players[player].getTeam() == winnerTeam)
            players[player].addRewardMoney(WINNER_TEAM_PRIZE);
        else
            players[player].addRewardMoney(LOSER_TEAM_PRIZE);
    }
}

void printWinnerTeam(string winnerTeam) {
    if(winnerTeam == "terrorist")
        cout << "terrorist won" << endl;
    else
        cout << "counter-terrorist won" << endl;
}

void playRound(bool& gameHasStarted, vector<Player>& players, vector<Weapon>& gameWeapons) {
    while(true) {
        string command;
        cin >> command;
        if(command == "add-user" || command == "score-board")
            perform(command, gameHasStarted, players, gameWeapons);
        else
            break;
    }
    int roundCommandCount;
    cin >> roundCommandCount;
    for(int command = 0; command < roundCommandCount; command++) {
        string roundCommand;
        cin >> roundCommand;
        perform(roundCommand, gameHasStarted, players, gameWeapons);
    }
    string winnerTeam;
    winnerTeam = calculateWinnerTeam(players);
    printWinnerTeam(winnerTeam);
    resetPlayers(players, gameWeapons, winnerTeam);
}

void arena() {
    Weapon Heavy("heavy", HEAVY_PRICE, HEAVY_DAMAGE, HEAVY_REWARD_MONEY);
    Weapon Pistol("pistol", PISTOL_PRICE, PISTOL_DAMAGE, PISTOL_REWARD_MONEY);
    Weapon Knife("knife", KNIFE_PRICE, KNIFE_DAMAGE, KNIFE_REWARD_MONEY);
    vector<Weapon> gameWeapons;
    gameWeapons.push_back(Heavy);
    gameWeapons.push_back(Pistol);
    gameWeapons.push_back(Knife);
    vector<Player> players;
    bool gameHasStarted = false;
    int roundsCount;
    string optionalCommand;
    
    cin >> roundsCount;
    for(int round = 0; round < roundsCount; round++) {
        playRound(gameHasStarted, players, gameWeapons);
    }
    cin >> optionalCommand;
    perform(optionalCommand, gameHasStarted, players, gameWeapons);
}

int main() {
    arena();
    return 0;
}
