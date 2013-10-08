/*
PROG:kruskal
ID:ddd

*/

#include<fstream>
using namespace std;

int N,M;

int main(){
	ofstream fout("kruskal.out");
	ifstream fin("kruskal.in");
	fin>>N>>M;
	
	int **e=new int*[M];

	for(int i=0;i<M;i++) {
		e[i]=new int[3];
		fin>>e[i][0]>>e[i][1]>>e[i][2];
	}


	int minw=e[0][2],min_e=0;
	for(int i=0;i<M;i++) {
		if (e[i][2]<minw){
			minw=e[i][2];
			min_e=i;
		}
	}
	bool *s=new bool[N+1];
	bool *se=new bool[M];
	for(int i=0;i<N+1;i++) s[i]=false;
	for(int i=0;i<M;i++) se[i]=false;
	se[min_e]=true;
	s[e[min_e][0]]=true,s[e[min_e][1]]=true;

	int w=minw,v=2;
	while(v<N){
		minw=-1,min_e=-1;
		for(int i=0;i<M;i++){
			if (se[i]) continue;
			if ((s[e[i][0]] && !s[e[i][1]]) || (!s[e[i][0]] && s[e[i][1]])){
				if (minw==-1 || minw>e[i][2]){
					minw=e[i][2];
					min_e=i;
				}
			}
		}
		if (min_e!=-1){
			v++;
			w+=e[min_e][2];
			se[min_e]=true;
			s[e[min_e][0]]=true,s[e[min_e][1]]=true;
		}
	}

	fout<<w<<endl;

	for(int i=0;i<M;i++) delete [] e[i];
	delete [] e;
	delete [] s;

	fout.close();
	fin.close();

	return 0;
}