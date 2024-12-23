#include<stdio.h>
#include<string.h>

typedef struct {
    int cellat;
    int round;
} PLAYER;

typedef struct {
    int start_cell;
    int end_cell;
} SNAKE;

typedef struct {
    int start_cell;
    int end_cell;
} LADDER;

typedef struct {
    PLAYER *player;
    SNAKE *snake;
    LADDER *ladder;
    int final_cell;
} CELL;

PLAYER players[100];
SNAKE snakes[100];
LADDER ladders[100];
CELL cells[10005];

int k, m, n, l, s, r;

const int lead_to_loop = -1;
const int multiway = -2;
const int completed = -3;
const int white = 0;
const int gray = 1;
const int black = 2;

int status[10000];

int dfs(int cur_cell) {
    if(status[cur_cell] == gray) return lead_to_loop;
    if(status[cur_cell] == black) return cells[cur_cell].final_cell;

    status[cur_cell] = gray;
    int final_cell;

    if(cells[cur_cell].final_cell == multiway)
        final_cell = multiway;
    else if(cells[cur_cell].ladder == NULL && cells[cur_cell].snake == NULL) 
        final_cell = cur_cell;
    else if(cells[cur_cell].ladder != NULL)
        final_cell = dfs(cells[cur_cell].ladder->end_cell);
    else 
        final_cell = dfs(cells[cur_cell].snake->end_cell);

    status[cur_cell] = black;
    cells[cur_cell].final_cell = final_cell;
    
    return final_cell;
}

int main() {

    scanf("%d%d%d%d%d%d", &k, &m, &n, &l, &s, &r);

    for(int i = 0 ; i <= m * n ; i++) {
        cells[i].player = NULL;
        cells[i].snake = NULL;
        cells[i].ladder = NULL;
        cells[i].final_cell = i;
    }

    for(int i = 0 ; i < l ; i++) {
        scanf("%d%d", &ladders[i].start_cell, &ladders[i].end_cell);
        if(cells[ladders[i].start_cell].ladder)
            cells[ladders[i].start_cell].final_cell = multiway;
        else 
            cells[ladders[i].start_cell].ladder = &ladders[i];
    }

    for(int i = 0 ; i < s ; i++) {
        scanf("%d%d", &snakes[i].start_cell, &snakes[i].end_cell);
        if(cells[snakes[i].start_cell].snake || cells[snakes[i].start_cell].ladder)
            cells[snakes[i].start_cell].final_cell = multiway;
        else
            cells[snakes[i].start_cell].snake = &snakes[i];
    }

    memset(status, white, (m*n+1)*sizeof(int));
    
    for(int cur_cell = 1 ; cur_cell <= m*n ; cur_cell++) dfs(cur_cell);

    for(int i = 0 ; i < k ; i++) {
        players[i].cellat = 0;
        players[i].round = 0;
    }

    for(int round = 1 ; round <= r ; round++) {
        for(int pl = 0 ; pl < k ; pl++) {
            int roll;
            scanf("%d", &roll);
            
            if(players[pl].cellat == completed) continue;
            if(players[pl].cellat == lead_to_loop) continue;
            if(players[pl].cellat == multiway) continue;

            players[pl].round = round;

            int final_cell = players[pl].cellat + roll;

            if (final_cell > m * n) continue;

            cells[players[pl].cellat].player = NULL;
            
            if(final_cell == m * n) {
                players[pl].cellat = completed;
                continue;
            }


            final_cell = players[pl].cellat = cells[final_cell].final_cell;
            if(players[pl].cellat == lead_to_loop) continue;
            if(players[pl].cellat == multiway) continue;            

            if(cells[final_cell].player != NULL) {
                cells[final_cell].player->cellat = 0;
            }
            cells[final_cell].player = &players[pl];
        }
    }

    for(int i = 0 ; i < k ; i++) {
        if(players[i].cellat == completed) {
            printf("%d COMPLETED %d\n", i+1, players[i].round);
        } else if(players[i].cellat == lead_to_loop) {
            printf("%d LOOPING %d\n", i+1, players[i].round);
        } else if(players[i].cellat == multiway) {
            printf("%d MULTIWAY %d\n", i+1, players[i].round);
        } else {
            printf("%d %d %d\n", i+1, players[i].cellat, players[i].round);
        }
    }    

    return 0;
}