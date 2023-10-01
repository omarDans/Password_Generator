#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

void generatePass(char*, int, char*);
void displayPassword(char passwords[][100], int);
void savePassword(char passwords[][100], int);


int main(void)
{
    char archivo;
    char pass_type[5];
    int length;
    char run_again = '\n';
    int numero = 1;
    printf("how long do you want the password to be: ");
    scanf("%d", &length);
    printf("what characters do you want to have on your password:\n-lowerLetters(l)\n-upperLetters(u)\n-numbers(n)\n-symbols(s)\n");
    scanf("%s", pass_type);
    printf("Choose the number of passwords to generate (default: 1): ");
    scanf("%d", &numero);
    char passwords[numero][100];
    while (run_again == '\n'){
        srand(time(NULL));
        for (int i = 0; i < numero; i++){
            generatePass(passwords[i], length, pass_type);
        }
        printf("\nGenerated Password(s):\n");
        displayPassword(passwords, numero);
        printf("Press enter to regenerate the passwords or any key to exit: ");
        run_again = getchar();

        while (getchar() != '\n'){
            continue;
        }
    }
    printf("Do you want to save the password(s) in a file?(y/n): ");
    scanf(" %c", &archivo);
    if (tolower(archivo) == 'y'){
        savePassword(passwords, numero);
    }
    return 0;
}


void generatePass(char *password, int length, char *pass_type)
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

    size_t string_length = strlen(all_characters);
    for (int i = 0; i < length; i++)
    {
        int p_key = rand() % string_length;
        password[i] = all_characters[p_key];
    }
    password[length] = '\0';
}

void displayPassword(char passwords[][100], int numero)
{
    for (int i = 0; i < numero; i++){
        printf("password %d: %s\n",i + 1,  passwords[i]);
    }
}


void savePassword(char passwords[][100], int numero)
{
    FILE *archivo;
    char name[100];
    printf("Specify the name of the file: ");
    scanf("%s", name);
    strcat(name, ".txt");
    archivo = fopen(name, "a");
    if (archivo == NULL){
        printf("Error opening file for writing.\n");
        return;
    }
    for (int i = 0; i < numero; i++){
        fprintf(archivo, "password %d: %s\n", i + 1, passwords[i]);
    }
    fclose(archivo);
    printf("Passwords saved succesfully!\n");
}
