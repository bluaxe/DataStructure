/*
ID:dddd1021
PROG:dualpal
LANG:C++
*/
#include<fstream>
#include<cstring>
using namespace std;
char res[50];
void change(int n,int B){
    int i=0,mo;
    while (n/B!=0){
		mo=n%B;
        res[i++]=(mo>9)?mo-10+'A':mo+'0';
        n/=B;
    }
    res[i++]=(n>9)?n-10+'A':n+'0';
    res[i]='\0';
}
bool pal(){
    int i=0,j;
    j=strlen(res)-1;
    while(res[i]==res[j] && i!=j){
		i++;
		j--;
	}
    if (i>=j) return true;
    else return false;
}

int main(){
    ofstream fout("dualpal.out");
    ifstream fin("dualpal.in");
	int N,S;
    fin>>N>>S;
	int i=0,n=S+1,cnt=0;
    while(i<N){
		cnt=0;
		for(int b=2;b<11;b++){
			change(n,b);
			if (pal()) {
				cnt++;
			}
			if (cnt>1) {
				i++;
				fout<<n<<endl;
				break;
			}
		}
		n++;
    }
}
