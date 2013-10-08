#include<iostream>
#include<fstream>
using namespace std;
struct list{
	short num;
	list *next;
};
list *getnum(){
	list *p,*q;
	p=new list;
	p->num=-1;
	char x;
	while((x=cin.get())){
		if (x=='\n') break;
		q=new list;
		q->num=x-'0';
		q->next=p;
		p=q;
	}
	return p;
}
int main(){
	ofstream out("bigint.out");
	ifstream in("bigint.in");
	cin.rdbuf(in.rdbuf());
	cout.rdbuf(out.rdbuf());
	list *n1,*n2,*n3,*p;
	short x=0;
	n1=getnum();
	n2=getnum();
	n3=new list;
	n3->num=-1;
	while(n1->num!=-1 || n2->num!=-1 || x!=0){
		p=new list;	
		p->num=(n1->num!=-1?n1->num:0)+(n2->num!=-1?n2->num:0)+x;
		x=p->num/10;
		p->num=p->num%10;
		p->next=n3;
		n3=p;
		n1=n1->num!=-1?n1->next:n1;
		n2=n2->num!=-1?n2->next:n2;
	}
	while(n3->num!=-1){
		cout<<n3->num;
		p=n3;
		n3=n3->next;
		delete p;
	}
	delete n3;
	in.close();
	out.close();
	return 0;
}
