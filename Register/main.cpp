//
//  main.cpp
//  Register
//
//  Created by Yancey Reid on 10/11/16.
//  Copyright © 2016 Yancey Reid. All rights reserved.
//

#include <iostream>
#include "Inventory.hpp"
#include "Register.hpp"
using namespace std;

int main() {
    cout << "register" << endl;
    Inventory Store;
    Register Customer(&Store);
    Customer.ringupitems();
    Customer.printreciept();
    return 0;
}
