# include <stdio.h>
# include <string.h>
# include <unistd.h>
# include <stdlib.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <fcntl.h>
# include <signal.h>


int main() {
    // Example 1: Adding entries to the history
    add_history("ls -l");
    add_history("cd /path/to/directory");
    add_history("git commit -m 'Initial commit'");

    // Example 2: Clear the history
    clear_history();
    printf("History cleared.\n");
    // Now the history is empty, and previously added entries are removed.

    // Example 3: Replace the current input line
    char* user_input = readline("Enter a command: ");
    if (strncmp(user_input, "hello", 5) == 0) {
        // Replace the input line with a greeting
        rl_replace_line("Hello, how can I help you?", 1);
        rl_redisplay();
    } else {
        // Replace the input line with an error message
        rl_replace_line("Error: Invalid command!", 1);
        rl_redisplay();
    }
    free(user_input);

    // Example 4: Redisplay the current input line after a delay
    user_input = readline("Enter something and wait for 2 seconds: ");
    // Wait for 2 seconds (pretending some processing is happening)
    sleep(2);
    // Replace the input line to show the completion message
    rl_replace_line("Processing complete!", 1);
    rl_redisplay();
    free(user_input);

    // Example 5: Using rl_on_new_line to handle multiline input
    while (1) {
        user_input = readline("Enter multiple lines (type 'exit' to quit):\n");
        if (strncmp(user_input, "exit", 4) == 0) {
            free(user_input);
            break;
        }
        // Process the multiline input here
        // ...

        // Notify Readline that we are on a new line
        rl_on_new_line();
    }

    return 0;
}