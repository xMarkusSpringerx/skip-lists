class Car {
public:
    string name;
    int value;

    /*
     * Aufruf mit     Event *e = new Event(&test_1, producerTime);
     * */

    Event( void (*called_function)(), int time) {
        timestamp = time;
        function = called_function;
    }


    ~Car() {
        delete ptr;
    }


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

