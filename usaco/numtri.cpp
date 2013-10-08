/*
PROG:numtri
ID:dddd1021
LANG:C++
*/

#include <fstream>
using namespace std;

int v[600000];
int m[600000];
int x[600000];
int n;

int main(){
	ofstream fout("numtri.out");
	ifstream fin("numtri.in");
	fin>>n;
	for(int i=0;i<n*(n+1)/2;i++) 
		fin>>v[i+1];
	int pos=1;
	for(int i=1;i<=n;i++)
		for(int j=0;j<i;j++)
			x[pos++]=i;
	//for(int i=0;i<=n*(n+1)/2;i++) fout<<v[i];
	int left,right;
	for(int i=1;i<=n*(n+1)/2;i++) {
		if (x[i-x[i]]==x[i]-1) left=m[i-x[i]]; else left=0;
		if (x[i-x[i]+1]==x[i]-1) right=m[i-x[i]+1]; else right=0;
		m[i]=((left>right?left:right)+v[i]);
	}

	int max=0;
	for(int i=n*(n-1)/2+1;i<=n*(n+1)/2;i++)
		if (m[i]>max) max=m[i];
	fout<<max<<endl;
	
	fout.close();
	fin.close();

	return 0;
}