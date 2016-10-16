//
//  Register.hpp
//  Chap13.Classes-CashRegister
//
//  Created by Yancey Reid on 10/11/16.
//  Copyright © 2016 Yancey Reid. All rights reserved.
//

#ifndef Register_hpp
#define Register_hpp
#include <stdio.h>

#include <iostream>
#include <vector>
#include <iomanip>
#include "Inventory.hpp"
using namespace std;

struct PurchaseData{
    int itemnum;
    int quantity;
    double price;
    double tax;
};

class Register{
private:
    Inventory *ptr = nullptr;
    double subtotal;
    double totaltax;
    vector<PurchaseData>purchaseditems;
    void SetSubtotalTax();
    void UpdateInventory();
    string filename;
    
public:
    Register(Inventory *);
    void ringupitems();
    double getotal() const{return subtotal + totaltax;}
    double gatax() const{return totaltax;}
    double getsubtotal() const{return subtotal;}
    void printreciept();
};

#endif /* Register_hpp */
