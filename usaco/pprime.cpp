/*
PROG:pprime
ID:dddd1021
LANG:C++
*/

#include <fstream>
#include <cmath>
using namespace std;

ofstream fout("pprime.out");
ifstream fin("pprime.in");

bool prime(int n){
	for(int i=2;i<sqrt(n)+1;i++){
		if (n%i==0) return false;
	}
	return true;
}

void swap(int &a,int &b){
	int t=a;
	a=b;
	b=t;
}

void quicksort(int *a,int first,int last){
	if (first>=last) return;
	int k=a[first],f=first,l=last;
	while(f<l){
		while(a[l]>k &&f<l) l--;
			swap (a[f],a[l]);
		while(a[f]<=k && f<l) f++;
			swap (a[f],a[l]);
	}
	a[f]=k;
	//while(a[f-1]==a[f]) f--;
	quicksort(a,first,f-1);
	quicksort(a,l+1,last);
}

int main(){
	int a,b;
	fin>>a>>b;
	
	int s[8];
	int ans[2000];
	int n,num,pos,cnt=0;
	for(int i=0;i<10000;i++) {
		//if (i%10==2 || i%10==5) continue;
		n=i,pos=0;
		while(n>0){
			s[pos++]=n%10;
			n/=10;
		}
		num=0;n=i;
		for(int j=1;j<pos;j++){
			num=num*10+s[j];
			n*=10;
		}
		//n/=10;
		n=n+num;
		/*
		for(int j=0;j<pos*2-1;j++)
			n=s[j]+n*10;
			*/
		if (prime(n)) ans[cnt++]=n;

	}
	ans[cnt++]=11;
	//fout<<"n:"<<cnt<<endl;
	//fout<<ans[cnt-1];
	quicksort(ans,0,cnt-1);
	for(int i=0;i<cnt;i++) 
		if (a<= ans[i] && ans[i]<=b) 
			fout<<ans[i]<<endl;

	fout.close();
	fin.close();
	
	return 0;
}