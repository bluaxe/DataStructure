/*
PROG:path
ID:ddd

吐槽为啥非要用类来写。...
*/

#include<fstream>
using namespace std;

class AjList{
	struct Node{
		int weight;
		int id;
		Node *next;
		Node(int which=0,int w=0):id(which),weight(w),next(NULL){}
	};

public :
	AjList(int s):size(s){	head=new Node[size+1];};
	~AjList();
	void add(int a,int b,int w);
	int path(int a,int len);

private :
	void find(bool *,int a,int len);
	Node *head;
	int size,path_num;

};

void AjList::find(bool *s,int a,int l){
	if (l==0) {path_num++;return ;}
	Node *p=head[a].next;
	while(p!=NULL){
		if (!s[p->id]){
			s[p->id]=true;
			find(s,p->id,l-1);
			s[p->id]=false;
		}
		p=p->next;
	}
}

int AjList::path(int a,int len){
	bool *s=new bool[size+1];
	for(int i=0;i<size+1;i++) s[i]=false;
	s[a]=true;
	path_num=0;
	find( s,a,len);
	delete [] s;
	return path_num;
}

AjList::~AjList(){
	Node *p,*q;
	for(int i=0;i<size+1;i++){
		p=head[i].next;
		while(p!=NULL){
			q=p;
			p=p->next;
			delete q;
		}
	}
}

void AjList::add(int a,int b,int w){
	if (a>size || b>size) return;
	Node *p=&head[a];
	while(p->next!=NULL)	p=p->next;
	p->next=new Node(b,w);
}

int main(){
	ofstream fout("path.out");
	ifstream fin("path.in");
	int n,m,start,M;
	fin>>n>>m>>start>>M;
	AjList aj(n);
	int a,b;
	for(int i=0;i<m;i++){
		fin>>a>>b;
		aj.add(a,b,1);
	}
	fout<<aj.path(start,M)<<endl;

	fout.close();
	fin.close();

	return 0;
}