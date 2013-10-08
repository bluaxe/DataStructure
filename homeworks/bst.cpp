#include<fstream>
using namespace std;


template <class Type>
class Bst{
private:
	struct BinaryNode{
		Type data;
		BinaryNode *left;
		BinaryNode *right;
		BinaryNode(const Type &dat,BinaryNode *lt,BinaryNode *rt)
			:data(dat),left(lt),right(rt){}
	};
public:
	BinaryNode *root;
	Bst(BinaryNode *t=NULL):root(t){}
	~Bst();
	bool find(const Type &x) const;
	bool find_ith(const int i,Type &x,BinaryNode *t);
	void insert(const Type &x);
	void remove(const Type &x);
	void remove_less_than(const Type &x,BinaryNode *&t);
	void remove_greater_than(const Type &x,BinaryNode *&t);	
	void remove_interval(const Type &x,const Type &y,BinaryNode *&t);
private:
	void deleteNode(BinaryNode *t){
			if (t==NULL) return;
			if (t->left!=NULL) deleteNode(t->left);
			if (t->right!=NULL) deleteNode(t->right);
			delete t;
		}
	void insert(const Type &x,BinaryNode *&t);
	void remove(const Type &x,BinaryNode *&t);
	bool find(const Type &x,const BinaryNode *t)const;
	int size(BinaryNode *t){
		if(t==NULL) return 0;
		else return 1+size(t->left)+size(t->right);
	}
};

template <class Type>
Bst<Type>::~Bst(){
	if(root!=NULL) deleteNode(root);
}

template <class Type>
bool Bst<Type>::find(const Type &x)const{
	return find(x,root);
}

template <class Type>
bool Bst<Type>::find(const Type &x,const BinaryNode *t)const {
	if (t==NULL) return false;
	else if (x<t->data) find(x,t->left);
		else if (x>t->data) find(x,t->right);
			else return true;
}

template <class Type>
bool Bst<Type>::find_ith(const int i,Type &x,BinaryNode *t){
	if (t==NULL) return false;
	int lLength=size(t->left);
	if (lLength==i-1) {
		x=t->data;
		return true;
	}
	else if(lLength>=i) 
		find_ith(i,x,t->left);
	else 
		find_ith(i-lLength-1,x,t->right);
}

template <class Type>
void Bst<Type>::insert(const Type &x){
	insert(x,root);
}

template <class Type>
void Bst<Type>::insert(const Type &x,BinaryNode *&t){
	if (t==NULL) t=new BinaryNode(x,NULL,NULL);
	else if (x<=t->data) insert(x,t->left);
	else if (x>t->data) insert(x,t->right);
}

template <class Type>
void Bst<Type>::remove(const Type &x){
	remove(x,root);
}

template <class Type>
void Bst<Type>::remove_less_than(const Type &x,BinaryNode *&t){
	if (t==NULL) return;
	else {
		if (t->data>=x) remove_less_than(x,t->left);
		else if (t->data<x) {
			deleteNode(t->left);
			BinaryNode *temp=t;
			t=t->right;
			delete temp;
			remove_less_than(x,t);
		}
	}
}

template <class Type>
void Bst<Type>::remove_greater_than(const Type &x,BinaryNode *&t){
	if (t==NULL) return;
	else {
		if (t->data<=x) remove_greater_than(x,t->right);
		else if (t->data>x) {
			deleteNode(t->right);
			BinaryNode *temp=t;
			t=t->left;
			delete temp;
			remove_greater_than(x,t);
		}
	}
}

template <class Type>
void Bst<Type>::remove_interval(const Type &x,const Type &y,BinaryNode *&t){
	if (t==NULL) return;
	else {
		if (t->data<=x) remove_interval(x,y,t->right);
		else if (t->data>=y) remove_interval(x,y,t->left);
		else{
			remove(t->data,t);
			remove_interval(x,y,t);
		}
	}
}

template <class Type>
void Bst<Type>::remove(const Type &x,BinaryNode *&t){
	if (t==NULL) return;
	else {
		if (x<t->data) remove(x,t->left);
		else if (x>t->data) remove(x,t->right);
		else {
			if (t->left!=NULL && t->right!=NULL){
				BinaryNode *&temp=t->right;
				while (temp->left!=NULL ) temp=temp->left;
				t->data=temp->data;
				remove(temp->data,temp);
			}
			else{
				BinaryNode *temp=t;
				t=(t->left==NULL?t->right:t->left);
				delete temp;
			}
		}
	}
}

int main(){
	ofstream fout("bst.out");
	ifstream fin("bst.in");
	Bst<int> a;
	int n,x,y;
	char opt[20];
	fin>>n;
	for(int i=0;i<n;i++){
		fin>>opt>>x;
		if(strcmp("insert",opt)==0){
			a.insert(x);
		}
		else if(strcmp("find",opt)==0){
			fout<<(a.find(x)?"Y":"N")<<endl;
		}
		else if(strcmp("delete",opt)==0){
			a.remove(x);
		}
		else if(strcmp("delete_less_than",opt)==0){
			a.remove_less_than(x,a.root);
		}
		else if(strcmp("delete_greater_than",opt)==0){
			a.remove_greater_than(x,a.root);
		}
		else if(strcmp("delete_interval",opt)==0){
			fin>>y;
			a.remove_interval(x,y,a.root);
		}
		else if(strcmp("find_ith",opt)==0){
			if(a.find_ith(x,y,a.root)) 
				fout<<y<<endl;
			else fout<<"N"<<endl;
		}
	}
	fout.close();
	fin.close();
	return 0;
}