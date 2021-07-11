/* This game is made by Tushaar Gusain
NIT Hamirpur
Github - gt2k01

Instructions - Fairly simple game just run it and play using arrow keys.
            Game gets over when snake bites itself.

            * Greed loses what it has gained*
                        :)
*/



#include <iostream>
#include <conio.h>
#include <windows.h>
using namespace std;

//these are keys for gameplay
#define KEY_UP 72
#define KEY_DOWN 80
#define KEY_LEFT 75
#define KEY_RIGHT 77

//Here are the variables of grid and snake
bool gameover;
const int breadth = 20;
const int height = 20;
int x, y, fruitx, fruity, points;
int tailx[100], taily[100];
int snake_size;
enum Directon { STOP = 0, LEFT, RIGHT, UP, DOWN};
Directon dir;

void Start() //initializing
{
    gameover = false;
    dir = STOP;
    x = breadth / 2;
    y = height / 2;
    fruitx = rand() % breadth;
    fruity = rand() % height;
    points = 0;
}

void Make() //Making the grid
{
    system("cls"); //clear screen
    for (int i = 0; i < breadth+2; i++)
        cout << "-";    //making horizontal wall
    cout << endl;

    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < breadth; j++)
        {
            if (j == 0)
                cout << "|";    //making vertical wall
            if (i == y && j == x)
                cout << "O";    //this is snake head
            else if (i == fruity && j == fruitx)
                cout << "F";    //this is its food
            else
            {
                bool print = false;
                for (int k = 0; k < snake_size; k++)
                {
                    if (tailx[k] == j && taily[k] == i)
                    {
                        cout << "o";    //print the rest part of snake, the tail
                        print = true;
                    }
                }
                if (!print)
                    cout << " ";
            }


            if (j == breadth - 1)
                cout << "|";
        }
        cout << endl;
    }

    for (int i = 0; i < breadth+2; i++)
        cout << "-";
    cout << endl;
    cout << "Score:" << points << endl;
}
void Command()
{
    if (_kbhit())   //checking which key is entered from user
    {
        switch (_getch())
        {
        case KEY_LEFT:
            dir = LEFT;
            break;
        case KEY_RIGHT:
            dir = RIGHT;
            break;
        case KEY_UP:
            dir = UP;
            break;
        case KEY_DOWN:
            dir = DOWN;
            break;
        case 'x':
            gameover = true;
            break;
        }
    }
}
void Gameplay()
{
    int prevX = tailx[0];   //these are used to print the snake as it goes ahead.
    int prevY = taily[0];   //Its current position is taken by its hind part
    int prev2X, prev2Y;
    tailx[0] = x;
    taily[0] = y;
    for (int i = 1; i < snake_size; i++)
    {
        prev2X = tailx[i];
        prev2Y = taily[i];
        tailx[i] = prevX;
        taily[i] = prevY;
        prevX = prev2X;
        prevY = prev2Y;
    }
    switch (dir)
    {
    case LEFT: //changing coordinates according to direction
        x--;
        break;
    case RIGHT:
        x++;
        break;
    case UP:
        y--;
        break;
    case DOWN:
        y++;
        break;
    default:
        break;
    }

    if (x >= breadth) x = 0; else if (x < 0) x = breadth - 1;   //if snake touches the wall it comes from the other side
    if (y >= height) y = 0; else if (y < 0) y = height - 1;

    for (int i = 0; i < snake_size; i++)
        if (tailx[i] == x && taily[i] == y)
            gameover = true;    //it head bites its tail then gameover

    if (x == fruitx && y == fruity) //if snake eats food
    {
        points += 10;   //increase the score
        fruitx = rand() % breadth;
        fruity = rand() % height;   //changing its new food location randomly
        snake_size++;   //increasing snake size
    }
}
int main()
{
    int difficulty;
    cout << "Enter the difficulty level. 0 is highest and anything larger is easier." << endl;
    cout << "It affects the speed of gameplay. Press enter after entering value.\n";
    cin >> difficulty;
    Start();
    while (!gameover)
    {
        Make();
        Command();
        Gameplay();
        Sleep(difficulty);
    }
    cout << "Your final score is " << points << endl;
    return 0;
}
