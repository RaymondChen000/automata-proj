#include <iostream>
#include <map>
#include <set>
#include <stack>
#include <string>
#include <vector>
using namespace std;

// States
enum class State { Q0, Q1, Q_FINAL };

// Alphabets
std::set<char> inputAlphabet;
std::set<char> stackAlphabet;

// Transition Rule
struct Transition {
    State nextState;
    std::string stackOperation;  // like when you pop 1, then push 'A'
};

class PDA{
    public:

    private:

};


int main() { 
    return 0;
}