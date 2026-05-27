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
    int attack = 10 ;
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

    virtual bool Skill(Monster* monster) = 0;
    virtual std::string Getskillname() = 0;

    //경험치 관련
    void Gainexp(int amount);
    void Printexpbar();
    virtual int Getrequiredexp() = 0;
    virtual void Applylevelupstats() = 0;

    // setter
    void Setjob(std::string job);
    void Setlevel(int level);
    void Sethp(int hp);
    void Setmaxhp(int maxhp);
    void Setmp(int mp);
    void Setmaxmp(int maxmp);
    void Setattack(int attack);
    void Setexp(int exp);
    void Setgold(int gold);

    // getter
    std::string Getjob();
    int Getlevel();
    int Gethp();
    int Getmaxhp();
    int Getmp();
    int Getmaxmp();
    int Getattack();
    int Getexp();
    int Getgold();
};