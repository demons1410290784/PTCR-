void ff(int ch)
{    int i,j;
     i=int((ch-1)/4);
     j=(ch-1)%4;
     codd(i,j);
}

void codd(int nb,char da)
{	int i,j,k,l;
	unsigned char asd[2][3]={0,1,1,0,0,1};
	for(l=0;l<2;l++) {
	  for(i=0;i<4;i++) {
	    for(j=0;j<35;j++) 	outa1(0);
				outa1(1);
	      for(j=0;j<8;j++)
		 for(k=0;k<3;k++) outa1( asd[(nb>>j)&1][k]);
	      for(j=0;j<4;j++)
		 for(k=0;k<3;k++) outa1( asd[(da>>j)&1][k]);
		}
		outa1(0);
		}
}

/*Rosc=220k imax=6400, imin=32700  */
/*Rosc=100k imax=3200, imin=32700  */
void outa1(int j)
{	int ii;
	D37a=(D37a&0xfe)|j;
	outportb(c,D37a^013);
	for(ii=0;ii<fshe_yanshi;ii++);
}
