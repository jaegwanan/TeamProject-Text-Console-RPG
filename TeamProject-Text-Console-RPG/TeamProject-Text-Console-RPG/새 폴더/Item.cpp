#include "Item.h"

// 생성자
Item::Item(
	ITEM itemType,
	string name,
	int price,
	int ability,
	string description,
	int count
)
	:
	m_itemType(itemType),
	m_name(name),
	m_price(price),
	m_ability(ability),
	m_description(description),
	m_count(count)
{
}

// 아이템 정보 출력 함수
void Item::ShowItemInfo()
{
	std::cout << "이름 : " << m_name << std::endl;

	std::cout << "타입 : ";

	switch (m_itemType)
	{
	case ITEM::ITEM_WEAPON:
		std::cout << "무기";
		break;

	case ITEM::ITEM_ARMOR:
		std::cout << "방어구";
		break;

	case ITEM::ITEM_ACCESSORY:
		std::cout << "장신구";
		break;

	case ITEM::ITEM_HP_POTION:
		std::cout << "포션";
		break;

	case ITEM::ITEM_MP_POTION:
		std::cout << "MP 포션";
		break;

	case ITEM::ITEM_ATTACK_POTION:
		std::cout << "공격력 증가 포션";
		break;

	default:
		std::cout << "없음";
		break;
	}

	std::cout << std::endl;

	std::cout << "가격 : " << m_price << std::endl;
	std::cout << "능력치 : " << m_ability << std::endl;
	std::cout << "설명 : " << m_description << std::endl;
	std::cout << "수량 : " << m_count << std::endl;
}