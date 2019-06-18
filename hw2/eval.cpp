//
//  eval.cpp
//  Homework2
//
//  Created by Shreya Chatterjee on 4/29/19.
//  Copyright © 2019 Shreya Chatterjee. All rights reserved.
//

#include <stdio.h>
#include <iostream>
#include <stack>
#include <string>
using namespace std;

int evaluate(string infix, string & postfix, bool & result);
int getPrecedence(char character);
bool isInfixValid(string infix);
string inToPost(string infix, string & postfix);
bool evaluatePost(string & postfix);
string takeSpacesOut (string infix);

int evaluate(string infix, string &postfix, bool& result) {
    // Evaluates a boolean expression
    //   If infix is a syntactically valid infix boolean expression,
    //   then set postfix to the postfix form of that expression, set
    //   result to the value of the expression, and return zero.  If
    //   infix is not a syntactically valid expression, return 1; in
    //   that case, postfix may or may not be changed, but result must
    //   be unchanged.
    
    infix = takeSpacesOut(infix);
    if (isInfixValid(infix) == true) {
        inToPost(infix, postfix);
        result = evaluatePost(postfix);
        return 0;
    }
    else {
        return 1;
    }
}

int getPrecedence (char character) {
    if (character == '!') {
        return 3;
    }
    if (character == '&') {
        return 2;
    }
    if (character == '^') {
        return 1;
    }
    else {
        return -1;
    }
}

string takeSpacesOut (string infix) {
    string newInfix = "";
    for (int i = 0; i < infix.size(); i++) {
        if (infix[i] != ' ') {
            newInfix += infix[i];
        }
    }
    return newInfix;
}

bool isInfixValid (string infix) {
    int leftParen = 0;
    int rightParen = 0;
    
    //not valid if: there are two operators/operands in a row, parentheses number don't match, some random character that's not allowed
    
    for (int i = 0; i < infix.size(); i++) {
        char ch = infix[i];
        
        switch(ch) {
            case 'T':
            case 'F':
                if (infix [i + 1] == 'T' || infix[i + 1] == 'F') {
                    return false; //can't have two operands in a row
                }
                if (infix [i + 1] == '!' || infix[i + 1] == '(') {
                    return false; //can't have these after T/F
                }
                if (infix [i - 1] == ')') {
                    return false;
                }
                break;
            case '!':
                break;
            case '&':
            case '^':
                if (infix[i + 1] == '&' || infix[i + 1] == '^') {
                    return false; //can't have two operators in a row
                }
                if (infix [i - 1] == '!' || infix [i - 1] == '(') {
                    return false;
                }
                break;
            case '(':
                leftParen++;
                if (infix[i + 1] == ')') {
                    return false; //empty parentheses
                }
                break;
            case ')':
                rightParen++;
                break;
            default:
                return false; //no other characters, other than the ones above, are allowed
        }
    }
    
    if (leftParen != rightParen) {
        return false; //parentheses numbers don't match
    }
    if (infix[infix.size() - 1] != 'T' && infix[infix.size() - 1] != 'F' && infix[infix.size() - 1] != ')') {
        return false; //cannot end on a operator
    }
    if (infix[0] != 'T' && infix[0] != 'F' && infix[0] != '(' && infix[0] != '!') {
        return false;
    }
    else {
        return true;
    }
}

string inToPost (string infix, string & postfix) {
    postfix = "";
    stack<char> operatorStack;
    
    for (int i = 0; i < infix.size(); i++) {
        char ch = infix[i];
        
        switch (ch) {
            case 'T':
            case 'F':
                postfix += ch;
                break;
            case '(':
                operatorStack.push(ch);
                break;
            case ')':
                //pop stack until matching '('
                while (operatorStack.top() != '(') {
                    char c = operatorStack.top();
                    postfix += c;
                    operatorStack.pop();
                }
                operatorStack.pop(); //remove the (
                break;
            case '!':
            case '^':
            case '&':
                if (ch == infix[0]) {
                    operatorStack.push(ch);
                    break;
                }
                while (!operatorStack.empty() && getPrecedence(ch) <= getPrecedence(operatorStack.top()) && operatorStack.top() != '(') {
                    postfix += operatorStack.top();
                    operatorStack.pop();
                }
                operatorStack.push(ch);
                break;
        }
    }
    
    while (operatorStack.empty() == false) {
        postfix += operatorStack.top();
        operatorStack.pop();
    }
    return postfix;
}

bool evaluatePost (string & postfix) {
    stack<char> operandStackTwo;
    char result;
    
    for (int i = 0; i < postfix.size(); i++) {
        char ch = postfix[i];
        if (ch == 'T' || ch == 'F') {
            operandStackTwo.push(ch);
        }
        else if (ch == '!') {
            //change the top operand
            if (operandStackTwo.top() == 'T') {
                operandStackTwo.top() = 'F';
            }
            else {
                operandStackTwo.top() = 'T';
            }
        }
        else {  //operator
            
            char operand2 = operandStackTwo.top();
            operandStackTwo.pop();
            char operand1 = operandStackTwo.top();
            operandStackTwo.pop();
            
            //!, ^, &&
            
            if (ch == '&') {
                if (operand1 == 'F' || operand2 == 'F') {
                    result = 'F';
                }
                else {
                    result = 'T';
                }
                operandStackTwo.push(result);
            }
            
            if (ch == '^') {
                if (operand1 == operand2) {
                    result = 'F';
                }
                else {
                    result = 'T';
                }
                operandStackTwo.push(result);
            }
        }
    }
    
    bool resultToReturn;
    if (operandStackTwo.top() == 'T') {
        resultToReturn = true;
    }
    else { //top = F
        resultToReturn = false;
    }
    
    return resultToReturn;
}
