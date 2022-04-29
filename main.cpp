#include <bits/stdc++.h>
using namespace std;

int ara[100][100];
bool revealed[100][100];
bool flagged[100][100];
bool gameOver;
int nof = 0, marked = 0;
int r = 15;
int c = 15;
int x, y;
void print(int ara[100][100], int n, int m, int x, int y){
    printf("---");
    for(int i=0; i<2*m; i++) printf("---");
    printf("\n");
    for(int i=0; i<n; i++){
        printf("---");
        for(int j=0; j<m; j++){
            if(i == x && j == y) {
//                if(revealed[i][j])printf("\033[1;46;42m %c \033[0m", ara[i][j] == -1 ? 'x' : ara[i][j] == 0 ? ' ' : '0' + ara[i][j]);
                printf("\033[1;46m %c \033[0m", ara[i][j] == -1 ? 'x' : ara[i][j] == 0 ? ' ' : '0' + ara[i][j]);
            }
            else if(ara[i][j] == -1) printf("\033[1;41m x \033[0m");
            else {
                if(revealed[i][j]) printf("\033[1;42m %c \033[0m", ara[i][j] == 0 ? ' ' : '0'+ara[i][j]);
                else printf(" %c ", ara[i][j] == 0 ? ' ' : '0'+ara[i][j]);
            }
            printf("---");
        }
        printf("\n");
    }
    printf("---");
    for(int i=0; i<2*m; i++) printf("---");
    printf("\n");
}

//void color(char c, )

void printGameOver(){
    printf("_________________________________________________________________________\n");
    printf("_________________________________________________________________________\n");
    printf("_________________________________________________________________________\n");
    printf("_________________________________________________________________________\n");
    printf("_______________________________GAME OVER_________________________________\n");
    printf("_________________________________________________________________________\n");
    printf("_________________________________________________________________________\n");
    printf("_________________________________________________________________________\n");
    printf("_________________________________________________________________________\n");
    printf("_________________________________________________________________________\n");
}


void print(){
    if(gameOver) {
        printGameOver();
        return;
    }
    int n = r;
    int m = c;
    printf("---");
    for(int i=0; i<2*m; i++) printf("---");
    printf("\n");

    for(int i=0; i<n; i++){
        printf("---");
        for(int j=0; j<m; j++){
            if(i == x && j == y){
                if(flagged[x][y]) printf("\033[1;45m F \033[0m");
                else if(revealed[x][y])printf("\033[1;46m %c \033[0m", ara[i][j] == 0 ? ' ' : '0' + ara[i][j]);
                else printf("\033[1;46m   \033[0m");
            }else {
                if(flagged[i][j]) printf("\033[1;41m F \033[0m");
                else if(revealed[i][j])printf("\033[1;42m %c \033[0m", ara[i][j] == 0 ? ' ' : '0' + ara[i][j]);
                else printf("   ");
            }
            printf("---");
        }
        printf("\n");
    }
    printf("---");
    for(int i=0; i<2*m; i++) printf("---");
    printf("\n");

}

void validateAndAddToQueue(int x, int y, queue<pair<int, int> > &q){
    if(x >= 0 && x < r && y >= 0 && y < c){
        if(revealed[x][y]) return;
        if(ara[x][y] == -1) return;
        else {
            revealed[x][y] = true;
            if(ara[x][y] == 0) q.push({x, y});
        }
    }
}

void revealFrom(int xx, int yy){
    queue<pair<int, int> > q;
    q.push({xx, yy});
    while(!q.empty()){
        pair<int, int> cxy = q.front();
        q.pop();
        int cx = cxy.first;
        int cy = cxy.second;
        validateAndAddToQueue(cx - 1, cy-1, q);
        validateAndAddToQueue(cx - 1, cy, q);
        validateAndAddToQueue(cx - 1, cy+1, q);
        validateAndAddToQueue(cx, cy-1, q);
        validateAndAddToQueue(cx, cy+1, q);
        validateAndAddToQueue(cx + 1, cy-1, q);
        validateAndAddToQueue(cx + 1, cy, q);
        validateAndAddToQueue(cx + 1, cy+1, q);
    }
}

void initiate(int rr = 15, int cc = 15, int density = 2){
        nof = 0;
        r = rr;
        c = cc;
        x = r/2;
        y = c/2;
        marked = 0;
        gameOver = false;
        for(int i=0; i<r; i++){
            for(int j=0; j<c; j++){
                revealed[i][j] = false;
                flagged[i][j] = false;
                int b = rand() % 10;
                if(b < density && !(x == i && y == j)) {
                    ara[i][j] = -1;
                    nof++;
                }
                else ara[i][j] = 0;
            }
        }
        for(int i=0; i<r; i++){
            for(int j=0; j<c; j++){
                if(ara[i][j] != -1)
                    for(int k=-1; k<2; k++){
                        for(int l=-1; l<2; l++){
                            if(i+k >= 0 && i+k < r && j+l >= 0 && j+l < c){
                                if(ara[i+k][j+l] == -1) ara[i][j]++;
                            }
                        }
                    }
            }
        }
        revealed[x][y] = true;
        revealFrom(x, y);
}

int main(){
    srand(time(NULL));
    initiate();
    while(true){
        char com;
        for(int i=0; i<30; i++) printf("\n");
        printf("Number of Total Mines: %d, Marked: %d\n", nof, marked);
        print();
        scanf("%c", &com);
        if(com == 'd' && y < c-1) y++;
        else if(com == 'a' && y > 0) y--;
        else if(com == 'w' && x > 0) x--;
        else if(com == 's' && x < r-1) x++;
        else if(com == 'r') {
            printf("Row, Column, Density: ");
            int row, column, density;
            scanf("%d %d %d", &row, &column, &density);
            initiate(row, column, density);
        }
        else if(com == 'm') {
            if(ara[x][y] == -1){
                cout<<"GAME OVER :(";
                gameOver = true;
            }
            revealed[x][y] = true;
            if(ara[x][y] == 0) revealFrom(x, y);
        }else if(com == 'f'){
            if(revealed[x][y]) continue;
            if(flagged[x][y]) {
                flagged[x][y] = false;
                marked--;
            }else{
                flagged[x][y] = true;
                marked++;
            }
        }
    }
    return 0;
}