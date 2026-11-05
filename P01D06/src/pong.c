
#include <stdio.h>

const int WIDTH = 80;
const int HEIGHT = 25;
int place_for_player_1 = HEIGHT / 2 - 1;
int place_for_player_2 = HEIGHT / 2 - 1;
int score_for_player_1 = 0;
int score_for_player_2 = 0;
int x_ball = WIDTH / 2;
int y_ball = HEIGHT / 2;
int x_dir = 1;
int y_dir = 1;

void g_horizontal_border_up() {
    printf("╔");
    for (int i = 1; i <= WIDTH; i++) {
        printf("═");
    }
    printf("╗\n");
}

void g_horizontal_border_down() {
    printf("╚");
    for (int i = 1; i <= WIDTH; i++) {
        printf("═");
    }
    printf("╝\n");
}

void g_empty_line() {
    printf("║");
    for (int i = 1; i <= WIDTH; i++) {
        printf(" ");
    }
    printf("║\n");
}

int g_rockets_in_y(int y) {
    for (int i = -1; i <= 1; i++) {
        if (place_for_player_1 + i == y) return 0;
        if (place_for_player_2 + i == y) return 0;
    }
    return 1;
}

void graphic() {
    printf("\033[H\033[J");  // Clear the screen
    g_horizontal_border_up();
    char s = ' ';
    for (int y = 0; y < HEIGHT; y++) {
        if (y_ball != y && g_rockets_in_y(y))
            g_empty_line();
        else {
            printf("║");
            for (int x = 0; x < WIDTH; x++) {
                s = ' ';
                if (y_ball == y && x_ball == x)
                    s = '0';
                else {
                    if (x == 9 && (place_for_player_1 + 1 == y || place_for_player_1 == y ||
                                   place_for_player_1 - 1 == y))
                        s = '|';
                    if (x == 69 && (place_for_player_2 + 1 == y || place_for_player_2 == y ||
                                    place_for_player_2 - 1 == y))
                        s = '|';
                }
                printf("%c", s);
            }
            printf("║\n");
        }
    }
    g_horizontal_border_down();
    for (int i = 0; i < 20; i++) printf(" ");
    printf("PLAYER 1:%d", score_for_player_1);
    for (int i = 0; i < 10; i++) printf(" ");
    printf("PLAYER 2:%d\n", score_for_player_2);
}

void graphic_win() {
    printf("\033[H\033[J");
    g_horizontal_border_up();
    for (int i = 0; i < 12; i++) g_empty_line();
    printf("║");
    for (int i = 0; i < 34; i++) {
        printf(" ");
    }
    if (score_for_player_1 > score_for_player_2)
        printf("PLAYER 1 WIN!");
    else
        printf("PLAYER 2 WIN!");

    for (int i = 0; i < 33; i++) {
        printf(" ");
    }
    printf("║\n");
    for (int i = 0; i < 13; i++) g_empty_line();
    g_horizontal_border_down();
}

int input() {
    char move = getchar();

    switch (move) {
        case ' ':
            return 1;
        case 'a':
        case 'A':
            if (place_for_player_1 > 1) place_for_player_1--;
            return 1;

        case 'z':
        case 'Z':
            if (place_for_player_1 < HEIGHT - 2) place_for_player_1++;
            return 1;

        case 'k':
        case 'K':
            if (place_for_player_2 > 1) place_for_player_2--;
            return 1;

        case 'm':
        case 'M':
            if (place_for_player_2 < HEIGHT - 2) place_for_player_2++;
            return 1;

        case '\n':
            return 0;

        default:
            return 0;
    }
}

void play_start() {
    x_ball += x_dir;
    y_ball += y_dir;

    if (y_ball <= 0 || y_ball >= HEIGHT - 1) {
        y_dir *= -1;
    }

    if (x_ball == 10 && (y_ball >= place_for_player_1 - 1 && y_ball <= place_for_player_1 + 1)) {
        x_dir *= -1;
    }
    if (x_ball == 69 && (y_ball >= place_for_player_2 - 1 && y_ball <= place_for_player_2 + 1)) {
        x_dir *= -1;
    }

    if (x_ball < 0) {
        score_for_player_2++;
        x_ball = WIDTH / 2;
        y_ball = HEIGHT / 2;
    }
    if (x_ball >= WIDTH) {
        score_for_player_1++;
        x_ball = WIDTH / 2;
        y_ball = HEIGHT / 2;
    }
}

int main() {
    while (score_for_player_1 < 21 && score_for_player_2 < 21) {
        if (input()) {
            play_start();
            graphic();
        }
    }

    graphic_win();

    return 0;
}
