#include <iostream>
#include <stack>
#include <string>
using namespace std;

// States
enum class State { Q0, Q1, Q_FINAL };

class PDA{
    public:
        //create the pda obj
        PDA() {
            currentState = State::Q0;
            stack.push('Z'); 

        }
    private:
        State currentState;
        std::stack<char> stack;
};


int main() { 
    return 0;
}