/*
PROG:clocks
ID:ddd1021
LANG:C++
*/

#include<fstream>
using namespace std;

ofstream fout("clocks.out");
ifstream fin("clocks.in");

int M[9][9]={
	1,1,0,1,1,0,0,0,0,
	1,1,1,0,0,0,0,0,0,
	0,1,1,0,1,1,0,0,0,
	1,0,0,1,0,0,1,0,0,
	0,1,0,1,1,1,0,1,0,
	0,0,1,0,0,1,0,0,1,
	0,0,0,1,1,0,1,1,0,
	0,0,0,0,0,0,1,1,1,
	0,0,0,0,1,1,0,1,1,
};

int c[9]={0};
int ac[9]={0};
int answer[9]={0};
int mini=30;

void check(int n){
	int ans[9]={0};
	int len=0;
	while(n>0){
		ans[len]=n%10-1;
		if (ans[len]<0 || ans[len++]>3 ) return ;
		n/=10;
	}
	//for(int j=0;j<len;j++) fout<<ans[j]<<' ';
	//fout<<endl;
	for(int i=0;i<9;i++) ac[i]=c[i];
	for(int i=0;i<9;i++){
		for(int j=0;j<9;j++){
			ac[j]=(ac[j]+ans[i]*M[i][j])%4;
		}
	}
	int cnt=0;
	for(int i=0;i<9;i++) {
		if (ac[i]!=3) return ;
		cnt+=ans[i];
	}
	if (cnt<mini){
		mini=cnt;
		for(int i=0;i<9;i++) answer[i]=ans[i];
	}
}

void process(int *num,int n){
	if (n<0) {
		int pattern=0;
		for(int i=0;i<9;i++) pattern=pattern*10+num[i];
		check(pattern);
		return ;
	}
	for(num[n]=1;num[n]<5;num[n]++){
		process(num,n-1);
	}
	return ;
}

int main(){
	for(int i=0;i<9;i++) {
		fin>>c[i];
		c[i]=c[i]/3-1;
		//fout<<c[i];
	}
	int num[9];
	process(num,8);

	//fout<<ans[n-1]+1;
	bool first=true;
	for(int i=0;i<9;i++) 
		for(int j=0;j<answer[i];j++)
			if(first) {
				fout<<i+1;
				first=false;
			}
			else fout<<' '<<i+1;
	fout<<endl;

	fout.close();
	fin.close();

	return 0;
}