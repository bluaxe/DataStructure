/*
ID:dddd1021
PROG:transform
LANG:C++
*/

#include <fstream>
using namespace std;
int N;
int r(char **a,int i,int j,int n){
	switch(n){
	case 1:
		return a[N-1-j][i];
	case 2:
		return a[N-1-i][N-1-j];
	case 3:
		return a[j][N-1-i];
	case 4:
		return a[i][N-1-j];
	case 5:
		return 0;
	case 6:
		return a[i][j];
	case 7:
		return r(a,i,N-1-j,1);
	case 8:
		return r(a,i,N-1-j,2);
	case 9:
		return r(a,i,N-1-j,3);

	}
}
bool equal(char **a,char **b,int n){
	int t;
	for(int i=0;i<N;i++){
		for(int j=0;j<N;j++){
			t=r(a,i,j,n);
			if (t!=b[i][j]) return false;
		}
	}
	return true;
}

int main(){
	ofstream fout("transform.out");
	ifstream fin("transform.in");
	fin>>N;
	char **before=new char *[N];
	char **after=new char *[N];
	for(int i=0;i<N;i++){
		before[i]=new char[N+1];
		fin>>before[i];
	}
	for(int i=0;i<N;i++){
		after[i]=new char[N+1];
		fin>>*(after+i);
	}
	int i;
	for(i=1;i<10;i++){
		if (equal(before,after,i)) break;
	}
	if (i==10) i=7;
	else if (i>6) i=5;
	fout<<i<<endl;
	for(int i=0;i<N;i++){
		delete [] before[i];	
		delete [] after[i];	
	}
	delete [] before;
	delete [] after;

    return 0;
}