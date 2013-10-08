#include<fstream>
using namespace std;
template <class Type>
class Set{
private:
	struct Node{
		Type data;
		Node *next;
	};
	Node *head,*tail;
	int length;	
public:
	Set():length(0){head=new Node;tail=head;}
	~Set();
	void insert(Type x);
	bool query(Type x);
};
template <class Type>
Set<Type>::~Set(){
	Node *temp=head;
	while (head!=tail){temp=head;head=head->next;delete temp;}
}
template <class Type>
void Set<Type>::insert(Type x){
	Node *temp=new Node;
	temp->data=x;
	temp->next=tail->next;;
	tail->next=temp;
	tail=temp;
	length++;
}
template <class Type>
bool Set<Type>::query(Type x){
	Node *temp=head;
	while(temp!=tail){
		if (temp->next->data==x) break;
		temp=temp->next;
	}
	if (temp!=tail) {
		Type swap=temp->data;
		temp->data=temp->next->data;
		temp->next->data=swap;
		return true;
	}
	else return false;
}
int main(){
	ofstream fout("optimization.out");
	ifstream fin("optimization.in");
	int n,m,x;
	Set<int> a;
	fin>>n;
	for(int i=0;i<n;i++) {
		fin>>x;
		a.insert(x);
	}
	fin>>m;
	for(int i=0;i<m;i++){
		fin>>x;
		fout<<(a.query(x)?"Y":"N")<<endl;
	}
	return 0;
}