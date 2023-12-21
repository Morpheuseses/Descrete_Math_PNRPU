#include <iostream>
#include <string>
#include <vector>
using namespace std;

#define STD_VEC_SIZE 8


class Func_fullness {
    bool** vecs;
    int vecs_size;
    bool** table;
public:
    Func_fullness() {
        vecs = nullptr;
        table = nullptr;
    }
    ~Func_fullness() {
        if (vecs != nullptr) {
            for (int i = 0; i < vecs_size; i++) {
                delete[] vecs[i];
            }
            delete[] vecs;
        }
        if (table != nullptr) {
            for (int i = 0; i < vecs_size; i++) {
                delete[] table[i];
            }
            delete[] table;
        }
    }
private:
    void valid_t0();
    void valid_t1();
    void valid_s();
    void valid_m();
    void valid_l();
    string convertTo8(string);
public:
    void input_vecs(int, string[]);
    void console_print_vecs();
    void fill_classes_table();
    void console_print_table(std::vector<std::string>);
};

// implementation
string Func_fullness::convertTo8(string vec) {
    string res = "";
    switch (vec.length())
    {
        case 1:
            for (int i = 0; i < 8; i++) {
                res += vec[0];
            }
            break;
        case 2:
            for (int i = 0; i < 2; i++) {
                res += vec[i];
                res += vec[i];
                res += vec[i];
                res += vec[i];
            }
            break;
        case 4:
            for (int i = 0; i < 4; i++) {
                res += vec[i];
                res += vec[i];
            }
            break;
    }
    return res;
}
void Func_fullness::input_vecs(int size, string strs[]) {
    vecs_size = size;
    this->vecs = new bool*[size];

    for (int i = 0; i < vecs_size; i++) {
        this->vecs[i] = new bool[STD_VEC_SIZE];
        for (int j = 0; j < STD_VEC_SIZE; j++) {
            this->vecs[i][j] = false;
        }
    }       
    
    for (int i = 0; i < size; i++) {
        string tmp = strs[i];
        if (tmp.size() < 8) {
            tmp = convertTo8(tmp);
        }
        for (int j = 0; j < STD_VEC_SIZE; j++) {
            if (tmp[j] == '1') {
                vecs[i][j] = true;
            }

        }
    }

}
void Func_fullness::valid_t0() {
    for (int i =0; i < vecs_size; i++) {
        if (vecs[i][0] == false) {
            table[i][0] = true;
        }
        else {
            table[i][0] = false;
        }
    }
}
void Func_fullness::valid_t1() {
    for (int i = 0; i < vecs_size; i++) {
        if (vecs[i][7] == true) {
            table[i][1] = true;
        }
        else {
            table[i][1] = false;
        }
    }
}
void Func_fullness::valid_s() {
    for (int i = 0; i < vecs_size; i++) {
        bool flag = false;
        for (int j = 0; j < STD_VEC_SIZE; j++) {
            if (this->vecs[i][j] == this->vecs[i][STD_VEC_SIZE-j-1]) {
                this->table[i][2] = false;
                flag = true;
                break;
            }
        }
        if (flag != true)
            this->table[i][2] = true;
    }
}
void Func_fullness::valid_m() {
    int order[6][4] = {
        {0, 1, 3, 7},
        {0, 1, 5, 7},
        {0, 2, 3, 7},
        {0, 2, 6, 7},
        {0, 4, 6, 7},
        {0, 4, 5, 7}
    };
    for (int v = 0; v < vecs_size; v++) {
        bool exit = false;
        for (int i = 0; i < 6 && exit == false; i++) {
            
            bool fl_changed = false;
            for (int j = 0; j < 4; j++) {
                if (vecs[v][order[i][j]] == true) {
                    fl_changed = true;
                };
                if (vecs[v][order[i][j]] == false && fl_changed == true) {
                    table[v][3] = false;
                    exit = true;
                    break;
                }
            };
        }
        if (exit == false) {
            table[v][3] = true;
        }
    }
}
void Func_fullness::valid_l() {
    for (int v = 0; v < vecs_size; v++) {
        
        bool arr[4]{false};
        // C_xy
        arr[0] = ((((vecs[v][0] + vecs[v][4]) % 2 + vecs[v][2]) % 2) + vecs[v][6]) % 2;
        // C_yz
        arr[1] = (((vecs[v][0] + vecs[v][2]) % 2 + vecs[v][1]) + vecs[v][3]) % 2;
        // C_xz
        arr[2] = (((vecs[v][0] + vecs[v][1]) % 2 + vecs[v][4]) + vecs[v][5]) % 2;
        // C_xyz
        arr[3] = arr[0];
        for (int i =1; i < vecs_size; i++) {
            arr[3] = (arr[3] + arr[i]) % 2;
        }

        if (arr[0] == true || arr[1] == true || arr[2] == true || arr[3] == true) {
            table[v][4] = false;
        }
        else {
            table[v][4] = true;
        }
    }
}
void Func_fullness::fill_classes_table() {
    this->table = new bool*[vecs_size];
    for (int i = 0; i < vecs_size; i++) {
        this->table[i] = new bool[5];
        for (int j = 0; j < 5; j++) {
            this->table[i][j] = false;
        }
    }
    valid_t0();
    valid_t1();
    valid_s();
    valid_m();
    valid_l();

    cout << endl;
    for (int j = 0; j < 5; j++) {
        bool flag = true;
        for (int i = 0; i < vecs_size; i++) {
            if (table[i][j] == false) {
                flag = false;
            }
        }
        if (flag == true) {
            cout << "The functions don't make up the full-fuctional system" << endl;
            return;
        }
    }
    cout << "The system is fully-fuctional " << endl;
}
void Func_fullness::console_print_vecs() {
    cout << '\n' << "Vectors you inserted in: " << endl;
    for (int i = 0; i < vecs_size; i++) {
        for (int j = 0; j < STD_VEC_SIZE; j++) {
            cout << vecs[i][j] << " ";
        }
        cout << endl;
    }
}
void Func_fullness::console_print_table(std::vector<std::string> headers) {
    
    int rows = vecs_size;

    vector<int> sizes;

    for (int i = 0; i < headers.size(); i++) {
        sizes.push_back(headers[i].size() + 2);
    }
    cout << "+";
    //print hat line
    for (int i = 0; i < headers.size(); i++) {
        for (int j = 0; j < sizes[i]; j++) {
            cout << "-";
        }
        cout << "+";
    }
    cout << endl;
    // print headers
    cout << "|";
    for (int i = 0; i < headers.size(); i++) {
        cout << " " << headers[i] << " |";
    }
    cout << endl;
    // print line
    cout << "+";
    for (int i = 0; i < headers.size(); i++) {
        for (int j = 0; j < sizes[i]; j++) {
            cout << "-";
        }
        cout << "+";
    }
    cout << endl;

    for (int i = 0; i < rows; i++) {
        int spaces1, spaces2;
            if (sizes[0] % 2 == 0) {
                spaces1 = sizes[0] / 2 - 1;
                spaces2 = sizes[0] / 2;
            }
            else {
                spaces1 = spaces2 = sizes[0] / 2;
            }
        cout << "|";
        for (int k = 0; k < spaces1; k++) {
                cout << " ";
        }
        cout << i;
        for (int k = 0; k < spaces2; k++) {
                cout << " ";
        }
        cout << "|";
        for (int j = 1; j < headers.size(); j++) {
            int spaces1, spaces2;
            if (sizes[j] % 2 == 0) {
                spaces1 = sizes[j] / 2 - 1;
                spaces2 = sizes[j] / 2;
            }
            else {
                spaces1 = spaces2 = sizes[j] / 2;
            }
            for (int k = 0; k < spaces1; k++) {
                cout << " ";
            }
            if (this->table[i][j-1] == true) {
                cout << "+";
            }
            else {

                cout << "-";
            }
            for (int k = 0; k < spaces2; k++) {
                cout << " ";
            }
            cout << "|";
        }
        cout << endl;
    }
    cout << "+";
    for (int i = 0; i < headers.size(); i++) {
        for (int j = 0; j < sizes[i]; j++) {
            cout << "-";
        }
        cout << "+";
    }
    cout << endl;
}
int main() {
    const int size = 2;
    string strs[size] = {
        "1010",
        "0110"
    };
    Func_fullness getter;
    getter.input_vecs(size, strs);
    getter.console_print_vecs();
    getter.fill_classes_table();
    std::vector<std::string> headers = {
        "Vec_num", "T0", "T1", "S", "M", "L" 
    };
    getter.console_print_table(headers);
    return 0;
}