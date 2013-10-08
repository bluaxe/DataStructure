/*
PROG:packrec
ID:dddd1021
LANG:C++
*/

#include<fstream>
#include<iostream>
using namespace std;

ofstream fout("packrec.out");
ifstream fin("packrec.in");

int width,height,area,min_a=10000,cnt=0;
int minimum[1000][3]={0};

void process(int *x,int *y){
	//type 1
	width=0;height=0;
	for(int i=0;i<4;i++){
		width+=x[i];
		if (y[i]>height) height=y[i];
	}
	if (width*height <= min_a) {
		min_a=height*width;
		minimum[cnt][0]=min_a;
		minimum[cnt][1]=width;
		minimum[cnt++][2]=height;
	}

	//type 2
	for(int bottom=0;bottom<4;bottom++){
		int upper_width=0,upper_height=0;

		for(int i=0;i<4;i++) if (i!=bottom) upper_width+=x[i];
		width=x[bottom]>upper_width?x[bottom]:upper_width;

		for(int i=0;i<4;i++) if (i!=bottom && y[i]>upper_height) upper_height=y[i];
		height=upper_height+y[bottom];

		if (width*height <= min_a) {
			min_a=height*width;
			minimum[cnt][0]=min_a;
			minimum[cnt][1]=width;
			minimum[cnt++][2]=height;
		}
	}

	//type 3
	for(int bottom=0;bottom<4;bottom++){
		for(int right=0;right<4;right++){
			if (right==bottom) continue;
			int upper_width=0,upper_height=0;

			for(int i=0;i<4;i++) if (i!=bottom && i!=right) upper_width+=x[i];
			width=(x[bottom]>upper_width?x[bottom]:upper_width)+x[right];

			for(int i=0;i<4;i++) if (i!=bottom && i!=right  && y[i]>upper_height) upper_height=y[i];
			upper_height+=y[bottom];
			height=y[right]>upper_height?y[right]:upper_height;

			if (width*height <= min_a) {
				min_a=height*width;
				minimum[cnt][0]=min_a;
				minimum[cnt][1]=width;
				minimum[cnt++][2]=height;
			}
		}
	}

	//type 4
	for(int left=0;left<4;left++){
		for(int right=0;right<4;right++){
			if (right==left) continue;
			int inner_width=0,inner_height=0;

			for(int i=0;i<4;i++) if (i!=left && i!=right && x[i]>inner_width) inner_width=x[i];
			width=x[left]+inner_width+x[right];

			for(int i=0;i<4;i++) if (i!=left && i!=right) inner_height+=y[i];
			height=y[left]>y[right]?y[left]:y[right];
			height=height>inner_height?height:inner_height;

			if (width*height <= min_a)  {
				min_a=height*width;
				minimum[cnt][0]=min_a;
				minimum[cnt][1]=width;
				minimum[cnt++][2]=height;
			}
		}
	}

	//type 5 好像 和 4一样啊！！

	//type 6
	for(int one=0;one<4;one++){
		for(int two=0;two<4;two++){
			if (two==one) continue;
			for(int three=0;three<4;three++){
				if (three==one || three ==two) continue;
				for(int four=0;four<4;four++){
					if (four==one || four==two || four==three) continue;
					int width1,width2,height1,height2;
					width1=x[one]+x[two];
					width2=x[three]+x[four];
					width=width1>width2?width1:width2;

					if (x[one]>x[three] && x[two]<x[four] &&y[one]<y[two] &&y[three]>y[four]) {
						height1=y[one]+y[three];
						height2=y[two]+y[four];
						height=height1>height2?height1:height2;
					}
					else{
						height1=y[one]>y[two]?y[one]:y[two];
						height2=y[three]>y[four]?y[three]:y[four];
						height=height1+height2;
					}
					if (width*height <= min_a)  {
						min_a=height*width;
						minimum[cnt][0]=min_a;
						minimum[cnt][1]=width;
						minimum[cnt++][2]=height;
					}
					/*
					if (width*height==36) {
						fout<<endl<<width<<' '<<x[one]+x[two]<<' '<<width2<<' '<<height<<' '<<height1<<' '<<height2;
						fout<<endl<<one<<' '<<two<<' '<<three<<' '<<four<<endl;
						for(int i=0;i<4;i++) {
							fout<<x[i]<<' '<<y[i]<<endl;
						}
					}
					*/
				}
			}
		}
	}

}

int main(){
	int rec[4][2],x[4],y[4];
	for(int i=0;i<4;i++) 
		fin>>rec[i][0]>>rec[i][1];
	for(int i=0;i<16;i++){
		int rotate[4]={(i&8)/8,(i&4)/4,(i&2)/2,i&1};
		for(int j=0;j<4;j++) {
			x[j]=rec[j][rotate[j]];
			y[j]=rec[j][1-rotate[j]];
		}
		process(x,y);
	}
	
	fout<<min_a<<endl;//min_area

	for(int i=0;i<cnt;i++){
		if (minimum[i][0]!=min_a) continue;
		if (minimum[i][1]>minimum[i][2]) {
			int t=minimum[i][1];
			minimum[i][1]=minimum[i][2];
			minimum[i][2]=t;
		}
	}
	for(int i=0;i<cnt;i++){
		if (minimum[i][0]!=min_a) continue;
		for(int j=i;j<cnt;j++){
			if (minimum[j][0]!=min_a) continue;
			if (minimum[j][1]<minimum[i][1]) {
				int t=minimum[i][1];
				minimum[i][1]=minimum[j][1];
				minimum[j][1]=t;
				t=minimum[i][2];
				minimum[i][2]=minimum[j][2];
				minimum[j][2]=t;
			}
		}
	}
	bool widths[51]={false};
	for(int i=0;i<cnt;i++){
		if (minimum[i][0]!=min_a) continue;
		if (widths[minimum[i][1]]) continue;
		fout<<minimum[i][1]<<' '<<minimum[i][2]<<endl;
		widths[minimum[i][1]]=true;
	}

	fout.close();
	fin.close();

	return 0;
}