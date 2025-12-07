#ifndef M_H
#define M_H

#include <string>

using namespace std;

enum State { P, Q, QA, QB, Q_FINAL, REJECT }; // States are enumerated for readbility 

class M {
    State currentState; 
    string stackContent; // We use a string as a stack. The end (back) is the TOP. It starts off as an empty string.
    string input; // Input string 
    int inputIndex; // Current index of the string being analyzed 
    int stepCount; // Current step counter

public:
    M(string inputString);
    string getUnreadInput();
    char getStackTop();
    void logStep(int ruleNum, string ruleDesc);
    void run();
};

#endif