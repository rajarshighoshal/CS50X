#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<cs50.h>
#include<ctype.h>

int main(int argc, string argv[])
{
    //checking if comman-line argument is valid
    if(argc != 2)
    {
        printf("Invalid comman-line argument.\n");
        return 1;
    }
    else
    {
        int k = atoi(argv[1]);
        
        //getting plaintext
        printf("plaintext: ");
        char *p = get_string();
        int l = strlen(p);
        
        //converting plaintext in cipher
        printf("ciphertext: ");
        char *c = malloc(sizeof(char)*l);
        for (int i = 0; i < l; i++)
        {
                //for uppercase letters
                if(isupper(p[i]))
                c[i] = ((p[i] - 'A' + k)%26 + 'A');
                //for lowercase letters
                else if(islower(p[i]))
                c[i] = ((p[i] - 'a' + k)%26 + 'a');
                //for other characters
                else
                c[i] = p[i]; 
            
        //printing cipher text
        printf("%c",c[i]);
        }
        printf("\n");
        
        free(c);
        
        return 0;
    }
    
}

