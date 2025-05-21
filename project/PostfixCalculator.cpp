#include <iostream>
#include <stack>
#include <vector>
#include <string>
#include <sstream>
#include <cctype>
#include <stdexcept>

class ExpressionParser {
private:
    int precedence(const std::string& op){
        if (op == "+" || op == "-") return 1;
        if (op == "*" || op == "/") return 2;
        return 0;
    }

    bool isOperator(const std::string& token){
        return token == "+" || token == "-" || token == "*" || token == "/";
    }
public:
    std::vector<std::string> tokenize(const std::string& expression){
        std::vector<std::string> tokens;
        std::string number;
        bool expectUnary = true;

        for(char ch : expression){
            if (std::isdigit(ch) || ch =='.') {
                number+= ch;
                expectUnary = false;
            }
            else{
                if (!number.empty())
                {
                    tokens.push_back(number);
                    number.clear();
                }

                if (ch == ' ') continue;

                if (ch == '-' && expectUnary){
                    number += ch;
                } else{
                    tokens.push_back(std::string(1,ch));
                    expectUnary = true;
                }
                
            }
        }
        return tokens;
    }
    std::vector<std::string> toPostfix(const std::vector<std::string>& tokens){
        std::vector<std::string> output;
        std::stack<std::string> opStack;
        for (const std::string& token : tokens){
            if(std::isdigit(token[0]) || (token.size() > 1 && std::isdigit(token[1]))) {
                output.push_back(token);
            } else if (isOperator(token)){
                while(!opStack.empty() && isOperator(opStack.top()) && precedence(opStack.top()) >= precedence(token)) {
                    output.push_back(opStack.top());
                    opStack.pop();
                }
                opStack.push(token);
            } else if (token == "(") {
                opStack.push(token);
            } else if (token == ")") {
                while(!opStack.empty() && opStack.top() != "(") {
                    output.push_back(opStack.top());
                    opStack.pop();
                }
                if(opStack.empty()) throw std::runtime_error("Parenthesis mismatch");
                opStack.pop();
            }
        }
        while (!opStack.empty()) {
            if (opStack.top() == "(") throw std::runtime_error("Parenthesis mismatch");
            output.push_back(opStack.top());
            opStack.pop();
        }
        return output;
    }
};

class CalculationEngine {
public:
    double evaluatePostfix (const std::vector<std::string>& postfix) {
        std::stack<double> Stack;
        
        for(const std::string& token : postfix) {
            if (std::isdigit(token[0]) || (token.size() > 1 && token[0] == '-')) {
                Stack.push(std::stod(token));
            } else {
                if (Stack.size() < 2) throw std::runtime_error("Invalid expression");

                double b = Stack.top(); Stack.pop();
                double a = Stack.top(); Stack.pop();
                double result = 0;

                if (token == "+") result = a + b;
                else if (token == "-") result = a - b;
                else if (token == "*") result = a * b;
                else if (token == "/") {
                    if (b == 0) throw std::runtime_error("Division by zero error");
                    result = a / b;
                } else {
                    throw std::runtime_error("?"+token);
                }

                Stack.push(result);
            }
        }

        if (Stack.size() != 1) throw std::runtime_error("error");

        return Stack.top();
    }
};

class CalculationApp {
public:
    void run() {
        ExpressionParser parser;
        CalculationEngine engine;
        std::string input;

        std::cout<<" PostfixCalculator (type 'exit' to quit):\n";
        
        while(true) {
            std::cout<<"\nEnter expression: ";
            std::getline(std::cin, input);
            if(input == "exit") break;

            try
            {
                auto tokens = parser.tokenize(input);
                auto postfix = parser.toPostfix(tokens);
                double result = engine.evaluatePostfix(postfix);

                std::cout<<"result: "<<result<<" \n";
            } 
            catch(const std::exception& e)
            {
                std::cerr << e.what() << '\n';
            }
        }
    }
};

int main()
{
    CalculationApp app;
    app.run();
    return 0;
}