#include <iostream>
#include <conio.h>
#include <windows.h>
//functions
int main();
void startGame();
void draw();
void input();
void logic();

//variables
bool gameOver;
const int height = 30, width = 30;
int playerX, playerY, fruitX, fruitY, score;
int tailX[100], tailY[100];
int nTail; //length of tail
enum Direction {STOP = 0, LEFT, RIGHT, UP, DOWN};
Direction dir;

void startGame(){
    gameOver = false;
    dir = STOP;
    //spawn locations
    playerX = width/2;
    playerY = height/2;
    fruitX = rand() % width;
    fruitY = rand() % height;
    score = 0;

}
void draw(){
    system("cls");
    //top wall
    for(int i =0; i< width+1; i++){
        std::cout<< "#";
    }
    std::cout<< std::endl;

    //Make game board
    for(int i =0; i< height; i++){
        for(int j =0; j<width; j++){
            if(j==0){
                std::cout << "#";
            }
            if (i == playerY && j == playerX){
                std::cout << "O";
            }
            else if (i == fruitY && j == fruitX){
                std::cout << "X";
            }
            else{
                bool print = false;
                for(int k = 0; k < nTail; k++){
                    if(tailX[k] == j && tailY[k] == i){
                        std::cout << "o";
                        print = true;
                    }
                }
                if(!print)
                    std::cout << " ";
            }

            if (j == width-1){
                std::cout << "#";

            }
        }
        std::cout << std::endl;
    }

    for (int i=0; i<width+1; i++){
        std::cout << "#";
    }
    std::cout<< std::endl;
    std::cout << "Score: "<< score << std::endl;
}
void input(){
    //return positive when key is pressed
    if(_kbhit()){
        switch(_getch()){
            case 'w':
                dir = UP;
                break;
            case 'a':
                dir = LEFT;
                break;
            case 's':
                dir = DOWN;
                break;
            case 'd':
                dir = RIGHT;
                break;
            case 'q':
                gameOver = true;
                break;
        }
    }
}
void logic()
{
    int prevX = tailX[0];
    int prevY = tailY[0];
    int prev2X, prev2Y;
    tailX[0] = playerX;
    tailY[0] = playerY;
    for (int i = 1; i< nTail; i++){
        prev2X = tailX[i];
        prev2Y = tailY[i];
        tailX[i] = prevX;
        tailY[i] = prevY;
        prevX = prev2X;
        prevY = prev2Y;
    }
    switch (dir)
    {
    //Changing coordinates of the snake
    case LEFT:
        playerX = playerX - 1 ;
        break;
    case RIGHT:
        playerX = playerX + 1 ;
        break;
    case UP:
        playerY = playerY - 1;
        break;
    case DOWN:
        playerY = playerY + 1;
        break;
    default:
        break;
    }
    //boundaries
    // Use this code below if you want to gameover if you hit the wall
    // if(playerX > width || playerX < 0 || playerY > height || playerY < 0){
    //     gameOver = true;
    // }
    //Snake hit wall goes to other side
    if (playerX >= width) {
        playerX = 0;
    }
    else if(playerX < 0){
        playerX = width-1;
    }
    if (playerY >= height) {
        playerY = 0;
    }
    else if(playerY < 0){
        playerY = height-1;
    }
    //Check if snake hits itself
    for (int i =0; i< nTail; i++){
        if (tailX[i] == playerX && tailY[i] == playerY){
            gameOver = true;
        }
    }
    //Eating fruit
    if(playerX == fruitX && playerY == fruitY){
        score+=10;
        fruitX = rand() % width;
        fruitY = rand() % height;
        nTail++;
    }
}
int main(){
    startGame();
    while(!gameOver){
        draw();
        input();
        logic();
        //make game slower
        Sleep(30);
    }
    return 0;
}