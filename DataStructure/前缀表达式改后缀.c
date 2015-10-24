#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char stack[102];
char target[100];
int length;
//返回栈顶元素
char top(char *s);
//删除栈顶元素
void pop(char *s);
//元素x插入栈顶
void push(char *s, char x);
//处理式子
void trans(char *exp, char *pexp);

int main(){
	char exp[100];

	scanf("%s",exp);
	trans(exp, target);
	printf("%s",target);
	return 0;
}

char top(char *s){
	if(!length)
		return '\0';
	else
		return *(s + length);
}
void pop(char *s){
	if(!length){
		printf("Error,the stack is empty.\n");
		return;
	}
	else{
		*(s + length) = '\0';
		length--;
	}
}
void push(char *s, char x){
	if(length >= 100){
		printf("Error,the stack is full.\n");
		return;
	}
	else{
		length++;
		*(s + length) = x;
	}
}

void trans(char *exp, char *pexp){
	while(*exp != '\0'){
		//若 *exp 是数字或字母，直接赋给*pexp
		if((*exp >= '0' && *exp <= '9')
			|| (*exp >= 'a' && *exp <= 'z')
			||(*exp >='A' && *exp <= 'Z'))
		{
			*(pexp++) = *(exp++);
		}
		//若 *exp 是除号(优先级最高)，直接进栈
		else if(*exp == '/'){
			push(stack, '/');
			exp++;
		}
		//若 *exp 是乘号(优先级仅次于除号)，若优先级低于栈顶元素则弹出栈顶后再进栈
		//目的是保持栈底到栈顶,优先级升序；否则直接进栈
		else if(*exp == '*'){
			if(top(stack) == '/'){
				*(pexp++) = top(stack);
				exp++;
				pop(stack);
				push(stack, '*');
			}
			else{
				push(stack, '*');
				exp++;
			}
		}
		//若 *exp 是减号(优先级次于乘号)，若优先级低于栈顶元素则弹出栈顶后再进栈
		//目的同上
		else if(*exp == '-'){
			if(top(stack) == '/' || top(stack) == '*'){
				*(pexp++) = top(stack);
				pop(stack);
			}
			else{
				push(stack, '-');
				exp++;
			}
		}
		//若 *exp 是加号(最低优先级)，则弹出栈顶元素，目的同上
		else if(*exp == '+'){
			if(top(stack) == '/' || top(stack) == '*' || top(stack) == '-'){
				*(pexp++) = top(stack);
				pop(stack);
			}
			else{
				push(stack, '+');
				exp++;
			}
		}
		//若 *exp 是左括号，则视括号中的是新的子式(内部运算顺序同外部但又完全独立于外部
                                                              //即运算顺序不受外部影响)
		else if(*exp == '('){
            exp++;
            push(stack,'(');    //用'('标记子式的开头
          }
          //若 *exp是右括号则表示扫描到达子式末尾，检查栈中'('之上是否还有元素(运算符号)，有则依次赋进pexp并弹出
        else if(*exp == ')'){
            exp++;
            do{
                *pexp = top(stack);
                pop(stack);
            }while(*(pexp++) != '(');
            *(--pexp) = '\0'; //因为while中的判断语句会在读到'('时写进pexp
        }
	}
	//扫描完成，检查栈中是否还有元素(运算符号)，有则依次赋进pexp并弹出
    while((*pexp = top(stack)) != '\0'){
        pop(stack);
        pexp++;
    }
}
