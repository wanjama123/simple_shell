#include "shell"

#define MAX_COMMAND_LENGTH 1024
#define PROMPT "simple_shell$ "

void print_prompt() {
    printf("%s", PROMPT);
    fflush(stdout);
}

char* read_command() {
    char* command = (char*) malloc(MAX_COMMAND_LENGTH * sizeof(char));
    fgets(command, MAX_COMMAND_LENGTH, stdin);
    return command;
}

int main() {
    char* command;
    char* argv[MAX_COMMAND_LENGTH/2 + 1];
    int argc;
    int status;
    pid_t pid;

    while (1) {
        print_prompt();
        command = read_command();

        if (feof(stdin)) {
            printf("\n");
            break;
        }

        argc = 0;
        argv[argc] = strtok(command, " \t\r\n");

        while (argv[argc] != NULL) {
            argc++;
            argv[argc] = strtok(NULL, " \t\r\n");
        }

        if (argc == 0) {
            continue;
        }

        pid = fork();

        if (pid == -1) {
            perror("fork");
            exit(EXIT_FAILURE);
        }

        if (pid == 0) {
            if (execvp(argv[0], argv) == -1) {
                perror("execvp");
            }
            exit(EXIT_FAILURE);
        }

        if (waitpid(pid, &status, 0) == -1) {
            perror("waitpid");
            exit(EXIT_FAILURE);
        }

        free(command);
    }

    return 0;
}
