#include<stdio.h>
#include<cs50.h>

int main(void)

{
    /*taking showertime t*/
    printf("Enter your shower time in minutes : ");
    int t = GetInt();
    /*shower water = 1.5 gallons/minute = 1.5*128 ounces = 192 ounces/minute*/
    /*1 bottle water = 16 ounces*/
    printf("You are using %d bottles of water for bathing\n",192/16*t);
    
}
