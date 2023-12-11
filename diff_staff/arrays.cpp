#include <iostream>
using namespace std;


class TestArray {
    bool** arr;
    int size;
public:
    TestArray() {
        arr = nullptr;
    }
    ~TestArray() {
        delete[] arr;
    }
    void made_arr() {
        this->arr = new bool*[4];
        for (int i = 0; i < 4; i++) {
        arr[i] = new bool[8];
        for (int j = 0; j < 8; j++) {
            arr[i][j] = false;
        }
    }
    }
    void print_arr() {
        for (int i = 0; i < size; i++) {
            for (int j = 0; j < 8; j++) {
            cout << arr[i][j] << " ";
        }
        cout << endl;
    }
    }
    string convertTo8(string vec) {
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
    void input_vecs(int size, string str_vecs[]) {
        this->arr = new bool*[size];
        for (int i = 0; i < size; i++) {
            arr[i] = new bool[8];
            for (int j = 0; j < 8; j++) {
                arr[i][j] = false;
            }
        }
        // here can be vectors of these sizes [1,2,4,8]
        // so we need to process the data somehow 
        this->size = size;
        for (int i = 0; i < size; i++) {
            string tmp;
            if (str_vecs[i].length() != 8) {
                tmp = convertTo8(str_vecs[i]);
            }
            else {
                tmp = str_vecs[i];
            }
            for (int j = 0; j < 8; j++) {
                if (tmp[j] == '1') {
                    arr[i][j] == true;
                }
            }
        }
        // initialize table 
    }
};

int main() {

    TestArray test;
    string strs[3] = {
        "10011010",
        "1010",
        "11010111"
    };
    test.input_vecs(3,strs);
    test.print_arr();
    
    return 0;
}