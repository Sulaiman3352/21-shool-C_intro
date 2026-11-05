#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>
#include <termios.h>
#include <signal.h>
#include <string.h>

static struct termios old_termios, new_termios;

void reset_terminal() {
    printf("\e[m"); // reset color changes
    printf("\e[?25h"); // show cursor
    fflush(stdout);
    tcsetattr(STDIN_FILENO, TCSANOW, &old_termios);
}

void configure_terminal(){
    tcgetattr(STDIN_FILENO, &old_termios);
    new_termios = old_termios; // save it to be able to reset on exit

    new_termios.c_lflag &= ~(ICANON | ECHO); // tern off echo + non-canonical input mode
    new_termios.c_cc[VMIN] = 0;
    new_termios.c_cc[VTIME] = 0;

    tcsetattr(STDIN_FILENO, TCSANOW, &new_termios); // finishing the the setup for tern off echo + non-canonical

    printf("\e[?25l]"); // hide cursor
    atexit(reset_terminal); // the func we will call when we exit the program
}

int read_key(char* buf, int q){
    if (buf[q] == '\141' && buf[q + 1] == '['){
        switch (buf[q + 2])
        {
        case 'a': return 1; // up for p1
        }
    }
    else if (buf[q] == '\172' && buf[q + 1] == '['){
        switch (buf[q + 2])
        {
        case 'z': return 2; // down for p1
        }
    }
    else if (buf[q] == '\153' && buf[q + 1] == '['){
        switch (buf[q + 2])
        {
        case 'k': return 3; // up for p2
        }
    }
    else if (buf[q] == '\155' && buf[q + 1] == '['){
        switch (buf[q + 2])
        {
        case 'm': return 4; // down fir p2
        }
    }
}

int read_input(){
    char buf[4096]; // maximum input buffer size
    int n = read(STDIN_FILENO, buf, sizeof(buf));
    int final_key = 0;

    for (int k = 0; k <= n -3; k+=3){
        int key = read_key(buf, k);
        if (key == 0) continue;
        final_key = key;
    }
    return final_key;
}

// print the input to make sure we are getting the correct input
void print_key(int key){
    if (key == 1) printf("p1 pressed up");
    if (key == 2) printf("p1 pressed down");
    if (key == 3) printf("p2 pressed up");
    if (key == 4) printf("p2 pressed down");
}

int main(){
    configure_terminal(); // to setup non-canonical mode
    while (1)  // the game loop
    {
        int key = read_input();
        printf_key(key);
        sleep(0.1seconds);
    }
    return 0;
}