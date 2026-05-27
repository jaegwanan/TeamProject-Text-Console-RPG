#include "shop.h"

// ������
Shop::Shop() : m_itemCount(0), m_shopSelectNum((int)SHOP::SHOP_TOWN)
{
    Item inputItem1(ITEM::ITEM_WEAPON, "����� ���", 10, 5,
        "��� ���������� �� �� �ִ� ���", 10);

    Item inputItem2(ITEM::ITEM_WEAPON, "�ٽ�Ÿ�� �ҵ�", 30, 20,
        "Ȳ�������� ������ ���� ȣ�ε��� ����", 5);

    Item inputItem3(ITEM::ITEM_WEAPON, "����Į����", 100, 50,
        "���� ���� �ڸ��� ���� �� �ִٴ� �� ��", 1);

    Item inputItem4(ITEM::ITEM_ARMOR, "���� ����", 10, 10,
        "źź�� �������� ���� ����", 10);

    Item inputItem5(ITEM::ITEM_ACCESSORY, "���� ���� �����", 25, 15,
        "Ư���� ���ַ� ������ �����", 8);

    Item inputItem6(ITEM::ITEM_HP_POTION, "HP ����", 10, 50,
        "HP�� ȸ����Ű�� ����", 10);

    Item inputItem7(ITEM::ITEM_MP_POTION, "MP ����", 15, 30,
        "MP�� ȸ����Ű�� ����", 10);

    Item inputItem8(ITEM::ITEM_ATTACK_POTION, "���ݷ� ����", 20, 10,
        "���ݷ��� ������Ű�� ����", 10);

    m_vItem.push_back(inputItem1);
    m_vItem.push_back(inputItem2);
    m_vItem.push_back(inputItem3);
    m_vItem.push_back(inputItem4);
    m_vItem.push_back(inputItem5);
    m_vItem.push_back(inputItem6);
    m_vItem.push_back(inputItem7);
    m_vItem.push_back(inputItem8);
}

// ���� ������ ���
void Shop::ShowShopItem()
{
    m_itemCount = 0;

    cout << "���� ������ ���� : "
        << m_vItem.size() << endl;

    for (m_viItem = m_vItem.begin(); m_viItem != m_vItem.end(); ++m_viItem)
    {
        cout << "=================================================" << endl;
        cout << ++m_itemCount << "��° ������" << endl;
        m_viItem->ShowItemInfo();
        Sleep(1000);
    }

    cout << "=================================================" << endl;
}

// ���� ��� ������
void Shop::ShopBuyItemPage(Character* player)
{
    while (true)
    {
        system("cls");

        cout << "=================================================" << endl;
        cout << "���� ���" << endl;

        ShowShopItem();

        if (m_itemCount == 0)
        {
            cout << "���� ���� : ��! �̾��ؿ�... ������ ���ȷȾ��..." << endl;
            cout << "=================================================" << endl;
            cout << "���� �޴��� ���ư��ϴ�." << endl;
            cout << "=================================================" << endl;
            Sleep(1000);
            return;
        }

        cout << "���� ���� : ����� ������ �͸� �鿩�����ϴ�!" << endl;
        cout << "=================================================" << endl;
        cout << "�÷��̾��� ������ : " << player->GetMoney() << endl;
        cout << "=================================================" << endl;
        cout << "��� ������ ��ðڽ��ϱ�?" << endl;
        cout << "���� �޴��� ���ư����� 0�� �Է��ϼ���." << endl;
        cout << "=================================================" << endl;
        cout << "�Է� : ";
        cin >> m_shopSelectNum;

        if (m_shopSelectNum == 0)
        {
            cout << "=================================================" << endl;
            cout << "���� �޴��� ���ư��ϴ�." << endl;
            cout << "=================================================" << endl;
            Sleep(500);
            return;
        }

        bool WrongSelect = ((m_shopSelectNum < 0) || (m_shopSelectNum > m_itemCount));

        while (WrongSelect)
        {
            system("cls");

            cout << "=================================================" << endl;
            cout << "���� ���" << endl;

            ShowShopItem();

            cout << "�÷��̾��� ������ : " << player->GetMoney() << endl;
            cout << "=================================================" << endl;
            cout << "���� ���� : �� �޶�� �Ͻô� ����? �ű⿣ �ƹ��͵� �����ϴ�!" << endl;
            cout << "�ٽ� �Է��ϼ���." << endl;
            cout << "���� �޴��� ���ư����� 0�� �Է��ϼ���." << endl;
            cout << "=================================================" << endl;
            cout << "�Է� : ";
            cin >> m_shopSelectNum;

            if (m_shopSelectNum == 0)
            {
                cout << "=================================================" << endl;
                cout << "���� �޴��� ���ư��ϴ�." << endl;
                cout << "=================================================" << endl;
                Sleep(500);
                return;
            }

            WrongSelect = ((m_shopSelectNum < 0) || (m_shopSelectNum > m_itemCount));
        }

        int selectedIndex = m_shopSelectNum - 1;

        bool NotEnoughMoney =
            m_vItem[selectedIndex].GetPrice() > player->GetMoney();

        if (NotEnoughMoney)
        {
            cout << "=================================================" << endl;
            cout << "���� ���� : �׳� �帱���� �����! ���� �����Ͻó׿�." << endl;
            cout << "=================================================" << endl;
            Sleep(1000);
        }
        else
        {
            BuyItem(m_shopSelectNum - 1, player);
        }
    }
}

// ���� �ȱ� ������
void Shop::ShopSellItemPage(Character* player)
{
    while (true)
    {
        system("cls");

        cout << "=================================================" << endl;
        cout << "���� �ȱ�" << endl;

        player->GetInventory()->ShowPlayerBag();

        if (player->GetInventory()->GetBagItemCount() == 0)
        {
            cout << "���� ���� : �ڳ״� ���� �� ������ ������ ���°� ���ھ�." << endl;
            cout << "=================================================" << endl;
            cout << "���� �޴��� ���ư��ϴ�." << endl;
            cout << "=================================================" << endl;
            Sleep(1000);
            return;
        }

        cout << "���� ���� : � ������ �Ǹ��Ͻǰǰ���!" << endl;
        cout << "=================================================" << endl;
        cout << "�÷��̾��� ������ : " << player->GetMoney() << endl;
        cout << "=================================================" << endl;
        cout << "��� ������ �Ľðڽ��ϱ�?" << endl;
        cout << "���� �޴��� ���ư����� 0�� �Է��ϼ���." << endl;
        cout << "=================================================" << endl;
        cout << "�Է� : ";
        cin >> m_shopSelectNum;

        int bagItemCount = player->GetInventory()->GetBagItemCount();

        if (m_shopSelectNum == 0)
        {
            cout << "=================================================" << endl;
            cout << "���� �޴��� ���ư��ϴ�." << endl;
            cout << "=================================================" << endl;
            Sleep(500);
            return;
        }

        bool WrongSelect = ((m_shopSelectNum < 0) || (m_shopSelectNum > bagItemCount));

        while (WrongSelect)
        {
            system("cls");

            cout << "=================================================" << endl;
            cout << "���� �ȱ�" << endl;

            player->GetInventory()->ShowPlayerBag();

            cout << "�÷��̾��� ������ : " << player->GetMoney() << endl;
            cout << "=================================================" << endl;
            cout << "�װ��� �������� �����ϴ�." << endl;
            cout << "�ٽ� �Է��ϼ���." << endl;
            cout << "���� �޴��� ���ư����� 0�� �Է��ϼ���." << endl;
            cout << "=================================================" << endl;
            cout << "�Է� : ";
            cin >> m_shopSelectNum;

            if (m_shopSelectNum == 0)
            {
                cout << "=================================================" << endl;
                cout << "���� �޴��� ���ư��ϴ�." << endl;
                cout << "=================================================" << endl;
                Sleep(500);
                return;
            }

            WrongSelect = ((m_shopSelectNum < 0) || (m_shopSelectNum > bagItemCount));
        }

        SellItem(m_shopSelectNum - 1, player);
    }
}

// ������ ����
void Shop::BuyItem(int itemIdx, Character* player)
{
    vector<Item>* playerBag = player->GetInventory()->GetBag();

    int existItem = player->GetInventory()->IsItemExist(m_vItem[itemIdx].GetName());

    if (existItem > -1)
    {
        playerBag->at(existItem).SetCount(playerBag->at(existItem).GetCount() + 1);
    }
    else
    {
        Item tempItem = m_vItem[itemIdx];
        tempItem.SetCount(1);
        playerBag->push_back(tempItem);
    }

    player->SetMoney(player->GetMoney() - m_vItem[itemIdx].GetPrice());

    m_vItem[itemIdx].SetCount(m_vItem[itemIdx].GetCount() - 1);

    if (m_vItem[itemIdx].GetCount() == 0)
    {
        m_vItem.erase(m_vItem.begin() + itemIdx);
    }

    cout << "=================================================" << endl;
    cout << "�������� �����߽��ϴ�." << endl;
    cout << "=================================================" << endl;
    Sleep(1000);
}

// ������ �Ǹ�
void Shop::SellItem(int itemIdx, Character* player)
{
    vector<Item>* playerBag = player->GetInventory()->GetBag();

    int sellPrice = playerBag->at(itemIdx).GetPrice() * 60 / 100;

    int existItem = IsItemExist(playerBag->at(itemIdx).GetName());

    if (existItem > -1)
    {
        m_vItem[existItem].SetCount(m_vItem[existItem].GetCount() + 1);
    }
    else
    {
        Item tempItem = playerBag->at(itemIdx);
        tempItem.SetCount(1);
        m_vItem.push_back(tempItem);
    }

    player->SetMoney(player->GetMoney() + sellPrice);

    playerBag->at(itemIdx).SetCount(playerBag->at(itemIdx).GetCount() - 1);

    if (playerBag->at(itemIdx).GetCount() == 0)
    {
        playerBag->erase(playerBag->begin() + itemIdx);
    }

    cout << "=================================================" << endl;
    cout << "�������� �Ǹ��߽��ϴ�." << endl;
    cout << "�Ǹ� �ݾ� : " << sellPrice << " ���" << endl;
    cout << "=================================================" << endl;
    Sleep(1000);
}

// ������ ���� �������� �ִ��� Ȯ��
int Shop::IsItemExist(const string& itemName)
{
    int result = -1;
    int itemCount = 0;

    for (m_viItem = m_vItem.begin(); m_viItem != m_vItem.end(); ++m_viItem)
    {
        if (m_viItem->GetName() == itemName)
        {
            result = itemCount;
            break;
        }

        ++itemCount;
    }

    return result;
}