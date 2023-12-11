#include <iostream>
#include <string>
using namespace std;



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
void print_strings(int size, string strs[]) {
    for (int i = 0; i < size; i++) {
        cout << strs[i] << endl;
    }
}
int main() {
    string str = "1101";
    cout << convertTo8(str) << endl;
    string strs[3] = {
        "fjsoiefjs",
        "fjsoejfsioefh",
        "fsoeoifisheol"
    };
    print_strings(3, strs);
    return 0;
}