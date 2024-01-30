#include <iostream>
#include <fstream>
#include <windows.h>
#include <string.h>
#include <conio.h>
using namespace std;
class item
{
public:
    int itemNo;
    char itName[50];
    float price, qnt, dis, tax;
};

class inventory
{
public:
    fstream f, f1;
    item i, it;
    int P = 0, P1 = 0;
    // void getdata()
    // {
    //     system("cls");

    // }

    void writeFile()
    {
        system("cls");
        f.open("store1.txt", ios::out | ios::app);
        cout << "\n\t\tADD A NEW PRODUCT\n\n";
        cout << "\nPRODUCT ID :- ";
        cin >> i.itemNo;
        cout << "\nPRODUCT NAME :- ";
        cin >> i.itName;
        cout << "\nPRICING :- ";
        cin >> i.price;
        cout << "\nQUANTITY :- ";
        cin >> i.qnt;
        f.write((char *)&i, sizeof(i));
        f.close();
        cout << "\nNEW PRODUCT ADDED TO INVENTORY";
        getch();
    }
    void showdata()
    {
        cout << i.itemNo << "\t\t";
        cout << i.itName << "\t\t ";
        cout << i.price << "\t\t";
        cout << i.qnt << "\n\n";
    }
    void display()
    {
        // system("cls");
        cout << "\n\t\t\tDISPLAY ALL PRODUCTS\n\n";
        cout << "\n ----------------------------------------------------------------";
        cout << "\n||    ID    ||    PRODUCT    ||    PRICE    ||    QUANTITY    ||";
        cout << "\n ---------------------------------------------------------------\n\n";
        f.open("store1.txt", ios::in);

        while (f.read((char *)&i, sizeof(i)))
        {
            cout << i.itemNo << "\t\t";
        cout << i.itName << "\t\t ";
        cout << i.price << "\t\t";
        cout << i.qnt << "\n\n";
        }
        f.close();
        getch();
    }

    void searchdata()
    {
        system("cls");
        int t = 0;
        char f_id[30];
        cout << "\t\tFIND STOCK IN INVENTORY\n\n";
        f.open("store.txt", ios::in);
        if (f.fail() == 1)
        {
            cout << "Data/ File Not Exists\n\n";
            return;
        }
        f.close();
        cout << "\n\nPRODUCT NAME : ";
        cin >> f_id;
        cout << "\n\n";
        cout << "\n\t\t ----------------------------------------------------------------";
        cout << "\n\t\t||    ID    ||    PRODUCT    ||    PRICE    ||    QUANTITY    |";
        cout << "\n \t\t---------------------------------------------------------------\n\n";
        f.open("store.txt", ios::in);
        while (f.read((char *)&i, sizeof(i)))
        {
            if (strcmpi(f_id, i.itName) == 0)
            {
                cout << "\t\t\t" << i.itemNo << "\t\t";
                cout << i.itName << "\t\t";
                cout << i.qnt << "\t  ";
                cout << i.price << "\n";
                t++;
            }
        }
        if (t == 0)
            cout << "\n\n\t\t\tENTERED DATA IS NOT AVAILABLE\n";
        f.close();
        getch();
    }

    void update()
    {
        int no, found = 0, n = 0;
        char c;
        system("cls");
        cout << "\n\t\tUPDATE PRODUCT DETAILS\n";
        cout << "\nPRODUCT ID :- ";
        cin >> no;
        cout << "\n\t\t ----------------------------------------------------------------";
        cout << "\n\t\t ||    ID    ||     PRODUCT     ||    PRICE    ||    QUANTITY    ||";
        cout << "\n \t\t ---------------------------------------------------------------\n\n";
        f.open("store.txt", ios::in | ios::out);
        f1.open("temp.txt", ios ::out | ios::app);
        while (f.read((char *)&i, sizeof(i)) && found == 0)
        {
            if (i.itemNo == no)
            {
                it = i;
                cout << "\t\t ";
                showdata();
                cout << "\n=>ENTER NEW DETAILS OF PRODUCT<=\n\n";
                cout << "PRESS 1 TO CHANGE UPDATE NAME...\nPRESS 2 TO CHANGE UPADTE PRICE...\nPRESS 3 TO CHANGE UPDATE QUANTITY...\t";
                c = getch();
                if (c == '1')
                {
                    cout << "\n\nENTER NEW PRODUCT NAME :- ";
                    cin >> it.itName;
                }
                else if (c == '2')
                {
                    cout << "\n\nENTER NEW PRODUCT PRICE :- ";
                    cin >> it.price;
                }
                else if (c == '3')
                {
                    cout << "\n\nENTER NEW PRODUCT QUANTITY :- ";
                    cin >> it.qnt;
                }
                else
                {
                    n = 1;
                    f1.write((char *)&i, sizeof(i));
                }
                if (n == 0)
                {
                    cout << "\n\nPRESS 1 CONFIRM TO UPDATE PRODUCT...OR ANY TO SKIP";
                    c = getch();
                    if (c == '1')
                        f1.write((char *)&it, sizeof(it));
                    else
                    {
                        f1.write((char *)&i, sizeof(i));
                        n = 1;
                    }
                }
                f.write((char *)&i, sizeof(i));
                found++;
            }
            else
            {
                f1.write((char *)&i, sizeof(i));
            }
        }
        f.close();
        f1.close();
        if (found == 0)
        {
            cout << "\n\t\tRECORD NOT AVAILABLE";
            remove("temp.txt");
        }
        else
        {
            cout << "\n\n\t\tRECORD UDATED";
            remove("store.txt");
            rename("temp.txt", "store.txt");
        }
        getch();
    }

    void delete_()
    {
        int t = 0, f_id;
        char c;
        system("cls");
        cout << "\n\n\t\tDELETE PRODUCT DETAILS\n\n";
        cout << "PRESS 1 TO DELETE SPECIFIC PRODUCT...\nPRESS 2 TO DELETE ALL PRODUCTS...  ";
        c = getch();
        if (c == '1')
        {
            cout << "\n\nPRODUCT ID -- ";
            cin >> f_id;
            cout << "\n";
            cout << "\n\t\t ----------------------------------------------------------------";
            cout << "\n\t\t||    ID    ||    PRODUCT    ||    PRICE    ||    QUANTITY    |";
            cout << "\n \t\t---------------------------------------------------------------\n\n";
            f.open("store.txt", ios::in);
            f1.open("temp.txt", ios::out);
            while (f.read((char *)&i, sizeof(i)))
            {
                if (f_id == i.itemNo)
                {
                    cout << "\t\t";
                    showdata();
                    t++;
                    cout << "\nPRESS 1 FOR CONFIRM TO DELETE PRODUCT...OR ANY TO CANCEL";
                    c = getch();
                    if (c == '1')
                    {
                        cout << "\n\nPRODUCT SUCCESSFULLY DELETED";
                    }
                    else
                    {
                        cout << "\n\nDELETING CANCELED";
                        f1.write((char *)&i, sizeof(i));
                    }
                }
                else
                {
                    f1.write((char *)&i, sizeof(i));
                }
            }
            f1.close();
            f.close();
            if (t == 0)
                remove("temp.txt");
            else
            {
                remove("store.txt");
                rename("temp.txt", "store.txt");
            }
        }
        else if (c == '2')
        {
            display();
            cout << "\nPRESS 1 FOR CONFIRM TO DELETE PRODUCT...OR ANY TO CANCEL\n";
            c = getch();
            if (c == '1')
            {
                cout << "\nALL RECORDS HAS BEEN DELETED\n";
                remove("store.txt");
                rename("temp.txt", "store.txt");
            }
        }
        getch();
    }

    void menu()
    {
        system("cls");
        f.open("store.txt", ios::in);
        if (!f)
        {
            cout << "ERROR!!! FILE IS NOT AVAILABLE\n\n\n GO TO ADMIN MENU TO CREATE FILE";
            getch();
            exit(0);
        }
        cout << "\n\n\t\t   ITEM MENU\n";
        cout << "\n ------------------------------------------------";
        cout << "\n||    ITEM.NO.    ||    NAME    ||    PRICE    ||";
        cout << "\n -----------------------------------------------\n\n";
        while (f.read((char *)&i, sizeof(i)))
        {
            cout << " " << i.itemNo << "\t\t" << i.itName << "\t\t" << i.price << endl;
        }
        f.close();
    }
    void place_order()
    {
        system("cls");
        if (P == 0)
        {
            password_user1();
            P++;
        }
        int b;
        int order_arr[50], quan[50], c = 0;
        char a;
        float amt, total = 0;
        char ch = 'Y';
        menu();
        cout << "\n\n=>PRESS 1 CONTINUED TO ORDER... OR EXIT";
        a = getch();
        if (a == '1')
        {
            do
            {
                cout << "\nITEM ID : ";
                cin >> order_arr[c];
                cout << "QUANTITY : ";
                cin >> quan[c];
                c++;
                cout << "\nWANT TO ORDER ANOTHER ITEM ? (y/n) : ";
                cin >> ch;
            } while (ch == 'y' || ch == 'Y');
            cout << "\n\t\t< ^_^THANKS FOR ORDER^_^ >\n";
            cout << "\nDO YOU NEED A INVOICE PRESS 1...\nWANT TO PLACE ANOTHER ORDER PRESS 2...\nOR ANY TO CONTINUE..";
            a = getch();
            if (a == '1')
            {
                system("cls");
                cout << "\n\n------------------------*********** INVOICE *********---------------------------\n";
                cout << "ITEM ID\t|\tNAME\t|\tQUANTITY\t|\tPRICE\t|\tTOTAL\n";
                cout << "------------------------------------------------------------------------------------\n";
                for (int x = 0; x <= c; x++)
                {
                    f.open("store.txt", ios::in);
                    f.read((char *)&i, sizeof(i));
                    while (!f.fail())
                    {
                        if (i.itemNo == order_arr[x])
                        {
                            amt = i.price * quan[x];
                            cout << "\n"
                                 << order_arr[x] << "\t\t" << i.itName << "\t\t\t" << quan[x] << "\t\t" << i.price << "\t  " << amt << "\t";
                            total += amt;
                        }
                        f.read((char *)&i, sizeof(i));
                    }
                    f.close();
                }
                cout << "\n------------------------------------------------------------------------------\n";
                cout << "\n\t\t\tTOTAL = " << total;
                getch();
            }
        }
    }
    int password_user()
    {
        string pass_reg = "";
        string name_reg = "";
        string pass = "";
        string name = "";
        fstream file;
        char ch;
        system("cls");
        cout << "\n\t\t\t\t\t---------------------------";
        cout << "\n\t\t\t\t\t>>      ADMIN PANEL       <<";
        cout << "\n\t\t\t\t\t---------------------------";
        cout << "\n\n\t\t\t\t\tUSER_NAME: ";
        cin >> name_reg;
        cout << "\n\t\t\t\t\tPASSWORD: ";
        ch = _getch();
        while (ch != 13)
        {
            pass_reg.push_back(ch);
            cout << '*';
            ch = _getch();
        }
        file.open("Edata.txt", ios::app);
        file << " " << name_reg << " " << pass_reg << "\n";
        file.close();
        cout << "\n\n\t\t\t\t\tLOGIN SUCCESFULLY";
        getch();
        return 0;
    }
    int password_user1()
    {
        string pass_reg = "";
        string name_reg = "";
        string pass = "";
        string name = "";
        fstream file;
        char ch;
        system("cls");
        cout << "\n\t\t\t -------------------------------------------";
        cout << "\n\t\t\t||            CONSUMER PANEL              ||";
        cout << "\n\t\t\t -------------------------------------------";
        cout << "\n\n\t\t\t   -| Press: [1] REGISTER & [2] LOGIN  |-";
        int selection;
        cout << "\n\nPlease Enter Value: ";
        cin >> selection;
        if (selection == 1)
        {
            system("cls");
            cout << "\n\t\t\t\t\t---------------------------";
            cout << "\n\t\t\t\t\t>> CONSUMER REGISTRATION <<";
            cout << "\n\t\t\t\t\t---------------------------";
            cout << "\n\n\t\t\t\t\tENTER A USER_NAME: ";
            cin >> name_reg;
            cout << "\n\t\t\t\t\tENTER A PASSWORD: ";
            ch = _getch();
            while (ch != 13)
            {
                pass_reg.push_back(ch);
                cout << '*';
                ch = _getch();
            }
            file.open("Epdata.txt", ios::app);
            file << " " << name_reg << " " << pass_reg << "\n";
            file.close();
            cout << "\nREGISTRATION SUCCESFULLY ";
            getch();
            password_user1();
        }
        else if (selection == 2)
        {
            system("cls");
            file.open("Epdata.txt", ios::in);
            cout << "\n\t\t\t\t\t--------------------";
            cout << "\n\t\t\t\t\t>> LOGIN CONSUMER <<";
            cout << "\n\t\t\t\t\t--------------------";
            cout << "\n\n\t\t\t\t\tUSER_NAME: ";
            cin >> name;
            cout << "\n\t\t\t\t\tPASSWORD: ";
            ch = _getch();
            while (ch != 13)
            {
                pass.push_back(ch);
                cout << '*';
                ch = _getch();
            }
            file >> name_reg >> pass_reg;
            while (!file.eof())
            {
                if (pass == pass_reg && name == name_reg)
                {
                    cout << "\n\n\n\t\t\t\t\t| VERFIYING COUSTOMER |\n\t\t\t\t\t";
                    for (int a = 1; a < 8; a++)
                    {
                        Sleep(500);
                    }
                    cout << "\n\nLOGIN SUCCESFULLY...\n\n";
                    system("PAUSE");
                    system("cls");
                    break;
                }
                else
                {
                    cout << "\n\n\n\t\t\t\t\t| VERFIYING COUSTOMER |\n\t\t\t\t\t";
                    for (int a = 1; a < 8; a++)
                    {
                        Sleep(500);
                    }
                    cout << "\n\nLOGIN FAILED...\n\n";
                    system("PAUSE");
                    system("cls");
                    password_user1();
                }
                file >> name_reg >> pass_reg;
            }
            file.close();
        }
        else
        {
            cout << "\nINVALID INPUT...TRY AGAIN";
            getch();
            password_user1();
        }
        return 0;
    }
    void admin_menu()
    {
        if (P1 == 0)
        {
            password_user();
            P1++;
        }
        char ch2;
        do
        {
            system("cls");
            cout << "\n\t\t\t\t\t-------------------------------" << endl;
            cout << "\t\t\t\t\t>> INVENTORY MANAGEMENT SYSTEM <<" << endl;
            cout << "\t\t\t\t\t-------------------------------" << endl;
            cout << "\t\t\t\t\t\t   ADMIN MENU";
            cout << "\n\t\t\t\t\t-------------------------------" << endl;
            cout << "\t\t\t\t\t 1. ADD NEW STOCK" << endl;
            cout << "\t\t\t\t\t 2. DISPLAY ALL STOCK" << endl;
            cout << "\t\t\t\t\t 3. FIND STOCK" << endl;
            cout << "\t\t\t\t\t 4. UPDATE STOCK" << endl;
            cout << "\t\t\t\t\t 5. DELETE STOCK" << endl;
            cout << "\t\t\t\t\t 6. BACK TO MAIN MENU" << endl;
            cout << "\t\t\t\t\t 7. EXIT" << endl;
            cout << "\t\t\t\t\t.................................." << endl;
            cout << "\t\t\t\t\t>> Choice Options: [1/2/3/4/5/6] <<" << endl;
            cout << "\t\t\t\t\t.................................." << endl;
            cout << "ENTER YOUR CHOICE : ";
            cin >> ch2;
            switch (ch2)
            {
            case '1':
                system("cls");
                writeFile();
                break;
            case '2':
                system("cls");
                display();
                break;
            case '3':
                system("cls");
                searchdata();
                break;
            case '4':
                system("cls");
                update();
                break;
            case '5':
                system("cls");
                delete_();
                break;
            case '6':
                show();
                getch();
                break;
            case '7':
                exit(0);
            default:
                cout << "/a";
            }
        } while (ch2 != '6');
    }
    void show()
    {
        char ch;
        do
        {
            system("cls");
            cout << "\n\t\t\t -------------------------------------------";
            cout << "\n\t\t\t||  WELCOME TO INVENTORY MANAGEMENT SYSTEM  ||";
            cout << "\n\t\t\t -------------------------------------------";
            cout << "\n\n\t\t\t   -| Press: [1] ADMIN & [2] COUSTOMER  |-";
            cout << "\n\nPlease Enter Value: ";
            cin >> ch;
            switch (ch)
            {
            case '1':
                system("cls");
                admin_menu();
                break;
            case '2':
                place_order();
                break;
            case '3':
                exit(0);
                break;
            default:
                cout << "\a";
            }
        } while (ch != '3');
    }
};
int main()
{
    // system("color F0");
    inventory I;
    I.show();
}