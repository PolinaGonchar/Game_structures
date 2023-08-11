#include <iostream>
#include <fstream>
#include <string>

using namespace std;

enum NaMe{
    //Knight =  75,
    Knight = 107,
    //Archer = 65,
    Archer = 97,
    //Pikeman = 80,
    Pikeman = 112
};

struct SCoordinates{
    int x, y;

    SCoordinates(): x(-1), y(-1){};
};

struct SUnity{
    char type;
    bool enemy;
    string name;
    static int id;
    int health;
    int damage;
    SCoordinates coord;

    SUnity(): type(0), enemy(true), name(""), health(0), damage(0){id++;};

    bool read_data(ifstream&);
    bool print_unit(ostream&);

};

int SUnity::id = 0;

struct SGame{
    char** map;
    SCoordinates map_size;
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


    bool read_size(ifstream&);
    bool read_map(ifstream&);
    bool print_map(ostream&);
    bool print(ostream&);
    void initUnits(ifstream&, ifstream& , ifstream&);
    void moveUnit(int indexUnit, int moveX , int moveY);
    void applyDamage(int indexUnit);
};



bool SUnity::read_data(ifstream& fin){
    fin >> name;
    if(!fin.good()){
        cerr << "Error reding name" << endl;
        fin.ignore();
        fin.clear();
        fin.close();
        return false;
    }
    fin >> health;
    if(!fin.good()){
        cerr << "Error reading health" << endl;
        fin.ignore();
        fin.clear();
        fin.close();
        return false;
    }
    fin >> damage;
    if(!fin.good()){
        cerr << "Error reading damage" << endl;
        fin.ignore();
        fin.clear();
        fin.close();
        return false;
    }
    /*if(enemy){
        fin >> coord.x;
        if (!fin.good()){
            cerr << "Error reading coord.x" << endl;
            fin.ignore();
            fin.clear();
            fin.close();
            return false;
        }
        fin >> coord.y;
        if (!fin.good()){
            cerr << "Error reading coord.y" << endl;
            fin.ignore();
            fin.clear();
            fin.close();
            return false;
        }
        else{
            return true;
        }*/
    return true;
}

bool SUnity::print_unit(ostream& out){
    out << type << endl;
    if(!out.good()){
        cerr<< "Error print ..." << endl;
        out.clear();
        //out.close();
        return false;
    }
    out << enemy << endl;
    if(!out.good()){
        cerr<< "Error print ..." << endl;
        out.clear();
        //out.close();
        return false;
    }
    out <<  name  << endl;
    if(!out.good()){
        cerr<< "Error print ..." << endl;
        out.clear();
        //out.close();
        return false;
    }
    out << id << endl;
    out << health << endl;
    if(!out.good()){
        cerr<< "Error print ..." << endl;
        out.clear();
        //out.close();
        return false;
    }
    out << damage << endl;
    if(!out.good()){
        cerr<< "Error print ..." << endl;
        out.clear();
        //out.close();
        return false;
    }
    out << coord.x << endl;
    if(!out.good()){
        cerr<< "Error print ..." << endl;
        out.clear();
        //out.close();
        return false;
    }
    out << coord.y << endl;
    if(!out.good()){
        cerr<< "Error print ..." << endl;
        out.clear();
        //out.close();
        return false;
    }
    return true;
}

bool SGame::read_size(ifstream& fin){
    fin >> map_size.x >> map_size.y;
    if (!fin.good()) {
        cerr << "Error reading map size" << endl;
        fin.ignore();
        fin.clear();
        fin.close();
        return false;
    }
    return true;
}

bool SGame::read_map(ifstream& fin){
    map = new char*[map_size.y];
    for(int i = 0 ; i < map_size.y; ++i){
        map[i]= new char[map_size.x];
    }
    for (int i = 0; i < map_size.y; ++i){
        for (int j = 0; j < map_size.x; ++j){
            fin >> map[i][j];
        }
    }
    return true;
}

bool SGame::print_map(ostream& out){
    for (int i = 0; i < map_size.y; ++i){
        for (int j = 0; j < map_size.x; ++j){
            out << map[i][j];
        }
        out << endl;
    }
    return true;
}

bool SGame::print(ostream& out){
    out << "Map size: " << map_size.x << " x " << map_size.y << endl;
    out << "Number of people: " << number_people << endl;

    out << "Map:" << endl;
    print_map(out);


    for (int i = 0; i < number_people; ++i){
       people[i].print_unit(out);
    }
    return true;
}


void SGame::initUnits(ifstream& knight_f, ifstream& archer_f, ifstream& pikeman_f){
    //изменить форы, добавить коменты и протестировать с неправильными буквами
    //не считываем корд из файла, а только в зависимости враг ли это или нет (смодиф функцию данные из файла)
    //Написать две функции в СГэйм движение и атака , если движение, то двигаемся по одной клетки на подумать ;( считываем с кодами Аски сам пототип прописать 
    //функция урон убираем кол хп с конкретным индексом
    //содать ид юнита , должна быть уник статик инт
    cout << "Provide the number of people: ";
    cin >> number_people;
    people = new SUnity[number_people];

    for(int i = 0 ; i < number_people ; ++i ){
        cout << "Choose who you want to play as: Knight(k), Archer(a), Pikeman(p) : ";
        char tmp_type;
        int tmp_enemy;
        bool successfull_type = false;
        bool successfull_enemy = false;

        while(!successfull_type){
            cin >> tmp_type;
            if(tmp_type == Knight || tmp_type == Archer || tmp_type == Pikeman){
                people[i].type = tmp_type;
                successfull_type = true;

                cout << "Is " << tmp_type << " an enemy? (0 for no, 1 for yes): ";
                while(!successfull_enemy){
                    cin >> tmp_enemy;
                    if(tmp_enemy == 0 || tmp_enemy == 1){
                        people[i].enemy = tmp_enemy;
                        successfull_enemy = true;
                    }
                    else{
                        cout << "Invalid input. Please enter 0 for no or 1 for yes." << endl;
                    }
                }
            }
            else{
                cout << "Invalid input. You can choose Knight (k), Archer (a), or Pikeman (p)" << endl;
            }
        }
    }

    for(int i = 0 ; i < number_people ; ++i){
        if(!people[i].enemy){
            people[i].coord.x = 0;
            people[i].coord.y = 0;
        }
        else{
            people[i].coord.x = map_size.x - 1 ;
            people[i].coord.y = map_size.y -1 ;
        }
    }

    for (int i = 0 ; i < number_people; ++i){
        switch(people[i].type){
            case Knight:
                people[i].read_data(knight_f);
                knight_f.seekg(0);
                break;
            case Archer:
                people[i].read_data(archer_f);
                archer_f.seekg(0);
                break;
            case Pikeman:
                people[i].read_data(pikeman_f);
                pikeman_f.seekg(0);
                break;
        }
    }
}
// cout << int(moj znak)-jak znalesc kod ASCII (A-65)



void SGame::moveUnit(int indexUnit, int moveX , int moveY){
    if (indexUnit >= 0 ){
        SCoordinates actual;
        actual.x = people[indexUnit].coord.x;
        actual.y = people[indexUnit].coord.y;
        if((actual.x + moveX) >= map_size.x || (actual.y + moveY) >= map_size.y || (actual.x + moveX) < 0 || (actual.y + moveY) < 0){
            cout << "Движение невозможно ";
        }
        else{
            people[indexUnit].coord.x += moveX;
            people[indexUnit].coord.y += moveY;
        }
    } else{
        cout << "Invalid unit index" << endl;
    }
}
void SGame::applyDamage(int indexUnit){
    if (indexUnit >= 0){
        people[indexUnit].health -= people[indexUnit].damage;
        if (people[indexUnit].health <= 0){
            cout << people[indexUnit].name << " has been defeated!" << endl;
        }
    } else{
        cout << "Invalid unit index" << endl;
    }
}

int main(int argc, char * argv[]){
    if(argc != 6){
        cerr << "Invalid number of arguments. Provide ./program_name input_map.txt input_unit1.txt input_unit2.txt input_unit3.txt output.txt" << endl;
        return 100;
    }


    ifstream fin_map(argv[1]);
    if(!fin_map.good()){
        cerr << "Failed to open input file_map" << "\n";
        fin_map.ignore();
        fin_map.clear();
        fin_map.close();
        return 101;
    }

    ifstream fin_K(argv[2]);
    if(!fin_K.good()){
        cerr << "Failed to open input file_unit1" << "\n";
        fin_K.ignore();
        fin_K.clear();
        fin_K.close();
        return 102;
    }

    ifstream fin_A(argv[3]);
    if(!fin_A.good()){
        cerr << "Failed to open input file_unit2" << "\n";
        fin_A.ignore();
        fin_A.clear();
        fin_A.close();
        return 103;
    }

    ifstream fin_P(argv[4]);
    if(!fin_P.good()){
        cerr << "Failed to open input file_unit3" << "\n";
        fin_P.ignore();
        fin_P.clear();
        fin_P.close();
        return 104;
    }

    ofstream fout(argv[5]);
    if(!fout.good()){
        cerr << "Failed to open output file" << "\n";
        fout.clear();
        fout.close();
        return 105;
        }

    SGame game;
    game.read_size(fin_map);
    game.read_map(fin_map);
    game.initUnits(fin_K, fin_A, fin_P);
    game.print(cout);

    fin_map.close();
    fin_K.close();
    fin_A.close();
    fin_P.close();
    fout.close();
    return 0;
}
