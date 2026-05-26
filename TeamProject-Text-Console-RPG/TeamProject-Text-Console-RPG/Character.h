// Character

#pragma once

#include<string>
#include<vector>

#include "Monster.h"
#include "Item.h"

class Character
{
protected:
    static Character* instance;

    std::string name;
    std::string job = "무직";
    std::string skillname;
    
    int level = 1 ;
    int hp = 200 ; 
    int maxhp = 200 ; 
    int mp = 100; 
    int maxmp = 100; 
    int attack = 30 ;
    int exp = 0;
    int gold = 0;

    std::vector<Item*> inventory;

public:
    Character(std::string name);

    static Character* getInstance(std::string name = "");
    virtual ~Character() {}

    void Displaystatus();
    void Levelup();
    /*void Useitem(int index);
    bool Skill(Monster* monster);
    void Additem(string item);*/
        
    virtual std::string Attackmessage() = 0;
 
    void Basicattack(Monster* monster);
    void Takedamage(int monsterattack);

    //경험치 관련
    void Gainexp(int amount);
    void Printexpbar();
    virtual int Getrequiredexp() = 0;
    virtual void Applylevelupstats() = 0;

    //setter
    void Setjob(std::string job) { this->job = job; }
    void Setlevel(int level) { this->level = level; }
    void Sethp(int hp) { this->hp = hp; }
    void Setmaxhp(int maxhp) { this->maxhp = maxhp; }
    void Setmp(int mp) { this->mp = mp; }
    void Setmaxmp(int maxmp) { this->maxmp = maxmp; }
    void Setattack(int attack) { this->attack = attack; }
    void Setexp(int exp) { this->exp = exp; }
    void Setgold(int gold) { this->gold = gold; }

    //getter 
    std::string Getjob() { return job; }
    int Getlevel() { return level; }
    int Gethp() { return hp; }
    int Getmaxhp() { return maxhp; }
    int Getmp() { return mp; }
    int Getmaxmp() { return maxmp; }
    int Getattack() { return attack; }
    int Getexp() { return exp; }
    int Getgold() { return gold; }
};