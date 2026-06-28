#include<iostream>

extern "C" {
    
int ws_handler() {
    std::cout << "POSEIDON desde C++\n";
    return 0;
}

}