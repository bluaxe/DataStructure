/*
PROG:spath
ID:ddd
话说数据量挺小的,纠结要不要spfa
*/

#include<fstream>
#define INF 0x7fffffff;
using namespace std;
const int MaxE(200);
const int MaxV(50);

struct Edge{
	int x,w,fa;
	Edge(int a=0,int weight=0,int f=0):x(a),w(weight),fa(f){} 
};

Edge E[MaxE ];
int size=0,pos[MaxV];

void addEdge(int a,int b,int w){
	int i=size++;
	E[i]=Edge(b,w,pos[a]);
	pos[a]=i;
}

bool inQ[MaxV];
int Q[100000];
int dis[MaxV];

void init(){for(int i=0;i<MaxV;i++) {pos[i]=-1;dis[i]=INF;}}

int main(){
	ofstream fout("spath.out");
	ifstream fin("spath.in");
	init();
	int n,m,start,end;
	fin>>n>>m>>start>>end;
	int a,b,w;
	for(int i=0;i<m;i++) {
		fin>>a>>b>>w;
		addEdge(a,b,w);
	}

	dis[start]=0;
	Q[0]=start;
	inQ[start]=true;
	int f=-1,t=0;
	while(f<t){
		f++;
		for(int p=pos[Q[f]];p!=-1;p=E[p].fa){
			if (dis[Q[f]]+E[p].w<dis[E[p].x]){
				dis[E[p].x]=E[p].w+dis[Q[f]];
				if (!inQ[E[p].x]){
					Q[++t]=E[p].x;
					inQ[E[p].x]=true;
				}
			}
		}
		inQ[Q[f]]=false;
	}

	fout<<dis[end]<<endl;
	
	fout.close();
	fin.close();

	return 0;
}