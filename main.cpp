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
    int health;
    int damage;
    SCoordinates coord;

    SUnity(): type(0), enemy(true), name(""), health(0), damage(0){};

    bool read_data(ifstream&);
    bool print_unit(ostream&);

};

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
    fin >> coord.x;
    if (!fin.good()){
        cerr << "Error reading coord.x" << endl;
        fin.ignore();
        fin.clear();
        fin.close();
        return false;
    }
    fin >> coord.y;
    if (!fin.good()) {
        cerr << "Error reading coord.y" << endl;
        fin.ignore();
        fin.clear();
        fin.close();
        return false;
    }
    else{
        return true;
    }
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

bool SGame::read_size(ifstream& fin) {
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
    for (int i = 0; i < map_size.y; ++i) {
        for (int j = 0; j < map_size.x; ++j) {
            fin >> map[i][j];
        }
    }
    return true;
}

bool SGame::print_map(ostream& out) {
    for (int i = 0; i < map_size.y; ++i) {
        for (int j = 0; j < map_size.x; ++j) {
            out << map[i][j];
        }
        out << endl;
    }
    return true;
}

bool SGame::print(ostream& out) {
    out << "Map size: " << map_size.x << " x " << map_size.y << endl;
    out << "Number of people: " << number_people << endl;

    out << "Map:" << endl;
    print_map(out);


    for (int i = 0; i < number_people; ++i) {
       people[i].print_unit(out);
    }
    return true;
}


void SGame::initUnits(ifstream& knight_f, ifstream& archer_f, ifstream& pikeman_f){
    cout << "Podaj ilosc osob ";
    cin >> number_people;
    people = new SUnity[number_people];

    cout <<  "Choose who you want to play as: Knight, Archer, Pikeman" << "\t";
    for(int i = 0 ; i < number_people ; ++i ){
        char tmp;
        cin >> tmp;
        if(tmp == Knight || tmp == Archer || tmp == Pikeman ){ //dodac else o tgm ze uzytkownik napisal nie ten znak
            people[i].type = tmp ;
        }
    }

    cout <<  "Choose who you want to play as: enemy or not" << "\t";
    for(int i = 0; i < number_people; ++i){
        int tmp;
        cin >> tmp;
        if(tmp == 0 || tmp == 1 ){ //dodac else o tgm ze uzytkownik napisal nie ten znak
            people[i].enemy = tmp ;
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
