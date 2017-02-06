#include <stdio.h>
#include <ctype.h>
#include <cs50.h>
#include <string.h>

int main(int argc, char* argv[])
{
    //checking if command-line argument is valid or not.
    if(argc != 2)
    {
        printf("Invalid command-line argument\n");
        return 1;
    }
    else
    {
        int keylen = strlen(argv[1]);   //keylen is keylength
        
        //looping of argv[1] to check if alphabetical charactersc are present
        for(int i = 0; i < keylen; i++)
        {
            //loop for getting alphabetical characters only
            if(!isalpha(argv[1][i]))
            {
                printf("Enter only characters A-Z or a-z in command-line argument\n");
                return 1;
                break;
            }    
        }
        //getting plainttext from user
        printf("plaintext: ");
        char *plaintext = get_string();
        int l = strlen(plaintext);    //l is length of plaintext
        
        //defining ciphertext
        char *ciphertext = malloc((sizeof(char)*l) + 1);
        
        //count_alpha == variable for counting alpha
        int count_alpha = 0;
        printf("ciphertext: ");
        for(int i = 0; i < l; i++)
        {
            int j = (count_alpha % keylen);
            if(isalpha(plaintext[i]))
            {
                //for uppercase text
                if(isupper(plaintext[i]))
                {
                    //for uppercase key
                    if(isupper(argv[1][j]))
                    ciphertext[i] = ((plaintext[i] + argv[1][j] - 2*'A')%26 + 'A');
                    //for lowercase key
                    else
                    ciphertext[i] = ((plaintext[i] - 'A' + argv[1][j] - 'a')%26 + 'A');
                }
                //for lowercase text
                if(islower(plaintext[i]))
                {
                    //for uppercase key
                    if(isupper(argv[1][j]))
                    ciphertext[i] = ((plaintext[i] - 'a' + argv[1][j] - 'A')%26 + 'a');
                    //for lowercase key
                    else
                    ciphertext[i] = ((plaintext[i] + argv[1][j] - 2*'a')%26 + 'a');
                }
                count_alpha++;
            }
            else
            {
                ciphertext[i] = plaintext[i];
            }
            
            //printing ciphertext
            printf("%c",ciphertext[i]);
        }
        printf("\n");
        
        free(ciphertext);
        
        return 0;
    }
}
