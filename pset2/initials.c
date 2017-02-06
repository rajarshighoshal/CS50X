/**code to collect input from user as an array
*coolect initials of each word given by user
*capitalize the initials
*prints them in the proper order
*/
#include<stdio.h>
#include<string.h>
#include<cs50.h>
#include<ctype.h>

int main(void)
{   
    //get strings and declare array
    string s = get_string();
    
    printf("%c",toupper(s[0]));
    
    for(int i = 0, l = strlen(s); i < l; i++)
    {
        if(isspace(s[i]))
        {
           printf("%c",toupper(s[i+1]));
        }
    }
 
     printf("\n");
}
