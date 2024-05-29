#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <windows.h>

void generatePass(char*, int, char*);
void displayPassword(char **, int);
void savePassword(char **, int);
void clearPasswords(char**, int, int);
void clearInputBuffer();
void print_with_delay(const char *, double );
void PreciseSleep(double);

int main(int argc, char *argv[])
{
    int gui = 0;
    char *help_prompt = "This is a Password Generator. With this program you can generate random passwords fast and easy :).\n"
                    "These are the arguments you can use:\n"
                    "-L: This is for the length of the password. Ex: passwd-gen.exe -L 9\n"
                    "-N: The number of the passwords you want to generate at the same time. Ez: passwd-gen.exe -N 3\n"
                    "-l: For using lowercase letters on the password gen (No Value). Ex: passwd-gen.exe -l\n"
                    "-u: For using uppercase letters on the password gen (No Value). Ex: passwd-gen.exe -u\n"
                    "-n: For using numbers on the password gen (No Value). Ex: passwd-gen.exe -n\n"
                    "-s: For using symbols on the password gen (No Value). Ex: passwd-gen.exe -s\n"
                    "-f: For saving the password(s) to a file (No Value -> It will ask you for the name when you finish generating). Ex: passwd-gen.exe -f";
    int numero = 1;
    char archivo = 'n';
    char pass_type[6] = "";
    for (int i = 0; i < 6; i++) {
        pass_type[i] = 1;
    }
    int length = 0;
    char c = ' ';
    if (argc != 1){
        for (int i = 0; i < argc; i++){
            if (strcmp(argv[i], "-L") == 0){
                if (i + 1 < argc){
                    int converted = atoi(argv[i+1]);
                    if (converted > 0){
                        length = atoi(argv[i+1]);
                        i++;
                    }else{
                        printf("Invalid value after -L. Please provide a positive number");
                        return 0;
                    }
                    
                }else{
                    printf("You didnt provide any value after: -L");
                    return 1;
                }

            } else if (strcmp(argv[i], "-l") == 0){
                pass_type[0] = 'l';
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
    } else {
        gui = 1;
        system("cls");
        double delayBanner = 0.001;
        double delayText = 0.01;
        print_with_delay("\033[0m\033[31m8 888888888o      .8.            d888888o.      d888888o.       \033[35m,o888888o.     8888888888   b.             8 \n", delayBanner);
        print_with_delay("\033[31m8 8888    `88.m   .888.         .`8888:' `88.  .`8888:' `88. \033[35m   8888     `88.   8888         888o.          8 \n", delayBanner);
        print_with_delay("\033[31m8 8888     `88  :88888.        8.`8888.   Y8  8.`8888.   Y8 \033[35m,8 8888       `8.  8888         Y88888o.       8 \n", delayBanner);
        print_with_delay("\033[31m8 8888     ,88 . `88888.       `8.`8888.      `8.`8888.     \033[35m88 8888            8888         .`Y888888o.    8 \n", delayBanner);
        print_with_delay("\033[31m8 8888.   ,88.8. `88888.       `8.`8888.      `8.`8888.    \033[35m88 8888            888888888888 8o. `Y888888o. 8 \n", delayBanner);
        print_with_delay("\033[31m8 888888888P.8`8. `88888.       `8.`8888.      `8.`8888.   \033[35m88 8888            8888         8`Y8o. `Y88888o8 \n", delayBanner);
        print_with_delay("\033[31m8 8888      .8' `8. `88888.       `8.`8888.      `8.`8888.  \033[35m88 8888   8888888  8888         8   `Y8o. `Y8888 \n", delayBanner);
        print_with_delay("\033[31m8 8888     .8'   `8. `88888.  8b   `8.`8888. 8b   `8.`8888. \033[35m`8 8888       .8'  8888         8      `Y8o. `Y8 \n", delayBanner);
        print_with_delay("\033[31m8 8888    .888888888. `88888. `8b.  ;8.`8888 `8b.  ;8.`8888  \033[35m  8888     ,88'   8888         8         `Y8o.` \n", delayBanner);
        print_with_delay("\033[31m8 8888   .8'       `8. `88888. `Y8888P ,88P'  `Y8888P ,88P'   \033[35m  `8888888P'     888888888888 8            `Yo \n\033[0m", delayBanner);

        print_with_delay("\n\n                                                                   \033[1;97mWelcome to Pass-Gen! - Created by omarDans\n", delayBanner);
        print_with_delay("\n\033[0mHow long do you want the password to be: ", delayText);
        scanf("%d", &length);
        clearInputBuffer();
        print_with_delay("\nwhat characters do you want to have on your password:\n-lowerLetters(l)\n-upperLetters(u)\n-numbers(n)\n-symbols(s): ", 0.01);
        fgets(pass_type, sizeof(pass_type), stdin);
        print_with_delay("Choose the number of password to generate (default: 1): ", delayText);
        scanf("%c", &c);
        if (c != '\n') {
            numero = c - '0';
            clearInputBuffer();
        }
    }
    char run_again = '\n';
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
        printf("Press enter to regenerate the passwords or enter any key to exit: ");
        scanf("%c", &run_again);
    }
    clearInputBuffer();
    if (gui == 1){
        printf("Do you want to save the password(s) in a file?(y/n): ");
        scanf("%c", &archivo);
        clearInputBuffer();
    }
    
    if (tolower(archivo) == 'y'){
        savePassword(passwords, numero);
    }
    for (int i = 0; i < numero; i++) {
        free(passwords[i]);
    }
    free(passwords);
    return 0;
}

void preciseSleep(double seconds) {
    LARGE_INTEGER frequency;
    LARGE_INTEGER start;
    LARGE_INTEGER end;

    // Obtener la frecuencia del contador de rendimiento
    QueryPerformanceFrequency(&frequency);

    // Obtener el valor actual del contador de rendimiento
    QueryPerformanceCounter(&start);

    // Calcular el tiempo de espera en ticks
    LONGLONG waitTicks = (LONGLONG)(seconds * frequency.QuadPart);

    do {
        // Obtener el valor actual del contador de rendimiento
        QueryPerformanceCounter(&end);
    } while ((end.QuadPart - start.QuadPart) < waitTicks);
}

void print_with_delay(const char *str, double delay) {
    while (*str) {
        putchar(*str++);
        fflush(stdout);
        preciseSleep(delay);
    }
}

void clearInputBuffer() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF) {}

}

void clearPasswords(char** password, int numero, int lenght) {
    for (int i = 0; i < numero; i++) {
        memset(password[i], 0, lenght);
    }
}

void generatePass(char *password, int length, char *pass_type)
{
    static const char symbols[] = "@#+-/()[]{}$&=?!";
    static const char numbers[] = "123456789";
    static const char mayus[] = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
    static const char minus[] = "abcdefghijklmnopqrstuvwxyz";
    
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
