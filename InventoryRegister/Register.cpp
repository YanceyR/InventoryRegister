//
//  Register.cpp
//  Chap13.Classes-CashRegister
//
//  Created by Yancey Reid on 10/11/16.
//  Copyright © 2016 Yancey Reid. All rights reserved.
//

#include "Register.hpp"
#include <iostream>
#include <vector>
#include <iomanip>

Register::Register(Inventory *inventorydata){
    ptr = inventorydata;
}

void Register::ringupitems(){
    char choice;
    PurchaseData temp;
    while(choice != 'n' & choice != 'N'){
        cout << "Enter item number you want to purchase: ";
        cin >> temp.itemnum;
        while(ptr->inventoryitems[temp.itemnum - 1].quantity <= 0 || temp.itemnum > ptr->inventoryitems.size()){
            cout << "Item is out of stock" << endl;
            cout << "Please enter another item number or enter -1 to exit: ";
            cin >> temp.itemnum;
            if(temp.itemnum == -1){
                exit(1);
            }
        }
        temp.itemnum -= 1;
        cout << "Enter amount: ";
        cin >> temp.quantity;
        while(temp.quantity < 0 || temp.quantity > ptr->inventoryitems[temp.itemnum].quantity){
            cout << "Input has to be positive or amount exceeds quantity in stock, re-enter: ";
            cin >> temp.quantity;
        }
        temp.price = (ptr->inventoryitems[temp.itemnum].unitprice) * temp.quantity;
        temp.tax = temp.price * ptr->data.taxrate;
        purchaseditems.push_back(temp);
        cout << "Enter 'Y' for another item or 'N' to finish: ";
        cin >> choice;
        cout << endl;
    }
    SetSubtotalTax();
    
}

void Register::SetSubtotalTax(){
    for (int i = 0; i < purchaseditems.size(); i++) {
        subtotal += purchaseditems[i].price;
        totaltax += purchaseditems[i].tax;
    }
}

void Register::UpdateInventory(){
    for (int i = 0; i < purchaseditems.size(); i++) {
        ptr->inventoryitems[purchaseditems[i].itemnum].quantity -= purchaseditems[i].quantity;
    }
    ptr->updateinventoryfile();
}

void Register::printreciept(){
    cout << left << setw(10) << "Item" << setw(10) << "Amount" << setw(10) << "Cost" << endl;
    for(int i = 0; i < purchaseditems.size(); i++){
        cout << setw(10) << ptr->inventoryitems[purchaseditems[i].itemnum].name;
        cout << setw(10) << purchaseditems[i].quantity;
        cout << "$" << setw(10) << purchaseditems[i].price << endl;
    }
    cout << endl;
    cout << setw(20) << "Subtotal: ";
    cout << "$" << setw(10) << subtotal << endl;
    cout << "Tax(" << (ptr->data.taxrate * 100) << setw(13) << "%): ";
    cout << "$" << setw(10) << totaltax << endl;
    cout << setw(20) << "Total: ";
    cout << "$" << setw(10) << subtotal + totaltax;
    cout << endl;
    ptr->updatearnings(subtotal + totaltax);
    UpdateInventory();
}

