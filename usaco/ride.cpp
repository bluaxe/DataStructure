/*
ID: dddd1021
PROG: ride
LANG: C++
*/

#include<fstream>
using namespace std;
int main() {
    ifstream fin("ride.in");
    ofstream fout("ride.out");
    char comet[7],group[7];
    fin>>comet>>group;
    int i=0,pc=1,pg=1;
    while(comet[i]!='\0'){
        pc*=(comet[i++]-'A'+1);
    }
    i=0;
    while(group[i]!='\0'){
        pg*=(group[i++]-'A'+1);
    }
    if ((pc%47)==(pg%47)){
        fout<<"GO"<<endl;
    }
    else
    {
        fout<<"STAY"<<endl;
    }
	return 0;
}
