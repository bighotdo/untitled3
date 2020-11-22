#include"HashMap.h"
#include<cstring>
#include <iostream>
namespace HashTable {
const char INFO[10] = {0,0,0,0,0,0,0,0,0,0};

    Element::Element():info(nullptr)  {
        this->busy = 0;
        this->info = new char [10];
        strcpy(this->info,INFO);
        this->key = 0;
    }

    Element::Element(int key, char info[]):info(nullptr) {
        this->busy = 1;
        this->info = new char [strlen(info)];
        strcpy(this->info,info);
        this->key = key;
    }

    std::ostream &operator<<(std::ostream &out, Element &Element) {
            out << Element.busy << ";" << Element.key << ";"<< Element.info << ";"<<"\n";

        return out;
    }


    std::istream &operator>>(std::istream &is, Element &Element) {
        int key;
        char info[10];
        is >> Element.key >> Element.info;
       return is;
    }


    HashMap::HashMap():array(nullptr){
        array = new Element[10];
        capacity = 10;
        for(int i = 0; i < 10; i++)
            array[i] = Element();
    }




    std::ostream& operator<<(std::ostream& out, HashMap& HashMap) {
        for (int i = 0; i < 10; ++i) {
            out << HashMap.array[i];
        }
        return out;
    }

    int HashMap::hash(int key)  {
        int capacity = 10;
        return key%capacity;
    }

    int Element::getBusy() const {
        return busy;
    }

    int Element::getKey() const {
        return key;
    }

    char *Element::getInfo() {
        return info;
    }

    void Element::setBusy(int a) {
        busy = a;
    }

    void Element::setKey(int a) {
        key = a;
    }

    void Element::setInfo(char *info) {//Declaration shadows a field of 'HashTable::Element'
        strcpy(this->info,info);
    }

    Element::~Element() {
        if(info != nullptr) {
            delete[]info;
            info = nullptr;
        }
    }

    Element::Element(const Element &ob) {
        if(strlen(ob.info)){
            info = new char[strlen(ob.info)];
            busy = ob.busy;
            key = ob.key;
            strcpy(info,ob.info);
        }
    }

    Element &Element::operator = (const Element &ob) {
        if(this != &ob) {
            delete[] info;
            info = nullptr;
            info = new char[strlen(ob.info)];
            strcpy(info,ob.info);
        }
        return *this;
    }

    void HashMap::trashCollect() const {
        int i = 0, j;
        while (i < this->capacity) {
            if (this->array[i].getBusy() != -1) {}
            else {
                j = i;
                while (j < this->capacity) {
                    this->array[j] = this->array[j + 1];
                    j++;
                }
                this->array[this->capacity] = Element();
            }
            i++;
        }
    }


   char* HashMap::operator[](int key) {
       int h = this->hash(key);
       int i = 0;
       while (array[(h + i)%capacity].getBusy() == 1 || array[(h + i)%capacity].getBusy() == -1)
       {

           if(i > capacity){
               std::cout<<"Not found";
               return nullptr;
           }
           if (array[(h + i)%capacity].getKey() == key) {
               char *a = array[(h + i) % capacity].getInfo();
               return a;
           }
           i++;
       }
        return nullptr;
    }

    Element HashMap::operator()(int key) {
        int h = this->hash(key);
        int i = 0;
        while (array[(h + i)%capacity].getBusy() == 1 || array[(h + i)%capacity].getBusy() == -1)
        {

            if(i > capacity){
                std::cout<<"Not found";
                return Element();
            }
            if (array[(h + i)%capacity].getKey() == key) {
                Element a = array[(h + i) % capacity];
                return a;
            }
            i++;
        }
        return Element();
    }


    HashMap &operator+=(HashMap  &Hashmap, Element &Element) {
        {
            int key =Element.getKey();
            char* info = Element.getInfo();
            int h = Hashmap.hash(Element.getKey());
            int i = 0;
            while (Hashmap.array[(h + i)%Hashmap.capacity].getBusy()==1 || Hashmap.array[(h + i)%Hashmap.capacity].getBusy()==-1)
            {
                i++;
                if(i > Hashmap.capacity){
                    std::cout<<"Full table";
                    return Hashmap;
                }
                if (Hashmap.array[(h + i)%Hashmap.capacity].getKey() == key && Hashmap.array[(h + i)%Hashmap.capacity].getBusy() == 1)
                    Element.setInfo(info);
                i++;
            }
            Hashmap.array[(h + i)%Hashmap.capacity] = Element;
        }
        return Hashmap;
    }

    HashMap &operator-=(HashMap &Hashmap, int key) {
        Element* Element ;

        int h = Hashmap.hash(key);
        int i = 0;
        while (Hashmap.array[(h + i)%Hashmap.capacity].getBusy()==1 || Hashmap.array[(h + i)%Hashmap.capacity].getBusy()==-1)
        {

            if(i > Hashmap.capacity){
                std::cout<<"Not found";
                Element = nullptr;
            }
            if (Element->getKey() == key)
                Element = &Hashmap.array[(h + i)%Hashmap.capacity];
            i++;
        }
            if (Element == nullptr) {
                std::cout << "Not Found";
                return Hashmap;
            } else
                Element->setBusy(-1);
            Hashmap.trashCollect();
        return Hashmap;
    }

    HashMap::~HashMap() {

    }

    HashMap::HashMap(const HashMap &ob):capacity(ob.capacity),array(nullptr) {
        if(capacity){
            array = new Element[capacity];
            for (int i = 0; i < capacity; i++) {
                array[i].setKey(ob.array[i].getKey());
                array[i].setInfo(ob.array[i].getInfo());
                array[i].setBusy(ob.array[i].getBusy());
            }
        }
    }

    HashMap &HashMap::operator = (const HashMap &ob) {
        if(this != &ob) {
            delete[] array;
            array = nullptr;
            if((capacity = ob.capacity) != 0) {
                array = new Element[capacity];
                for (int i = 0; i < capacity; i++) {
                    array[i].setKey(ob.array[i].getKey());
                    array[i].setInfo(ob.array[i].getInfo());
                    array[i].setBusy(ob.array[i].getBusy());
                }
            }
        }
        return *this;
    }

    HashMap::HashMap(Element &Element):array(nullptr) {
            capacity = 1;
            array = new class Element[1];
            array->setKey(Element.getKey());
            array->setBusy(1);
    }
}