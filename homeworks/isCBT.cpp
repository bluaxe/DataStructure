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
private:
	Node<type> *root;
	int height;
public:
	void levelOrder(ostream &out,int n);
	void preOrder(ostream &out,Node<type> *r);
	void postOrder(ostream &out,Node<type> *r);
	bool isCBT(int n);
	Tree(Node<type> *r);
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
	Node<type> **arr=new Node<type>*[n];
	int pos=0,tail=1;
	arr[0]=root;
	while (pos!=tail){
		if (arr[pos]->left!=NULL) arr[tail++]=arr[pos]->left;
		if (arr[pos]->right!=NULL) arr[tail++]=arr[pos]->right;
		out<<arr[pos]->data<<' ';
		pos++;
	}
}

template <class type>
bool Tree<type>::isCBT(int n){
	Node<type> **arr=new Node<type>*[n];
	int pos=0,tail=1;
	bool over=false;
	arr[0]=root;
	while (pos!=tail){
		if (arr[pos]->left!=NULL) arr[tail++]=arr[pos]->left;
		else over=true;
		if (over && (arr[pos]->left!=NULL || arr[pos]->right!=NULL)) return false;
		if (arr[pos]->right!=NULL) arr[tail++]=arr[pos]->right;
		else over=true;
		pos++;
	}
	return true;
}

template <class type>
void Tree<type>::preOrder(ostream &out,Node<type> *r){
	out<<r->data<<' ';
	Tree<type> left(r->left),right(r->right);
	if (r->left!=NULL) left.preOrder(out,r->left);
	if (r->right!=NULL) right.preOrder(out,r->right);
}

template <class type>
void Tree<type>::postOrder(ostream &out,Node<type> *r){
	Tree<type> left(r->left),right(r->right);
	if (r->left!=NULL) left.postOrder(out,r->left);
	if (r->right!=NULL) right.postOrder(out,r->right);
	out<<r->data<<' ';
}

int main(){
	ifstream fin("isCBT.in");
	ofstream fout("isCBT.out");
	int n,left,right,v;
	fin>>n;
	Node<int> *Tarray=new Node<int>[n];
	for(int i=0;i<n;i++) {
		Tarray[i].data=i+1;
		Tarray[i].father=NULL;
		Tarray[i].left=NULL;
		Tarray[i].right=NULL;
	}
	bool *RootNum=new bool[n];
	for(int i=0;i<n;i++) RootNum[i]=true;
	for (int i=0;i<n;i++){
		fin>>left>>right;
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
	Node<int> *root;
	for(int i=0;i<n;i++) 
		if (RootNum[i]) {
			root=Tarray+i;
			break;
		}
	Tree<int> T(root);
	if (T.isCBT(n)) fout<<"Y";
	else fout<<"N";
	fin.close();
	fout.close();
	return 0;
}