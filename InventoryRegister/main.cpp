//
//  main.cpp
//  InventoryRegister
//
//  Created by Yancey Reid on 10/11/16.
//  Copyright © 2016 Yancey Reid. All rights reserved.
//

#include <iostream>
#include "Inventory.hpp"
#include "Register.hpp"
using namespace std;
int menu(Inventory &);

int main() {
    Inventory Store;
    Store.displayinventory();
    
    menu(Store);
    /*
     Register Customer(&Store);
     Customer.ringupitems();
     Customer.printreciept();
     
     Store.displayinventory();
     */
    return 0;
    
}
int menu(Inventory &Store){
    char staychoice;
    int choice;
    cout << "Main Menu: " << endl;
    cout << "1) Display inventory" << endl;
    cout << "2) Display profit" << endl;
    cout << "3) Find item data" << endl;
    cout << "4) Change item data" << endl;
    cout << "5) Add item(s) to inventory" << endl;
    cout << "6) Delete item(s) from inventory" << endl;
    cout << "7) Display tax rate" << endl;
    cout << "8) Change tax rate" << endl;
    cout << "9) Display desired profit percentage" << endl;
    cout << "10) Change desired profit percentage" << endl;
    cout << "11) Exit Program" << endl;
    cout << endl;
    cout << "Enter 1 - 10: ";
    cin >> choice;
    cout << endl;
    while(choice < 1 || choice > 11){
        cout << "Invalid input, re-enter: ";
        cin >> choice;
    }
    int intemp;
    switch(choice){
        case 1:
            Store.displayinventory();
            break;
        case 2:
            cout << "Total Profit: $" << Store.getotalprofit() << endl;
            break;
        case 3:
            cout << "Enter item ID number: ";
            cin >> intemp;
            cout << endl;
            Store.displayitem(intemp);
            break;
        case 4:
            Store.changeitem();
            break;
        case 5:
            cout << "Enter amount of item types to add: ";
            cin >> intemp;
            Store.additem(intemp);
            break;
        case 6:
            cout << "Enter amount of item types to delete: ";
            cin >> intemp;
            Store.deleteitem(intemp);
            break;
        case 7:
            cout << "Tax Rate: " << Store.getaxrate() * 100 << "%" << endl;
            break;
        case 8:
            cout << "Enter new tax rate in percentage: ";
            cin >> intemp;
            Store.changetaxrate(intemp);
            break;
        case 9:
            cout << "Desired Profit Percentage: " << Store.getprofitpercent() * 100 << "%" << endl;
            break;
        case 10:
            cout << "Enter new profit percentage: ";
            cin >> intemp;
            Store.changeprofitpercent(intemp);
            break;
        case 11:
            cout << "Exiting Program" << endl;
            return 1;
    }
    cout << "Enter 'Y' to return to main menu or 'N' to exit: ";
    cin >> staychoice;
    if (staychoice == 'y' || staychoice == 'Y'){
        menu(Store);
    }
    return 0;
}

