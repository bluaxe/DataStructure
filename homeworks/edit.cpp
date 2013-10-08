#include<iostream>
#include<fstream>
#include<string.h>
using namespace std;
struct seq{
	char *data;
	seq *prior;
	seq *next;
};
void cut(char *line,int x,int n){ for (int i=x+n-1;i<(signed)strlen(line)+1;i++) *(line+i-n)=*(line+i); }
void insert(char *&line,int x,char *word){
	char *p=new char[strlen(line)+strlen(word)+1];	
	*(p+strlen(line)+strlen(word))='\0';
	int i,j;
	for (i=0;i<x-1;i++) *(p+i)=*(line+i);
	for (j=i;j<(signed)strlen(word)+i;j++) *(p+j)=*(word+j-i);
	j-=i;
	for (i=i;i<(signed)strlen(line);i++) *(p+i+j)=*(line+i);
	delete []line;
	line=p;
}
void quit(seq *head,seq *tail,char *name){
	seq *p;
	ofstream fout;
	fout.open(name);
	p=head->next;
	while(p!=tail){
		fout<<p->data;
		p=p->next;
	}
	fout.close();
}
void open(seq *head,char *name){
	ifstream fin;
	fin.open(name);
	seq *p=head->next,*q;
	char x,s[2]="1";
	int i=1;
	while ((x=fin.get())){
		if (x==EOF) break;
		s[0]=x;
		insert(p->data,i++,s);
		if (x=='\n') {
			q=new seq;
			q->data=new char;
			*(q->data)='\0';
			q->next=p->next;
			q->prior=p;
			p->next=q;
			q->next->prior=q;
			p=q;
			i=1;
		}
	}
	fin.close();
}
int main(){
	//io
	ofstream out("edit.out");
	ifstream in("edit.in");
	cin.rdbuf(in.rdbuf());
	cout.rdbuf(out.rdbuf());
	//init
	seq head,tail,*p=new seq;
	p->data=new char;
	*(p->data)='\0';
	head.next=p;
	p->prior=&head;
	p->next=&tail;
	tail.prior=p;
	//open
	char inst[5],filename[30],str[2000];
	int para1,para2,para3,lines(0);
	cin>>inst>>filename;
	open(&head,filename);
	p=&head;
	while(p!=&tail){
			lines++;
			p=p->next;
	}
	while(cin>>inst){
		switch(inst[0]){
			case 'l':
				cin>>para1>>para2;	
				if (para1<1 || para1>lines-2 || para2<1 || para2>lines-2 || para1>para2) {
					cout<<"Error!"<<endl;
					break;
				}
				p=&head;
				for (int i=0;i<para1;i++) p=p->next;
				for (int i=0;i<para2-para1+1;i++,p=p->next) cout<<p->data;
				break;
			case 'i':
				cin>>para1>>para2;	
				if (para1<1 || para1>lines-2) {
					cout<<"Error!"<<endl;
					break;
				}
				cin.get();
				cin.getline(str,2000);
				p=&head;
				for (int i=0;i<para1;i++) p=p->next;
				if (para2>strlen(p->data)){//换行符需保持在末尾
					cout<<"Error!"<<endl;
					break;
				}
				insert(p->data,para2,str);
				break;
			case 'd':
				cin>>para1>>para2>>para3;
				if (para1<1 || para1>lines-2) {
					cout<<"Error!"<<endl;
					break;
				}
				p=&head;
				for (int i=0;i<para1;i++) p=p->next;
				if (para2+para3-1>strlen(p->data)-1 || para3<0 || para2<0){//换行符需保持在末尾
					cout<<"Error!"<<endl;
					break;
				}
				cut(p->data,para2,para3);
				break;
			case 'q':
				quit(&head,&tail,filename);
				break;
		}
		if (inst[0]=='q') break;
	}
	p=head.next;
	seq *q;
	while(p!=&tail){
		delete []p->data;
		q=p;
		p=p->next;
		delete q;
	}
	in.close();
	out.close();
	return 0;
}
