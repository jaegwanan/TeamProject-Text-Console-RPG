#include "Inventory.h"
#include "Character.h"

// 생성자
Inventory::Inventory()
    : m_bagItemCount(0),
    m_inventorySelectNum((int)INVENTORY::INVENTORY_TOWN)
{
    m_equipWeapon = new Item(
        ITEM::ITEM_WEAPON,
        "평범한 장검",
        10,
        5,
        "어느 상점에서나 살 수 있는 장검",
        1
    );

    m_equipArmor = new Item(
        ITEM::ITEM_ARMOR,
        "더러운 옷",
        0,
        0,
        "처음 공장에서 만들어졌을 때는 깨끗했을거야.",
        1
    );

    m_equipAccessory = new Item(
        ITEM::ITEM_ACCESSORY,
        "목걸이",
        0,
        0,
        "어머니의 사진이 들어 있는 목걸이",
        1
    );
}

// 소멸자
Inventory::~Inventory()
{
    delete m_equipWeapon;
    delete m_equipArmor;
    delete m_equipAccessory;
}

// 인벤토리 출력
void Inventory::ShowPlayerBag()
{
    m_bagItemCount = 0;

    if (m_vBag.empty())
    {
        cout << "=================================================" << endl;
        cout << "인벤토리가 비어 있습니다." << endl;
        cout << "=================================================" << endl;
        return;
    }

    for (m_viBag = m_vBag.begin(); m_viBag != m_vBag.end(); ++m_viBag)
    {
        cout << "=================================================" << endl;
        cout << ++m_bagItemCount << "번째 아이템" << endl;

        m_viBag->ShowItemInfo();

        Sleep(500);
    }

    cout << "=================================================" << endl;
}

// 장비 확인 및 교체
void Inventory::ShowPlayerEquip(Character* player)
{
    ShowEquipText();

    cout << "=================================================" << endl;
    cout << "플레이어의 장비 확인하기를 선택하셨습니다." << endl;
    cout << "1~3을 입력해 원하는 장비를 교체합니다." << endl;
    cout << "0을 누르면 이전으로 돌아갑니다." << endl;
    cout << "=================================================" << endl;
    cout << "입력 : ";

    cin >> m_inventorySelectNum;

    bool WrongSelect = ((0 > m_inventorySelectNum) || (m_inventorySelectNum > 3));

    while (WrongSelect)
    {
        ShowEquipText();

        cout << "=================================================" << endl;
        cout << "그곳엔 아이템이 없습니다. 다시 입력하세요." << endl;
        cout << "이전으로 돌아가려면 0을 입력하세요." << endl;
        cout << "=================================================" << endl;
        cout << "입력 : ";

        cin >> m_inventorySelectNum;

        WrongSelect = ((0 > m_inventorySelectNum) || (m_inventorySelectNum > 3));
    }

    if (m_inventorySelectNum == 0)
    {
        return;
    }

    if (m_vBag.empty())
    {
        cout << "=================================================" << endl;
        cout << "교체할 아이템이 없습니다." << endl;
        cout << "=================================================" << endl;
        Sleep(1000);
        return;
    }

    ITEM selectItemType = (ITEM)m_inventorySelectNum;

    system("cls");

    ShowPlayerBag();

    cout << "원하는 아이템을 선택하세요." << endl;
    cout << "이전으로 돌아가려면 0을 입력하세요." << endl;
    cout << "=================================================" << endl;
    cout << "입력 : ";

    cin >> m_inventorySelectNum;

    if (m_inventorySelectNum == 0)
    {
        cout << "=================================================" << endl;
        cout << "인벤토리 메뉴로 돌아갑니다." << endl;
        cout << "=================================================" << endl;

        Sleep(500);
        return;
    }

    WrongSelect = ((0 > m_inventorySelectNum) || (m_inventorySelectNum > m_bagItemCount));

    while (WrongSelect)
    {
        system("cls");

        ShowPlayerBag();

        cout << "그곳엔 아이템이 없거나 올바르지 않은 장비 타입입니다." << endl;
        cout << "다시 입력하세요." << endl;
        cout << "이전으로 돌아가려면 0을 입력하세요." << endl;
        cout << "=================================================" << endl;
        cout << "입력 : ";

        cin >> m_inventorySelectNum;

        if (m_inventorySelectNum == 0)
        {
            return;
        }

        WrongSelect = ((0 > m_inventorySelectNum) || (m_inventorySelectNum > m_bagItemCount));
    }

    int selectedIndex = m_inventorySelectNum - 1;

    bool WrongType = selectItemType != m_vBag[selectedIndex].GetType();

    if (WrongType)
    {
        cout << "=================================================" << endl;
        cout << "아이템 타입이 맞지 않습니다." << endl;
        cout << "=================================================" << endl;

        Sleep(1000);
    }
    else
    {
        ChangePlayerEquip(player, m_inventorySelectNum - 1);
    }
}

// 장비 출력
void Inventory::ShowEquipText()
{
    system("cls");

    cout << "=================================================" << endl;
    cout << "플레이어의 장비" << endl;
    cout << "=================================================" << endl;

    cout << "1.무      기" << endl;
    m_equipWeapon->ShowItemInfo();

    Sleep(500);

    cout << "=================================================" << endl;
    cout << "2.방  어  구" << endl;
    m_equipArmor->ShowItemInfo();

    Sleep(500);

    cout << "=================================================" << endl;
    cout << "3.장  신  구" << endl;
    m_equipAccessory->ShowItemInfo();

    Sleep(500);
}

// 장비 교체
void Inventory::ChangePlayerEquip(Character* player, int itemIdx)
{
    Item newItem = m_vBag[itemIdx];
    int existItem;

    if (newItem.GetType() == ITEM::ITEM_WEAPON)
    {
        player->Setattack(player->Getattack() - m_equipWeapon->GetAbility());

        existItem = IsItemExist(m_equipWeapon->GetName());

        if (existItem > -1)
            m_vBag[existItem].SetCount(m_vBag[existItem].GetCount() + 1);
        else
            m_vBag.push_back(*m_equipWeapon);

        delete m_equipWeapon;
        m_equipWeapon = new Item(newItem);

        player->Setattack(player->Getattack() + m_equipWeapon->GetAbility());
    }
    else if (newItem.GetType() == ITEM::ITEM_ARMOR)
    {
        player->Setmaxhp(player->Getmaxhp() - m_equipArmor->GetAbility());

        existItem = IsItemExist(m_equipArmor->GetName());

        if (existItem > -1)
            m_vBag[existItem].SetCount(m_vBag[existItem].GetCount() + 1);
        else
            m_vBag.push_back(*m_equipArmor);

        delete m_equipArmor;
        m_equipArmor = new Item(newItem);

        player->Setmaxhp(player->Getmaxhp() + m_equipArmor->GetAbility());
        player->Sethp(player->Gethp() + m_equipArmor->GetAbility());
    }
    else if (newItem.GetType() == ITEM::ITEM_ACCESSORY)
    {
        player->Setmaxmp(player->Getmaxmp() - m_equipAccessory->GetAbility());

        existItem = IsItemExist(m_equipAccessory->GetName());

        if (existItem > -1)
            m_vBag[existItem].SetCount(m_vBag[existItem].GetCount() + 1);
        else
            m_vBag.push_back(*m_equipAccessory);

        delete m_equipAccessory;
        m_equipAccessory = new Item(newItem);

        player->Setmaxmp(player->Getmaxmp() + m_equipAccessory->GetAbility());
        player->Setmp(player->Getmp() + m_equipAccessory->GetAbility());
    }

    m_vBag[itemIdx].SetCount(m_vBag[itemIdx].GetCount() - 1);

    if (m_vBag[itemIdx].GetCount() == 0)
    {
        m_vBag.erase(m_vBag.begin() + itemIdx);
    }

    cout << "=================================================" << endl;
    cout << "장비를 교체했습니다." << endl;
    cout << "=================================================" << endl;

    Sleep(1000);
}

// 아이템 존재 확인
int Inventory::IsItemExist(const string& itemName)
{
    int result = -1;
    int itemCount = 0;

    for (m_viBag = m_vBag.begin(); m_viBag != m_vBag.end(); ++m_viBag)
    {
        if (m_viBag->GetName() == itemName)
        {
            result = itemCount;
            break;
        }

        ++itemCount;
    }

    return result;
}