#include<fstream>
#include<iostream>
using namespace std;
template <class type>
class priorityQueue{
private:
	type *array;
	int maxSize,currentSize;
	void doubleSpace();
	void percolateUp(int i);
public:
	priorityQueue(int capacity=55){ array=new type[capacity];maxSize=capacity;currentSize=0;array[0]=0;}
	void enQueue(const type &x);
	int getSize(){return currentSize;}
	int find(const type &x);
	void decrease(int i,type v);
	void print(ofstream & out){for (int i=1;i<currentSize+1;i++) out<<array[i]<<' ';}
};

template <class type>
void priorityQueue<type>::enQueue(const type &x){
	int pos=++currentSize;
	array[pos]=x;
	percolateUp(pos);
};
template <class type>
void priorityQueue<type>::decrease(int i,type v){
	array[i]-=v;
	percolateUp(i);
}
template <class type>
void priorityQueue<type>::percolateUp(int i){
	type x=array[i];
	while(array[i/2]>x){
		array[i]=array[i/2];
		i/=2;
	}
	array[i]=x;
};
template <class type>
int priorityQueue<type>::find(const type &x){
	int i=1,min=0;
	for (;i<currentSize+1;i++)
		if (array[i] >= x && (array[i] <= array[min] || min ==0) )
			min=i;
	return min;
}
int main(){
	ofstream fout("pack.out");
	ifstream fin("pack.in");
	priorityQueue<double> a;
	int n,pos;
	double weight;
	fin>>n;
	for(int i=0;i<n;i++){
		fin>>weight;
		pos=a.find(weight);
		if (pos == 0) a.enQueue(1-weight);
		else a.decrease(pos,weight);
	}
	fout<<a.getSize();
	fout.close();
	fin.close();
}	