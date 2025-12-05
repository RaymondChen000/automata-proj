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
            stack.push('Z'); //initial state
        }

        //return true if valid false if not
        bool valid(const std::string& s){   
            //for each char in the input string s
            for(char c : s){
                //check if it is valid so far
                if(step(c) == false){
                    return false;
                }
            }
        }

    private:
        State currentState;
        std::stack<char> stack;

        bool step(char c){
            if (stack.empty()){
                return false;
            }

            char top = stack.top();


        }
};


int main() { 
    return 0;
}