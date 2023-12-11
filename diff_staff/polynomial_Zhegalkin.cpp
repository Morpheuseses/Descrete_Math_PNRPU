#include <iostream>
using namespace std;


bool addition_mod2(bool f1, bool f2) {
    return (f1 + f2) % 2;
}


void Zhegalkin(bool vec[]) {
    bool arr[8]{false};
    arr[0] = vec[0];
    for (int i = 1; i < 8; i++) {
        bool sum = arr[0];
        for (int j = 1; j < i; j++) {
            sum = (sum + arr[j]) % 2;
        }
        if (((sum + 1) % 2) == vec[i]) {
            arr[i] = true;
        }
        else {
            arr[i] = false;
        }
    }

    for (int i = 0; i < 8; i++) {
        if (!(i < 3 || i == 4) && arr[i] == true) {
            cout << "false" << endl;
            return;
        }
    }
    cout << "true" << endl;
}

int main() {
    // 1101 0011
    bool vec[8] = {false, false, true, true, true, true, true, true};
    
    Zhegalkin(vec);
}

