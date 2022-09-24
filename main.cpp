#include <iostream>
#include <Windows.h>
#include <conio.h>
#include <ctime>
#include <cstdlib>

using namespace std;

bool gameOver=false;
const int width = 40, height = 20;
int x, y, fruitX, fruitY, score;
int tailX, tailY;
int nTail=2;
int table[height][width];
enum eDirecton {STOP = 0, RIGHT, UP, LEFT, DOWN};
eDirecton dir;

void setup(){
    //gameOver=false;

    dir = STOP;

    x = width / 2;
    y = height / 2;


    for(int i=0; i <= nTail; i++){
        table[y][x-i]=-1;
        //cout << "table[y][x-"<<i<<"]=-1;" <<endl;
    }

    tailX=x-nTail;
    tailY=y;

    srand(time(0));
    fruitX = rand() % width-2;
    fruitY = rand() % height-2;
    table[fruitY][fruitX] = 1;

    score = 0;
}

bool isGameover(int mode){
    //bool gameOver=false;
    switch(mode){
    case 0:
        if(x >= width || x < 0 || y >= height || y < 0 ) //outside of the area
            gameOver=true;
        if(x == tailX && y == tailY)
            gameOver=true;
        break;
    case 1:
        system("pause");
        exit(0);
        break;
    default:
        gameOver=false;
        if(x >= width || x < 0 || y >= height || y < 0 ) //outside of the area
            gameOver=true;
        if(x == tailX && y == tailY)
            gameOver=true;

    }

    return gameOver;
}

void draw(int mode=0){
    system("cls");
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    cout<<"score: "<<score<<endl;

    switch(mode){
    case 0:
        for(int i =0; i < height;i++){ // Print Table
            for(int j =0; j < width; j++){

                SetConsoleTextAttribute(hConsole, 7);
                if(i == 0 || i == height - 1 || j == 0 || j == width-1){
                    cout<<"*";
                    //cout << table[i][j]<<endl;
                }
                else if(table[i][j] == 1){
                    SetConsoleTextAttribute(hConsole, 4);
                    cout<<"F";
                }
                else if(table[i][j] < 0){
                    SetConsoleTextAttribute(hConsole, 6);
                    cout<<"O";
                }
                /*else if(table[i][j] < 0){
                    SetConsoleTextAttribute(hConsole, 6);
                    cout<<"O";

                }*/
                else{
                    cout <<" ";
                }

            }
            cout << endl;
        }
        break;
    case 1:
        for(int i =0; i < height;i++){
            for(int j =0; j < width; j++){
                cout << " " <<table[i][j]<<" ";
            }
            cout<<endl;
        }
        break;

    }

    /*for(int i =0; i < height;i++){
        for(int j =0; j < width; j++){
            cout << " " <<table[i][j]<<" ";
        }
        cout<<endl;
    }*/

    //fruit




}

void moveTail(int tailDir){
    switch(tailDir){
        case -2: // up
            table[tailY][tailX] = 0;
            tailY--;
            break;
        case -4: // down
            table[tailY][tailX] = 0;
            tailY++;
            break;
        case -3: //left
            table[tailY][tailX] = 0;
            tailX--;
            break;
        case -1: // right
            table[tailY][tailX] = 0;
            tailX++;
            break;
    }
}

void addTail(){
    switch(table[fruitY][fruitX]){
        case -2:
            tailY++;
            table[tailY][tailX] = -2;
            //moveTail(table[tailY][tailX]);
            break;
        case -4:
            tailY--;
            table[tailY][tailX] = -4;
            //moveTail(table[tailY][tailX]);
            break;
        case -3:
            tailX++;
            table[tailY][tailX] = -3;
            //moveTail(table[tailY][tailX]);
            break;
        case -1:
            tailX--;
            table[tailY][tailX] = -1;
            //moveTail(table[tailY][tailX]);
            break;
        }
}

void logic(){
    if(x == fruitX && y == fruitY){
        score++;
        addTail();


        fruitX = rand() % width-2;
        fruitY = rand() % height-2;
        do{
            fruitX = rand() % width-2;
            fruitY = rand() % height-2;
        } while((fruitX >= width || fruitX <= 0 || fruitY >= height || fruitY <= 0) || (fruitX >= tailX && fruitY >= tailY) );
        table[fruitY][fruitX] = 1;
    }

    switch(dir){
    case UP:
        cout << table[y-1][x] << endl;
        if(table[y-1][x] < 0){
            cout << "gameover by: case UP: Line 185" << endl;
            isGameover(1);
        }
        table[y][x] = -2;
        y--;
        table[y][x] = -2;
        moveTail(table[tailY][tailX]);
        break;
    case DOWN:
        cout << table[y+1][x] << endl;
        if(table[y+1][x] < 0){
            cout << "gameover by: case DOWN: Line 196" << endl;
            isGameover(1);
        }
        table[y][x] = -4;
        y++;
        table[y][x] = -4;
        moveTail(table[tailY][tailX]);
        break;
    case LEFT:
        cout << table[y][x-1] << endl;
        if(table[y][x-1] < 0){
            cout << "gameover by: case LEFT: Line 207" << endl;
            isGameover(1);
        }
        table[y][x] = -3;
        x--;
        table[y][x] = -3;
        moveTail(table[tailY][tailX]);
        break;
    case RIGHT:
        cout << table[y][x+1] << endl;
        if(table[y][x+1] < 0){
            cout << "gameover by: case RIGHT: Line 218" << endl;
            isGameover(1);
        }
        table[y][x] = -1;
        x++;
        table[y][x] = -1;
        moveTail(table[tailY][tailX]);
        break;
    }
}

void input(){
    cout << "fruitAxis : (" << fruitY<<","<<fruitX << ")"<<endl;
    cout << "tailAxis : (" << tailY<<","<<tailX << ")"<<endl;
    cout << "headAxis : (" << y<<","<<x << ")"<<endl;
    if(_kbhit()){
        switch(_getch()){
        case 'w':
            if(dir == DOWN)
                break;
            dir = UP;
            break;
        case 's':
            if(dir == UP)
                break;
            dir = DOWN;
            break;
        case 'a':
            if(dir == RIGHT)
                break;
            dir = LEFT;
            break;
        case 'd':
            if(dir == LEFT)
                break;
            dir = RIGHT;
            break;

        //capital letter
        case 'W':
            if(dir == DOWN)
                break;
            dir = UP;
            break;
        case 'S':
            if(dir == UP)
                break;
            dir = DOWN;
            break;
        case 'A':
            if(dir == RIGHT)
                break;
            dir = LEFT;
            break;
        case 'D':
            if(dir == LEFT)
                break;
            dir = RIGHT;
            break;
        case 'x':
            isGameover(1);
            break;
        case 'p':
            system("pause");
            break;
        }
    }
}

int main()
{
    //system("color 04");
    setup();
    while(!isGameover(0)){
        draw();
        input();
        logic();
        //system("CLS");
        Sleep(100);
    }
    //draw();

    return 0;
}