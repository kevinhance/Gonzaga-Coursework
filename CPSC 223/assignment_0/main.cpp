u// Kevin Hance
// Assignment 0
// 8/30/2017

#include <iostream>
#include <map>
#include <vector>
#include <memory>

#include "a.h"

using namespace std;

int main(int argc, char* argv[]) {
    auto a = make_shared<A>();
    a->setStuff(__cplusplus);
    cout << a->getStuff() << endl;
    return 0;
}