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
            //table header
            cout << "Step\tUnread Input\tTop of Stack\tState\n";
            cout << "---------------------------------------------\n";
            //first row
            cout << 0 << "\t" << s << "\t\t" << stack.top() << "\t\t" << getState() << "\n";

            //process each char in the string
            //for i is 0 to size of string, get each char at string[i] and call step function. Then get the unread string and print the table row for this step
            for(int i = 0; i<s.size(); i++){
                    char c = s[i];
                    if (step(c) == false){
                        return false;
                    }

                    //get remaining string now that we took char at i to the stack
                    string unread;
                    if(i+1 < s.size()){
                        unread = s.substr(i+1);  //unread is from current char+1 to end
                    }
                    else{
                        unread = ""; //nothing left
                    }
                    cout << i+1 << "\t" << unread << "\t\t" << stack.top() << "\t\t" << getState() << "\n";
            }

            //Q0 state is empty str, Q1 state is after reading all b and stack back to only z
            if ((currentState == State::Q1 || currentState == State::Q0) && stack.top() == 'Z'){
                currentState == State::Q_FINAL;
                return true;
            }
            
            return false;
        }

    private:
        State currentState;
        std::stack<char> stack;

        //get current state as string
        string getState() const{
            switch(currentState){
                case State::Q0:
                    return "Q0";
                case State::Q1:
                    return "Q1";
                case State::Q_FINAL:
                    return "Q_FINAL";
            }
            //return unknown state
            return "?";
        }

        //process one step of the pda, return true if valid transition, false if not
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