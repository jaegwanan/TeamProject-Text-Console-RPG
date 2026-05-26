#pragma once

#include "Header.h"
#include "Inventory.h"

class Player
{
private:
	Inventory* m_inventory; // 인벤토리

	int m_money; // 돈

	int m_hp; // 체력
	int m_mp; // 마나

	int m_atk; // 공격력
	int m_def; // 방어력

public:
	Player();
	~Player();

	Inventory* GetInventory() { return m_inventory; }

	int GetMoney() { return m_money; }
	void SetMoney(int money) { m_money = money; }

	int GetHp() { return m_hp; }
	void SetHp(int hp) { m_hp = hp; }

	int GetMp() { return m_mp; }
	void SetMp(int mp) { m_mp = mp; }

	int GetAtk() { return m_atk; }
	void SetAtk(int atk) { m_atk = atk; }

	int GetDef() { return m_def; }
	void SetDef(int def) { m_def = def; }

	void ShowStat();
};