/*
PROG:sort3
ID:dddd1021
LANG:C++
*/

#include<fstream>
using namespace std;

int n;
void swap(int *s,int a,int b){
	int t=s[a];
	s[a]=s[b];
	s[b]=t;
}

void quicksort(int *a,int first,int last){
	if (first>=last) return;
	int f=first,l=last;
	int k=a[first];
	while(f<l){
		while(a[l]>k && f<l) l--;
		swap(a,f,l);
		while(a[f]<=k && f<l) f++;
		swap(a,f,l);
	}
	a[f]=k;
	quicksort(a,first,f-1);
	quicksort(a,l+1,last);
}

int main(){
	ofstream fout("sort3.out");
	ifstream fin("sort3.in");
	fin>>n;
	int *a=new int[n],cnt=0;
	int *s=new int[n];
	for(int i=0;i<n;i++) {fin>>a[i];s[i]=a[i];}
	quicksort(s,0,n-1);
	//for(int i=0;i<n;i++) fout<<s[i]<<endl;
	for(int i=0;i<n;i++){
		if (a[i]!=s[i]){
			for(int j=i+1;j<n;j++){
				if (a[i]==s[j] && a[j]==s[i]) {
					cnt++;
					swap(a,i,j);
					break;
				}
			}
		}
	}
	for(int i=0;i<n;i++){
		if (s[i]!=1 && a[i]==1) cnt+=2;
	}
	fout<<cnt<<endl;

	fout.close();
	fin.close();

	return 0;

}