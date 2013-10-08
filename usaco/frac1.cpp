/*
PROG:frac1
ID:dddd1021
LANG:C++
*/

#include<fstream>
using namespace std;

int N;
int num[40000][2];
int ans[40000][2];

void swap(int a,int b){
	int t1=num[b][0],t2=num[b][1];
	num[b][0]=num[a][0];
	num[b][1]=num[a][1];
	num[a][0]=t1;
	num[a][1]=t2;
}

void quicksort(int first,int last){
	if (first>=last) return;
	int f=first,l=last;
	int t1=num[f][0],t2=num[f][1];
	while(f<l){
		while((num[l][0]*t2-num[l][1]*t1)>0 && f<l) l--;
		swap(f,l);
		while((num[f][0]*t2-num[f][1]*t1)<=0 && f<l) f++;
		swap(f,l);
	}
	num[f][0]=t1;
	num[f][1]=t2;
	quicksort(first,f-1);
	quicksort(l+1,last);
}

int main(){
	ofstream fout("frac1.out");
	ifstream fin("frac1.in");
	fin>>N;
	int cnt=0;

	num[cnt][0]=0,num[cnt++][1]=1;
	
	for(int i=1;i<=N;i++){
		for(int j=1;j<i;j++){
			num[cnt][0]=j;
			num[cnt++][1]=i;
		}
	}
	num[cnt][0]=1,num[cnt][1]=1;

	quicksort(1,cnt);

	int min,minpos;
	for(int i=0;i<cnt;i++){
		min=num[i][0];
		minpos=i;
		while (num[i][0]*num[i+1][1]-num[i][1]*num[i+1][0]==0){
			if (num[i+1][0]<min){
				min=num[i+1][0];
				minpos=i+1;
			}
			i++;
		}
		fout<<num[minpos][0]<<'/'<<num[minpos][1]<<endl;
	}
	fout<<"1/1"<<endl;

	fout.close();	
	fin.close();

	return 0;
}