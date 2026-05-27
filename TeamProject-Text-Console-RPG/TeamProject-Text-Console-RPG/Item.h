#pragma once

#include "Header.h"

class Item
{
private:
    ITEM m_itemType;

    string m_name;

    int m_price;

    int m_ability;

    string m_description;

    int m_count;

public:
    // »ý¼ºÀÚ
    Item(
        ITEM itemType,
        string name,
        int price,
        int ability,
        string description,
        int count
    );

    ITEM GetType()
    {
        return m_itemType;
    }

    void SetType(const ITEM itemType)
    {
        m_itemType = itemType;
    }

    string GetName()
    {
        return m_name;
    }

    void SetName(const string name)
    {
        m_name = name;
    }

    int GetPrice()
    {
        return m_price;
    }

    void SetPrice(const int price)
    {
        m_price = price;
    }

    int GetAbility()
    {
        return m_ability;
    }

    void SetAbility(const int ability)
    {
        m_ability = ability;
    }

    string GetDescription()
    {
        return m_description;
    }

    void SetDescription(const string description)
    {
        m_description = description;
    }

    int GetCount()
    {
        return m_count;
    }

    void SetCount(const int count)
    {
        m_count = count;
    }

    void ShowItemInfo();
};