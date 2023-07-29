#include <iostream>
#include <string>
#include "math.h"
using namespace std;

const int MAX_STACK_SIZE = 20;
const float PI = 3.1415925;


int opPriority(char ch) {
    int priority;
    switch(ch) {
    case 's':
        priority = 4;
        break;
    case 'c':
        priority = 4;
        break;
    case 't':
        priority = 4;
        break;
    case 'S':
        priority = 4;
        break;
    case 'C':
        priority = 4;
        break;
    case 'T':
        priority = 4;
        break;
    case 'l':
        priority = 4;
        break;
    case 'L':
        priority = 4;
        break;
    case '*':
        priority = 3;
        break;
    case '/':
        priority = 3;
        break;
    case '+':
        priority = 2;
        break;
    case '-':
        priority = 2;
        break;
    default:
        priority = 1;
        break;

    }
    return priority;
}

bool isNumber(char c)
{
    if ((c >= 48 && c <= 57) || c == '.')
        return true;
    else
        return false;
}

class opStack {
private:
    char* data;
    int top;
public:
    opStack();
    void push(char c);
    char pop();
    char peek();
    bool isEmpty();
    bool isFull();
};
opStack::opStack()
{
    data = new char[MAX_STACK_SIZE];
    top = -1;
}
void opStack::push(char c)
{
    data[++top] = c;
}
char opStack::pop()
{
    return data[top--];
}
char opStack::peek()
{
    return data[top];
}

bool opStack::isEmpty()
{
    return top == -1;
}
bool opStack::isFull()
{
    return top == MAX_STACK_SIZE - 1;
}

class numStack {
private:
    float* data;
    int top;
public:
    numStack();
    void push(float num);
    float pop();
    bool isEmpty();
    bool isFull();
};
numStack::numStack() {
    data = new float[MAX_STACK_SIZE];
    top = -1;
}
void numStack::push(float num)
{
    data[++top] = num;
}
float numStack::pop()
{
    return data[top--];
}

bool numStack::isEmpty()
{
    return top == -1;
}
bool numStack::isFull()
{
    return top == MAX_STACK_SIZE - 1;
}

class Calculator {
private:
    int result;
    char expression[100];
    opStack opstack;
    numStack numstack;
public:
    void doCalculate();
    void postfix(string str);
    float calSqrt(float);
    float calLog(float);
    float calTriFunc(char, float);
    void Conversion(int num, int conversion);
};

void Calculator::postfix(string str)
{
    int i = 0, index = 0;
    char ch;
    while (str[i] != '\0') {
        if (str[i] == ' ')
            i++;
        else if (isNumber(str[i])) {
            while (isNumber(str[i]))
                expression[index++] = str[i++];
            expression[index++] = ' ';
        }
        else if (str[i] == '(') {
            opstack.push(str[i]);
            i++;
        }
        else if (str[i] == ')') {
            ch = opstack.pop();
            while (true) {
                expression[index++] = ch;
                expression[index++] = ' ';
                ch = opstack.pop();
                if (ch != '(')
                    break;
            }
            i++;
        }
        else {
            if (opstack.isEmpty())
                opstack.push(str[i++]);
            else {
                
                while (opPriority(opstack.peek()) >= opPriority(str[i])) {
                    ch = opstack.pop();
                    expression[index++] = ch;
                    expression[index++] = ' ';
                    if (opstack.isEmpty())
                        break;
                }
                opstack.push(str[i]); 
                i++;
            }
        }
    }           
    while (true) {
        ch = opstack.pop();
        expression[index++] = ch;
        expression[index++] = ' ';
        if (opstack.isEmpty())
            break;
    }
    expression[index] = '\0';
}

void Calculator::doCalculate()
{
    int i = 0, index;
    float val, result, num1, num2;
    char ch;
    char tempStr[20];
    while (expression[i] != '\0') {
        if (isNumber(expression[i])) {
            index = 0;
            while (isNumber(expression[i]))
                tempStr[index++] = expression[i++];
            tempStr[index] = '\0';
            val = atof(tempStr);
            numstack.push(val);
        }
        else if (expression[i] == ' ')
            i++;
        else if (expression[i] == 's' || expression[i] == 'S' || expression[i] == 'c' || expression[i] == 'C' || expression[i] == 't' || expression[i] == 'T') {
            result = calTriFunc(expression[i], numstack.pop());
            numstack.push(result);
            i++;
        }
        else if (expression[i] == 'l') {
            result = calLog(numstack.pop());
            numstack.push(result);
            i++;
        }
        else if (expression[i] == 'r') {
            result = calSqrt(numstack.pop());
            numstack.push(result);
            i++;
        }
        else {
            ch = expression[i++];
            num1 = numstack.pop();
            num2 = numstack.pop();
            if (ch == '+')
                result = num2 + num1;
            else if (ch == '-')
                result = num2 - num1;
            else if (ch == '*')
                result = num2 * num1;
            else if (ch == '/')
                result = num2 / num1;
            numstack.push(result);
        }
        i++;
    }           
    cout << "value: " << numstack.pop() << endl;
}
float Calculator::calSqrt(float value) {
    return sqrt(value);
}

float Calculator::calLog(float value) {
    return log10(value);
}

float Calculator::calTriFunc(char c, float val) {
    switch (c) {
    case 's':
        return sin(PI * val / 180);
    case 'c':
        return cos(PI * val / 180);
    case 't':
        return tan(PI * val / 180);
    case 'S':
        return asin(val);
    case 'C':
        return acos(val);
    case 'T':
        return atan(val);
    }
    return 1;
}

void Calculator::Conversion(int num, int converter) {
    int binary[16];
    int i, count = 0;
    switch (converter) {
    case 2: // 2진수
        while (num > 0) {
            binary[count] = num % 2;
            num = num / 2;
            count++;
        }
        binary[count] = '\0';
        cout << "2진수: ";
        for (i = count - 1; i >= 0; i--) {
            cout << binary[i];
        }
        cout << endl;
        break;
    case 8: // 8진수
        cout << std::oct << "8진수: " << num << endl;
        break;
    case 16: // 16진수
        cout << std::hex << "16진수: " << num << endl;
        break;
    default:
        break;
    }
}

int main(void)
{
    string str;
    int num, converter;
    int menu;
    Calculator calculator;
    while (true) {
        cout << " ---------------- 공학용 계산기 ----------------" << endl;
        cout << "메뉴 선택([1] 사칙연산, [2] 진수변환, [3] 프로그램 종료)";
        cin >> menu;
        switch (menu) {
        case 1:
            cout << "  수식 입력: ";
            cin >> str;
            if (str.find("sin") != string::npos) {
                str.replace(str.find("sin"), 3, "s");
            }
            else if (str.find("cos") != string::npos) {
                str.replace(str.find("cos"), 3, "c");
            }
            else if (str.find("tan") != string::npos) {
                str.replace(str.find("tan"), 3, "t");
            }
            else if (str.find("asin") != string::npos) {
                str.replace(str.find("asin"), 4, "S");
            }
            else if (str.find("acos") != string::npos) {
                str.replace(str.find("acos"), 4, "C");
            }
            else if (str.find("atan") != string::npos) {
                str.replace(str.find("atan"), 4, "T");
            }
            else if (str.find("log") != string::npos) {
                str.replace(str.find("log"), 3, "l");
            }
            else if (str.find("root") != string::npos) {
                str.replace(str.find("root"), 4, "r");
            }
            calculator.postfix(str);
            calculator.doCalculate();
            cout << endl;
            break;
        case 2:
            cout << "  숫자 입력: ";
            cin >> num;
            cout << "  변환할 진수 입력(2,8,16): ";
            cin >> converter;
            calculator.Conversion(num, converter);
            cout << endl;
            break;
        case 3:
            break;
        }
        if (menu == 3)
            break;
    }
    return 0;
}