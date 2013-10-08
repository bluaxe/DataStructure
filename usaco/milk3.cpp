/*
PROG:milk3
ID:dddd1021
LANG:C++
*/

#include<fstream>
using namespace std;

int qa[10000],qb[10000],qc[10000];

void pour(int &a,int &b,int B){
	if (a+b>B) {
		a-=B-b;
		b=B;
	}else {
		b=a+b;
		a=0;
	}
}

bool h[1000000];
bool ans[30];

int main(){
	ofstream fout("milk3.out");
	ifstream fin("milk3.in");
	int A,B,C;
	fin>>A>>B>>C;

	qa[0]=0,qb[0]=0,qc[0]=C;
	h[C]=true;

	int f=-1,t=0;
	while(f<t){
		f++;
		int a=qa[f],b=qb[f],c=qc[f];
		pour(a,b,B);
		if (!h[a*10000+b*100+c]){
			t++;
			qa[t]=a,qb[t]=b,qc[t]=c;
			h[a*10000+b*100+c]=true;
		}
		a=qa[f],b=qb[f],c=qc[f];
		pour(a,c,C);
		if (!h[a*10000+b*100+c]){
			t++;
			qa[t]=a,qb[t]=b,qc[t]=c;
			h[a*10000+b*100+c]=true;
		}
		a=qa[f],b=qb[f],c=qc[f];
		pour(b,a,A);
		if (!h[a*10000+b*100+c]){
			t++;
			qa[t]=a,qb[t]=b,qc[t]=c;
			h[a*10000+b*100+c]=true;
		}
		a=qa[f],b=qb[f],c=qc[f];
		pour(b,c,C);
		if (!h[a*10000+b*100+c]){
			t++;
			qa[t]=a,qb[t]=b,qc[t]=c;
			h[a*10000+b*100+c]=true;
		}
		a=qa[f],b=qb[f],c=qc[f];
		pour(c,b,B);
		if (!h[a*10000+b*100+c]){
			t++;
			qa[t]=a,qb[t]=b,qc[t]=c;
			h[a*10000+b*100+c]=true;
		}
		a=qa[f],b=qb[f],c=qc[f];
		pour(c,a,A);
		if (!h[a*10000+b*100+c]){
			t++;
			qa[t]=a,qb[t]=b,qc[t]=c;
			h[a*10000+b*100+c]=true;
		}
	}

	int res[30];
	for(int i=0;i<=t;i++){
		if (qa[i]==0){ 
			ans[qc[i]]=true;
		}
	}
	
	int cnt=0;
	for(int i=0;i<30;i++)
		if (ans[i]) res[cnt++]=i;

	fout<<res[0];
	for(int i=1;i<cnt;i++)
		fout<<' '<<res[i];
	fout<<endl;

	fout.close();
	fin.close();

	return 0;
}