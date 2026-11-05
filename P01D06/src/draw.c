#include <stdio.h>

int place_for_player_1 = 5;
int place_for_player_2 = 20;
int score_for_player_1 = 0;
int score_for_player_2 = 0;
char input_1, input_2;
int x_ball = 50, y_ball = 20;

void g_horizontal_border_up() {
    printf("╔");
    for (int i = 1; i <= 80; i++) {
        printf("═");
    }
    printf("╗\n");
}
void g_horizontal_border_doun() {
    printf("╚");
    for (int i = 1; i <= 80; i++) {
        printf("═");
    }
    printf("╝\n");
}
void g_empty_line() {
    printf("║");
    for (int i = 1; i <= 80; i++) {
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

void graphic() {  // Диана
    printf("\033[H\033[J");
    g_horizontal_border_up();
    char s = ' ';
    for (int y = 0; y < 25; y++) {
        if (y_ball != y && g_rockets_in_y(y))
            g_empty_line();
        else {
            printf("║");
            for (int x = 0; x < 80; x++) {
                s = ' ';
                if (y_ball == y && x_ball == x) s = '0';
                // если не мяч то рокетка
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
    g_horizontal_border_doun();
    for (int i = 0; i < 20; i++) printf(" ");
    printf("PLAYER 1:%d", score_for_player_2);
    for (int i = 0; i < 10; i++) printf(" ");
    printf("PLAYER 2:%d\n", score_for_player_1);
}

void graphic_win() {  // Диана
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
    g_horizontal_border_doun();
}

int main() {
    graphic();
    graphic_win();
    return 0;
}
