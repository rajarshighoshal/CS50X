#include<stdio.h>
#include<cs50.h>

int main(void)
{
    int h,row,col1,col2,coltoprint;
    /*h=height of pyramid, row=row variable,col1=col variable for space,col2 = col variable for #,coltoprint=space columns to print in 1st row*/
    
  do
  {
    printf("Enter the height of pyramid(a non negative integer no greater than 23):");
    h = GetInt();
  }
  while(h<0 || h>23);
  
    coltoprint = h-2;
    
    for(row=1; row<=h; row++)
    {
      for(col1=0; col1<=coltoprint; col1++)
      {
          printf(" ");
      }
      for(col2=0; col2<=row; col2++)
      {
          printf("#");
      }
      coltoprint--;
      printf("\n");
    }
  
  
}