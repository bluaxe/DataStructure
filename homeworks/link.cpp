#include<iostream>
#include<fstream>
using namespace std;

//class list 
template <class type>
class list{
	public:
		virtual void clear()=0;
		virtual int length() const=0;
		virtual void insert(int i, const type &x)=0;
		virtual void remove(int i)=0;
		virtual int search(const type &x) const=0;
		virtual type visit(int i) const=0;
		virtual void traverse() const=0;
		virtual ~list() {};
};

//class OutOfBound and IllegalSize
class OutOfBound {};
class IllegalSize {};

//class seqList
template <class type>
class seqList: public list<type>{
	private:
		type	*data;
		int currentLength;
		int maxSize;
		void doubleSpace();
	public:
		seqList(int initSize=10);
		seqList(const seqList<type> &x);
		~seqList() {delete []data;}
		void clear() {currentLength=0;}
		int length() const {return currentLength;}
		void insert(int i ,const type &x);
		void remove(int i);
		int search(const type &x) const;
		type visit(int i) const;
		void traverse() const;
		seqList<type> operator+(const seqList<type> &x) const;
		seqList<type> operator=(const seqList<type> &x);
};

template <class type>
void seqList<type> ::doubleSpace(){
	type *tmp=data;

	maxSize *=2;
	data=new type[maxSize];
	for (int i=0;i<currentLength;i++) data[i]=tmp[i];
	delete []tmp;
}

template <class type>
seqList<type>::seqList(int initSize){
	if (initSize<=0) throw IllegalSize();
	data=new type[initSize];
	maxSize=initSize;
	currentLength=0;
}

template <class type>
seqList<type>::seqList(const seqList<type> &x){
	currentLength=x.currentLength;
	maxSize=x.maxSize;
	data=new type[maxSize];
	for(int i=0;i<currentLength;i++) data[i]=x.data[i];
}

template <class type>
void seqList<type>:: insert(int i,const type &x){
	if (i<0 || i>currentLength) throw OutOfBound();
	if (currentLength==maxSize) doubleSpace();
	for (int j=currentLength;j>i;j--) data[j]=data[j-1];
	data[i]=x;
	++currentLength;
}

template <class type>
void seqList<type>:: remove(int i){
	if (i<0 || i>currentLength-1) throw OutOfBound();
	for (int j=i;j<currentLength-1;j++) data[j]=data[j+1];
	--currentLength;
}

template <class type>
int seqList<type>:: search(const type &x) const{
	int i;
	for (i=0;i<currentLength && data[i]!=x;i++);
	if (i==currentLength) return -1;
	else return i;
}

template <class type>
type seqList<type>:: visit(int i) const{
	if (i<0 || i>currentLength-1) throw OutOfBound();
	return data[i];
}
 
template <class type>
void seqList<type>:: traverse() const{
	//cout<<endl;
	for (int i=0;i<currentLength;i++)
		cout<<data[i]<<' ';
}
 
template <class type>
seqList<type> seqList<type>:: operator+(const seqList<type> &x) const{
	seqList<type> tmp(maxSize+x.maxSize);
	tmp.currentLength=currentLength+x.currentLength;
	for(int i=0;i<currentLength;i++) tmp.data[i]=data[i];
	for(int i=0;i<x.currentLength;i++) tmp.data[i+currentLength]=x.data[i];
	return tmp;
}

template <class type>
seqList<type> seqList<type>:: operator=(const seqList<type> &x){
	delete []data;	
	currentLength=x.currentLength;
	maxSize=x.maxSize;
	data=new type[maxSize];
	for(int i=0;i<currentLength;i++) data[i]=x.data[i];
	return *this;
}

template<class type>
void process(type t){
	seqList<type> a,b,c;
	type value;

	int size_a,size_b;

	cin>>size_a>>size_b;

	for(int i=0;i<size_a;i++) {
		cin>>value;
		a.insert(i,value);
	}
	for(int i=0;i<size_b;i++) {
		cin>>value;
		b.insert(i,value);
	}

	c=a+b;
	c.traverse();
	//cout<<endl;
}
int main(){
	ofstream out("link.out");
	ifstream in("link.in");
	cin.rdbuf(in.rdbuf());
	cout.rdbuf(out.rdbuf());
	char type[8];
	cin>>type;
	switch (type[0]){
		case('i'):
			int T_int;
			process(T_int);
			break;
		case('c'):
			char T_char;
			process(T_char);
			break;
		case('d'):
			double T_double;
			process(T_double);
			break;
	}
	in.close();
	out.close();
	return 0; 
}
