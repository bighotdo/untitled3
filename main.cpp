#include <iostream>
#include "HashMap.h"
int main() {
    HashTable::HashMap table;
    HashTable::HashMap table2;
    HashTable::Element a1(10,"llllll");
    HashTable::Element a2(13,"22222222");
    HashTable::Element a3(15,"333333333");
    HashTable::Element a4(19,"44444444");
    HashTable::Element a5(16,"5555");
    HashTable::Element a6(22,"6666666");
    HashTable::Element a7(37,"77777");
    (table += a1) += a2;
    table2 += a3;
    table += a4;
    table2 += a5;
    table += a6;
    table2 += a7;
    std::cout<<table<<"\n";
    table -= 22;
    std::cout<<table<<"\n";
    char* a = table[10];
    std::cout<<a;
    table = table;
    std::cout<<table2<<"\n";
    std::cin>>a7;
    table += a7;
    std::cout<<table<<"\n";
}
