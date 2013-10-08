/*
ID:dddd1021
PROG:namenum
LANG:C++
*/
#include<fstream>
#include<cstring>
using namespace std;

ofstream fout("namenum.out");
ifstream fin("namenum.in");
ifstream dict("dict.txt");

long dictindex[26][26][26][26];

char input[13];
char output[13];
int len;

const char data[10][4]={"   ","   ","ABC","DEF","GHI","JKL","MNO","PRS","TUV","WXY"};

void getindex(){
	char word[13];
	char stag='A',tag='A',ttag='R',ftag='O';
	long pos;
	dict.seekg(0,ios::beg);
	for(int i=0;i<26;i++) for(int j=0;j<26;j++) for(int k=0;k<26;k++) dictindex[0][i][j][k]=0;
	dict>>word;
	
	while(!dict.eof()){
		while(word[0]==tag && !dict.eof()) {
			while(word[1]==stag && word[0]==tag&& !dict.eof()) {
				while(word[2]==ttag && word[1]==stag && word[0]==tag&& !dict.eof()) {
					while(word[3]==ftag && word[2]==ttag && word[1]==stag && word[0]==tag&& !dict.eof()) {
						pos=dict.tellg();
						dict>>word;
					}
					tag=word[0];
					stag=word[1];
					ttag=word[2];
					ftag=word[3];
					if(ftag-'A'>=0 && ftag-'A'<26 && ttag-'A'>=0 && ttag-'A'<26 && tag-'A'>=0 && tag-'A'<26 && stag-'A'>=0 && stag-'A'<26) 
						dictindex[tag-'A'][stag-'A'][ttag-'A'][ftag-'A']=pos;
				}
				//if(ttag-'A'>=0 && ttag-'A'<26) for(int i=0;i<26;i++) dictindex[tag-'A'][stag-'A'][ttag-'A'][i]=0;
			}
			
			//pos=dict.tellg();
			//dict>>word;
		}
		//if(tag-'A'>=0 && tag-'A'<26) for(int i=0;i<26;i++) dictindex[tag-'A'][stag-'A'][i]=0;
	}
	dict.clear();
}
int n=0;
void judge(){
	len=strlen(output);
	if (len>3 && dictindex[output[0]-'A'][output[1]-'A'][output[2]-'A'][output[3]-'A']==0) return;
	char word[13];
	if (len<4) dict.seekg(0);
	else dict.seekg(dictindex[output[0]-'A'][output[1]-'A'][output[2]-'A'][output[3]-'A']);
	while(!dict.eof()){
		dict>>word;
		if (len>3 &&(word[0]!=output[0] || word[1]!=output[1])) break;	
		//if (strlen(word)!=len) continue;
		if (strcmp(word,output)==0){
			n++;
			fout<<output<<endl;
			break;
		}
	}
	dict.clear();
}
void process(int cnt){
	if (input[cnt]=='\0'){
		judge();
		return;
	}
	for(int j=0;j<3;j++){
		output[cnt]=data[input[cnt]-'0'][j];
		process(cnt+1);
	}
}
int main(){
	
	getindex();
	fin>>input;
	process(0);
	if (n==0) fout<<"NONE"<<endl;
	return 0;
}