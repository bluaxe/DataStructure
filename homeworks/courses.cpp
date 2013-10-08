/*
PROG:courses
ID:ddd

*/

#include<fstream>
using namespace std;

struct Node{
	int id;
	Node *next;
};

int N,M,*in;
Node *v,**tail;//用tail保存链表尾巴，保证插入效率..

int main(){
	ofstream fout("courses.out");
	ifstream fin("courses.in");
	fin>>N>>M;

	v=new Node[N+1];
	tail=new Node *[N+1];
	in=new int[N+1];

	for(int i=0;i<N+1;i++) {tail[i]=&v[i];in[i]=0;}
	
	int a,b;
	for(int i=0;i<M;i++) {
		fin>>a>>b;
		tail[a]->next=new Node;
		tail[a]=tail[a]->next;
		tail[a]->id=b;
		in[b]++;
	}

	Node *p;
	int n=0,cnt=0;
	bool *s=new bool[N+1];
	for(int i=1;i<N+1;i++) {if (in[i]>0) n++;s[i]=false;}

	while(n>0){
		cnt++;
		n=0;
		for(int i=1;i<N+1;i++){
			if (in[i]==0) s[i]=true;
			else if (in[i]>0) n++;
		}
		for(int i=1;i<N+1;i++){
			if (s[i]){
				p=&v[i];
				while(p!=tail[i]){
					p=p->next;
					in[p->id]--;
				}
				in[i]=-1;
				s[i]=false;
			}
		}
	}

	fout<<cnt<<endl;

	//删内存...
	Node *q;
	for(int i=0;i<N+1;i++) {
		tail[i]->next=NULL;
		p=v[i].next;
		while(p!=NULL){
			q=p;
			p=p->next;
			delete q;
		}
	}
	delete [] v;
	delete [] tail;
	delete [] s;

	fout.close();
	fin.close();

	return 0;
}
