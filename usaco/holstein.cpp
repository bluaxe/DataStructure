/*
PROG:holstein
ID:dddd1021
LANG:C++
*/

#include<fstream>
using namespace std;

int V,*v,G,**g;

inline int pow(){
    int t=1,p=G;
    while(p>0){t*=2;p--;}
    return t;
}

inline void getc(int *a,int k){
    for(int i=0;i<G;i++){
        a[i]=k%2;
        k/=2;
    }
}

int main(){
    ofstream fout("holstein.out");
    ifstream fin("holstein.in");

    fin>>V;
    v=new int[V];
    for(int i=0;i<V;i++) fin>>v[i];

    fin>>G;
    g=new int *[G];
    for(int i=0;i<G;i++)
    {
        g[i]=new int [V];
        for(int j=0;j<V;j++)
            fin>>g[i][j];
    }

    int times=pow(),*c=new int[G],*res=new int [V],i,j,k;

	int ans[100][2]={0},cnt=0,mini=G,n;
    for(k=1;k<times;k++){
            getc(c,k);
            for(i=0;i<V;i++) res[i]=0;
            for(i=0;i<G;i++)
            if (c[i])
                for(j=0;j<V;j++){
                    res[j]+=g[i][j];
                }

			for(i=0;i<V;i++) if (res[i]<v[i]) break;
			if (i==V) {
				n=0;
				for(i=0;i<G;i++) if (c[i]) n++;
				/*
				for(i=0;i<G;i++) fout<<c[i]<<' ';
				fout<<n;
				fout<<endl;
				*/
				if (n<=mini){
					mini=n;
					ans[cnt][0]=k,ans[cnt][1]=n;
					cnt++;
				}
			}
			/*
            for(int i=0;i<V;i++) fout<<res[i]<<' ';
            fout<<endl;
			*/
	}
    //for(int i=0;i<V;i++) fout<<g[G-1][i]<<endl;
	//i=0;
	int pos=-1,*max=new int [G];
	for(i=0;i<G;i++) max[i]=0;
	for(i=0;i<cnt;i++){
		if (ans[i][1]==mini) {
			getc(c,ans[i][0]);
			for(j=0;j<G;j++) if (c[j]<max[j]) break;
			if (j==G) {
				pos=i;
				for(j=0;j<G;j++) max[j]=c[j];
			}
			/*
			for(j=0;j<G;j++) fout<<c[j]<<' ';
			fout<<endl;
			*/		
		}
	}
	fout<<mini;
	for(i=0;i<G;i++) if (max[i]) fout<<' '<<i+1;
	fout<<endl;

    delete [ ]v;
    for(int i=0;i<G;i++) delete [] g[i];
    delete [] g;
    delete [] c;
    delete []res;

    fout.close();
    fin.close();

    return 0;
}
