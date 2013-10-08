/*
PROG:sprime
ID:dddd1021
LANG:C++
*/

#include<fstream>
#include<memory.h>
#include<cmath>
using namespace std;

ofstream fout("sprime.out");
ifstream fin("sprime.in");

int b=1000000,length;
bool *prime=new bool[b+6];

int first[4]={2,3,5,7},last[4]={1,3,7,9};

int ans[8];
int result[1000],cnt=0;

bool isP(int n){
	if (n<b){
		return prime[n];
	}
	else 
		for(int i=2;i<sqrt(n)+1;i++) {
			if (!prime[i]) continue;
			if (n%i==0)	return false;
		}
	return true;
}

void judge(){
	int n;
	for(int l=2;l<=length;l++){
		n=0;
		for(int i=0;i<l;i++) n=n*10+ans[i];
		if (!isP(n)) return;
	}
	result[cnt++]=n;
}

void process(int n){
	if (n==-1) {
		judge();
		return;
	}
	else if(n==0){
		for(int i=0;i<4;i++){
			ans[n]=first[i];
			process(n-1);
		}
	}
	else 
	for(int i=0;i<4;i++){
		ans[n]=last[i];
		process(n-1);
	}
}

int main(){
	memset(prime,true,b+7);
	prime[1]=false;
	
	for(int i=1;i*6<=b;i++) {
		prime[i*6]=false;
		prime[i*6+2]=false;
		prime[i*6+3]=false;
		prime[i*6+4]=false;
	}
	unsigned int t1,t2,j;
	for(int i=0;i*6<sqrt(b);++i){
		t1=i*6+1;
		if (prime[t1]){
			for(j=t1,t2=j*t1;t2<=b;++j,t2=j*t1){
				if (prime[t2]) prime[t2]=false;
			}
		}
		t1=i*6+5;
		if (prime[t1]){
			for(j=t1,t2=j*t1;t2<=b;++j,t2=j*t1){
				if (prime[t2]) prime[t2]=false;
			}
		}
	}

	fin>>length;
	process(length-1);
	//≈≈–Ú∞°
	for(int i=0;i<cnt;i++)
		for(int j=i;j<cnt;j++)
			if (result[j]<result[i]){
				int t=result[i];
				result[i]=result[j];
				result[j]=t;
			}
	for(int i=0;i<cnt;i++) fout<<result[i]<<endl;


	//for(int i=0;i<b;i++) if (prime[i]) fout<<i<<endl;
	//delete [] prime;

	fout.close();
	fin.close();

	return 0;
}