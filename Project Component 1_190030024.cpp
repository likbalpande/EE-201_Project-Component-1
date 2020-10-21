#include <stdio.h>
#include <stdlib.h>
#include <math.h>

int Result(float K[])
{ int Int[3];float diff[3];
  for(int i=0;i<3;i++)
  {Int[i]=(int)K[i];
   if(!(Int[i]==1||Int[i]==2||Int[i]==3||Int[i]==4))K[i]=0; }
   for(int i=0;i<3;i++) {
   diff[i]=1; if(K[i]==0)continue;
    for(int j=0;j<3;j++)
   { float temp= j+2-K[i];
    if(temp<0)temp=-temp;
    if(temp<diff[i])diff[i]=temp; }}
    float temp[3];
    for(int i=0;i<3;i++)
{ temp[i]=diff[i];}
for(int i=0;i<3;i++)
{ for(int j=0;j<3;j++)
  if(temp[i]<temp[j]){
  float dust=temp[i];
  temp[i]=temp[j];
  temp[j]=dust; }}
int index;
for(int i=0;i<3;i++)
if(diff[i]==temp[0])index=i;
return index;}

int main()
{
FILE *fptr;
char filename[]= "data_190030024.csv";
fptr = fopen(filename,"r");
float n[100000];float sum=0,sum2=0;
float K[3],Lamda=0,sigma[2];
//Taking numbers
for(int i=0;i<100000;i++)
{fscanf(fptr,"%f", &n[i]);
 sum2+=(n[i]*n[i]);
 sum+=n[i];}
//Expected value of Z
float E_z=sum/100000;
// Variance of Z
float var_z=((sum2/100000)-((E_z)*(E_z)));
printf("E[Z] = %.3f\nvar(Z) = %.3f\n",E_z,var_z);
/*
Equation 1--> E_z=10*K*E_w;
              E_w=E_z/(10*K);

Equation 2--> var_z-3=100*K*var_w;
              var_w=(var_z-3)/(100*K);
*/
//Exponential distribution
K[0]=(E_z*E_z)/(var_z-3);
Lamda=(10*K[0])/E_z;
printf("\nCase 1: Exponential distribution\n");
printf("K = %.3f\n",K[0]);
printf("Lambda = %.3f\n",Lamda);

//Rayleigh distribution
K[1]=(E_z*E_z*(4-3.141))/(3.141*(var_z-3));
sigma[0]=(sqrt(2/3.141))*(E_z/(10*K[1]));
printf("\nCase 2: Rayleigh distribution\n");
printf("K = %.3f\n",K[1]);
printf("Sigma = %.3f\n",sigma[0]);

//Half-normal distribution
K[2]=(E_z*E_z*(3.141-2))/(2*(var_z-3));
sigma[1]=(sqrt(3.141/2))*(E_z/(10*K[2]));
printf("\nCase 3: Half-normal distribution\n");
printf("K = %.3f\n",K[2]);
printf("Sigma = %.3f\n",sigma[1]);

//Best Fit 'K'
printf("\nBest approximation for 'K' will be : ");
int index=Result(K);
int check=K[index];
if((K[index]-check)>(check+1-K[index]))printf("%i\n\n",check+1);
else printf("%i\n\n",check);
exit(190030024); return 0;}
