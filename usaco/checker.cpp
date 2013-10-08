/*
PROG:checker
ID:dddd1021
LANG:C++
*/

#include<fstream>
using namespace std;

int N,cnt=0;
int ans[100000][30],t[30];

bool x[30],y[60],z[60];

void go(int n){
	if (n==N) {
		for(int i=0;i<N;i++)
			ans[cnt][i]=t[i];
		cnt++;
		return;
	}
	for(int i=0;i<N;i++){
		if (x[i] || y[i-n+N] || z[n+i]) continue;
		y[i-n+N]=z[n+i]=x[i]=true;
		t[n]=i;
		go(n+1);
		y[i-n+N]=z[n+i]=x[i]=false;
	}

}

int main(){
	ofstream fout("checker.out");
	ifstream fin("checker.in");
	fin>>N;

	go(0);

	for(int i=0;i<3;i++){
		fout<<ans[i][0]+1;
		for(int j=1;j<N;j++)
			fout<<' '<<ans[i][j]+1;
		fout<<endl;
	}
	fout<<cnt<<endl;

	fout.close();
	fin.close();

	return 0;
}