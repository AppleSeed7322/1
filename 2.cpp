#include <iostream>
#include <string>
#include <cctype>
#include <algorithm>
#include <sstream>
#include <vector>
using namespace std;

struct Node {
    string data;
    Node* next;
};

class Stack {
private:
    Node* top;
public:
    Stack() { top = nullptr; }
    void push(const string& value) {
        Node* newNode = new Node;
        newNode->data = value;
        newNode->next = top;
        top = newNode;
    }
    string pop() {
        if (isEmpty()) return "";
        Node* temp = top;
        string value = temp->data;
        top = top->next;
        delete temp;
        return value;
    }
    string peek() { return isEmpty() ? "" : top->data; }
    bool isEmpty() { return top == nullptr; }
};

int precedence(const string& op) {
    if (op == "^") return 3;
    if (op == "*" || op == "/") return 2;
    if (op == "+" || op == "-") return 1;
    return 0;
}

bool isRightAssociative(const string& op) {
    return op == "^";
}

bool isOperator(const string& token) {
    return token == "+" || token == "-" || token == "*" || token == "/" || token == "^";
}

vector<string> tokenize(const string& expr) {
    vector<string> tokens;
    string temp = "";
    for (char ch : expr) {
        if (isspace(ch)) continue;
        if (isalnum(ch)) temp += ch;
        else {
            if (!temp.empty()) {
                tokens.push_back(temp);
                temp = "";
            }
            tokens.push_back(string(1, ch));
        }
    }
    if (!temp.empty()) tokens.push_back(temp);
    return tokens;
}

string infixToPostfix(const string& infix, bool& valid) {
    Stack s;
    string postfix = "";
    vector<string> tokens = tokenize(infix);
    valid = true;

    for (const string& token : tokens) {
        if (isalnum(token[0])) {
            postfix += token + " ";
        } else if (token == "(") {
            s.push(token);
        } else if (token == ")") {
            bool found = false;
            while (!s.isEmpty()) {
                string topToken = s.pop();
                if (topToken == "(") { found = true; break; }
                postfix += topToken + " ";
            }
            if (!found) { valid = false; return "Error: Unmatched parentheses."; }
        } else if (isOperator(token)) {
            while (!s.isEmpty() && isOperator(s.peek())) {
                string topOp = s.peek();
                int prec1 = precedence(topOp);
                int prec2 = precedence(token);
                if ((prec1 > prec2) || (prec1 == prec2 && !isRightAssociative(token))) {
                    postfix += s.pop() + " ";
                } else break;
            }
            s.push(token);
        } else {
            valid = false;
            return "Error: Invalid character in expression.";
        }
    }

    while (!s.isEmpty()) {
        if (s.peek() == "(" || s.peek() == ")") { valid = false; return "Error: Unmatched parentheses."; }
        postfix += s.pop() + " ";
    }

    if (!postfix.empty() && postfix.back() == ' ') postfix.pop_back();
    return postfix;
}

string infixToPrefix(const string& infix, bool& valid) {
    string reversed = infix;
    reverse(reversed.begin(), reversed.end());
    for (char &ch : reversed) {
        if (ch == '(') ch = ')';
        else if (ch == ')') ch = '(';
    }

    string postfix = infixToPostfix(reversed, valid);
    if (!valid) return postfix;

    istringstream iss(postfix);
    vector<string> tokens;
    string token;
    while (iss >> token) tokens.push_back(token);
    reverse(tokens.begin(), tokens.end());

    string prefix = "";
    for (const string& t : tokens) prefix += t + " ";
    if (!prefix.empty()) prefix.pop_back();
    return prefix;
}

int main() {
    string infix;
    cout << "Enter Infix Expression: ";
    getline(cin, infix);

    bool validPostfix, validPrefix;
    string postfix = infixToPostfix(infix, validPostfix);
    string prefix = infixToPrefix(infix, validPrefix);

    cout << "Postfix: " << postfix << endl;
    cout << "Prefix: " << prefix << endl;
    return 0;
}
