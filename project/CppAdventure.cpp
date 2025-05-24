#include<iostream>
#include<string>


class Character {
protected:
    std::string name;
    int hp;
    int attackPower;

public:
    Character(const std::string& name, int hp, int attackPower)
        : name(name), hp(hp), attackPower(attackPower) {}

    virtual ~Character() = default;
    
    virtual void attack(Character& target);
    void takeDamage(int damage);
    bool isAlive() const;

    std::string getName() const { return name;}
    int getHp() const { return hp; };
};

class Player : public Character {
public: 
    Player(const std::string& name)
        : Character(name, 100, 15) {}
};

class Monster : public Character {
public:
    Monster(const std::string& name, int hp, int attackPower) 
        : Character(name, hp, attackPower) {}
};

class BattleManager {
public:
    void startBattle(Player& player, Monster& monster);
};

class Game{
public:
    void run();
};

void Character::attack(Character& target) {
    std::cout<< name << " attacks " << target.getName() << " for " << attackPower << " damage.\n";
    target.takeDamage(attackPower);
}

void Character::takeDamage(int damage)
{
    hp -= damage;
    if (hp < 0) hp = 0;
}

bool Character::isAlive() const {
    return hp > 0;
}

void BattleManager::startBattle(Player& player, Monster& monster) {
    std::cout << "Battle Start: " << player.getName() << " vs" << monster.getName() << "\n";
    while (player.isAlive() && monster.isAlive()) {
        player.attack(monster);
        if (!monster.isAlive()) break;
        monster.attack(player);
    }

    if (player.isAlive())
        std::cout << player.getName() << " wins!\n";
    else
        std::cout<< player.getName() << "wins!\n";
}

void Game::run() {
    std::string playerName;
    std::cout<<"Enter your name: ";
    std::getline(std::cin, playerName);

    Player player(playerName);
    Monster goblin("Goblin", 50, 10);

    BattleManager battle;
    battle.startBattle(player, goblin);
}
int main()
{
    Game game;
    game.run();
    return 0;
}