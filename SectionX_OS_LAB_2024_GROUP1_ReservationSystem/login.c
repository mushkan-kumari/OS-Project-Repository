#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <string.h>

#define PORT 8080

//Enter these details to start the server
//Admin username: mushkan_kumari
//Admin password: mus123

int user_count;
int login = 0;

int hash_password(char *password) {
    int hash = 0;
    while (*password) {
        hash += *password++;
    }
    return hash;
}

int login_user(const char *uname, char *pass,char* option) {
    char hashed_password[100], username[100], password[100], role[10];
    sprintf(hashed_password, "%d", hash_password(pass));

    FILE *file = fopen("users.txt", "r");
    if (file == NULL) return 0;

    fscanf(file, "%d", &user_count);
    for (int i = 0; i < user_count; i++) {
        fscanf(file, "%s %s %s", username, password, role);
        if (strcmp(username, uname) == 0 && strcmp(password, hashed_password) == 0 && strcmp(role,option)==0) {
                fclose(file);
                return 1; // Successful login
            } 
    }
     printf("\nIncorrect credentials or role!! Please try again...\n\n");
    fclose(file);
    printf("\nInvalid username or password!\n\n");
    return 0;
}

int main() {
    int opt;
    char username[50] = {0};
    char password[50] = {0};

    do {
        printf("\n==========================================\n");
        printf("   Welcome to Railway Reservation System\n");
         printf("\t\tLOGIN PAGE\n");
        printf("==========================================\n");
        printf("[1] User \n");
        printf("[2] Admin\n");
        printf("[3] Exit Login Page\n");
        printf("\n\nChoose an option: ");
        scanf("%d", &opt);
        getchar(); 

            switch (opt) {
                case 1:{
                    if (access("./client", F_OK) == -1) {
                        // Compile the client program
                        if (system("gcc client1.c -o client") == -1) {
                            perror("Compilation failed");
                            return EXIT_FAILURE;
                        }
                    }

                    // Execute the client program
                    char *args[] = {"./client", NULL}; // Arguments for the client executable
                    execvp(args[0], args); // Execute the client program

                    // If execvp returns, there was an error
                    perror("execvp failed");
                    return EXIT_FAILURE;
                    break;
                }

                case 2:{
                  printf("Enter username: ");
                 fgets(username, sizeof(username), stdin);
                 username[strcspn(username, "\n")] = 0;
        
                 printf("Enter password: ");
                 fgets(password, sizeof(password), stdin);
                 password[strcspn(password, "\n")] = 0;
        
                 login = login_user(username, password,"admin");
                  if(login){
                    if (access("./server", F_OK) == -1) {
                        // Compile the server program
                        if (system("gcc server1.c -o server") == -1) {
                            perror("Compilation failed");
                            return EXIT_FAILURE;
                        }
                    }

                    // Execute the server program
                    char *arg[] = {"./server", NULL}; // Arguments for the server executable
                    execvp(arg[0], arg); 
                    perror("execvp failed");
                    return EXIT_FAILURE;
                }
            }
                    break;

                case 3:
                login=0;
                printf("\n\nExiting the Login page....\n\n");
                break;

                default:
                    printf("Invalid option. Please choose the right option.\n");
                    break;
            
            }
    } while (opt!=3);

    return EXIT_SUCCESS;
}




