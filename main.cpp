#include <iostream>
#include "SkipSet.h"
#include <set>
using namespace std;

class Car {
public:
    string name;
    int value;

    bool operator==(Car const& c) const
    {
        return name == c.name;
    }
    bool operator!=(Car const& rhs) const
    {
        return !(this->operator==(rhs));
    }


    friend std::ostream & operator<<(std::ostream &os, const Car &c) {
        os << c.name;
        return os;
    }


    friend bool operator < ( Car const& a, Car const& b) {
        return a.name < b.name;
    };
};

typedef std::chrono::high_resolution_clock Clock;

int main() {


    long count = 100000000;

    int i = 0;

    auto t1 = Clock::now();
    SkipSet<int> ss;

    while(i < count) {

        ss.insert(i);
        i++;
    }

    auto t2 = Clock::now();

    std::cout << "SkipSet: " << std::chrono::duration_cast<std::chrono::milliseconds>(t2 - t1).count() <<  " Millisekunden" << std::endl;

    auto t3 = Clock::now();
    std::set<int> standard_s;
    i = 0;
    while(i < count) {
        standard_s.emplace(i);
        i++;
    }
    auto t4 = Clock::now();

    std::cout << "STL Set: " << std::chrono::duration_cast<std::chrono::milliseconds>(t4 - t3).count() <<  " Millisekunden" << std::endl;





    /*
    SkipSet<int> ss;
    int i = 1;
    while(i < 10) {
        ss.insert(i);
        i++;
    }



    auto it = ss.begin();

    while(it != ss.end()) {
        ss.print();
    }


    SkipSet<Car> ss;
    Car c1;
    c1.name = "Opel";
    c1.value = 1;
    Car c2;
    c2.name = "Audi";
    c2.value = 1;
    Car c3;
    c3.name = "Mercedes";
    c3.value = 1;
    ss.insert(c1);
    ss.insert(c2);
    ss.insert(c3);
    ss.print();

     */

    return 0;
}

