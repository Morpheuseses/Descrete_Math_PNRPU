#include <iostream>
#include <vector>
#include <set>
#include <cmath>
#include <string>
#include <algorithm>
#include <fstream>
using namespace std;

typedef vector<int> Conjuction;
// let's define quantity of variables. Let's it be function with 4 variables


class Quine_minimization {
    vector<int> func_vec;
    vector<Conjuction> conjuctions;
    vector<Conjuction> implicants; // if variable is not in conjuction it becomes an -1
public:
    vector<int> stringToVec(string);
    void input_vec(string vec); // fill the conjucitons field

    void console_print_conjuctions(vector<Conjuction>);
    void print_mtx();
    void print_table();
    void minimize(); // don't know how to realize
    void get_vec_from_file(string);

    vector<Conjuction> get_implicants();


    // void get_result(); // return minimized function
};

vector<int> Quine_minimization::stringToVec(string str) {
    vector<int> res;

    for (int i = 0; i < str.size(); i++) {
        if (str[i] == '1') {
            res.push_back(1);
        }
        if (str[i] == '0') {
            res.push_back(0);
        }
    }
    return res;
}
void Quine_minimization::get_vec_from_file(string filename) {
    ifstream file;
    file.open(filename);
    if (!file.is_open()) {
        std::cout << "Bad file" << std::endl;
        return;
    }
    vector<int> res;
    int num;
    for (int i = 0; i < 16; i++){
        file >> num;
        res.push_back(num);
    }
    if (res.size() != 16) {
        std::cout << "Wrong size of vector"<< endl;
        return;
    }
    func_vec = res;
    input_vec("file");

}
void Quine_minimization::input_vec(string vec) {
    if (vec != "file") {
    if (vec.length() != 16) {
        std::cout << "Wrong vector size!" << endl;
        return;
    }
    for (int i = 0; i < 16; i++) {
        if (vec[i] != '1' && vec[i] != '0') {
            std::cout << "Wrong values in the input vector" << endl;
            return;
        }
    }
    
    this->func_vec = stringToVec(vec);
    }
    std::cout << "Vector is accepted" << endl;

    int i = 0;
    for (int x = 0; x < 2; x++) {
        for (int y = 0; y < 2; y++) {
            for (int z = 0; z < 2; z++) {
                for (int w = 0; w < 2; w++) {
                    if (func_vec[i] == 1) {
                        Conjuction curr = { x, y, z, w };
                        conjuctions.push_back(curr);
                    }
                    i++;
                }
            }
        }
    }
    std::cout << "Perfect disjunctive normal form have been made successfully" << endl;
    print_mtx();
    console_print_conjuctions(conjuctions);
}

vector<Conjuction> Quine_minimization::get_implicants() {
    // 1 step gettihg 3 vars
    vector<Conjuction> used; 
    vector<Conjuction> third_level;

    for (int i = 0; i < conjuctions.size(); i++) {
        for (int j = i; j < conjuctions.size(); j++) {
            int numb_same = 0;
            int map = 0;
            Conjuction curr = vector<int>(4, -1);
            for (int k = 0; k < 4; k++) {
                if (conjuctions[i][k] == conjuctions[j][k] && conjuctions[i][k] != -1) {
                    numb_same++;
                    curr[k] = conjuctions[i][k];
                }
                if ((conjuctions[i][k] != -1) && (conjuctions[j][k] != -1)) {
                    map++;
                }
            }
            if (numb_same == 3 && find(third_level.begin(), third_level.end(), curr) == third_level.end() && (map == 4)) {
                third_level.push_back(curr);
                used.push_back(conjuctions[i]);
                used.push_back(conjuctions[j]);
            }
            else if (find(third_level.begin(), third_level.end(), curr) != third_level.end()) {
                used.push_back(conjuctions[i]);
                used.push_back(conjuctions[j]);
            }
        }
    }
    
    vector<Conjuction> result; // it will be returned to the implicants vector 

    for (int i = 0; i < conjuctions.size(); i++) {
        if (find(used.begin(), used.end(), conjuctions[i]) == used.end()) {
            result.push_back(conjuctions[i]);
        }
    }
    
    vector<Conjuction> second_level;

    // 2 step getting 2 vars
    for (int i = 0; i < third_level.size(); i++) {
        for (int j = i; j < third_level.size(); j++) {
            int numb_same = 0;
            int map = 0;
            Conjuction curr = vector<int>(4, -1);
            for (int k = 0; k < 4; k++) {
                if (third_level[i][k] == third_level[j][k] && third_level[i][k] != -1) {
                    numb_same++;
                    curr[k] = third_level[i][k];
                }
                if ((third_level[i][k] != -1) && (third_level[j][k] != -1)) {
                    map++;
                }
            }
            if (numb_same == 2 && find(second_level.begin(), second_level.end(), curr) == second_level.end() && (map == 3)) {
                second_level.push_back(curr);
                used.push_back(third_level[i]);
                used.push_back(third_level[j]);
            }
            else if (find(second_level.begin(), second_level.end(), curr) != second_level.end()) {
                used.push_back(third_level[i]);
                used.push_back(third_level[j]);
            }
        }
    }
    for (int i = 0; i < third_level.size(); i++) {
        if (find(used.begin(), used.end(), third_level[i]) == used.end()) {
            result.push_back(third_level[i]);
        }
    }

    vector<Conjuction> first_level;
    //3 step 1 var conjuciton
    for (int i = 0; i < second_level.size(); i++) {
        for (int j = i; j < second_level.size(); j++) {
            int numb_same = 0;
            int map = 0;
            Conjuction curr = vector<int>(4, -1);
            for (int k = 0; k < 4; k++) {
                if (second_level[i][k] == second_level[j][k] && second_level[i][k] != -1) {
                    numb_same++;
                    curr[k] = second_level[i][k];
                }
                if ((second_level[i][k] != -1) && (second_level[j][k] != -1)) {
                    map++;
                }
            }
            if (numb_same == 1 && find(first_level.begin(), first_level.end(), curr) == first_level.end() && (map == 2)) {
                first_level.push_back(curr);
                used.push_back(second_level[i]);
                used.push_back(second_level[j]);
            }
            else if (find(first_level.begin(), first_level.end(), curr) != first_level.end()) {
                used.push_back(second_level[i]);
                used.push_back(second_level[j]);
            }
        }
    }
    for (int i = 0; i < second_level.size(); i++) {
        if (find(used.begin(), used.end(), second_level[i]) == used.end()) {
            result.push_back(second_level[i]);
        }
    }
    /*for (auto x : to_erase) {
        implicants.erase(find(implicants.begin(), implicants.end(), x));    
    }*/
    for (int i = 0; i < first_level.size(); i++) {
        result.push_back(first_level[i]);
    }
    implicants = result;
    return result;
}

void Quine_minimization::console_print_conjuctions(vector<Conjuction> vec) {
    std::cout << "      ";
    for (int i = 0; i < vec.size(); i++) {
        Conjuction curr_conj = vec[i];
        for (int k = 0; k < 4; k++)
            if (curr_conj[k] == 1)
                std::cout << " ";
            else if (curr_conj[k] == 0)
                std::cout << "_";

        if (i != vec.size() - 1) {
            std::cout << "   ";
        }
    }
    std::cout << endl;
    std::cout << "PDNF: ";
    for (int i = 0; i < vec.size(); i++) {
        Conjuction curr_conj = vec[i];
        if (curr_conj[0] != -1)
            std::cout << "x";
        if (curr_conj[1] != -1)
            std::cout << "y";
        if (curr_conj[2] != -1)
            std::cout << "z";
        if (curr_conj[3] != -1)
            std::cout << "w";
        if (i != vec.size() - 1) {
            std::cout << " v ";
        }
    }
    std::cout << endl;
}
void Quine_minimization::print_mtx() {
    std::cout << "x y z w  f" << endl;
    int i = 0;
    for (int x = 0; x < 2; x++) {
        for (int y = 0; y < 2; y++) {
            for (int z = 0; z < 2; z++) {
                for (int w = 0; w < 2; w++) {
                    if (func_vec[i] == 1) {  
                        std::cout << x << " " << y << " " << z << " " << w << "  1 !" << endl;
                    }
                    else {
                        std::cout << x << " " << y << " " << z << " " << w << "  0" << endl;
                    }
                    i++;
                }
            }
        }
    }
    std::cout << endl;
}
void Quine_minimization::print_table() {
    std::cout << endl;
    std::cout << "---|Table|---" << endl;
// table header 
    std::cout << "    |";
    for (int i = 0; i < conjuctions.size(); i++) {
        Conjuction curr_conj = conjuctions[i];
        for (int k = 0; k < 4; k++)
            if (curr_conj[k] == 1)
                std::cout << " ";
            else if (curr_conj[k] == 0)
                std::cout << "_";

        if (i != conjuctions.size() - 1) {
            std::cout << "  |";
        }
    }
    std::cout << endl;
    std::cout << "____|";
    for (int i = 0; i < conjuctions.size(); i++) {
        Conjuction curr_conj = conjuctions[i];
        if (curr_conj[0] != -1)
            std::cout << "x";
        if (curr_conj[1] != -1)
            std::cout << "y";
        if (curr_conj[2] != -1)
            std::cout << "z";
        if (curr_conj[3] != -1)
            std::cout << "w";
        if (i != conjuctions.size() - 1) {
            std::cout << "  |";
        }
    }
    std::cout << endl;

// printing rows 
    // create valid vector
    vector<vector<bool>> valid = vector<vector<bool>>(implicants.size(), vector<bool>(conjuctions.size(), false));

    // create valid values
    for (int i = 0; i < implicants.size(); i++) {
        for (int j = 0; j < conjuctions.size(); j++) {
            int numb_size = 0;
            int implicant_size = 0;
            for (int k = 0; k < 4; k++) {
                if (implicants[i][k] == conjuctions[j][k]) 
                    numb_size++;
                if (implicants[i][k] != -1)
                    implicant_size++;
            }
            if (numb_size == implicant_size) {
                valid[i][j] = true;
            }
        }
    }
    
    
    // print 
    for (int i = 0; i < valid.size(); i++) {
        int numb_var = 0;
        Conjuction curr_conj = implicants[i];
        for (int k = 0; k < 4; k++)
            if (curr_conj[k] == 1)
                std::cout << " ";
            else if (curr_conj[k] == 0)
                std::cout << "_";
        std::cout << endl;
        numb_var = 0;
        if (curr_conj[0] != -1) {
            std::cout << "x";
            numb_var++;
        }
        if (curr_conj[1] != -1) {
            std::cout << "y";
            numb_var++;
        }
        if (curr_conj[2] != -1) {
            std::cout << "z";
            numb_var++;
        }
        if (curr_conj[3] != -1) {
            std::cout << "w";
            numb_var++;
        }
        for (int i = 0; i < 4-numb_var; i++)
            std::cout << " ";
        std::cout << "|";

        for (int j = 0; j < valid[0].size(); j++) {
            if (valid[i][j] == true)
                std::cout << "   +  |";
            else
                std::cout << "      |";
        }
        std::cout << endl;
    }
}
int main() {
    Quine_minimization minimizer;
    string str = "1100110011000010";
    string str2 = "1110001000110000";
    string str3 = "1111110011111100";
    string str4 = "1100000000001111";
    string str5 = "1011001100111111";
    string str_inp = "1100110001111100";
    cout << "Input vector: "<< str_inp << endl;
    //minimizer.get_vec_from_file("./vector.txt");
    minimizer.input_vec(str_inp);
    
    minimizer.console_print_conjuctions(minimizer.get_implicants());
    minimizer.print_table();
    //minimizer.console_print_conjuctions(minimizer.get_implicants());
    return 0;
}