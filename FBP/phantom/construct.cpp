#include <fstream>
#include <cmath>
#include <math.h>
const double pi=3.1415926;
/*
double sin(double angle);
double cos(double angle);
double fact(int n);
*/
int main()
{
using namespace std;

 double x[10],y[10],major[10],minor[10],angle[10],value[10],x_axis[201][201],y_axis[201][201],
phantom[201][201],x_new[201][201],y_new[201][201] ;
 x[0]=0.0;   y[0]=0.0;       major[0]=0.92;   minor[0]=0.69;   angle[0]=pi/2.0;     value[0]=2.5;
 x[1]=0.0;   y[1]=-0.0184;   major[1]=0.874;  minor[1]=0.6624; angle[1]=pi/2.0;     value[1]=-0.98;
 x[2]=0.22;  y[2]=0.0;       major[2]=0.31;   minor[2]=0.11;   angle[2]=2.0/5.0*pi; value[2]=-1.2; 	
 x[3]=-0.22; y[3]=0.0;       major[3]=0.41;   minor[3]=0.16;   angle[3]=3.0/5.0*pi; value[3]=-1.2;
 x[4]=0.0;   y[4]=0.35;      major[4]=0.25;   minor[4]=0.21;   angle[4]=pi/2.0;     value[4]=0.53;
 x[5]=0.0;   y[5]=0.1;       major[5]=0.046;  minor[5]=0.046;  angle[5]=0.0;        value[5]=0.53;
 x[6]=0.0;   y[6]=-0.1;      major[6]=0.046;  minor[6]=0.046;  angle[6]=0.0;        value[6]=1.25;
 x[7]=-0.08; y[7]=-0.605;    major[7]=0.046;  minor[7]=0.023;  angle[7]=0.0;        value[7]=0.7;
 x[8]=0.0;   y[8]=-0.605;    major[8]=0.023;  minor[8]=0.023;  angle[8]=0.0;        value[8]=1.0;
 x[9]=0.06;  y[9]=-0.605;    major[9]=0.046;  minor[9]=0.023;  angle[9]=pi/2.0;     value[9]=0.7;
 for(int j=0 ; j<201 ; j++)
 {x_axis[0][j]=-1.0;   y_axis[j][0]=1.0;}  
 for (int i=1;i<201  ;i++)
    for (int j=1 ; j<201 ;j++)
 {
 x_axis[i][j]=x_axis[i-1][j]+0.01;
 y_axis[i][j]= y_axis[i][j-1]-0.01;
 }
 for (int i=0 ; i<201 ; i++)
   for (int j=0; j<201 ; j++)
   phantom[i][j]=0;
   
   
 for (int i=0  ;  i<9  ; i++)
 {
   for (int j=0  ;  j<201  ; j++  )
      for (int k=0 ; k<201 ; k++   )
   {
       x_new[j][k]= ((x_axis[j][k]-x[i])*cos(angle[i]))+((y_axis[j][k]-y[i])*sin(angle[i]))  ;
       y_new[j][k]= -((x_axis[j][k]-x[i])*sin(angle[i]))+((y_axis[j][k]-y[i])*cos(angle[i]))  ;
   }
  
  for (int m=0 ;  m<201  ;  m++) 
    {
     for (int n=0 ; n<201  ;   n++)    
      {
       if ((pow(x_new[m][n],2)/pow(major[i],2))+(pow(y_new[m][n],2)/pow(minor[i],2))<=1)
	// index[m][n] = 1.0;         
	phantom[m][n]=phantom[m][n]+ value[i];
        
        else
	 //index[m][n] = 0.0;
        phantom[m][n]=phantom[m][n];
	 //phantom[m][n] = phantom[m][n] + index[m][n]*value[i]
      }
     }
 } 

  ofstream out_stream;
  out_stream.open("phantom9.txt");
   for (int i=0 ; i<201 ; i++)
     {
     for (int j=0 ; j<201 ; j++)
       

       out_stream<<phantom[j][i]<<"\t";
       
       out_stream<<endl;
       }
  return 0; 

}
/*
double fact(int n)
{
int value(1);
for (int i=1;i<=n;i++)
value=value*i;
return(value);
}

double sin(double angle)
{
 double value(0);
 for (int i=0  ;i<=8 ;i++)
 value=value+(pow(-1.0,i)/fact(2.0*i+1.0)*pow(angle,2.0*i+1.0));
 
 return(value);
}


double cos(double angle)
{
double value(0);
for (int i=0    ; i<=8; i++)
value=value+(pow(-1.0,i)/fact(2.0*i)*pow(angle,2.0*i));

return(value);
}*/
