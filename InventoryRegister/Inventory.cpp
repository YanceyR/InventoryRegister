//
//  Inventory.cpp
//  Chap13.Classes-CashRegister
//
//  Created by Yancey Reid on 10/11/16.
//  Copyright © 2016 Yancey Reid. All rights reserved.
//

#include "Inventory.hpp"
#include <iostream>
#include <vector>
#include <iomanip>

using namespace std;
void Inventory::getfile(){
    char choice;
    ItemData temp;
    char lastletindex;
    
    cout << "A) Create new inventory file" << endl;
    cout << "B) Use existing inventory file" << endl;
    cout << "Choice: ";
    cin.get(choice);
    cin.ignore();
    while (choice != 'B' & choice != 'b' & choice != 'A' & choice != 'a' ) {
        cout << "Invalid input, please enter 'A' or 'B': ";
        cin.get(choice);
        cin.ignore();
    }
    
    cout << "Enter file name including extension(.dat): ";
    getline(cin, filename);
    lastletindex = filename.size() - 1; //setting variable to index of last letter in filename
    
    //checking if file included .dat extension
    while (filename[lastletindex - 3] != '.' & filename[lastletindex - 2] != 'd' & filename[lastletindex - 1] != 'a' & filename[lastletindex] != 't') {
        cout << "File name did not include extension '.dat, re-enter: ";
        getline(cin, filename);
        lastletindex = filename.size() - 1;
    }
    
    switch(choice)
    {
        case 'a':
        case 'A':
            setitems();
            break;
        case 'b':
        case 'B':
            file.open(filename, ios::in | ios::binary);
            if (file.fail()){  //checking if file exists
                cout << "The file doesn't exits" << endl;
                cout << "Creating file: " << filename << endl;
                setitems();
            }
            else{
                file.read(reinterpret_cast<char *>(&data), sizeof(data)); //reading taxrate, profit, and types of items
                for (int i = 0; i < data.types ; i++) {
                    inventoryitems.push_back(temp);  //adding value in vector to be used for the memory location when reading
                    file.read(reinterpret_cast<char *>(&(inventoryitems[i])), sizeof(ItemData)); //reading item data
                }
                file.close();
                cout << "Read File: " << filename << endl;
            }
            break;
    }
    cout << endl;
}

void Inventory::setitems(){
    cout << "What is your tax rate in percentge: ";
    cin >> data.taxrate; data.taxrate = data.taxrate/100.00;
    cout << "Enter desired amount of profit in percetage: ";
    cin >> data.profitpercent; data.profitpercent = data.profitpercent/100.00;
    cout << "How many item types: ";
    cin >> data.types;
    cin.ignore();
    cout << endl;
    
    additem(data.types);
}

void Inventory::selectionsort(){
    int startScan, minIndex, minCode;
    ItemData minValue;
    for (startScan = 0; startScan < (inventoryitems.size() - 1); startScan++) {
        minValue = inventoryitems[startScan];
        minIndex = startScan;
        minCode = inventoryitems[startScan].itemcode;
        for(int index = startScan + 1; index < inventoryitems.size(); index++) {
            if (inventoryitems[index].itemcode < minCode) {
                minValue = inventoryitems[index];
                minCode = inventoryitems[index].itemcode;
                minIndex = index;
            }
        }
        inventoryitems[minIndex] = inventoryitems[startScan];
        inventoryitems[startScan] = minValue;
    }
}

int Inventory::finditem(int code) const{
    int first = 0;
    int last = inventoryitems.size() - 1;
    int middle;
    int position = -1;
    bool found = false;
    while (!found && first <= last){
        middle = (first + last) / 2;
        if (inventoryitems[middle].itemcode == code){
            found = true;
            position = middle;
        }
        else if (inventoryitems[middle].itemcode > code){
            last = middle - 1;
        }
        else
            first = middle + 1;
    }
    return position;
}

void Inventory::changeitem(){
    bool tof = false;
    int itemcode;
    int itemindex;
    int intemp;
    cout << "Enter item ID code or -1 to exit. WARNING UNSAVED DATA WILL BE LOST IF EXIT" << endl;
    cout << endl;
    do{
        cout << "Enter item ID code: ";
        cin >> itemcode;
        cin.ignore();
        if (itemcode == -1) {
            cout << "Item change exited!" << endl;
            exit(-1);
        }
        else if (finditem(itemcode) == -1){
            tof = true;
            cout << "Item: " << itemcode << "does not exist, re-enter.";
        }
    }while(tof);
    
    cout << "Old: " << endl;
    itemindex = finditem(itemcode);
    displayitem(itemcode);
    cout << endl;
    cout << "Enter item name: ";
    cin.getline(inventoryitems[itemindex].name, 50);
    cout << "Enter price: ";
    cin >> intemp;
    while (intemp < 0) {
        cout << "Price has to be equal or greater to 0, re-enter: ";
        cin >> intemp;
    }
    inventoryitems[itemindex].price = intemp;
    inventoryitems[itemindex].unitprice = (inventoryitems[itemindex].price * data.profitpercent) + inventoryitems[itemindex].price;
    cout << "Enter amount: ";
    cin >> inventoryitems[itemindex].quantity;
    cin.ignore();
    cout << endl;
    updateinventoryfile();
}

void Inventory::additem(int number){
    ItemData temp;
    bool tof = false;
    cout << "Enter item ID code or -1 to exit. WARNING UNSAVED DATA WILL BE LOST IF EXIT" << endl;
    cout << endl;
    for (int i = 0; i < number; i++) {
        do{
            cout << "Enter item ID code: ";
            cin >> temp.itemcode;
            cin.ignore();
            if (temp.itemcode == -1) {
                cout << "Import exited!" << endl;
                exit(-1);
            }
            else if (finditem(temp.itemcode) != -1){
                tof = true;
                cout << "Item: " << temp.itemcode << " already exists, re-enter.";
            }
        }while(tof);
        
        cout << "Enter item name: ";
        cin.getline(temp.name, 50);
        cout << "Enter price: ";
        cin >> temp.price;
        while (temp.price < 0) {
            cout << "Price has to be equal or greater to 0, re-enter: ";
            cin >> temp.price;
        }
        temp.unitprice = (temp.price * data.profitpercent) + temp.price;
        data.investment += temp.price;
        cout << "Enter amount: ";
        cin >> temp.quantity;
        cin.ignore();
        cout << endl;
        inventoryitems.push_back(temp); //additng temporary stucture to vector
    }
    selectionsort();
    updateinventoryfile();
    cout << "Import Saved/Successful" << endl;
}

void Inventory::deleteitem(int number){
    int itemcode;
    bool tof;
    cout << "Enter item ID code or -1 to exit. WARNING UNSAVED DATA WILL BE LOST IF EXIT" << endl;
    cout << endl;
    for (int i = 0; i < number; i++) {
        do{
            cout << "Enter item ID code: ";
            cin >> itemcode;
            cin.ignore();
            if (itemcode == -1) {
                cout << "Deletion exited!" << endl;
                exit(-1);
            }
            else if (finditem(itemcode) == -1){
                tof = true;
                cout << "Item: " << itemcode << " does not exist, re-enter." << endl;
            }
            else
                tof = false;
        }while(tof);
        
        inventoryitems.erase(inventoryitems.begin() + finditem(itemcode)); //deleting from vector
    }
    updateinventoryfile();
    cout << "Deletion Saved/Successful" << endl;
}

void Inventory::displayinventory() const{
    for(int i = 0; i < inventoryitems.size(); i++){
        cout << left << setw(14) << "Item ID Code: " << inventoryitems[i].itemcode << endl;
        cout << setw(14) << "Item Name: " << inventoryitems[i].name << endl;
        cout << fixed << setprecision(2); //setting output to two decimal places
        cout << setw(14) << "Price: " << "$" << inventoryitems[i].price << endl;
        cout << setw(14) << "Unit Price: " << "$" << inventoryitems[i].unitprice << endl;
        cout << setw(14) << "Quantity: " << inventoryitems[i].quantity << endl;
        cout << endl;
    }
}

void Inventory::displayitem(int itemcode) const{
    int itemindex = finditem(itemcode);
    cout << left << setw(14) << "Item ID Code: " << inventoryitems[itemindex].itemcode << endl;
    cout << setw(14) << "Item Name: " << inventoryitems[itemindex].name << endl;
    cout << fixed << setprecision(2); //setting output to two decimal places
    cout << setw(14) << "Price: " << "$" << inventoryitems[itemindex].price << endl;
    cout << setw(14) << "Unit Price: " << "$" << inventoryitems[itemindex].unitprice << endl;
    cout << setw(14) << "Quantity: " << inventoryitems[itemindex].quantity << endl;
    cout << endl;
}

void Inventory::updateinventoryfile(){
    file.open(filename, ios::out | ios::binary);
    file.write(reinterpret_cast<char *>(&data), sizeof(data));  //writing taxrate, profit, and types of items
    for (int i = 0; i < data.types ; i++) {
        file.write(reinterpret_cast<char *>(&(inventoryitems[i])), sizeof(ItemData));   //writing item data
    }
    file.close();
    cout << "Updated File: " << filename << endl;
}
