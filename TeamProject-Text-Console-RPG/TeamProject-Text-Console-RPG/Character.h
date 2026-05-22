// Character

#pragma once

#include<string>
#include<vector>

#include "Monster.h"
#include "Item.h"

class Character
{
private:
    static Character* instance;

    std::string name;
    std::string job = "무직";
    std::string skillname;
    
    int level = 1 ;
    int hp = 200 ; // 현재체력 
    int maxhp = 200 ; // 최대체력 
    int mp = 100; // 현재마나 
    int maxmp = 100; // 최대마나 
    int attack = 30 ;
    int exp = 0;
    int gold;

    std::vector<Item*> inventory;

public:
    Character(std::string name);

    static Character* getInstance(std::string name = "");

    void Displaystatus();
    void Levelup();
    void Useitem(int index);
    bool Skill(Monster* monster);
    void Additem(string item);
        
    virtual string Attackmessage() = 0;
    virtual bool Skill (Monster* monster) = 0;
    virtual void Basicattack(Monster* monster) = 0;

    //setter 설정
    void Setjob(std::string job) { this->job = job; }
    void Setlevel(int level) { this->level = level; }
    void Sethp(int hp) { this->hp = hp; }
    void Sethp(int maxhp) { this->maxhp = hp; }
    void Setmp(int mp) { this->mp = mp; }
    void Setmp(int maxmp) { this->maxmp = mp; }
    void Setattack(int attack) { this->attack = attack; }
    void Setexp(int exp) { this->exp = exp; }
    void Setgold(int gold) { this->gold = gold; }

    //getter 설정
    string Getjob() { return job; }
    int Getlevel() { return level; }
    int Gethp() { return hp; }
    int Getmaxhp() { return maxhp; }
    int Getmp() { return mp; }
    int Getmaxmp() { return maxmp; }
    int Getattack() { return attack; }
    int Getexp() { return exp; }
    int Getgold() { return gold; }
};