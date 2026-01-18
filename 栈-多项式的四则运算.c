/*
给定一道没有括号的四则混合运算算术题（可能包含多余的空格），请编程计算出结果。运算规则如下：

既有乘、除法又有加、减法的，要先算乘除法，再算加减法；
同级运算时，要从左往右按顺序计算；
所有除法运算的结果都只保留整数部分（直接舍弃小数部分）。
例如：当算术题为 2+3*4-10/6+1/2?4 时：
优先计算乘除法，有 3*4=12，10/6=1，1/2*4=0；
然后计算加减法，2+3*4-10/6+1/2*4=2+12-1+0=13，故输出 13。
输入格式
输入一个字符串，表示算术题：
字符串长度 5≤长度 ≤100000；
字符串中只包含数字字符以及 +，-，*，/ 运算符；
不含括号，可能包含空格；
算式中的运算数范围：1≤ 运算数 ≤200。
输出格式
输出一个整数，表示算术题的计算结果。题目数据保证算式的每一步运算的结果都在 -2×10^9～2×10^9之间。
*/

#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

#define MAX_SIZE 100

// 定义栈结构（用于字符运算符）
typedef struct {
    char data[MAX_SIZE];
    int top;
} Stack;

// 定义数字栈（用于计算后缀表达式）
typedef struct {
    double data[MAX_SIZE];
    int top;
} NumStack;

// 初始化运算符栈
void initStack(Stack* s) {
    s->top = -1;
}

// 初始化数字栈
void initNumStack(NumStack* s) {
    s->top = -1;
}

// 检查运算符栈是否为空
int isEmpty(Stack* s) {
    return s->top == -1;
}

// 检查数字栈是否为空
int isNumStackEmpty(NumStack* s) {
    return s->top == -1;
}

// 运算符栈入栈
void push(Stack* s, char c) {
    if (s->top < MAX_SIZE - 1) {
        s->data[++(s->top)] = c;
    }
}

// 数字栈入栈
void pushNum(NumStack* s, double num) {
    if (s->top < MAX_SIZE - 1) {
        s->data[++(s->top)] = num;
    }
}

// 运算符栈出栈
char pop(Stack* s) {
    if (!isEmpty(s)) {
        return s->data[(s->top)--];
    }
    return '\0';
}

// 数字栈出栈
double popNum(NumStack* s) {
    if (!isNumStackEmpty(s)) {
        return s->data[(s->top)--];
    }
    return 0.0;
}

// 获取运算符栈顶元素（不弹出）
char peek(Stack* s) {
    if (!isEmpty(s)) {
        return s->data[s->top];
    }
    return '\0';
}

// 获取运算符优先级[6,8](@ref)
int getPriority(char op) {
    switch (op) {
        case '+':
        case '-':
            return 1;
        case '*':
        case '/':
            return 2;
        default:
            return 0; // 包括括号等特殊情况
    }
}

// 中缀表达式转后缀表达式[6,8](@ref)
void infixToPostfix(char* infix, char* postfix) {
    Stack opStack;
    initStack(&opStack);
    int i = 0, j = 0;
    char token;
    
    while ((token = infix[i]) != '\0') {
        if (isspace(token)) {
            i++; // 跳过空格
            continue;
        }
        
        if (isdigit(token) || token == '.') {
            // 处理数字（包括多位数和小数）
            while (isdigit(infix[i]) || infix[i] == '.') {
                postfix[j++] = infix[i++];
            }
            postfix[j++] = ' '; // 用空格分隔数字
            continue;
        }
        
        if (token == '(') {
            // 左括号直接入栈[6](@ref)
            push(&opStack, token);
            i++;
        } else if (token == ')') {
            // 右括号：弹出栈内运算符直到左括号[6](@ref)
            while (!isEmpty(&opStack) && peek(&opStack) != '(') {
                postfix[j++] = pop(&opStack);
                postfix[j++] = ' ';
            }
            pop(&opStack); // 弹出左括号但不输出
            i++;
        } else if (token == '+' || token == '-' || token == '*' || token == '/') {
            // 运算符：处理优先级[8](@ref)
            while (!isEmpty(&opStack) && 
                   getPriority(peek(&opStack)) >= getPriority(token) &&
                   peek(&opStack) != '(') {
                postfix[j++] = pop(&opStack);
                postfix[j++] = ' ';
            }
            push(&opStack, token);
            i++;
        } else {
            printf("错误：无效字符 '%c'\n", token);
            exit(1);
        }
    }
    
    // 弹出栈中剩余所有运算符[6](@ref)
    while (!isEmpty(&opStack)) {
        postfix[j++] = pop(&opStack);
        postfix[j++] = ' ';
    }
    postfix[j] = '\0'; // 字符串结束符
}

// 计算后缀表达式[6,7](@ref)
double evaluatePostfix(char* postfix) {
    NumStack numStack;
    initNumStack(&numStack);
    int i = 0;
    char token;
    
    while ((token = postfix[i]) != '\0') {
        if (isspace(token)) {
            i++;
            continue;
        }
        
        if (isdigit(token) || token == '.') {
            // 提取完整数字（包括小数）
            char numStr[20];
            int j = 0;
            while (isdigit(postfix[i]) || postfix[i] == '.') {
                numStr[j++] = postfix[i++];
            }
            numStr[j] = '\0';
            pushNum(&numStack, atof(numStr)); // 转换为double入栈
            continue;
        }
        
        if (token == '+' || token == '-' || token == '*' || token == '/') {
            // 弹出两个操作数（注意顺序：先弹出的是右操作数）
            double b = popNum(&numStack);
            double a = popNum(&numStack);
            double result = 0.0;
            
            switch (token) {
                case '+':
                    result = a + b;
                    break;
                case '-':
                    result = a - b;
                    break;
                case '*':
                    result = a * b;
                    break;
                case '/':
                    if (b != 0.0) {
                        result = a / b;
                    } else {
                        printf("错误：除数不能为零！\n");
                        exit(1);
                    }
                    break;
            }
            pushNum(&numStack, result);
            i++;
        }
    }
    return popNum(&numStack); // 返回最终结果
}

int main() {
    char infix[MAX_SIZE];
    char postfix[MAX_SIZE * 2]; // 后缀表达式可能更长
    double result;
    
    printf("请输入算术表达式（支持 +、-、*、/ 和括号，例如：1+(3-1)*3/2-5）：\n");
    if (fgets(infix, MAX_SIZE, stdin) == NULL) {
        printf("读取输入失败！\n");
        return 1;
    }
    
    // 移除换行符
    infix[strcspn(infix, "\n")] = '\0';
    
    // 中缀转后缀
    infixToPostfix(infix, postfix);
    printf("后缀表达式：%s\n", postfix);
    
    // 计算后缀表达式
    result = evaluatePostfix(postfix);
    printf("计算结果：%.2f\n", result);
    
    return 0;
}












