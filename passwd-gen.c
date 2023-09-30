#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <string.h>

char generatePass(char*, int, char*);


int main(void)
{
    char pass_type[5];
    int length;
    char run_again = '\n';
    printf("how long do you want the password to be: ");
    scanf("%d", &length);
    printf("what characters do you want to have on your password:\n-lowerLetters(l)\n-upperLetters(u)\n-numbers(n)\n-symbols(s)\n");
    scanf("%s", pass_type);
    char final_pass[length + 1];
    while (run_again == '\n'){
        generatePass(final_pass, length, pass_type);
        printf("Here is your password: %s\n", final_pass);
        printf("Press enter to regenerate the password (maybe you will need to press enter twice) or any other key to exit: ");
        run_again = getchar();
        
        while (getchar() != '\n'){
            continue;
        }
    }  
    return 0;
}


char generatePass(char *password, int length, char *pass_type)
{
    static char symbols[] = "@#+-/()[]{}$&=¿?¡!";
    static char numbers[] = "123456789";
    static char mayus[] = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
    static char minus[] = "abcdefghijklmnopqrstuvwxyz";
    
    char all_characters[100] = "";

    if (strchr(pass_type, 'l') != NULL){
        strcat(all_characters, minus);
    }
    if (strchr(pass_type, 'u') != NULL){
        strcat(all_characters, mayus);
    }
    if (strchr(pass_type, 'n') != NULL){
        strcat(all_characters, numbers);
    }
    if (strchr(pass_type, 's') != NULL){
        strcat(all_characters, symbols);
    }

    srand(time(NULL));
    size_t string_length = strlen(all_characters);

    for (int i = 0; i < length; i++)
    {
        int p_key = rand() % string_length;
        password[i] = all_characters[p_key];
    }
    password[length] = '\0';
}