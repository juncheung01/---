//һԪ����ʽ�ı�ʾ�Լ����
//�ſ�
//141402054
#include<iostream>
#include<stdlib.h>
using namespace std;

typedef struct LNode{
	float coef;//ϵ��
	int exp;//ָ��
	struct LNode * next;
} polynomial;
//����ʽ��ʼ������
polynomial *creat_poly(int n){
	polynomial *L=(polynomial *)malloc(sizeof(LNode));
	L->next=NULL;
	polynomial *q=L;
	for(int i=0;i<n;i++){
		polynomial *p=(polynomial *)malloc(sizeof(LNode));
		cin>>p->coef>>p->exp;
		p->next=q->next;
		q->next=p;
		q=p;
	}
	return L;
}
polynomial *add_poly(polynomial * La,polynomial * Lb){
	polynomial *pa=La->next;
	polynomial *pb=Lb->next;
	polynomial *Lc,*pc,*r;
	Lc=La;pc=La;
	while(pa&&pb){
		if(pa->exp<pb->exp){
			pc->next=pa;
			pc=pa;
			r=pa;
			pa=pa->next;
			free(r);
		}
		else if(pa->exp>pb->exp){
			pc->next=pb;
			pc=pb;
			pb=pb->next;
		}
		else {
			float sum=pa->coef+pb->coef;
			if(sum==0.0){
				pc->next=pa->next;
				pc=pa;
				r=pa;
				pa=pa->next;
				free(r);
				r=pb;
				pb=pb->next;
				free(r);
				}
			else{
				pa->coef=sum;
				pc->next=pa;
				pc=pa;
				pa=pa->next;
				r=pb;
				pb=pb->next;
				free(r);
			}
		}
	}
		pc->next=pa?pa:pb;
		free(Lb);
	return Lc;					
}

void print_poly(polynomial * L){
	polynomial *p=L->next;
	while(p){
		cout<<p->coef<<"X"<<p->exp;
		if(p->next)cout<<"+";
		p=p->next;
	}
	cout<<endl;
}

int main(){
	int len1,len2;
	cout<<"������������ʽ�ĳ���"<<endl;
	cin>>len1>>len2;
	cout<<"�����һ������ʽ��ϵ����ָ��"<<endl;
	polynomial * a=creat_poly(len1);
	cout<<"����ڶ�������ʽ��ϵ����ָ��"<<endl;
	polynomial *b=creat_poly(len2);
	print_poly(add_poly(a,b));
	return 0;
}
