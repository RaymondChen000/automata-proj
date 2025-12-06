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

            if (currentState == State::Q1 && stack.top() == 'Z'){
                currentState == State::Q_FINAL;
                return true;
            }
            
            return false;
        }

    private:
        State currentState;
        std::stack<char> stack;

        bool step(char c){
            if (stack.empty()){
                return false;
            }

            char top = stack.top();
            //for reading a's
            if (currentState == State::Q0){
                if (c== 'A'){
                    if (top == 'Z' || top == 'A'){
                        stack.push('A');
                        return true;
                    }
                }
                if (c=='B'){
                    if (top == 'A'){
                        stack.pop();
                        //means its time to start reading b
                        currentState = State::Q1;
                        return true;
                    }
                }
            }
            
            //for reading b's
            if (currentState == State::Q1){
                if(c=='B'){
                    if(top=='A'){
                        stack.pop();
                        return true;
                    }
                }
            }

            return false;
        }
};


int main() { 
    PDA pda;
    std::string input;
    std::cout << "Enter a string of 'A's and 'B's: ";
    std::cin >> input;

    if(pda.valid(input)){
        std::cout << "Accepted";
    }
    else{
        std::cout << "Rejected";
    }

    return 0;
}