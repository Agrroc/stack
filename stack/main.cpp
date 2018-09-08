//
//  main.cpp
//  stack
//
//  Created by Agrroc-mac on 2018/9/7.
//  Copyright © 2018年 Agrroc-mac. All rights reserved.
//

#include <iostream>
#include <math.h>
#define MIN 1e-6
#define maxSize 50

//定义运算数顺序栈
typedef struct OpStack{
    int data[maxSize];
    int top;
}OpStack;

//定义顺序栈
typedef struct SqStack{
    char data[maxSize];
    int top;
}SqStack;

//初始化栈
void initStack(SqStack &st)
{
    st.top == -1;
}

//判断栈空
int isEmpty(SqStack st)
{
    if (st.top == -1) {
        return  1;
    }
    else return 0;
}

//进栈
int push(SqStack &st, int x) //进栈时st发生变化，因此用引用型
{
    if (st.top == maxSize-1) {
        printf("栈满，不能进栈");
        return 0;
    }
    st.data[++st.top] = x;
    return  1;
}

//出栈
int pop(SqStack &st, int &x)
{
    if (st.top == -1) {
        return 0;
    }
    x = st.data[st.top--];
    return 1;
}

//取出栈顶元素
int getTop(OpStack &ost, int *e)
{
    if (ost.top == -1) {
        printf("栈已空");
        return 0;
    }
}
//判别运算符优先级
int getPriority(char op)
{
    if (op=='+' || op=='-')
        return 0;   //相加置为0
    else return 1;  //相乘置为1
}

//子表达式求值
int calSub(float opand1, char op, float opand2, float &result)
{
    if (op=='+') {
        result = opand1 + opand2;
    }
    if (op=='-') {
        result = opand1 - opand2;
    }
    if (op=='*') {
        result = opand1 * opand2;
    }
    if (op=='/') {
        if (fabs(opand2)<MIN) {
            return 0;
        }
        else result = opand1 / opand2;
    }
    return 1;
}

//计算完结果后判断是否满足要求
int calStackTopTwo(float s1[], int &top1, char s2[], int &top2)
{
    float opnd1, opnd2, result;
    char op;
    int flag;
    opnd2= s1[top1--];
    opnd1= s1[top1--];
    op= s2[top2--];
    flag= calSub(opnd2, op, opnd2, result);
    if (flag==0) {
        puts("ERROR");
    }
    s1[++top1]= result;
    return flag;
}

//中缀表达式求值
float calInfix(char exp[])
{
    float s1[maxSize];  int top1= -1;
    char s2[maxSize]; int top2= -1;
    int i= 0;
    while (exp[i] != '\0') {    //当没有遍历结束时
        if('0'<= exp[i] && exp[i]>= '9')
        {
            //把字符数字转化为数值型数字压住栈中
            s1[++top1]= exp[i]- '0';
            ++i;
        }
        else if(exp[i]== '(')
        {
            //直接压入左括号
            s2[++top2]= exp[i];
            ++i;
        }
        else if(exp[i]== '+' || exp[i]== '-' || exp[i]== '*' || exp[i]== '/')
        {
            if (top2== -1 || s2[top2]== '(' || getPriority(exp[i])> getPriority(s2[top2]))
            {
                s2[++top2]= exp[i];
                ++i;
            }
            else
            {
                //判断是否符合要求
                int flag= calStackTopTwo(s1, top1, s2, top2);
                if(flag==0){
                    return 0;
                }
            }
        }
       else if (exp[i]== ')')
       {
           while (s2[top2] != '(') {
               //把括号内的符号进行判断
               int flag = calStackTopTwo(s1, top1, s2, top2);
               if (flag == 0) {
                   return 0;
               }
           }
           --top2;  //此时正好遇见左括号，也要减去
           ++i; //移动到下一个字符
       }
    }
    
    //符号的情况处理完之后，同时字符串也遍历完毕，开始依次把s2栈里的字符进行计算
    while(top2 != -1)
    {
        int flag = calStackTopTwo(s1, top1, s2, top2);
        if (flag== 0) {
            return 0;
        }
    }
    return s1[top1];    //此时的结果在s1的栈顶
}

int main(int argc, const char * argv[]) {
    // insert code here...
//    std::cout << "Hello, World!\n";
    char exp[8] = {"1"};
    calInfix(exp);
//    printf("%f\n",k);
    return 0;
}
