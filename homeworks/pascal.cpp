#include<fstream>
#include<cstring>
using namespace std;

int stack[2000]={-1};
bool match=true;
int head=0;

void Push(char *str){
	if (strcmp(str,"begin")==0)
		stack[head] = 0;
	else if (strcmp(str,"if")==0)
		stack[head] = 1;
	else if (strcmp(str,"then")==0)
		stack[head] = 2;
	head ++;
}

void pop(char *str){
	if (head!=0) head --;
	else {
		match=false;
		return;
	}
	if (strcmp(str,"then")==0 && stack[head] == 1) return;
	else if (strcmp(str,"else")==0 && stack[head] == 2) return;
	else if (strcmp(str,"end")==0 && stack[head] == 0) return;
	match = false;
}

int main(){
	ifstream fin("pascal.in");
	ofstream fout("pascal.out");

	char str[100];
	while (fin >> str){
		if (strcmp(str,"begin")==0 || strcmp(str,"if")==0) Push(str);
		else if (strcmp(str,"then")==0) {
			pop(str);
			Push(str);
		}
		else if (strcmp(str,"else")==0 || strcmp(str,"end")==0) pop(str);
	}
	if (match && head==0)
		fout<<"Match!";
	else
		fout << "Error!";
	fin.close();
	fout.close();
}
