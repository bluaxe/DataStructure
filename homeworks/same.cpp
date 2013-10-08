#include<fstream>
#include<iostream>
#include<string>
using namespace std;
template <class type>
struct Node{	 		
	type data;
	Node<type> *father,*left,*right;
};
template <class type>
class Tree{
private:
	Node<type> *root;
	int height;
public:
	string midOrder(Node<type> *r,string &midOrd);
	Tree(Node<type> *r=NULL):root(r){};
	~Tree(){};
};

template <class type>
string Tree<type>::midOrder(Node<type> *r,string &midOrd){
	Tree<type> left(r->left),right(r->right);
	if (r->left!=NULL) left.midOrder(r->left,midOrd);
	char t='0'+r->data;
	midOrd.push_back(t);
	if (r->right!=NULL) right.midOrder(r->right,midOrd);
	return midOrd;
}

int main(){
	ifstream fin("same.in");
	ofstream fout("same.out");
	int n,left,right,v;
	Node<int> *root;
	fin>>n;
	Node<int> *Tarray=new Node<int>[n];
	for(int i=0;i<n;i++) {
		Tarray[i].father=NULL;
		Tarray[i].left=NULL;
		Tarray[i].right=NULL;
	}
	bool *RootNum=new bool[n];
	for(int i=0;i<n;i++) RootNum[i]=true;
	for (int i=0;i<n;i++){
		fin>>left>>right>>v;
		Tarray[i].data=v;
		if (left!=0) {
			Tarray[i].left=&Tarray[left-1];
			Tarray[left-1].father=&Tarray[i];
			RootNum[left-1]=false;
		}
		if (right!=0) {
			Tarray[i].right=&Tarray[right-1];
			Tarray[right-1].father=&Tarray[i];
			RootNum[right-1]=false;
		}
	}
	for(int i=0;i<n;i++) 
		if (RootNum[i]) {
			root=Tarray+i;
			break;
		}
	Tree<int> T1(root);
	string mid;
	T1.midOrder(root,mid);

	//µÚ¶þ¿ÃÊ÷
	fin>>n;
	Node<int> *Tarray1=new Node<int>[n];
	for(int i=0;i<n;i++) {
		Tarray1[i].father=NULL;
		Tarray1[i].left=NULL;
		Tarray1[i].right=NULL;
	}
	bool *RootNum1=new bool[n];
	for(int i=0;i<n;i++) RootNum1[i]=true;
	for (int i=0;i<n;i++){
		fin>>left>>right>>v;
		Tarray1[i].data=v;
		if (left!=0) {
			Tarray1[i].left=&Tarray1[left-1];
			Tarray1[left-1].father=&Tarray1[i];
			RootNum1[left-1]=false;
		}
		if (right!=0) {
			Tarray1[i].right=&Tarray1[right-1];
			Tarray1[right-1].father=&Tarray1[i];
			RootNum1[right-1]=false;
		}
	}
	for(int i=0;i<n;i++) 
		if (RootNum1[i]) {
			root=Tarray1+i;
			break;
		}
	Tree<int> T2(root);
	string mid2;
	T2.midOrder(root,mid2);
	if (mid.compare(mid2)) fout<<"N";
	else fout<<"Y";
	fin.close();
	fout.close();
	return 0;
}