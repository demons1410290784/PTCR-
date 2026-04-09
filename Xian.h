#include"stdio.h"
#include"dos.h"
#include"graphics.h"
int ddtt,dlt;

#define UNI 1
#define BIP 0
#define SGL 1
#define DIF 0
#define N 500
float Resistance0;
unsigned char BC12=0;
unsigned char BC13=0;
unsigned char BC14=0;
typedef unsigned int WORD;
int NN;
float V_antn;

unsigned R0_sw0=0,R0_sw1=0;
unsigned PR_sw0=0,PR_sw1=0;
unsigned PR_sw[4]={0,0,0,0};

void codd12();
void outa12();

unsigned int fshe_yanshi1=30000;

int a=0x378,b=0x379,c=0x37a,D37a,D11=0;

unsigned char d378=0;

void codd12(int nb,char da)
{	int i,j,k,l;
	unsigned char asd[2][3]={0,1,1,0,0,1};
	for(l=0;l<2;l++) {
	for(i=0;i<4;i++) {
	   for(j=0;j<35;j++) outa12(0);
			     outa12(1);
	      for(j=0;j<8;j++)
		 for(k=0;k<3;k++) outa12( asd[(nb>>j)&1][k]);
	      for(j=0;j<4;j++)
		 for(k=0;k<3;k++) outa12( asd[(da>>j)&1][k]);
		}
		outa12(0);
		}
}

void outa12(int j)
{	unsigned int ii;
	D37a=(D37a&0xfe)|j;
	outportb(a,D37a);
	for(ii=0;ii<fshe_yanshi1;ii++);
}

void PTCR_sw(int ch1)
{  int i,j,l;

       l=ch1/16;
       ch1=ch1-l*16;

	if(l==1)codd12(4,1);
	else codd12(4,0);

			for(i=0;i<4;i++ )codd12(i,0);
			i=ch1/4;
			j=ch1-4*i;
			codd12(i,1<<j);
}


