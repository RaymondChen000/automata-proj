#include "M.h"
#include <iomanip>
#include <iostream>
#include <vector>

using namespace std;

// Enumerated states are converted to strings for table output 
string stateToString(State s) {
    switch(s) {
        case P: return "p";         // Start State
        case Q: return "q";         // Look-ahead State
        case QA: return "qa";       // 'a' Processor State 
        case QB: return "qb";       // 'b' Processor State 
        case Q_FINAL: return "q$";  // Accept State
        default: return "ERROR"; // Reject state 
    }
}
// Constructor function 
M::M(string inputString) {
    currentState = P; // Always start at state P
    stackContent = ""; // Always start with an empty stack 
    input = inputString; // User inputString gets copied into input variable
    
    inputIndex = 0; // Index counter initialized to 0
    stepCount = 0;  // Counter initalized to 0 
}
// Helper function that returns unread string text
string M::getUnreadInput() {
    if (inputIndex >= input.length()) return "";
    return input.substr(inputIndex);
}
// Helper function that checks stack
char M::getStackTop() {
    if (stackContent.empty()) { // Checks stack if its empty 
        return 'e'; 
    }
    return stackContent.back(); // If not empty, it returns the top character
}
// Outputs each step the machine takes onto screen. Also checks for empty stack.
void M::logStep(int ruleNum, string ruleDesc) {
    string stackDisplay = stackContent; // Copies stack content into variable
    
    if (stackDisplay == "") {
        stackDisplay = "e"; // If stack content was empty print e 
    } 
    
    // Prints row for table 
    cout << left << setw(5) << stepCount             // Prints step currently at 
         << left << setw(8) << stateToString(currentState) // Prints state currently at 
         << left << setw(15) << getUnreadInput()          // Prints the currently unread string text 
         << left << setw(15) << stackDisplay         // Prints current stack content 
         << left << setw(8) << ruleNum               // Prints transition rule 
         << ruleDesc << endl;                        
}
// Main program 
void M::run() {
    // Prints table header
    cout << "\n" << left << setw(5) << "Step" 
    << left << setw(8) << "State" 
    << left << setw(15) << "Unread" 
    << left << setw(15) << "Stack" 
    << left << setw(8) << "T rule" 
    << "R rule used" << endl;
    cout << "----------------------------------------------------------------" << endl;

    bool running = true; 

    while (running) { 

        char nextChar = ' '; if (inputIndex < input.length()) nextChar = input[inputIndex]; // next character look ahead

        char stackTop = getStackTop(); 

        // We always start at P, then state goes to Q, and then push the Start Symbol 'S' onto the stack (trans rule 1)
        if (currentState == P) {
            logStep(1, "");
            currentState = Q; // moves to state q
            stackContent.push_back('S'); // S gets pushed onto the stack 
            stepCount++; // move from step 0 (init at 0 earlier) to step 1
        
            continue;
        }

        // LOOK AHEAD STATE Q
        // it either recieves an 'a' or a 'b' and decides to move from there
            
        if (currentState == Q) {
        
            // ---READS A--- recieves a 'a' as input, moves to state qa to process 
            if (nextChar == 'a') {
                logStep(2, "");
                currentState = QA; // moves to state qa
            
                inputIndex++; // index counter moves forward after reading the 'a' 
                stepCount++;
            
                continue;
            }
        
            // ---READS B--- recieves a 'b' as input, moves to state qb to process 
            else if (nextChar == 'b') {
                logStep(4, "");
                currentState = QB; // moves to state q 
            
                inputIndex++; // index counter moves forward after reading the 'b'
                stepCount++;
            
                continue;
            }
        
            // ---READS $--- recieves a '$' as input, so user string is accepted 
            else if (nextChar == '$') {
                logStep(6, "");
                currentState = Q_FINAL; // moves -> Q_FINAL, which is the accept state 
            
                stepCount++;
                
                // DISPLAYS THAT STRING WAS ACCEPTED 
                string finalOutput;
                if (stackContent.empty()) {
                    finalOutput = "e";
                } else {
                    finalOutput = stackContent;
                }

                cout << left << setw(5) << stepCount 
                     << left << setw(8) << stateToString(currentState) 
                     << left << setw(15) << "" 
                     << left << setw(15) << finalOutput 
                     << "ACCEPTED" << endl;
                return;
            }
        }

        // PROCESSING STATES QA and QB
        
        // ---PROCESSING STATE QA--- 
        // balancing; an 'a' was read so a 'b' must be pushed 
        if (currentState == QA) {
 
            if (stackTop == 'S') { // top of stack is S from the earlier look-ahead state
                logStep(7, "S -> aSb");
                stackContent.pop_back(); // Pops S from the stack 
                
                // S-> aSb  Push in reverse for 'a' to end up on TOP (bc of liFo principle)
                stackContent.push_back('b'); // bottom 
                stackContent.push_back('S'); // mid
                stackContent.push_back('a'); // topmost
                
                stepCount++;
            
                continue;
            }
            
            else if (stackTop == 'a') {
                logStep(3, "");
                stackContent.pop_back(); // Pop 'a'
                
                currentState = Q;        // Go back to Q to look for next input
                stepCount++;
                
                continue;
            }
        }

        // ---PROCESSING STATE QB---
        // now if a 'b' is read we just pop 'b' from the stack 
        if (currentState == QB) {
            
            // trans rule 8 is just cleanup and sets the stage for rule 5, get rid of the S from the top of stack  
            if (stackTop == 'S') { // top of stack is S from the earlier look-ahead state 
                logStep(8, "S -> e");
                stackContent.pop_back(); // Pop S
            
                stepCount++;
            
                continue;
            }
            
            // trans rule 5; pops the b from the stack
            else if (stackTop == 'b') { 
                logStep(5, "");
                stackContent.pop_back(); // pops 'b' from top of stack 
                currentState = Q; // goes back to the look-ahead state Q 
                
                stepCount++;
            
            continue;
            }
        }
    
    currentState = REJECT;
        cout << "------------------------------------------------------------------" << endl;
        cout << "String has been rejected and is not a part of the language\n";
        running = false;
    }
}