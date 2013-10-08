/*
PROG:barn1
ID:dddd1021
LANG:C++
*/

#include<fstream>
using namespace std;

int find(bool *stalls,int i,int j,int C){
	int max=0,k=i,t,pos=0;
	while(k<j+1){
		while(stalls[k]) k++;
		t=0;
		if (k>j) break;
		while(!stalls[k]) k++,t++;
		if (t>max && t<=C) {
			max=t;
			pos=k;
		}
	}
	for(i=0;i<max;i++,pos--){
		stalls[pos-1]=true;
	}
	return max;
}

int main(){
	ofstream fout("barn1.out");
	ifstream fin("barn1.in");
	int M,S,C;
	fin>>M>>S>>C;
	bool *stalls=new bool[S+1];
	for(int i=0;i<S+1;i++) stalls[i]=false;
	
	int t,max=S,min=0;
	for(int i=0;i<C;i++) {
		fin>>t;
		stalls[t]=true;
	}
	while (!stalls[min]) min++;
	while (!stalls[max]) max--;

	int N=max-min+1;
	C=S-C;
	while(M>1){
		C=find(stalls,min,max,C);
		N-=C;
		M--;
	}

	fout<<N<<endl;

	delete []stalls;

	fout.close();
	fin.close();

	return 0;
}