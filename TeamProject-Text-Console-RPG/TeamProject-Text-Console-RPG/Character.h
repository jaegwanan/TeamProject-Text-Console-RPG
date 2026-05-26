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
    std::string job = "¹«Á÷";
    std::string skillname;
    
    int level = 1 ;
    int hp = 200 ; // ?„ìž¬ì²´ë ¥ 
    int maxhp = 200 ; // ìµœë?ì²´ë ¥ 
    int mp = 100; // ?„ìž¬ë§ˆë‚˜ 
    int maxmp = 100; // ìµœë?ë§ˆë‚˜ 
    int attack = 30 ;
    int exp = 0;
    int gold;

    std::vector<Item*> inventory;

public:
    Character(std::string name);

    static Character* getInstance(std::string name = "");

    void Displaystatus();
    void Useitem(int index);
    bool Skill(Monster* monster);
    void Additem(string item);

    // °æÇèÄ¡, ·¹º§ °ü·Ã
    virtual int Getrequiredexp() = 0;
    virtual void Applylevelupstats() = 0;

    void Gainexp(int amount); // °æÇèÄ¡ È¹µæ
    void Printexpbar(); // °æÇèÄ¡¹Ù Ãâ·Â


    virtual string Attackmessage() = 0;
    virtual bool Skill (Monster* monster) = 0;
    virtual void Basicattack(Monster* monster) = 0;

    //setter ?¤ì •
    void Setjob(std::string job) { this->job = job; }
    void Setlevel(int level) { this->level = level; }
    void Sethp(int hp) { this->hp = hp; }
    void Setmaxhp(int maxhp) { this->maxhp = hp; }
    void Setmp(int mp) { this->mp = mp; }
    void Setmaxmp(int maxmp) { this->maxmp = mp; }
    void Setattack(int attack) { this->attack = attack; }
    void Setexp(int exp) { this->exp = exp; }
    void Setgold(int gold) { this->gold = gold; }

    //getter ?¤ì •
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