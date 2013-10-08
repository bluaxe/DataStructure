#include<fstream>
using namespace std;

template <class Type>
class Set{
	template <class Type>
	friend Set<Type> operator+(const Set<Type> &a,const Set<Type> &b);
	template <class Type>
	friend Set<Type> operator-(const Set<Type> &a,const Set<Type> &b);
	template <class Type>
	friend Set<Type> operator*(const Set<Type> &a,const Set<Type> &b);
	template <class Type>
	friend ostream &operator<<(ostream &os,const Set<Type> &s);
public:
	Set(int n=100):MaxSize(n),length(0){data=new Type[MaxSize];};
	Set(const Set<Type> &t);
	~Set(){delete []data;}
	int exsit(Type x) const;
	void insert(Type x);
	void dele(Type x);
	void deleByPos(int pos){for(int i=pos;i<length;i++) data[i]=data[i+1];length--;}
	Set<Type> operator=(Set<Type> &t);
private:
	Type *data;
	int MaxSize,length;
	void doubleSpace();
};

template <class Type>
Set<Type> operator+(const Set<Type> &a,const Set<Type> &b){
	Set<Type> t(a);
	for (int i=0;i<b.length;i++)
		t.insert(b.data[i+1]);
	return t;
}

template <class Type>
Set<Type> operator-(const Set<Type> &a,const Set<Type> &b){
	Set<Type> t(a);
	int pos;
	for (int i=0;i<b.length;i++){
		pos=t.exsit(b.data[i]);
		if (pos>0) t.deleByPos(pos);
	}
	return t;
}

template <class Type>
Set<Type> operator*(const Set<Type> &a,const Set<Type> &b){
	Set<Type> t;
	for (int i=0;i<a.length;i++)
		if (b.exsit(a.data[i+1])) t.insert(a.data[i+1]);
	return t;
}

template <class Type>
ostream &operator<<(ostream &os,const Set<Type> &s){
	quick_sort(s.data,1,s.length);
	for(int i=0;i<s.length;i++) os<<s.data[i+1]<<' ';
	os<<endl;
	return os;
}

template <class Type>
Set<Type> Set<Type>::operator=(Set<Type> &t){
	MaxSize=t.MaxSize;
	length=t.length;
	data=new Type[MaxSize];
	for(int i=0;i<length+1;i++) data[i]=t.data[i];
	return t;
}

template <class Type>
Set<Type>::Set(const Set<Type> &t){
	MaxSize=t.MaxSize;
	length=t.length;
	data=new Type[MaxSize];
	for(int i=0;i<length+1;i++) data[i]=t.data[i];
}

template <class Type>
void Set<Type>::dele(Type x){
	int pos=exsit(x);
	if (pos>0){
		for (int i=pos;i<length;i++)
			data[i]=data[i+1];
		length--;
	}
}

template <class Type>
int Set<Type>::exsit(Type x) const {
	data[0]=x;
	int i;
	for(i=length;data[i]!=data[0];i--);
	return i;
}

template <class Type>
void Set<Type>::insert(Type x){
	if (!exsit(x)){
		if (length+1<MaxSize)
			data[++length]=x;
		else {
			doubleSpace();
			data[++length]=x;
		}
	}
}

template <class Type>
void Set<Type>::doubleSpace(){
	Type *temp=data;
	MaxSize*=2;
	data=new Type[MaxSize];
	for(int i=0;i<length+1;i++) data[i]=temp[i];
	delete []temp;
}

template <class Type>
void quick_sort(Type s[],int l,int r){
	if (l<r){
		Type x=s[l];
		int i=l,j=r;
		while (i<j){
			while (i<j && s[j]>=x) j--;
			if (i<j) s[i++]=s[j];
			while (i<j && s[i]<x) i++;
			if (i<j) s[j--]=s[i];
		}
		s[i]=x;
		quick_sort(s,l,i-1);
		quick_sort(s,i+1,r);
	}
}

int main(){
	ofstream fout("settest.out");
	ifstream fin("settest.in");
	Set<int> s;
	int n,m,t;
	char opt;
	fin>>n;
	for (int i=0;i<n;i++){
		fin>>opt>>m;
		Set<int> temp(m);
		for(int j=0;j<m;j++){
			fin>>t;
			temp.insert(t);
		}
		if (opt=='+') {
			fout<<(s=s+temp);
		}
		else if (opt=='-'){
			fout<<(s=s-temp);
		}
		else if (opt=='*') {
			fout<<(s=s*temp);
		}
	}
	fin.close();
	fout.close();
	return 0;
}