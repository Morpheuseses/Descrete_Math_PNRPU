#include <iostream>
#include <string>
#include <vector>
using namespace std;

class Func_classes {
    bool** vecs;
    int vecs_size; // second equel 8
    bool** table;
public:
    Func_classes() {
        vecs = nullptr;
        table = nullptr;
    }    
    ~Func_classes() {
        for (int i = 0; i < vecs_size; i++) {
            delete[] vecs[i]; 
        }
        delete[] vecs;
        for (int i = 0; i < vecs_size; i++) {
            delete[] table[i]; 
        }
        delete[] table;
    }
    void input_vecs(int, string[]);
    void fill_classes_table();
    string convertTo8(string);
    void console_print_table(std::vector<string>);
    void valid_t0();
    void valid_t1();
    void valid_s();
    void valid_m(); // !!!!!!
    void valid_l(); // !!!!!!
    void find_polynomial_Zhegalkin(); // !!!!
};
string Func_classes::convertTo8(string vec) {
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
void Func_classes::input_vecs(int size, string str_vecs[]) {
    this->vecs = new bool*[size];
    for (int i = 0; i < size; i++) {
        vecs[i] = new bool[8];
        for (int j = 0; j < 8; j++) {
            vecs[i][j] = false;
        }
    }
    for (int i = 0; i < 8; i++) {
        cout << vecs[0][i] << " ";
    }
    // here can be vectors of these sizes [1,2,4,8]
    // so we need to process the data somehow 
    vecs_size = size;
    for (int i = 0; i < size; i++) {
        string tmp;
        if (str_vecs[i].length() != 8) {
            tmp = convertTo8(str_vecs[i]);
        }
        else {
            tmp = str_vecs[i];
        }
        for (int j = 0; j < 8; j++) {
            if (str_vecs[i][j] == '1') {
                vecs[i][j] == true;
            }
        }
    }
    // initialize table 
    this->table = new bool*[size];
    for (int i = 0; i < size; i++) {
        table[i] = new bool[5];
    }
    for (int i = 0; i < 8; i++) {
        cout << vecs[0][i] << " ";
    }
}
void Func_classes::fill_classes_table() {
    // T_0, T_1, S, M, L
    valid_t0();
    valid_t1();
    valid_s();
    valid_m();
    valid_l();
}
void Func_classes::valid_t0() {
    for (int i = 0; i < vecs_size; i++) {
        for (int j = 0; j < 8; i++) {
            if (vecs[i][j] == true) {
                table[i][0] = false;
                continue;
            }
        }
        table[i][0] = true;
    }
}
void Func_classes::valid_t1() {
    for (int i = 0; i < vecs_size; i++) {
        for (int j = 0; j < 8; i++) {
            if (vecs[i][j] == false) {
                table[i][1] = false;
                continue;
            }
        }
        table[i][0] = true;
    }
}
void Func_classes::valid_s() {
    for (int i = 0; i < vecs_size; i++) {
        for (int j = 0; j < 8; i++) {
            if (vecs[i][j] == vecs[i][8-j]) {
                table[i][2] = false;
                continue;
            }
        }
        table[i][2] = true;
    }
}
void Func_classes::valid_m() { // correct this 
    string comb[8] = {
        "000",
        "001",
        "010",
        "011",
        "100",
        "101",
        "110",
        "111"
    };
    int check_order[8] = {
        0,
        1,
        2,
        4,
        3,
        5,
        6,
        7
    };
    for (int i = 0; i < vecs_size; i++) {
        bool flag = false;
        for (int j = 0; j < 8; j++) {
            if (vecs[i][check_order[j]] == true) {
                flag = true;
            }
            if (vecs[i][j] == false && flag) {
                table[i][3] = false;        
            }
        }
        table[i][3] = true;
    }
}
void Func_classes::valid_l() {

}
void Func_classes::console_print_table(std::vector<std::string> headers) {
    
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
            if (table[i][j] == true) {
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
// get several vectors then process 'em and write result table in console


int main() {
    Func_classes getter;
    int size = 3;
    // here can be vectors of these sizes [1,2,4,8]
    string inp_strs[size] = {
        "10101010",
        "10101111",
        "10101011"
    };

    getter.input_vecs(size, inp_strs);
    getter.fill_classes_table();
    std::vector<string> headers = {
        "Vec_num", "T0", "T1", "S", "M", "L" 
    };
    getter.console_print_table(headers);
    return 0;
}

// масич, дискр, физика, прогр в кс, дпо, физкул