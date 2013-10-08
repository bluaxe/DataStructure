/*
PROG:castle
ID:dddd1021
LANG:C++
*/

#include<fstream>
using namespace std;

int X,Y;
int *wall;
int *comp;

void get_aj(int *aj,int p){
	int w=wall[p];
	for(int i=0;i<4;i++){
		aj[i]=(w%2);
		w/=2;
	}
	aj[0]=(!aj[0])?p-1:-1;
	aj[1]=(!aj[1])?p-X:-1;
	aj[2]=(!aj[2])?p+1:-1;
	aj[3]=(!aj[3])?p+X:-1;
}

void find(int p){
	int new_node=1;
	int aj[4]={-1};
	while(new_node!=0){
		new_node=0;
		for(int i=0;i<X*Y;i++){
			if (comp[i]!=-2) continue;
			comp[i]=p;
			get_aj(aj,i);
			for(int j=0;j<4;j++){
				if (aj[j]>=0 && comp[aj[j]]==-1) {
					comp[aj[j]]=-2;					
					new_node++;				
				}
			}
		}
	}
}

int main(){
	ofstream fout("castle.out");
	ifstream fin("castle.in");

	fin>>X>>Y;

	wall =new int[X*Y];
	for(int i=0;i<X*Y;i++) fin>>wall[i];
	/*
	for(int i=0;i<Y;i++){
		for(int j=0;j<X;j++)
			fout<<wall[i*X+j];
		fout<<endl;
	}
	*/
	
	comp =new int[X*Y];
	for(int i=0;i<X*Y;i++) comp[i]=-1;
	for(int i=0;i<X*Y;i++){
		if (comp[i]==-1){
			comp[i]=-2;
			find(i);
		}
	}

	int * capa=new int [X*Y];
	for(int i=0;i<X*Y;i++) capa[i]=0;
	for(int i=0;i<X*Y;i++) capa[comp[i]]++;
	int rooms=0,mcapa=0;
	for(int i=0;i<X*Y;i++) if (capa[i]>0) rooms++;	
	for(int i=0;i<X*Y;i++) if (capa[i]>mcapa) 	mcapa=capa[i];

	fout<<rooms<<endl<<mcapa<<endl;

	int max=0,max_x,max_y;
	char oren;
	for(int x=0;x<X;x++){
		for(int y=Y-1;y>=0;y--){
		if ( y>0 && comp[y*X+x]!=comp[y*X+x-X]){
			if (capa[comp[y*X+x]]+capa[comp[y*X+x-X]]>max){
				max=capa[comp[y*X+x]]+capa[comp[y*X+x-X]];
				max_x=x,max_y=y,oren='N';
			}
		}
		if (X!=x+1 && comp[y*X+x]!=comp[y*X+x+1]){
			if (capa[comp[y*X+x]]+capa[comp[y*X+x+1]]>max){
				max=capa[comp[y*X+x]]+capa[comp[y*X+x+1]];
				max_x=x,max_y=y,oren='E';
			}
		}
		}
	}
	fout<<max<<endl<<max_y+1<<' '<<max_x+1<<' '<<oren<<endl;


	fout.close();
	fin.close();

	return 0;
}

