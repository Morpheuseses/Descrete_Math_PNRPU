#include <iostream>
#include <algorithm>
#include <ctime>
using namespace std;


#define LEFT_BOUND -200
#define RIGHT_BOUND 200

#define EXIT_MODE 100
#define CALC_MODE 101

struct MySet {
    bool* container;
    int size;
    int max_size;
    string name;
    MySet() {
        container = nullptr;
        size = 0;
        name = "";
    }
    MySet(int max_size, string name) {
        container = new bool[max_size];
        for (int i = 0; i < max_size; i++) {
            container[i] = false;
        }
        size = 0;
        this->max_size = max_size;
        this->name = name;
    }
    void clear() {
        for (int i = 0; i < max_size; i++) {
            container[i] = false;
        }
    }
    void copy(MySet*& set) {
        container = new bool[max_size];
        for (int i = 0; i < max_size; i++) {
            this->container[i] = set->container[i];
        }
        this->size = set->size;
    }
    ~MySet() {
        if (container != nullptr) {
            delete[] this->container;
        }
    }
};

class Setcalc {
    int max_size;
    MySet* set_A;
    MySet* set_B;
    MySet* set_C;
    MySet* result;
    MySet* prev_result;
    MySet* zero;
    int left_bound;
    int right_bound;

    int mode;
public:
    Setcalc() {
        set_A = set_B = set_C = result = prev_result = nullptr;
        max_size = 0;
        mode = CALC_MODE;
        console_define_bounds();
        zero = new MySet(0, "zero");
    }
    //operations
    void Union(MySet*&, MySet*&);
    void Intersection(MySet*&, MySet*&);
    void Difference(MySet*&, MySet*&);
    void Symmetrical_difference(MySet*&, MySet*&);
    void Complement(MySet*&);
    // console methods
    void console_define_bounds();

    void console_input_set(MySet*&);
    void input_set_random(MySet*&, int); // set, size
    void console_input_set_manual(MySet*&, int);
    void console_input_set_condition(MySet*&, int);

    void console_output_set(MySet*&);
    void console_calc();
    void console_help_note();
    MySet*& get_set_from_char(char);
    void loop();
    ~Setcalc() {
        set_A->~MySet();
        set_B->~MySet();
        set_C->~MySet();
        result->~MySet();
        prev_result->~MySet();
    }
};

// operations
void Setcalc::Union(MySet*& set_a, MySet*& set_b) {
    for (int i = 0; i < max_size; i++) {
        if (set_a->container[i] == true || set_b->container[i] == true) {
            result->container[i] = true;
        }
        else {
            result->container[i] = false;
        }
    }
}
void Setcalc::Difference(MySet*& set_a, MySet*& set_b) {
    for (int i = 0; i < max_size; i++) {
        if (set_a->container[i] == true && set_b->container[i] != true) {
            result->container[i] = true;
        }
        else {
            result->container[i] = false;
        }
    }
}
void Setcalc::Intersection(MySet*& set_a, MySet*& set_b) {
    for (int i =0; i < max_size; i++) {
        if (set_a->container[i] == true && set_b->container[i] == true) {
            result->container[i] = true;
        }
        else {
            result->container[i] = false;
        }
    }
}
void Setcalc::Symmetrical_difference(MySet*& set_a, MySet*& set_b) {
    Union(set_a, set_b);
    MySet* tmp1 = new MySet(max_size, "");
    tmp1->copy(result);
    Intersection(set_a, set_b);
    MySet* tmp2 = new MySet(max_size, "");
    tmp2->copy(result);
    Difference(tmp1, tmp2);
    delete tmp1;
    delete tmp2;
}
void Setcalc::Complement(MySet*& set) {
    for (int i = 0; i < max_size; i++) {
        result->container[i] = !(set->container[i] == true);
    }
}
void Setcalc::console_define_bounds() {
    cout << "Enter bounds of universe" << endl;
    cin >> left_bound >> right_bound;
    while (!(left_bound >= LEFT_BOUND &&  right_bound <= RIGHT_BOUND) || left_bound == right_bound) {
        cout << "Try again, bound must be in [-200, 200]" << endl;
        cin >> left_bound >> right_bound;
    }
    
    max_size = right_bound - left_bound + 1;
    set_A = new MySet(max_size, "A");
    set_B = new MySet(max_size, "B");
    result = new MySet(max_size, "C");
    prev_result = new MySet(max_size, "D");
        
}
void Setcalc::console_input_set(MySet*& set) {
    cout << "Enter amount of elements, which will be in the set" << endl;
    int size;
    cin >> size;
    while (size > max_size) {
        cout << "Write another size. Size must be in ["<< left_bound << ", " << right_bound << "]" << endl;
        cin >> size;
    }
    cout << "Enter way of how you want to fill the set" << endl;
    cout << "1.Manually 2.Randomly 3.Randomly with condition" << endl;
    int way;
    cin >> way;
    while (way != 1 && way != 2 && way != 3) {
        cout << "Choose correct answer" << endl;
        cin >> way;
    }
    switch (way) {
        case 1:
            console_input_set_manual(set, size);
            break;
        case 2:
            input_set_random(set, size);
            break;
        case 3:
            console_input_set_condition(set, size);
            break;
    }
}
void Setcalc::console_input_set_manual(MySet*& set, int size) {
    set->clear();
    
    int i = 0;
    int elem;
    while (i < size) {
        cin >> elem;
        if (set->container[elem-left_bound] == false && (elem >= left_bound && elem <= right_bound)) {
            set->container[elem-left_bound] = true;
            set->size++;
            i++;
        }
        else {
            if (set->container[elem-left_bound] && (elem >= left_bound && elem <= right_bound)) {cout << "Element " <<  elem << "has already been added" << endl;}
            if (!(elem >= left_bound && elem <= right_bound)) {cout << "Element "<< elem << "is not in bounds" << endl;}
            cout << "Try again" << endl;
        }
    }
}
void Setcalc::input_set_random(MySet*& set, int size) {
    set->clear();
    int elem;
    int i = 0;
    while (i < size) {
        elem = rand() % (max_size);
        if (set->container[elem] == false) {
            set->container[elem] = true;
            set->size++;
            i++;
        }
    }
}
void Setcalc::console_input_set_condition(MySet*& set, int size) {
    set->clear();

    int is_positive, is_negative;

    cout << "Can the set have positive values? If yes, then write - 1, else - 0" << endl;
    cin >> is_positive;
    while (is_positive != 0 && is_positive != 1) {
        cout << "Wrong value. It's must be 1 or 0" << endl;
        cin >> is_positive;
    }

    cout << "Can the set have negative values? If yes, then write - 1, else - 0" << endl;
    cin >> is_negative;
    while (is_negative != 0 && is_negative != 1) {
        cout << "Wrong value. It's must be 1 or 0" << endl;
        cin >> is_negative;
    }
    int n; // divisor
    int b;
    cout << "Because definition even/edd and also becouse division on some divisor must be this parameters:" << endl;
    cout << "Enter the greatest number, which division will be in needed condition" << endl;
    cout << "Enter 1, if there no division condition, enter 2 if you really needed in even/odd confition" << endl;
    cin >> n;
    while (n < 1) {
        cout << "Divisor can't be less than 1" << endl;
        cin >> n;
    }
    cout << "Enter remainder of division on written number" << endl;
    cout << "Even numbers, when divided on 2 gives 2, odd - 1" << endl;
    cout << "Number can be divided, if the remainder equal 0" << endl;
    cin >> b;
    while (b < 0 || b>=n) {
        cout << "Remainder from division can't be less than 0 or greater than divisor" << endl;
        cin >> b;
    }
    int new_max;
    for (int i = left_bound; i < right_bound + 1; i++) {
        if ((i % n == b) && ((i > 0 && is_positive==1)||(i < 0 && is_negative==1)||(i==0))) {
            new_max++;
        }
    }
    while (size>new_max){
        cout << "Set size greater than the greatest avialiable size of the set" << endl;
        cin >> size;
    }

    int elem;
    int i = 0;
    while (i < size) {
        elem = rand() % (max_size) + left_bound;
        if (!(set->container[elem-left_bound] == true) && (elem % n == b) && ((elem > 0 && is_positive)||(elem<0 && is_negative)||(elem==0))) {
            set->container[elem-left_bound] = true;
            set->size++;
            i++;
        }
    }
}
void Setcalc::console_output_set(MySet*& set) {
    cout << set->name << " ";
    cout << "[ ";
    for (int i = 0; i < max_size; i++) {
        if (set->container[i] == true)
            cout << i+left_bound << " ";
    }
    cout << "]" << endl;
}
MySet*& Setcalc::get_set_from_char(char setname) {
    switch (setname) {
        case 'A':
        case 'a':
            return set_A;
        case 'B':
        case 'b':
            return set_B;
        case 'C':
        case 'c':
            return result;
        case 'D':
        case 'd':
            return prev_result;
        default:
            return zero;
    }
}
void Setcalc::console_help_note() {
    cout << "__________________Set Calculator___________________" << endl;
    cout << "Basics:" << endl;
    cout << "-Firstly there are 4 sets to work with: A, B, C, D" << endl;
    cout << "-Sets A and B needed to do operations, when C - result set(every operation will be saved as it), D - store previous result " << endl;
    cout << endl;
    cout << "-To do input write A=(name and equal sign)" << endl;
    cout << "-Type A, B, C, D to get output of the set" << endl;
    cout << endl;
    cout << "-Type some of this operations A+B(Union), A*B(intersection), A^B(Symmetrical_difference), A-B(difference),~A(Complement) " << endl;
    cout << "to get the result of the operations in set C" << endl;
    cout << "-Enter this operations WITHOUT spaces, it won't work, if you do it that way" << endl;
    cout << endl;
    cout << "Type help to get this note again" << endl;
    cout << "Type bounds to change the bounds of universe" << endl;
    cout << "Type q to quit the program" << endl << endl;
    
}
void Setcalc::console_calc() {
    cout << ">";
    string str;

    string sets = "ABCDabcd";
    //string operations = "+-*^";
    cin >> str;
    if (str == "bounds") {
        console_define_bounds();
        return;
    }
    if (str == "help") {
        console_help_note();
    }
    if (str.length() == 1) {
        if (str[0] == 'q') {
            mode = EXIT_MODE;
            return;
        }
        if (find(sets.begin(), sets.end(), str[0]) != sets.end()) {
            console_output_set(get_set_from_char(str[0]));
            return;    
        }
    }
    if (str.length() == 2 && find(sets.begin(), sets.end(), str[1]) != sets.end() && str[0] == '~') {
        Complement(get_set_from_char(str[1]));
        cout << "Result:" << endl;
        console_output_set(result);
        return;
    }
    
    if (str.length() == 3) {
        switch (str[1]) {
            case '+':
                prev_result->copy(result); 
                Union(get_set_from_char(str[0]), get_set_from_char(str[2]));
                cout << "Result:" << endl;
                console_output_set(result);
                break;
            case '-':
                prev_result->copy(result); 
                Difference(get_set_from_char(str[0]), get_set_from_char(str[2]));
                cout << "Result:" << endl;
                console_output_set(result);
                break;
            case '^':
                prev_result->copy(result); 
                Symmetrical_difference(get_set_from_char(str[0]), get_set_from_char(str[2]));
                cout << "Result:" << endl;
                console_output_set(result);
                break;
            case '*':
                prev_result->copy(result); 
                Intersection(get_set_from_char(str[0]), get_set_from_char(str[2]));
                cout << "Result:" << endl;
                console_output_set(result);
                break;
            case '=': { // a = b 
                MySet* set_a = get_set_from_char(str[0]);
                MySet* set_b = get_set_from_char(str[2]);
                set_a->copy(set_b);
                cout << "Now "<< set_a->name << " equal " << set_b->name << endl;
                break;
            }
            default:
                cout << "Write right operation" << endl;
                break;
        }
    }
    if (str.length() == 2 && find(sets.begin(), sets.end(), str[0]) != sets.end() && str[1] == '=') {
        console_input_set(get_set_from_char(str[0]));
    }
    else if (str[1] == '=' && str.length() == 2 && (find(sets.begin(), sets.end(), str[0]) == sets.end() || str.length() == 2 && find(sets.begin(), sets.end(), str[2]) == sets.end())) {
        cout << "Write name of right set " << endl;
    }
}
void Setcalc::loop() {
    console_help_note();
    do 
        console_calc();
    while (mode == CALC_MODE);
}

int main(int argc, char* argv[]) {
    srand(time(NULL));
    Setcalc calc;
    calc.loop();
    return 0;
}
