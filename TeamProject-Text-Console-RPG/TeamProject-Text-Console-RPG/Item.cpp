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
    cout << "이름 : " << m_name << endl;

    cout << "타입 : ";

    switch (m_itemType)
    {
    case ITEM::ITEM_WEAPON:
        cout << "무기";
        break;

    case ITEM::ITEM_ARMOR:
        cout << "방어구";
        break;

    case ITEM::ITEM_ACCESSORY:
        cout << "장신구";
        break;

    case ITEM::ITEM_HP_POTION:
        cout << "HP 포션";
        break;

    case ITEM::ITEM_MP_POTION:
        cout << "MP 포션";
        break;

    case ITEM::ITEM_ATTACK_POTION:
        cout << "공격력 증가 포션";
        break;
    case ITEM::ITEM_DETOX_POTION:
        cout << "해독제";
        break;

    default:
        cout << "없음";
        break;
    }

    cout << endl;

    cout << "가격 : " << m_price << endl;
    cout << "능력치 : " << m_ability << endl;
    cout << "설명 : " << m_description << endl;
    cout << "수량 : " << m_count << endl;
}