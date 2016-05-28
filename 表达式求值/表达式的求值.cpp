/*
*简单表达式的求值
*张俊
*141402054
*/
#define OVERFLOW -1
#define OK 1
#define ERROR 0
#define STACK_INIT_SIZE 100
#define STACK_INCEREMENT 10
#include <iostream.h>
#include <stdlib.h>
typedef int Status;
int int_max=10000;
char operators[7]={'+','-','*','/','(',')','#'};//运算符数组
int op_piro[7][7]={
{1,1,-1,-1,-1,1,1},
{1,1,-1,-1,-1,1,1},
{1,1,1,1,-1,1,1},
{1,1,1,1,-1,1,1},
{-1,-1,-1,-1,-1,0,int_max},
{1,1,1,1,int_max,1,1},
{-1,-1,-1,-1,-1,int_max,0},};//优先级数组
char str[100];
typedef struct{
	char *base;
	char *top;
	int stacksize;
}charStack;
typedef struct{
	int *base;
	int *top;
	int stacksize;
}intStack;
//初始化栈
template<class T1,class T2>
Status InitStack(T1 &t){
	t.base=(T2 *)malloc(STACK_INIT_SIZE*sizeof(T2));
	if(!t.base)return OVERFLOW;
	t.top=t.base;
	t.stacksize=STACK_INIT_SIZE;
	return OK;
}
//取栈顶元素
template<class T1,class T2>
T2 GetTop(T1 t1){
	if(t1.top==t1.base)return '\0';
		return *(t1.top-1);
}
//压栈
template<class T1,class T2>
Status Push(T1 &t1,T2 t2){
	if(t1.top-t1.base>=t1.stacksize)
	{
		t1.base=(T2 *)realloc(t1.base,(t1.stacksize+STACK_INCEREMENT)*sizeof(T2));
		if(!t1.base)return OVERFLOW;
		t1.top=t1.base+t1.stacksize;
		t1.stacksize+=STACK_INCEREMENT;
	}
	*t1.top++=t2;
	return OK;
}
//出栈
template<class T1,class T2>
Status Pop(T1 &t1,T2 &t2){
	if(t1.top==t1.base)return ERROR;
	t2=*--t1.top;
	return OK;
}
//通过运算符获得所在数组的标号
int getNum(char c,char operators[]){
	for(int i=0;i<7;i++){
		if(operators[i]==c)
			return i;
	}
	return -1;
}
//计算的函数
int Operate(int a,char op,int b){
	switch(getNum(op,operators)){
	case 0:return a+b;
	case 1:return a-b;
	case 2:return a*b;
	case 3:return a/b;
	}
	return -1;
}
//进行操作的函数
int EvaluateExpression(char operators[],int op_piro[7][7],char str[]){
	int i=0;
	charStack OPTR;
	intStack OPND;
	InitStack<charStack,char>(OPTR);
	InitStack<intStack,int>(OPND);
	Push(OPTR,'#');
	while(str[i]!='#'||GetTop<charStack,char>(OPTR)!='#'){
		if(str[i]>='0'&&str[i]<='9'){
			char opnd[10];
			int k=0;
			do{
				opnd[k++]=str[i++];
			}
			while(str[i]>='0'&&str[i]<='9');
			opnd[k]='\0';
			Push(OPND,atoi(opnd));
		}
		else{
			char c=GetTop<charStack,char>(OPTR);	
			switch(op_piro[getNum(c,operators)][getNum(str[i],operators)]){
			case -1:Push(OPTR,str[i]);i++;break;
			case 0:Pop(OPTR,c);i++;break;
			case 1:{
				char op=NULL;int a=0,b=0;
				Pop(OPTR,op);
				Pop(OPND,b);
				Pop(OPND,a);
				Push(OPND,Operate(a,op,b));
				//i++;
				break;
			}
		}

	}	
}
	return GetTop<intStack,int>(OPND);
}
void main(){
	cout<<"请输入一个英文字符算数表达式并以#结束"<<endl;
	char str[1000];
	cin>>str;
	cout<<EvaluateExpression(operators,op_piro,str)<<endl;
}