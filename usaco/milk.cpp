/*
PROG:milk
ID:dddd1021
LANG:C++
*/

#include<fstream>
using namespace std;

struct farmer{
	int price;
	int amount;
};

void swap(farmer *s,int a,int b){
	farmer t=s[a];
	s[a]=s[b];
	s[b]=t;
}

void quicksort(farmer *s,int low,int high){
	if (high<=low) return;
	int l=low,h=high;
	farmer k=s[low];
	while(high>low){
		while(s[high].price>k.price && high>low) high--;
		swap(s,high,low);
		while(s[low].price<=k.price && high>low) low++;
		swap(s,high,low);
	}
	s[low]=k;
	while(s[low].price==s[low-1].price) low--;
	quicksort(s,l,low-1);
	quicksort(s,high+1,h);
}

void sort(farmer *s,int n){
	quicksort(s,0,n-1);
}

int main(){
	ofstream fout("milk.out");
	ifstream fin("milk.in");
	int N,M;
	fin>>N>>M;
	farmer *s=new farmer[M];
	for(int i=0;i<M;i++) 
		fin>>s[i].price>>s[i].amount;
	sort(s,M);
	/*
	for(int i=0;i<M;i++)
		fout<<s[i].price<<' '<<s[i].amount<<endl;
		*/
	int i=0,money=0;
	while(N>s[i].amount){
		N-=s[i].amount;
		money+=s[i].amount*s[i].price;
		i++;
	}
	money+=N*s[i].price;
	fout<<money<<endl;
	delete [] s;

	fout.close();
	fin.close();

	return 0;
}