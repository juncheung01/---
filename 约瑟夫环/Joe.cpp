//Լɪ��
//�ſ�
//141402054
#include <iostream.h>
#include <stdlib.h>
#define OK 1
#define ERROR 0
typedef int Status;
typedef struct LNode{
	int num,key;
	LNode *next;
}JCircle;
//��ʼ���������γ�һ��ʼ�Ļ���QΪ��ѭ����β���
Status init(JCircle * &Q,int n){
	JCircle * q =(JCircle *)malloc(sizeof(LNode));
	if(!q) return ERROR;
	JCircle *r=q;
	JCircle * p=NULL;
	q->num=1;
	q->next=NULL;
	cin>>q->key;
	for(int i=2;i<=n;i++){
		p=(JCircle *)malloc(sizeof(LNode));
		if(!p) return ERROR;
		p->num=i;
		cin>>p->key;
		r->next=p;
		r=p;
	}
	p->next=q;
	Q=p;
	return OK;
}
//����Լɪ�򻷵ĺ���
void Joe(JCircle *n,int init_m,int num){
	JCircle *p=n;
	JCircle *q=p->next;
	JCircle * r=NULL;
	int m=init_m;
	for(int i=0;i<num;i++){
		int times=1;
		while(p!=q){
			if(times==m){
				cout<<q->num<<" ";
				m=q->key;
				r=q;
				p->next=q->next;
				q=q->next;
				free(r);
			}
			else{
				p=q;
				q=q->next;
				times++;
			}
			if(p==q)cout<<q->num<<" ";
		}
		
	}
}
void main(){
	int num;//����
	int m;//һ��ʼ������mֵ
	cin>>num>>m;
	JCircle *p=NULL;
	if(!init(p,num)) cout<<"error";
	Joe(p,m,num);
	
}