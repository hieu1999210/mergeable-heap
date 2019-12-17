#ifndef data__
#define data__
#include <string>
#include <iostream>
#include <sstream>
class Data {
    public:
        std::string key;
        int value;
        Data (std::string key, int value) {
            this->key = key;
            this->value = value;
        }
        void display() {
            std::cout << "[key: " << key 
                      << ", value: " << value
                      << "]";
        }
        friend std::ostream& operator<<(std::ostream& os, const Data& data) {
            os << "(key: " << data.key 
               << ", value: " << data.value
               << ")";
            return os;
        }
};
#endif