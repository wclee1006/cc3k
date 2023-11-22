#ifndef __Player__H
#define __Player__H
#include "Character.h"
#include "Info.h"

class Potion;

class Player : public Character {
    protected:
    int gold = 0; //How much gold the player has accumulated starting from the beginning of the game
    bool bSuit = false; //False if the player does not have the Barrier Suit, true if the player does have the Barrier Suit
    bool compass = false;
    bool onStair = false;
    bool isDead = false;
    std::string race; //to tell the display what race is the player
    std::string action; // to tell the display what player just did

    public:
    void actionfloor();
    bool Isitonstair();
    bool getisDead();
    void move(Direction dir);
    void attack(Direction dir);
    void use(Direction dir);
    int getgold();
    std::string getrace();
    std::string getaction();
    std::string getDisplay() const override;
    void isOnStair(bool onStair = true);
    void hasSuit(bool bSuit= true);
    void hasCompass(bool compass= true);
    explicit
      Player();
    virtual ~Player();
    virtual void gainGold(int gain) = 0; //Is called to increment the Player’s integer field gold whenever they gain gold
    virtual void applyPotion(Potion &pot) = 0; //Is called to modify one of the Player’s stats whenever they use a potion 
    virtual void resetAtkDef() = 0; //Is called every time the Player begins a new floor to reset their ATK and DEF stats. Does NOT affect HP
    void newTurn() override;
    void attacksOn(Enemy &enemy) override;
    int attackedBy(int enemyAtk) override;
    void attacked(CellContent &attacker) override;

    virtual void updateinfo();
};

#endif
