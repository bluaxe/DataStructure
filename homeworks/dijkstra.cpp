/*
PROG:dijkstra
ID:ddd

*/

#include<fstream>
#define INF 0x7fffffff
using namespace std;
const int MaxE(60000);
const int MaxV(20000);

ofstream fout("dijkstra.out");
ifstream fin("dijkstra.in");

struct Edge{
	int x,w,fa;
	Edge(int a=0,int weight=0,int f=0):x(a),w(weight),fa(f){} 
};

Edge E[MaxE ];//边列表,用邻接表方式保存
int size=0,pos[MaxV];

void addEdge(int a,int b,int w){
	E[size++]=Edge(b,w,pos[a]);
	pos[a]=size-1;
}

int dis[MaxV];
int fa[MaxV];

struct QueueElement{
	int x,dis;
	QueueElement(int xx=0,int d=INF):x(xx),dis(d){}
};

QueueElement Queue[MaxV];
int QueuePos[MaxV];
int ss=0;

void enQueue(int x,int d){
	QueueElement p(x,d);
	int f,i;
	for(i=++ss;p.dis<Queue[f=i>>1].dis;i=f){
		Queue[i]=Queue[f];
		QueuePos[Queue[f].x]=i;
	}
	Queue[i]=p;
	QueuePos[p.x]=i;
}
void change(int x,int d){
	QueueElement p(x,d);
	int f,i;
	for(i=QueuePos[x];p.dis<Queue[f=i>>1].dis;i=f){
		Queue[i]=Queue[f];
		QueuePos[Queue[f].x]=i;
	}
	Queue[i]=p;
	QueuePos[p.x]=i;
}
int deQueue(){
	int x=Queue[1].x;
	QueueElement p=Queue[ss--];
	int f,i;
	for(i=1;(f=i<<1)<= ss;i=f){
		if (f+1<=ss && Queue[f+1].dis<Queue[f].dis) f++;
		if (Queue[f].dis<p.dis){
			Queue[i]=Queue[f];
			QueuePos[Queue[f].x]=i;
		}else break;
	}
	Queue[i]=p;
	QueuePos[p.x]=i;
	return x;
}

void init(){
	for(int i=0;i<MaxV;i++) {pos[i]=-1;dis[i]=INF;fa[i]=-1;}
	Queue[0]=QueueElement(0,0);
}

int path_len(int end){
	int cnt=0;
	while(end!=-1){
		end=fa[end];
		cnt++;
	}
	return cnt;
}

void print(int end){
	if (end!=-1){
		print(fa[end]);
		if (fa[end]!=-1) fout<<' ';
		fout<<end;
	}
}

int main(){
	init();

	int n,m,start,end;
	fin>>n>>m>>start>>end;

	int a,b,w;
	for(int i=0;i<m;i++) {
		fin>>a>>b>>w;
		addEdge(a,b,w);
	}

	dis[start]=0;
	int know_num=1,p,q;
	for(int i=1;i<n+1;i++) enQueue(i,dis[i]);

	while(know_num<n){
		q=deQueue();
		/*
		fout<<"deQ:"<<q<<endl;
		for(int i=1;i<n+1;i++) fout<<dis[i]<<' ';
		fout<<endl;
		*/
		for(p=pos[q];p!=-1;p=E[p].fa){
			if (dis[q]+E[p].w>0 && (dis[q]+E[p].w<dis[E[p].x] ||(path_len(q)+1<path_len(E[p].x) && dis[q]+E[p].w==dis[E[p].x] ) )){
				dis[E[p].x]=E[p].w+dis[q];
				fa[E[p].x]=q;
				change(E[p].x,dis[E[p].x]);
			}
		}
		know_num++;
	}
	if (dis[end]!=INF){
		fout<<dis[end]<<endl;
		print(end);
		fout<<endl;
	}
	else fout<<"INF"<<endl;
	
	fout.close();
	fin.close();

	return 0;
}
