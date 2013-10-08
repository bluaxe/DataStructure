/*
PROG:calfflac
ID:dddd1021
LANG:C++
*/

#include <fstream>
using namespace std;

bool equal(char *s,int a,int b){
	int va = (s[a]-'A'<26)?s[a]-'A':s[a]-'a';
	int vb = (s[b]-'A'<26)?s[b]-'A':s[b]-'a';
	if (va==vb) return true;
	return false;
}

int process(char *s,int p,int Max){
	//if (s[p]<65 || s[p]>122 || (s[p]>90 && s[p]<97)) return 0;
	int left=(s[p]==s[p-1])?p-1:p,right=(s[p]==s[p+1])?p+1:p;
	while(equal(s,left,right) && left>=0 && right<Max){
		left--;
		right++;
		while((s[left]<65 || s[left]>122 || (s[left]>90 && s[left]<97)) && left>0) left--;
		while((s[right]<65 || s[right]>122 || (s[right]>90 && s[right]<97)) && right<Max) right++;
	}
	left++;
	right--;
	while(s[left]<65 || s[left]>122 || (s[left]>90 && s[left]<97)) left++;
	while(s[right]<65 || s[right]>122 || (s[right]>90 && s[right]<97)) right--;
	int cnt=0;
	for(int i=left;i<right+1;i++) 
		if ((s[i]>64 && s[i]<91) || (s[i]>96 &&s[i]<123)) 
			cnt++;
	return cnt;
}

int main(){
	ofstream fout("calfflac.out");
	ifstream fin("calfflac.in");
	char s[20000],temp;
	int len=0;
	while(!fin.eof()){
		temp=fin.get();
		//fout<<temp;
		s[len++]=temp;
	}
	//for(int i=0;i<len-1;i++) fout<<s[i];
	int t,max=0,pos;
	for(int i=0;i<len;i++) {
		t=process(s,i,len);
		if (t>max) {
			max=t;
			pos=i;
		}
	}
	fout<<max<<endl;
	//for(int i=pos-max/2;i<pos+max/2+1;i++) fout<<s[i];

	int left=(s[pos]==s[pos-1])?pos-1:pos,right=(s[pos]==s[pos+1])?pos+1:pos;
	while(equal(s,left,right) && left>=0 && right<len){
		left--;
		right++;
		while((s[left]<65 || s[left]>122 || (s[left]>90 && s[left]<97)) && left>0) left--;
		while((s[right]<65 || s[right]>122 || (s[right]>90 && s[right]<97)) && right<len) right++;
	}
	left++;
	right--;
	while(s[left]<65 || s[left]>122 || (s[left]>90 && s[left]<97)) left++;
	while(s[right]<65 || s[right]>122 || (s[right]>90 && s[right]<97)) right--;

	for(int i=left;i<right+1;i++) fout<<s[i];
	fout<<endl;

	fout.close();
	fin.close();

	return 0;
}