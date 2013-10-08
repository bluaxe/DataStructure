#include<fstream>
#include<iostream>
using namespace std;
template <class type>
struct Node{	 		
	type data;
	Node<type> *father,*left,*right;
};
template <class type>
class Tree{
public:
	Node<type> *root;
	void levelOrder(ostream &out,int n);
	void preOrder(ostream &out,Node<type> *r);
	void postOrder(ostream &out,Node<type> *r);
	Tree(Node<type> *r=NULL);
	~Tree();
};

template <class type>
Tree<type>::Tree(Node<type> *r=NULL):root(r){
}

template <class type>
Tree<type>::~Tree(){
}

template <class type>
void Tree<type>::levelOrder(ostream &out,int n){
	Node<type> **arr=new Node<type>*[n],*son;
	int pos=0,tail=1;
	arr[0]=root;
	while (pos!=tail){
		son=arr[pos]->left;
		while (son!=NULL) {
			arr[tail++]=son;
			son=son->right;
		}
		out<<arr[pos]->data<<' ';
		pos++;
	}
}

template <class type>
void Tree<type>::preOrder(ostream &out,Node<type> *r){
	out<<r->data<<' ';
	Node<type> *son(r->left);
	Tree<type> temp;
	while(son!=NULL){
		temp.root=son;
		temp.preOrder(out,son);
		son=son->right;
	}
}

template <class type>
void Tree<type>::postOrder(ostream &out,Node<type> *r){
	Node<type> *son(r->left);
	Tree<type> temp;
	while(son!=NULL){
		temp.root=son;
		temp.postOrder(out,son);
		son=son->right;
	}
	out<<r->data<<' ';
}

int main(){
	ifstream fin("traverse.in");
	ofstream fout("traverse.out");
	int n,left,right,v;
	fin>>n;
	Node<int> *root;
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
	Tree<int> T(root);
	T.preOrder(fout,root);
	fout<<endl;
	T.postOrder(fout,root);
	fout<<endl;
	T.levelOrder(fout,n);
	fout<<endl;
	fin.close();
	fout.close();
	return 0;
}