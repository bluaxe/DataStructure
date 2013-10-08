#include<fstream>
using namespace std;
int A(int m,int n){
	if (m==0) return n+1;
	else if (n==0 && m!=0) return A(m-1,1);
	else if (n!=0 && m!=0) return A(m-1,A(m,n-1));
}
int main(){
	ofstream fout("ackerman.out");
	ifstream fin("ackerman.in");
	int m,n;
	fin>>m>>n;
	fout<<A(m,n);
	fout.close();
	fin.close();
}
