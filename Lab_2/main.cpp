#include <iostream>
#include <fstream>
#include <unordered_map>
#include <string>
using namespace std;


#define ROW 6
#define COL 6

class Relation_detector {
private:
    bool** mtx;
    const char* filename = "./tests/m8.txt"; // change file here
    unordered_map<std::string, bool> relations; 
public:
    void detect_relations();
    void console_print_relations(); 
    void enter_mtx();
    void console_print_mtx();
    // check truthfulness of relations 
    void check_reflexivity();
    void check_antireflexivity();
    void check_symmetry();
    void check_antisymmetry();
    void check_asymmetry();
    void check_transitivity();
    void check_connectivity();
};

void Relation_detector::enter_mtx() {
    ifstream ifile;
    ifile.open(filename);
    if (!ifile.is_open()) {
        cout << "Bad file" << endl;
        return;
    }
    mtx = new bool*[ROW];
    for (int i = 0; i < ROW; i++) {
        mtx[i] = new bool[COL];
    }
    int input;
    
    for (int i = 0; i < ROW; i++) {
        for (int j = 0; j < COL; j++) {
            ifile >> input;
            if (input == 1) {
                mtx[i][j] = true;
            }
            else if (input == 0) {
                mtx[i][j] = false;
            }
        }
    }
    
    cout << "Matrix has loaded successfully" << endl;
    ifile.close();
}

void Relation_detector::console_print_mtx() {
    cout << "Matrix: " <<endl;
    cout << "Name of matrix file - " << filename << endl;
    for (int i = 0; i < 6; i++) {
        for (int j = 0; j < 6; j++) {
            if (mtx[i][j] == true)
                cout << 1 << ' ';
            else
                cout << 0 << ' ';
        }
        cout << endl;
    }
    cout << endl;
}

void Relation_detector::check_reflexivity() {
    for (int i = 0; i < ROW; i++) {
        if (mtx[i][i] != true) {
            relations["reflexivity"] = false;
            return;
        }
    }
    relations["reflexivity"] = true;
}
void Relation_detector::check_antireflexivity() {
    for (int i = 0; i < ROW; i++) {
        if (mtx[i][i] != false) {
            relations["anti-reflexivity"] = false;
            return;
        }
    }
    relations["anti-reflexivity"] = true;
}
void Relation_detector::check_symmetry() {
    for (int i = 0; i < ROW; i++) {
        for (int j = 0; j < COL; j++) {
            if (i != j && !(mtx[i][j] == false || mtx[j][i] == true)) {
                relations["symmetry"] = false;
                return;
            }
        }
    }
    relations["symmetry"] = true;
}
// (mtx[i][j]==true) && (mtx[j][i]==true) -> mtx[i][j] == mtx[j][i]
// mtx[i][j] == false || mtx[j][i] == false || mtx[i][j] == mtx[i][j]
void Relation_detector::check_antisymmetry() { 
    for (int i = 0; i < ROW; i++) {
        for (int j = 0; j < COL; j++) {
            if (i != j && !(mtx[i][j] == false || mtx[j][i] == false)) {
                relations["antisymmetry"] = false;
                return;
            }
        }
    }
    relations["antisymmetry"] = true;
}
void Relation_detector::check_asymmetry() {
    for (int i = 0; i < ROW; i++) {
        for (int j = 0; j < COL; j++) {
            if (!(mtx[i][j] == false || mtx[j][i] == false)) {
                relations["asymmetry"] = false;
                return;
            }
        }
    }
    relations["asymmetry"] = true;
    relations["antisymmetry"] = false;
}
void Relation_detector::check_transitivity() {
    for (int i = 0; i < ROW; i++) {
        for (int j = 0; j < COL; j++) {
            for (int k = 0; k < ROW; k++) {
                if ((mtx[i][j] == true) && (mtx[j][k] == true) && (mtx[i][k] == false)) {
                    relations["transitivity"] = false;
                    return;
                }
            }
        } 
    }
    relations["transitivity"] = true;
}
void Relation_detector::check_connectivity() {
    for (int i = 0; i < ROW; i++) {
        for (int j = 0; j < COL; j++) {
            if ((mtx[i][j] == false) && (mtx[i][j] == mtx[j][i]) && i != j) {
                relations["connectivity"] = false;
                return;
            }
        }
    }
    relations["connectivity"] = true;
}   
void Relation_detector::detect_relations() {

    check_reflexivity();
    
    check_antireflexivity();
    
    check_symmetry();
    
    check_antisymmetry();

    check_asymmetry();
    
    check_transitivity();

    check_connectivity();
}
void Relation_detector::console_print_relations() {
    cout << "Existing relations" << endl;
    for (auto elem : relations) {
        cout << elem.first << " " << elem.second << endl;
    }
}
int main() {
    Relation_detector detector;
    detector.enter_mtx();
    detector.console_print_mtx();
    detector.detect_relations();
    detector.console_print_relations();
    return 0;
}