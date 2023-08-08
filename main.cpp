#include <iostream>
#include <fstream>
#include <string>

using namespace std;

struct SKord{
    int x, y;
    
    SKord():x(-1), y(-1){};
};

struct SUnity{
    string typ;
    bool wrag;
    string nazwa;
    int zdrowie;
    int uron;
    SKord coor;
    
    SUnity(): typ(""), wrag(true), nazwa(""), zdrowie(0), uron(0){};
    
    void read_data(ifstream&);
    
};

struct SGame{
    char** map;
    SKord map_size;
    int number_people;
    SUnity* people;
    
    SGame():map(nullptr), number_people(0), people(nullptr){};
    ~SGame(){
        if(map){
            for(int i = 0; i < map_size.y; i++){
                delete[]map[i];
                map[i] = nullptr;
            }
            delete [] map;
            map = nullptr;
        }
        if(people){
            delete [] people;
            people = nullptr;
        }
    }
    
    
    void read_size(ifstream&);
    void read_map(ifstream&);
    void print_map(ofstream&);
    void print(ofstream&);
};



// сделать 3 файла с инфой о людях рыцарь,лучник,пикинер(начинаю прописывать все даные без типа и без врага
int main(int argc, char * argv[]) {
    
    //считываю размер карты, а потом саму карту
    
    //SwitchСпросить сколько создать юниитов (в функции иниц). Вызываю функцию, которая инициалировала бы табличку с чувачками , использующая дефолт данные и ее заполняет из файла
    return 0;
}
