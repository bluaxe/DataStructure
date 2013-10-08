/*
PROG:crypt1
ID:dddd1021
LANG:C++
*/

#include<fstream>
using namespace std;

int main(){
	ofstream fout("crypt1.out");
	ifstream fin("crypt1.in");
	int N;
	fin>>N;
	bool set[10]={false};
	int temp;
	for(int i=0;i<N;i++){
		fin>>temp;
		set[temp]=true;
	}
	int num1,result,total=0;
	for(int i=1;i<10;i++){
		if (!set[i]) continue;

		for(int j=0;j<10;j++){
			if (!set[j]) continue;

			for(int k=0;k<10;k++){
				if (!set[k]) continue;

				num1=i*100+j*10+k;
				for(int p=1;p<10;p++){
					if (!set[p]) continue;
					if (p*num1>999) continue;
					if (!set[p*num1/100] || !set[(p*num1/10)%10] || !set[p*num1%10]) continue;

					for(int q=0;q<10;q++){
						if (!set[q]) continue;
						if (q*num1>999) continue;
						if (!set[q*num1/100] || !set[(q*num1/10)%10] || !set[q*num1%10]) continue;
						result=num1*(p*10+q);
						if (result>9999) continue;
						if (set[result/1000] && set[(result/100)%10] && set[(result/10) %10 ] && set[result%10]) {
							//fout<<num1<<endl<<p*10+q<<endl;
							//fout<<result<<endl;
							total++;
						}
					}
				}
			}
		}
	}
	fout<<total<<endl;

	fout.close();
	fin.close();

	return 0;
}