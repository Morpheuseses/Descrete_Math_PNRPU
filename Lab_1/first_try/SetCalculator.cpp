#include "SetCalculator.h"


MySet SetCalculator::Union(MySet set_A, MySet set_B) {

    MySet set_result = MySet(0, set_A.max_size);

    for (int i = 0; i < set_A.max_size; i++) {
        if (set_A.container[i] || set_B.container[i]) {
            set_result.container[i] = true;
            set_result.size++;    
        }
    }
    return set_result;
}

MySet SetCalculator::Intersect(MySet set_A, MySet set_B) {

    MySet set_result = MySet(0, set_A.max_size);

    for (int i = 0; i < set_A.max_size; i++) {
        if (set_A.container[i] && set_B.container[i]) {
            set_result.container[i] = true;
            set_result.size++;    
        }
    }
    return set_result;
}

MySet SetCalculator::Difference(MySet set_A, MySet set_B) {

    MySet set_result = MySet(0, set_A.max_size);

    for (int i = 0; i < set_A.max_size; i++) {
        if (set_A.container[i] && !(set_B.container[i])) {
            set_result.container[i] = true;
            set_result.size++;    
        }
    }
    return set_result;
}

MySet SetCalculator::Symmetrical_difference(MySet set_A, MySet set_B) {

    MySet set_result = MySet(0, set_A.max_size);

    MySet Union_AB = Union(set_A, set_B);
    MySet Intersect_AB = Intersect(set_A, set_B);

    return Difference(Union_AB, Intersect_AB);
}

MySet SetCalculator::Addition(MySet set_A) {
    MySet set_result = MySet(set_A.max_size, set_A.max_size);

    for (int i = 0; i < set_A.max_size; i++) {
        if (set_A.container[i]) {
            set_result.container[i] = false;
        }
        else {
            set_result.container[i] = true;
        }
    }
    return set_result;
}

void SetCalculator::console_define_bounds() {
    cout << "Enter bounds of universe: " << endl;
    cin >> local_left_bound >> local_right_bound;

    while (local_left_bound < LEFT_BOUND || local_right_bound > RIGHT_BOUND 
                                || local_right_bound < local_left_bound) {
        cout << "Enter bounds again(left bound < right bound, global universe = [-200,200]):" << endl;
        cin >> local_left_bound >> local_right_bound;
    }

    set_A = MySet(0, local_right_bound - local_left_bound + 1);
    set_B = MySet(0, local_right_bound - local_left_bound + 1);
    set_result = MySet(0, local_right_bound - local_left_bound + 1);
    prev_result = MySet(0, local_right_bound - local_left_bound + 1);

    zero = MySet(-1,-1);
}

void SetCalculator::console_input_set(MySet& set, int size) {
    cout << "How you want to fill the set?" << endl;
    cout << "1.Manual, 2.Random, 3.Condition" << endl;
    int choice;
    cin >> choice;
    switch (choice) {
        case 1:
            console_input_values_manual(set, size);
            break;
        case 2:
            console_input_values_random(set, size);
            break;
        case 3:
            console_input_values_condition(set, size);
            break;
        default:
            cout << "Try, again" << endl;
    }
}

void SetCalculator::console_input_values_manual(MySet& set, int size) {
    int i = 0; // counter
    int elem;
    while (i < size) {
        cin >> elem;
        if (!set.container[elem-local_left_bound] && (elem >= local_left_bound && elem <= local_right_bound)) {
            i++;
            set.size++;
        }
        else {
            cout << "Try another value";
            if (set.container[elem-local_left_bound]) cout << "Element " << elem << " have already put" << endl;
            if (!(elem >= local_left_bound && elem <= local_right_bound)) cout << "Element " << elem << " out of local universe" << endl;
        }
    }
}

void SetCalculator::console_input_values_random(MySet& set, int size) {
    int i = 0;
    int elem;
    while (i < size) {
        elem = rand() % (local_right_bound - local_left_bound + 1);
        if (!set.container[elem-local_left_bound] && (elem >= local_left_bound && elem <= local_right_bound)) {
            i++;
            set.size++;
        }
    }
}
// don't know how to do it, should do it later
void SetCalculator::console_input_values_condition(MySet& set, int size) {
    int i = 0;
    int elem;
    while (i < size) {
        elem = rand() % (local_right_bound - local_left_bound + 1);
        if (!set.container[elem-local_left_bound] && (elem >= local_left_bound && elem <= local_right_bound)) {
            i++;
            set.size++;
        }
    }
}

void SetCalculator::console_output_set(MySet set) {
    if (set.size = -1) {
        cout << "Can't write the set" << endl;
        return;
    }
    cout << endl;
    cout << "[";
    for (int i = 0; i < set.max_size-1; i++) {
        if (set.container[i]) {
            cout << i + local_left_bound << ", ";
        }
    }
    cout << set.container[set.max_size-1] << "]" << endl;
}

MySet& SetCalculator::get_set_from_char(char setname) {
    switch (setname) {
        case 'A':
            return set_A;
        case 'B':
            return set_B;
        case 'C':
            return set_result;
        case 'D':
            return prev_result;
        default:
            cout << "Can't recognize set" << endl;
            return zero;
    }
}

void SetCalculator::console_input_calc() {
    cout << ">";
    string str;
    char operation;
    if (str.length() == 1 && str[0] != 'q') {
        console_output_set(get_set_from_char(str[0]));
        return;
    }
    else if (str[0] == 'q') {
        mode = EXIT_MODE;
        return;
    }
    if (str.length() == 2 && '~') {
        prev_result = set_result;
        set_result = Addition(get_set_from_char(str[1]));
        cout << "Addition result:" << endl;
        console_output_set(set_result);
        return;
    }
    string sets = "ABCD";
    string operations = "-+*^";
    operation = str[1];
    if (str.length() == 3 &&  find(operations.begin(), operations.end(), str[1]) != operations.end()
                && (find(sets.begin(), sets.end(), str[0]) != sets.end())) {
        switch (operation) {
            case '+':
                prev_result = set_result;
                set_result  = Union(get_set_from_char(str[0]),get_set_from_char(str[2]));
                cout << "Union result:" << endl;
                console_output_set(set_result);
                break;
            case '*':
                prev_result = set_result;
                set_result = Intersect(get_set_from_char(str[0]),get_set_from_char(str[2]));
                cout << "Intersect result:" << endl;
                console_output_set(set_result);
                break;
            case '-':
                prev_result = set_result;
                set_result = Difference(get_set_from_char(str[0]), get_set_from_char(str[2]));
                cout << "Difference result:" << endl;
                console_output_set(set_result);
                break;
            case '^':
                prev_result = set_result;
                set_result = Symmetrical_difference(get_set_from_char(str[0]), get_set_from_char(str[2]));
                cout << "Symmetrical difference result:" << endl;
                console_output_set(set_result);
                break;
            default:
                cout << "Try Again. How you get here?";
                break;
        }
    }
    else {
        cout << "You wrote something wrong, try again" << endl;
    }
}

void SetCalculator::doWork() {
    console_define_bounds();
    do {
        console_input_calc();
    }
    while (mode != EXIT_MODE);
}