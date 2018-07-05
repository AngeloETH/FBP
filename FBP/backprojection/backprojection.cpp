#include<fstream> 
#include<math.h> 
#include<cmath>
const double pi=3.14159265359;
int main()
{
using namespace std;
double sinogram[180][201],x_axis[201][201],y_axis[201][201],fbp[201][201];
for (int i=0 ; i<201 ; i++)
{x_axis[0][i]=-1;y_axis[i][0]=1.0;}
for (int i=0 ; i<201 ; i++)
	for( int j=0 ; j<201 ; j++)
       {
       x_axis[i][j]=x_axis[i-1][j]+0.01;
       y_axis[i][j]= y_axis[i][j-1]-0.01;
       fbp[i][j]=0;
       }
ifstream ifile;
ofstream ofile;
ifile.open("sinogramoutput.txt");
for (int i=0 ; i<180 ; i++)
	for (int j=0 ; j<201 ; j++)
   ifile>>sinogram[i][j];
    


for (int k=1 ; k<=180 ; k++)
    {
     double t_axis[201][201],s_axis[201][201],sum[201][201],forward[201][201];
     for(int i=0 ; i<201 ; i++)
     forward[i][0]=sinogram[k][i];
     for (int i=0 ; i<201 ; i++)
     	for (int j=0 ; j<201 ; j++)
     	{
      sum[201][201]=0 ;
      t_axis[i][j]=cos(k*pi/180)*x_axis[i][j]-sin(k*pi/180)*y_axis[i][j];
      s_axis[i][j]=sin(k*pi/180)*x_axis[i][j]+cos(k*pi/180)*y_axis[i][j];
      }
      for (int i=0 ; i<201 ; i++)
       for (int j=1 ; j<201 ; j++)
       forward[i][j]=forward[i][j-1];
     for (int i=0 ; i<201 ; i++)
     	for (int j=0 ; j<201 ; j++)
        {
        double a,b;
        a=(t_axis[i][j]+1)/0.01;
        b=(s_axis[i][j]+1)/0.01;
        int fa,cb;
        fa=floor(a);
        cb=ceil(200-b);
        if (a<=200 && a>=0 && b<=200 && b>=0)
        	{
            double alpha,beta,high_y,low_y;
        	alpha=t_axis[i][j]-x_axis[fa][0];
        	beta= s_axis[i][j]-y_axis[0][cb];
        	high_y=(1-alpha)*forward[fa+1][cb-1]+alpha*forward[fa][cb-1];
        	low_y= (1-alpha)*forward[fa+1][cb]+alpha*forward[fa][cb];
        	sum[i][j]=(1-beta)*high_y+beta*low_y;
            }
         
        fbp[i][j]=fbp[i][j]+sum[i][j];
        
        }

    }
ofile.open("bp.txt");
for (int i=0 ; i<201 ; i++)
	{
	for (int j=0 ; j<201 ; j++)
    ofile<<fbp[j][i]<<"\t";
    ofile<<endl;
    }
 return 0;
}
