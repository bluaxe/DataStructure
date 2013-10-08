/*
ID: dddd1021
PROG: beads
LANG: C++
 */
#include <fstream>
using namespace std;
int main(){
    ofstream fout("beads.out");
    ifstream fin("beads.in");
    int N;
    fin>>N;
    char *array=new char[N];
    int *len=new int[N];
    int *back=new int[N];
    for (int i=0;i<N;i++){
        fin>>array[i];
    }
    char color;
    for(int i=0;i<N;i++){
       int next=(i+1)%N; 
	   int n=0;
       color=array[i];
	   n++;
       while (array[next]==color || array[next]=='w' || color=='w' ){
		   if (color=='w' && array[next]!='w') color=array[next];
            next=(next+1)%N;
			n++;
			if (n==N) break;
	   }
	   len[i]=n;
	   back[next]=(back[next]<n && array[i]!=array[next])?n:back[next];
    }

	int max=0;
    for (int i=0;i<N;i++){
        if (len[i]+back[i]>max) max=len[i]+back[i];
    }
	if (max>N) max=N;
	fout<<max<<endl;
	return 0;
};
