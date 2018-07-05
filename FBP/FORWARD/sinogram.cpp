#include<fstream> 
#include<math.h> 
#include<cmath>
const double pi=3.14159265359;
//double interp2(double x_axis[][] , double y_axis[][], double phantom[][] ,double t_axis[][] ,bouble s_axis[][]);
int main()
{
using namespace std;
double x_axis[201][201],y_axis[201][201],phantom[201][201],sinogram[180][201];
ifstream ifile;
ofstream ofile;
ifile.open("phantom.txt");
ofile.open("sinogramoutput.txt");
for (int i=0; i<201 ; i++)
	for (int j=0; j<201; j++)
ifile>>phantom[j][i];
for (int n=0 ; n<180 ; n++)
    for (int k=0 ; k<201 ; k++)
    sinogram[n][k]=0; 
    
for(int j=0 ; j<201 ; j++)
 {x_axis[0][j]=-1.0;   y_axis[j][0]=1.0;}  

 for (int i=1;i<201  ;i++)
    for (int j=1 ; j<201 ;j++)
 {
 x_axis[i][j]=x_axis[i-1][j]+0.01;
 y_axis[i][j]= y_axis[i][j-1]-0.01;
 }
 
for (int k=1 ; k<=180 ; k++)

{  
//int k=1;
	
    double project[201][201],t_axis[201][201],s_axis[201][201];
    for (int m=0 ; m<201 ; m++)
    for (int n=0 ; n<201 ; n++)
	{
     project[m][n]=0.0;
 	 t_axis[m][n]=  x_axis[m][n]*cos(pi/180*k ) + y_axis[m][n]*sin(pi/180*k ); // Rotated Axis
         s_axis[m][n]= -x_axis[m][n]*sin(pi/180*k ) + y_axis[m][n]*cos(pi/180*k ); // Rotated Axis
 	}
	
		for (int m=0 ; m<201 ; m++)
		   for (int n=0 ; n<201 ; n++)
{
    double a,b;
    int fa,cb;
    a=(t_axis[m][n]+1.0)/0.01; // Range from 0 (if t_axis is -1) to 200 (if t_axis is 1)
    b=(s_axis[m][n]+1.0)/0.01; //
    fa=floor(a); // Get an integer for index value
    cb=ceil(200-b); // Get an integer for index
    if(a>=0 && a<=200 && b>=0 && b<=200)
//if ( t_axis[m][n]>=x_axis[i][j] && t_axis[m][n]<=x_axis[i+1][j] && s_axis[m][n]<=y_axis[i][j] && s_axis[m][n]>=y_axis[i][j+1] )
	{
	double alpha , beta ,high_y ,low_y ;
	alpha=t_axis[m][n]-x_axis[fa][0]; // The distance between the point of interest and starting point (x-axis)
	beta =s_axis[m][n]-y_axis[0][cb]; // The distance between the interpolated point and the starting point (y-axis)
	high_y=(1-alpha)*phantom[fa+1][cb-1]+alpha*phantom[fa][cb-1];
	low_y =(1-alpha)*phantom[fa+1][cb]+alpha*phantom[fa][cb];
	project[m][n]=(1-beta)*high_y+beta*low_y;
	}

}
      

	
	for ( int m=0 ; m<201 ; m++)
	for ( int n=0 ; n<201 ; n++)
	sinogram[k-1][m]=sinogram[k-1][m]+(project[m][n]*0.01);


}



 
  
   for (int i=0 ; i<180 ; i++)
     {
     for (int j=0 ; j< 201; j++)
       

       ofile<<sinogram[i][j]<<"\t";
       
       ofile<<endl;
       }
  return 0; 

}

/*
double interp2(double x_axis[][] , double y_axis[][], double phantom[][] ,double t_axis[][] ,bouble s_axis[][])
{
	double project[201][201];
	for (int i=0 ; i<201 ; i++)
 	   for (int j=0 ; j<201 ; j++)
		for (int m=0 ; m<201 ; m++)
		   for (int n=0 ; n<201 ; n++)
{
if ( t_axis[m][n]>=x_axis[i][j] && t_axis[m][n]<=x_axis[i+1][j] && s_axis[m][n]<=y_axis[i][j] && s_axis[m][n]>=y_axis[i][j+1] )
	{
	double alpha , beta ,high_y ,low_y ;
	alpha=t_axis[m][n]-x_axis[i][j];
	beta =s_axis[m][n]-y_axis[i][j+1];              
	high_y=(1-alpha)*phantom[i+1][j]+alpha*phantom[i][j];
	low_y =(1-alpha)*phantom[i+1][j+1]+alpha*phantom[i][j+1];
	project[m][n]=(1-beta)*high_y+beta*low_y;
	}
else 
	project[m][n]=0;
}       
 return(project);

}
*/
