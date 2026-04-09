/*
**	FILENAME			RT.cpp
**
**	PURPOSE				此类可用于处理测试系统得到的温度、阻值等数据。
**						通过调用公式计算实验目标需要的PTCR重要参数，包
**						括温度系数、居里点等
*/

#include "stdafx.h"
#include "Ptcr.h"
#include "RT.h"
#include "math.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// 构造/析构
//////////////////////////////////////////////////////////////////////

//
//	构造函数：初始化参数
//
CRT::CRT()
{
	Initialization();
	ReadZeroResi=FALSE;
	m_DrawDotFlag==FALSE;
	m_DatOrRtFile=1;
}

//
//	析构函数
//
CRT::~CRT()
{

}

//
//	初始化函数
//
void CRT::Initialization()
{
	int i;

// WriteZero();
// ReadZero();
	for(i=0;i<NMBOFSPL;i++)
	{
		m_iEndDot[i]=0;
		m_iStartDot[i]=0;
		m_fRes25[i]=0;
		m_fTemCurie[i]=0;
		m_fResCurie[i]=0;
		m_fResMin[i]=0;
		m_fResMax[i]=0;
		m_fTemMin[i]=0;
		m_fTemMax[i]=0;
		m_fTemCoe10[i]=0;
		m_fCurieRange[i]=0;
		m_fResRatio[i]=0;
		m_fTemCoe25[i]=0;
		m_fTemCoe50[i]=0;
		m_fTemCur[i]=0;	
	}
	
	for(i=0;i<MAXOFSPL;i++)
	{
		xc[i]=0;
		yc[i]=0;
	}

	m_rtSave.Initialization();
}

//
//	获取居里点阻值（常数表示）
//
float CRT::GetRes25(int i)
{

	return m_fRes25[i];
}

//
//	获取最小阻值
//
float CRT::GetResMin(int i)
{
	return m_fResMin[i];
}

//
//	获取居里点阻值（指数表示）
//
float CRT::GetResCurie(int i)
{
	return m_fResCurie[i];
}

//
//	获取最大阻值
//
float CRT::GetResMax(int i)
{
	return m_fResMax[i];
}

//
//	获取阻值范围
//
float CRT::GetResRatio(int i)
{
	return m_fResRatio[i];
}

//
//	获取居里点温度
//
float CRT::GetTemCurie(int i)
{
	return m_fTemCurie[i];
}

//
//	获取阻值最小时温度
//
float CRT::GetTemMin(int i)
{
	return m_fTemMin[i];
}

//
//	获取阻值最大时温度
//
float CRT::GetTemMax(int i)
{
	return m_fTemMax[i];
}

//
//	获取温度系数α10/25
//
float CRT::GetTemCoe10(int i)
{
	return m_fTemCoe10[i];
}

//
//	获取温度系数α15/25
//
float CRT::GetTemCoe25(int i)
{
	return m_fTemCoe25[i];
}

//
//	获取温度系数α0/15
//
float CRT::GetTemCoe50(int i)
{
	return m_fTemCoe50[i];
}

//
//	获取温度范围
//
float CRT::GetCurieRange(int i)
{
	return m_fCurieRange[i];
}

//
//	计算温度系数α
//
float CRT::GetAlfa(int index, float T0, float T1)
{
	int i;
    //int jmin,jmax;
    float x,y,xr,yr;
    float Tju=0;
    float Alfa=0;              /*all R are log value*/

/*get Alfa*/
    Tju=m_fTemCurie[index];
    if(Tju>m_fTemMin[index])
	{
		x=Tju+T0;
		y=Tju+T1;
	}

    if( Tju==0 || y>=xc[m_iCount[index]-2] )
		Alfa=0;     /*can't calculate Alfa*/
    else
	{
		for(i=0;i<m_iCount[index];i++)
			if(xc[i]>x) 
				break;
	
		xr = GetR(i-1,x);
		
		for(i=0;i<m_iCount[index];i++)
			if(xc[i]>y) 
				break;
	
		yr = GetR(i-1,y);
		
		Alfa = (float) (2.303 * (yr-xr) * 100.0/(T1-T0));
	}

    return Alfa;

}

//
//	获取测定温度xc[i]附近t温度时的拟合阻值
//
float CRT::GetR(int i, float t)
{
	float a1,a2,a3,a,b,c;
    float r;



	if(i==0){
     if(xc[i+1]==xc[i])return yc[i];
	 else if((xc[i+1]-xc[i])<1)	{//温度间隔太小，直线拟合
		 a1 = (yc[i+1]-yc[i]) / (xc[i+1]-xc[i]);
//	     r=a1*(t-xc[i])/(xc[i+1]-xc[i]);
 	     	a2=yc[i]-a1*xc[i];
            r=a1*t+a2;
         return r;
	 }
	 else if((xc[i]-t)>20)	{//温度间隔太大，直线拟合
		 a1 = (yc[i+1]-yc[i]) / (xc[i+1]-xc[i]);
//	     r=a1*(t-xc[i])/(xc[i+1]-xc[i]);
	
 	     	a2=yc[i]-a1*xc[i];
     r=a1*t+a2;
     return r;
	 }
	}

	a1 = (yc[i+1]-yc[i]) / (xc[i+1]-xc[i]);
	if(yc[i+2]==0) 
		  a2 = (yc[i]) / (xc[i]);
    else
          a2 = (yc[i+2]-yc[i]) / (xc[i+2]-xc[i]);
    a3 = (a2-a1) / (xc[i+2]-xc[i+1]);

    a = a3;
    b = a1 - a3*(xc[i]+xc[i+1]);
    c = a3*xc[i]*xc[i+1] - a1*xc[i] + yc[i];
	
    r = a*t*t + b*t + c;	

    
	a=log10(m_rtSave.m_SpecialR);
	if(r>a)
		r=a;
    
	return r;
}

//
//	获取拟合阻值
//
float CRT::GetSpecialR(int i, float t,int index)
{
	float a1,a2,a3,a,b,c;
    float r;

	if(i==0){
		i=i+1; 
    	a1 = (yc[i+1]-yc[i]) / (xc[i+1]-xc[i]);
        a2 = (yc[i+2]-yc[i]) / (xc[i+2]-xc[i]);
        a3 = (a2-a1) / (xc[i+2]-xc[i+1]);
    a = a3;
    b = a1 - a3*(xc[i]+xc[i+1]);
    c = a3*xc[i]*xc[i+1] - a1*xc[i] + yc[i];
    r = a*t*t + b*t + c;
	i=i-1;
	}
   else if((i>=1)&&(i<=(m_iEndDot[index]-m_iStartDot[index])-4))
   {
    	a1 = (yc[i+1]-yc[i-1]) / (xc[i+1]-xc[i-1]);
        a2 = (yc[i+2]-yc[i-1]) / (xc[i+2]-xc[i-1]);
        a3 = (a2-a1) / (xc[i+2]-xc[i+1]);
	a = a3;
    b = a1 - a3*(xc[i-1]+xc[i+1]);
    c = a3*xc[i-1]*xc[i+1] - a1*xc[i-1] + yc[i-1];
    r = a*t*t + b*t + c;
   }
   else if(i>=(m_iEndDot[index]-m_iStartDot[index])-4)
   {
	i=i-3; 
   	a1 = (yc[i+1]-yc[i]) / (xc[i+1]-xc[i]);
        a2 = (yc[i+2]-yc[i]) / (xc[i+2]-xc[i]);
        a3 = (a2-a1) / (xc[i+2]-xc[i+1]);
    a = a3;
    b = a1 - a3*(xc[i]+xc[i+1]);
    c = a3*xc[i]*xc[i+1] - a1*xc[i] + yc[i];
    r = a*t*t + b*t + c;
	i=i+3;
   }


	if(r>3e8)
		r=3e8;
    //if(r<0)
	//	r=0;
    
	return r;
}

//
//	计算第i组数据居里点、最值、范围、温度系数α
//
void CRT::Calculation(int index)
{
    int i,j;
    int jmin,jmax;
    float x,y,xr,yr;
    float Rcur=0,Tcur=0;
    float Rmin=0,Rmax=0,Tmin=0,Tmax=0;
    float Tju=0,T25=0,Rju=0,R25,T2cur=0;
    float Alfa=0;              /*all R are log value*/
    float Belta=0,Trange=0;


	for(i=0;i<MAXOFSPL;i++)
	{
		xc[i]=0;
		yc[i]=0;
	}

    j=0;
	float rr0=0,tt0=0;
	//初始化各参数
//	index=1;//10-10oyj
   tt0=fabs(m_rtSave.m_fTem[index][j]);//m_fTem[j]的绝对值
   while((fabs(m_rtSave.m_fPtc[index][j]-1.0)<1e-2&&tt0<1e-2)
			||(fabs(m_rtSave.m_fPtc[index][j]-0.1)<1e-2&&tt0<1e-2)
			||(fabs(m_rtSave.m_fPtc[index][j]-0.001)<1e-2&&tt0<1e-2)) 
			//m_fPtc[j]属于(-0.009,0.011),(0.09,0.11),(0.99,1.01)这三个范围内且tt0<0.01时:
	{
		if(j>MAXOFSPL-1)return;	
		j++;
    tt0=fabs(m_rtSave.m_fTem[index][j]);	//m_fTem[j]的绝对值
	}
    if(fabs(m_rtSave.m_fTem[index][j+1])!=0)	//若m_fTem[j+1]不为零
	{
    	if(fabs(m_rtSave.m_fTem[index][j])>fabs(m_rtSave.m_fTem[index][j+1]))	//若|m_fTem[j]|>|m_fTem[j+1]|
	    	j++;
	}
    m_iStartDot[index]=j;
    for(i=0;i<MAXOFSPL;i++)
	{
		if((fabs(m_rtSave.m_fPtc[index][j]-1.0)<1e-2&&fabs(m_rtSave.m_fTem[index][j])<1e-2)
			||(fabs(m_rtSave.m_fPtc[index][j]-0.1)<1e-2&&fabs(m_rtSave.m_fTem[index][j])<1e-2)
			||(fabs(m_rtSave.m_fPtc[index][j]-0.001)<1e-2&&fabs(m_rtSave.m_fTem[index][j])<1e-2))
			//m_fPtc[j]属于(-0.009,0.011),(0.09,0.11),(0.99,1.01)这三个范围内且|m_fTem[j]|<0.01时:
		{
			m_iEndDot[index]=j; 
			break;
		}
		yc[i]= (float) log10( (double)m_rtSave.m_fPtc[index][j] ); /*yc[0]...yc[count-1]:log of PTCR R value*/
		xc[i]=m_rtSave.m_fTem[index][j++];        /*xc[0]...xc[count-1]:Temperature value*/
        if(fabs(m_rtSave.m_fPtc[index][j]-1.0)<1e-5 && fabs(m_rtSave.m_fPtc[index][j-1]-1.0)>1e-5)
	    	m_iCount[index]=i+1;
  }
 
	m_iEndTem[index]=xc[i-1];
	m_iCount[index] = m_iEndDot[index]-m_iStartDot[index] ;				/*获取有效测量点的数量iCount*/
	if(m_iEndDot[index]-m_iStartDot[index]>2)
	{
/*获取当前阻值Rcur和当前温度Tcu*/
		if(xc[0]>25.0)

		{
			Rcur=yc[0];
			Tcur=xc[0];
		Rcur = GetR(0,25.0);
		Tcur = 25.0;

		}
		else
		{
			for(i=0;i<m_iCount[index];i++)
				if(xc[i]>25.0) 
					break;   /*25.0在xc[i-1],xc[i],xc[i+1]的范围内*/
			
			Rcur = GetR(i-1,25.0);
			Tcur = 25.0;
		}


/*获取最小阻值Rmin、最小阻值时温度Tmin、最大阻值Rmax和最大阻值处温度Tmax*/
		jmin=0;
		jmax=0;
		Rmin=yc[jmin];    /*根据测量结果计算最大、最小点*/
		Rmax=yc[jmax];
		for(j=0;j<m_iCount[index];j++)
		{
			if(j==m_iCount[index])
				j=j-1;
			
			if(yc[j]<Rmin)
			{
				Rmin=yc[j];
				jmin=j;
			}
		
			if(yc[j]>Rmax)
			{
				Rmax=yc[j];
				jmax=j;
			}
		}

		if( jmin==0 || jmin==m_iCount[index]-1 ) 
		{
			Rmin=yc[jmin];
			Tmin=xc[jmin];
		}
		else
		{              /*根据计算结果获取最小值*/
			i=jmin-1;      /*三个连续点的开头*/
			j=jmin+1;      /*三个连续点的结尾*/
			y=xc[i];
			Rmin=yc[i];
			do
			{
				x = GetR(i,y);
				if(x<Rmin)
				{
					Rmin=x;
					Tmin=y;
				}
				y=  (float) (y+0.1);
			}while( y <= xc[j] );
		}

		if( jmax==0 || jmax==m_iCount[index]-1 )	
	{
			Rmax=yc[jmax];
			Tmax=xc[jmax];
		}
		else
		{
			i=jmax-1;      /*三个连续点的开头*/
			j=jmax+1;      /*三个连续点的结尾*/
			y=xc[i];
			Rmax=yc[i];
			do
			{
				x = GetR(i,y);
				if(x>Rmax)	
				{
					Rmax=x;
					Tmax=y;
				}
				y= (float) (y+0.1);
			}while( y <= xc[j] );
		}                 /*end of else()*/

/*计算温度范围Temp Range和阻值范围Belta*/
		Belta = Rmax - Rmin;
		Trange = Tmax - Tmin;

/*计算当前温度Tcur*/
		Rju	= (float) ( log10(2.0) + Rcur);    /*logRju=log(2*Rmin)=log2+logRmin*/
		if((Rju>=Rmax)||(Trange<=0)) 
			Tcur=0;         /*Tju无法计算*/
		else
		{
			for(i=jmin;i<=m_iCount[index];i++)
				if(Rju>yc[i] && Rju<yc[i+1]) 
					break;	//获取最接近Rju的测量点编号i
			
			if(i<=m_iCount[index]-1)
				Tcur = GetT(i,Rju);
			else
				Tcur=0;
		}

/*计算Tju和Rju*/
		Rju	= (float) ( log10(2.0) + Rmin);    /*logRju=log(2*Rmin)=log2+logRmin*/
		if((Rju>=Rmax)||(Trange<=0)) 
			Tju=0;         /*无法计算Tju*/
		else
		{
			for(i=jmin;i<=m_iCount[index];i++)
				if(Rju>yc[i] && Rju<yc[i+1]) 
					break;
			
			if(i<=m_iCount[index]-1)
				Tju = GetT(i,Rju);
			else
				Tju=0;
		}

/*计算温度系数Alfa*/
		if(Tju>Tmin)
		{
			x= (float) (Tju+10.0);
			y= (float) (Tju+25.0);
		}
		
		if( Tju==0 || y>=xc[m_iCount[index]-2] )
			Alfa=0;     /*无法计算Alfa*/
		else
		{
			for(i=0;i<m_iCount[index];i++)
				if(xc[i]>x)
					break;
	
			xr = GetR(i-1,x);
			
			for(i=0;i<m_iCount[index];i++)
				if(xc[i]>y)
					break;
	
			yr = GetR(i-1,y);
			Alfa = (float) ( 2.303 * (yr-xr) * 100.0/15.0);
		}
	}
	else
	{
		Rcur=yc[0];
		Tcur=xc[0];
	}


    m_fTemCur[index]=Tcur;

    m_fTemCurie[index]=Tju;
    m_fResCurie[index]=(float)pow(10.0,(double)Rju);
    m_fResMin[index]=(float)pow(10.0,(double)Rmin);
    m_fTemMin[index]=Tmin;
    m_fResMax[index]=(float)pow(10.0,(double)Rmax);
    m_fTemMax[index]=Tmax;
    m_fTemCoe10[index]=Alfa;
    m_fCurieRange[index]=Trange;
    m_fResRatio[index]=(float)pow(10.0,Belta);
    m_fTemCoe50[index]=GetAlfa(index,0,15);
    m_fTemCoe25[index]=GetAlfa(index,15,25);
 
    if(GetStartTem0(index)>25.0) {
		m_fRes25[index]=(float)pow(10.0,(double)Rcur);
	 m_fTemCur2R25[index]=Tcur;
	}
	else {
        m_fTemCur2R25[index]=Tcur;
		m_fRes25[index]=(float)pow(10.0,(double)Rcur);
	}
//oyj
	m_iStartTem0[index]=xc[0];
	m_iStartRes0[index]=yc[0];
//oyj    
}


//
//	获取居里点温度
//
float CRT::GetTemCur(int i)
{
	return m_fTemCur[i];
}

//
//	获取测定阻值yc[i]附近r阻值时的拟合温度
//
float CRT::GetT(int i, float r)
{
	float a1,a2,a3,a,b,c;
    float x,y,dr;
    float t;

    a1 = (yc[i+1]-yc[i]) / (xc[i+1]-xc[i]);
    a2 = (yc[i+2]-yc[i]) / (xc[i+2]-xc[i]);
    a3 = (a2-a1) / (xc[i+2]-xc[i+1]);

    a = a3;
    b = a1 - a3*(xc[i]+xc[i+1]);
    c = a3*xc[i]*xc[i+1] - a1*xc[i] + yc[i];

    y = xc[i];
    dr = yc[i] - r;
    dr = dr>0 ? dr : -dr;     /*absolute value*/
    t=y;
    do{
	    x = a*y*y + b*y + c - r;
	    x = x>0 ? x : -x;
	    if(x<dr){
		dr=x;
		t=y;
	    }
	    y= (float) (y+0.1);
    }while( y <= xc[i+2] );
    /*return t;*/
    return t;
}

//
//	获取温度t对应的拟合阻值
//
float CRT::GetAnyR(float t,int index)
{
	float r;
	float r0,r1,r2;
    int gi;

	for(gi=0;gi<m_iEndDot[index]-m_iStartDot[index];gi++)
	{   if(xc[gi]>t) break;}

		if(gi==0){
			r=GetR(gi,t);
		}
		else if((yc[gi+1]-yc[gi]>1.5)&&(gi>2)){//lby
           r=GetR(gi-2,t);
		}
		else if((yc[gi+1]-yc[gi]<-1.5)&&(gi>2)){//lby
           r=GetR(gi-2,t);
		}
	    else
		   r=GetR(gi-1,t);

return  r;
}

//
//	获取有效测量点数量
//
int CRT::GetCount(int index)
{
	return m_iCount[index];
}

//
//	获取编号i测量点温度
//
float CRT::GetX(int i)
{
	return xc[i];
}

//
//	获取编号i测量点阻值
//
float CRT::GetY(int i)
{
	return yc[i];
}

//
//	获取起始测量点编号
//
int CRT::GetStart(int index)
{
	return m_iStartDot[index];
}

//
//	获取末尾测量点编号
//
int CRT::GetEnd(int index)
{
	return m_iEndDot[index];
}

//
//	写通道校零文件
//
int CRT::WriteZero()
{
	CString str;

CFileDialog dlg(TRUE,NULL,NULL,OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT,"通道校零文件(ZERORANG.RES)|*.RES");	
	if(dlg.DoModal()==IDOK)
	{
		str=dlg.GetFileName();
		CFile file(str,CFile::modeCreate|CFile::modeWrite);
			
	for(int i=0;i<32;i++)
	{// m_fResi[i]=0.1111;
		if(i<m_Number){ 
			m_Zeroresi[i]=m_fResi[i];
		    str.Format("%6.4f\r\n",m_fResi[i]);
		}
		else str.Format("%6.4f\r\n",m_Zeroresi[i]);

	  file.Write(str,str.GetLength());
	}

	//		file.Write(m_fResi,sizeof(m_fResi));
		file.Close();
	}
return TRUE;
}

//
//	读通道校零文件
//
int CRT::ReadZero()
{
//static int j=0;
	CString str="zerorang.res";
//if(j==1) return TRUE;

 CFileDialog dlg(TRUE,NULL,NULL,OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT,"通道校零文件(ZERORANG.RES)|*.RES");	
	if(dlg.DoModal()==IDOK)
	{
		str=dlg.GetFileName();
		CFile file(str,CFile::modeRead);
	char str0[80];	
		for(int i=0;i<32;i++)
		{ // m_fResi[i]=0.1;	
  //			str.Format("%6.4f",m_fResi[i]);
      //    int j=7;
			file.Read(str0,8);
		m_Zeroresi[i]=atof(str0);
		};
	file.Close();
	}
 //j=1; 
// ReadZeroResi=FALSE;

	ReadZeroResi=TRUE;
	return TRUE;
}

//
//	获取起始测量点温度
//
float CRT::GetStartTem0(int i)
{
  return m_iStartTem0[i];
}

//
//	获取起始测量点阻值
//
float CRT::GetStartRes0(int i)
{
  return m_iStartRes0[i];
}

//
//	获取末尾测量点编号
//
float CRT::GetEndTem(int i)
{
 return m_iEndTem[i];
}

//
//	获取阻值r对应的拟合温度
//
float CRT::GetAnyT(float r, int index)
{

	int i,j;
	float t,R_min;
	R_min=yc[0];
	for(i=0,j=0;i<m_iEndDot[index]-m_iStartDot[index];i++)
		if(yc[i]<R_min && yc[i]!=0)
		{
		  R_min=yc[i];
		  j=i;
		}
	if(yc[j]>r)  
		return -100;
	else
	{
	   for(j=0;j<m_iEndDot[index]-m_iStartDot[index];j++)
		if(yc[j]>r) break;
		
	
//		if(j>=m_iEndDot[index]-m_iStartDot[index] || yc[j]==0)
		if(j>=m_iEndDot[index]-m_iStartDot[index])
			return -100;
		else
		{
      	  t=GetT(j-1,r);
          return t;
		}
	}
    
}
