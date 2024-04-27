#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

void generatePass(char*, int, char*);
void displayPassword(char **passwords, int);
void savePassword(char **passwords, int);


int main(int argc, char *argv[])
{
    char *help_prompt = "This is a Password Generator. With this program you can generate random passwords fast and easy :).\n"
                    "These are the arguments you can use:\n"
                    "-l: This is for the length of the password. Ex: passwd-gen.exe -l 9\n"
                    "-N: The number of the passwords you want to generate at the same time. Ez: passwd-gen.exe -N 3\n"
                    "-m: For using lowercase letters on the password gen (No Value). Ex: passwd-gen.exe -m\n"
                    "-u: For using uppercase letters on the password gen (No Value). Ex: passwd-gen.exe -u\n"
                    "-n: For using numbers on the password gen (No Value). Ex: passwd-gen.exe -n\n"
                    "-s: For using symbols on the password gen (No Value). Ex: passwd-gen.exe -s\n"
                    "-f: For saving the password(s) to a file (No Value -> It will ask you for the name when you finish generating). Ex: passwd-gen.exe -f";
    int numero = 1;
    char archivo = 'n';
    char pass_type[5] = "";
    for (int i = 0; i < 5; i++) {
        pass_type[i] = 1;
    }
    int length = 0;
    if (argc == 1){
        printf("%s", help_prompt);
        return 0;
    }
    for (int i = 0; i < argc; i++){
        if (strcmp(argv[i], "-l") == 0){
            if (i + 1 < argc){
                int converted = atoi(argv[i+1]);
                if (converted > 0){
                    length = atoi(argv[i+1]);
                    i++;
                }else{
                    printf("Invalid value after -l. Please provide a positive number");
                    return 0;
                }
                
            }else{
                printf("You didnt provide any value after: -l");
                return 1;
            }

        } else if (strcmp(argv[i], "-m") == 0){
            pass_type[0] = 'm';
        } else if (strcmp(argv[i], "-u") == 0){
            pass_type[1] = 'u';
        } else if (strcmp(argv[i], "-n")== 0){
            pass_type[2] = 'n';
        } else if (strcmp(argv[i], "-s")== 0){
            pass_type[3] = 's';
        } else if (strcmp(argv[i], "-f")== 0){
            archivo = 'y';
        } else if (strcmp(argv[i], "-N")== 0){
            if (i + 1 < argc){
                int converted = atoi(argv[i+1]);
                if (converted > 0){
                    numero = atoi(argv[i + 1]);
                    i++;
                }else{
                    printf("Invalid value after -N. Please provide a valid positive number");
                    return 0;
                }
                
            } else{
                printf("You didnt provide any value after: -N");
                return 1;
            }
        } else if (strcmp(argv[i], "-h") == 0){
            printf("%s", help_prompt);
            return 0;
        }
    }
    printf("%s", pass_type);
    // int length;
    char run_again = '\n';
    // printf("how long do you want the password to be: ");
    // scanf("%d", &length);
    // printf("what characters do you want to have on your password:\n-lowerLetters(l)\n-upperLetters(u)\n-numbers(n)\n-symbols(s)\n");
    // scanf("%s", pass_type);
    // printf("Choose the number of passwords to generate (default: 1): ");
    // scanf("%d", &numero);
    // char passwords[numero][100];
    char **passwords = (char **)malloc(numero* sizeof(char*));
    if (passwords == NULL) {
        printf("Error: No se pudo asignar memoria para las contraseñas.\n");
        return -1;
    }

    for (int i = 0; i < numero; i++) {
        passwords[i] = (char *)malloc((length + 1) * sizeof(char));
        if (passwords[i] == NULL) {
            printf("Error: No se pudo asignar memoria para la contraseña %d. \n", i + 1);
            return -1;
        }
    }
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
    // printf("Do you want to save the password(s) in a file?(y/n): ");
    // scanf(" %c", &archivo);
    if (tolower(archivo) == 'y'){
        savePassword(passwords, numero);
    }
    for (int i = 0; i < numero; i++) {
        free(passwords[i]);
    }
    free(passwords);
    return 0;
}


void generatePass(char *password, int length, char *pass_type)
{
    static const char symbols[] = "@#+-/()[]{}$&=?!";
    static const char numbers[] = "123456789";
    static const char mayus[] = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
    static const char minus[] = "abcdefghijklmnopqrstuvwxyz";
    
    char all_characters[100] = "";

    if (strchr(pass_type, 'm') != NULL){
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

void displayPassword(char **passwords, int numero)
{
    for (int i = 0; i < numero; i++){
        printf("password %d: %s\n",i + 1,  passwords[i]);
    }
}


void savePassword(char **passwords, int numero)
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
