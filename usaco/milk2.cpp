/*
ID:dddd1021
PROG:milk2
LANG:C++
*/

#include<fstream>
using namespace std;

int main(){
	ofstream fout("milk2.out");
	ifstream fin("milk2.in");

	int N,begin,end,max=0,min=1000000;
	bool m[1000000]={false};

	fin>>N;
	for (int i=0;i<N;i++){
		fin>>begin>>end;
		for(int j=begin;j<end;j++) m[j]=true;
		if (begin<min) min=begin;
		if (end>max) max=end;
	}

	int t=0,t_no=0,p=min;
	while(p<max+1){
		int start=p;
		while(m[p]) p++;
		if (p-start>t) t=p-start;
		if (p==end) break;
		start=p;
		while(!m[p] && p<max+1) p++;
		if (p-start>t_no) t_no=p-start;
	}

	fout<<t<<' '<<t_no<<endl;

	return 0;
}