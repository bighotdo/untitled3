#include <iostream>
namespace HashTable{
    class Element{
        friend std::ostream& operator<<(std::ostream& out, Element& Element);
        friend std::istream& operator>>(std::istream& is, Element& Element);
    public:
        Element();
        Element(int, char info[]);
        int getBusy() const;
        int getKey() const;
        char *getInfo();
        void setBusy(int busy);
        void setKey(int key);
        void setInfo(char *info);
        Element(const Element & ob);
        Element & operator = (const Element& ob);
        ~Element();
    private:
        char *info;
        int busy;
        int key;
    };


    class HashMap{
        friend std::ostream& operator<<(std::ostream& out, HashMap& HashMap);
        //friend std::ostream& operator>>(std::ostream& out, HashMap& HashMap);
        friend HashMap& operator+= (HashMap  &Hashmap, Element &Element);
        friend HashMap& operator-= (HashMap  &Hashmap, int key);
    public:
        HashMap();
        HashMap(Element& Element);//Single-argument constructors must be marked explicit to avoid unintentional implicit conversions
        HashMap(const HashMap & ob);
        ~HashMap();
        static int hash(int key);
        void trashCollect() const;
        char* operator[] (int index);
        Element operator() (int index);
        HashMap & operator = (const HashMap& ob);// оператор присваивания
    private:
        int capacity;
        Element *array;
    };
}
