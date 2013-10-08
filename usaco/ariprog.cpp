/*
PROG:ariprog
ID:dddd1021
LANG:C++
*/

#include <fstream>
using namespace  std;

int N,M;
bool bis[250*250*9]={false};
int *bisnum,total=0;

inline bool judge(int start,int step){
	int n=0,num=start;
	while(++n<N){
		num+=step;
		if (!bis[num]) return false;
	}
	return true;
}

int main(){
	ofstream fout("ariprog.out");
	ifstream fin("ariprog.in");
	fin>>N>>M;
	M++;
	for(int i=0;i<M;i++)
		for(int j=i;j<M;j++)
			if (!bis[i*i+j*j]) {
				total++;
				bis[i*i+j*j]=true;
			}

	bisnum=new int[total*9];
	int n=0;
	for(int i=0;i<M*M*2;i++) 
		if (bis[i]) 
			bisnum[n++]=i;
	//for(int i=0;i<total;i++) fout<<bisnum[i]<<endl;
	int cnt=0;
	for(int step=1;step<M*M*2/N+1;step++){
		for(int pos=0;pos<total && bisnum[pos] + (N-1)*step <= bisnum[total-1];pos++){
			if (judge(bisnum[pos],step)){
				fout<<bisnum[pos]<<' '<<step<<"\n";
				cnt++;
			}
		}
	}
	if (cnt==0) fout<<"NONE"<<endl;
	
	delete [] bisnum;
	fout.close();
	fin.close();

	return 0;
}
