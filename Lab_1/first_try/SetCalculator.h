#pragma once 
#include <string>
#include <iostream>
#include <algorithm>

using std::cout;
using std::cin;
using std::endl;
using std::string;
using std::find;

#define LEFT_BOUND -200
#define RIGHT_BOUND 200

#define CALC_MODE 101
#define EXIT_MODE 100


struct MySet {
    bool* container;
    static int max_size;
    int size;
    MySet();
    MySet(int size, int max_size) {
        this->container = new bool[max_size];
        this->max_size = max_size;
        this->size = size;
    }
    ~MySet() {
        delete container;
    }
};

class SetCalculator {
private:
    int local_left_bound;
    int local_right_bound;
    MySet zero;
    MySet set_A;
    MySet set_B;
    MySet set_result; // C set
    MySet prev_result; // D set

    int mode = CALC_MODE;
    // operations
    MySet  Union                 (MySet, MySet);
    MySet  Intersect             (MySet, MySet);
    MySet  Difference            (MySet, MySet);
    MySet  Symmetrical_difference(MySet, MySet);
    MySet  Addition              (MySet);
public:
    // setup
    void console_define_bounds();
    // set input and output 
    void console_input_set(MySet&, int);
    MySet& get_set_from_char(char);
    // ways of filling sets with values
    void  console_input_values_manual   (MySet&, int); // set, size
    void  console_input_values_random   (MySet&, int); // set, size
    void  console_input_values_condition(MySet&, int); // set, size

    void console_output_set(MySet);
    // input of the query and output of the result
    void console_input_calc();
    // setup and loop
    void doWork();

    ~SetCalculator() {
        set_A.~MySet();
        set_B.~MySet();
        set_result.~MySet();
    }
};