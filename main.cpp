#include <iostream>
#include <string>
#include <vector>
#include <iomanip>
#include "M.h"

using namespace std;

int main() {
    string userString;
    
    cout << "--- DPDA for L = { a^n b^n } ---\n";
    cout << "Write 'exit' to end the program\n";

    while (true) {
        cout << "\nEnter string to check: ";
        cin >> userString;

        // USER WANTS TO EXIT THE PROGRAM 
        if (userString == "exit" || userString == "quit") {
                cout << "Exiting\n";
                break;
        }

        // APPENDS $
        // All inputted strings must have a $ appended for the machine to know its reached the end of input 
        if (userString.empty() || userString.back() != '$') {
            userString += "$";
        }

        // Loaads string into machine 
        M automaton(userString);
        // RUNS PROGRAM 
        automaton.run();
    }

    return 0;
}