//
//  Inventory.hpp
//  Chap13.Classes-CashRegister
//
//  Created by Yancey Reid on 10/11/16.
//  Copyright © 2016 Yancey Reid. All rights reserved.
//

#ifndef Inventory_hpp
#define Inventory_hpp
#include <stdio.h>
#include <iostream>
#include <vector>
#include <iomanip>
#include <fstream>
using namespace std;

struct InventData{
    double taxrate;
    double profitpercent;
    int types;
    double investment;
    double earnings;
    
};

struct ItemData{
    int itemcode;
    char name[50];
    double price;
    double unitprice;
    int quantity;
};

class Inventory{
    friend class Register;
private:
    vector<ItemData> inventoryitems;
    InventData data;
    fstream file;
    string filename;
    void getfile();
    void setitems();
    void selectionsort();
    int finditem(int) const;
    void updateinventoryfile();
    void updatearnings(double x){data.earnings += x;}
public:
    Inventory(){getfile();}
    void displayinventory() const;
    double getotalprofit() const{return data.earnings - data.investment;}
    void displayitem(int) const;
    void changeitem();
    void additem(int);
    void deleteitem(int);
    double getaxrate() const {return data.taxrate;}
    void changetaxrate(int x){data.taxrate = x/100.00;};
    double getprofitpercent() const{return data.profitpercent;}
    void changeprofitpercent(int x){data.profitpercent = x/100.00;}
    int changeitemquantity(int);
};



#endif /* Inventory_hpp */
