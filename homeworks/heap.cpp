#include<fstream>
using namespace std;
class priorityQueue{
private:
	int *array;
	int maxSize,currentSize;
	void doubleSpace();
	void percolateUp(int i);
public:
	priorityQueue(int capacity=55){ array=new int[capacity];maxSize=capacity;currentSize=0;array[0]=0;}
	void enQueue(const int &x);
	int find(const int&x);
	void decrease(int i,int v);
};
void priorityQueue::enQueue(const int &x){
	int pos=++currentSize;
	array[pos]=x;
	percolateUp(pos);
};
void priorityQueue::decrease(int i,int v){
	array[i]-=v;
	percolateUp(i);
}
void priorityQueue::percolateUp(int i){
	int x=array[i];
	while(array[i/2]>x){
		array[i]=array[i/2];
		i/=2;
	}
	array[i]=x;
};
int priorityQueue::find(const int &x){
	int i=1,min=0;
	for (;i<currentSize+1;i++)
		if (array[i]>x && (array[i]<array[min] || min ==0) )
			min=i;
	return min;
}
int main(){
	ofstream fout("heap.out");
	ifstream fin("heap.in");
	priorityQueue a;
	char opt[10];
	int n,para1,para2;
	fin>>n;
	for(int i=0;i<n;i++){
		fin>>opt;
		if (opt[0] == 'i'){
			fin>>para1;
			a.enQueue(para1);
		}
		else if (opt[0] == 'f'){
			fin>>para1;
			fout<<a.find(para1)<<endl;
		}
		else if (opt[0] == 'd' ){
			fin>>para1>>para2;
			a.decrease(para1,para2);
		}
	}
	fout.close();
	fin.close();
}	