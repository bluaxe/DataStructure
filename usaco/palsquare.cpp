/*
ID:dddd1021
PROG:palsquare
LANG:C++
*/
#include<fstream>
#include<cstring>
using namespace std;
int B;
char res[18];
void change(int n){
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
    ofstream fout("palsquare.out");
    ifstream fin("palsquare.in");
    fin>>B; 
	char result[18];
    for(int i=1;i<300;++i){
        change(i*i);
        if (pal()) {
			strcpy(result,res);
			change(i);
			for(int j=strlen(res)-1;j>=0;j--) fout<<res[j];
			fout<<' '<<result<<endl;
		}
    }
}
