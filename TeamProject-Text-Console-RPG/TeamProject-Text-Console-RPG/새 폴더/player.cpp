#include "Player.h"

Player::Player() : m_inventory(new Inventory()),
m_money(0), m_hp(100), m_mp(50), m_atk(10), m_def(5)
{
}

Player::~Player()
{
	delete m_inventory;
}

void Player::ShowStat()
{
	system("cls");

	int totalAtk =
		m_atk
		+ m_inventory->GetWeapon()->GetAbility();

	int totalDef =
		m_def
		+ m_inventory->GetArmor()->GetAbility()
		+ m_inventory->GetAccessory()->GetAbility();

	std::cout << "=================================================" << std::endl;

	std::cout << "플레이어의 골드 : "
		<< m_money
		<< std::endl;

	std::cout << "플레이어의 HP : "
		<< m_hp
		<< std::endl;

	std::cout << "플레이어의 MP : "
		<< m_mp
		<< std::endl;

	std::cout << "플레이어의 공격력 : "
		<< m_atk
		<< " + "
		<< m_inventory->GetWeapon()->GetAbility()
		<< " = "
		<< totalAtk
		<< std::endl;

	std::cout << "플레이어의 방어력 : "
		<< m_def
		<< " + "
		<< m_inventory->GetArmor()->GetAbility()
		<< " + "
		<< m_inventory->GetAccessory()->GetAbility()
		<< " = "
		<< totalDef
		<< std::endl;

	std::cout << "=================================================" << std::endl;
}