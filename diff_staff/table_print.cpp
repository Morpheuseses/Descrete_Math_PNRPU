#include <iostream>
#include <string>
#include <vector>
using namespace std;

void console_print_table(std::vector<std::string> headers, bool**& table, int rows) {
    // find sizes
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


int main() {
    int rows = 4;
    int cols = 5;

    bool** table = new bool*[rows];

    for (int i = 0; i < rows; i++) {
        table[i] = new bool[cols];
    }

    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            table[i][j] = false;
        }
    }
    std::vector<string> headers = {
        "Vecs", "T0", "T1", "S", "M", "L"
    };

    console_print_table(headers, table, rows);

    return 0;
}