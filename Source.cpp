#include<iostream>
#include<conio.h>
#include<Windows.h>

using namespace std;

bool gameOver;
//snake head coordinates
int x, y;
//fruit position
int FruitX, FruitY;
//score
int score;
//map dimensions
const int width=20;
const int height=20;
//snake tail coordinates
int TailX[100], TailY[100];
//tail length
int nTail;
//snake directions
enum Direction
{
	STOP = 0, LEFT, RIGHT, UP, DOWN
};

Direction dir;

void Setup()
{
	gameOver = false;//game is not over
	dir = STOP;//the snake does not move when the game starts
	//snake's head will be spawned in the center of the map
	x = width / 2;
	y = height / 2;
	//the fruit will be spawned in the random position
	FruitX = rand() % width;
	FruitY = rand() % height;
	//initial score
	score = 0;
}

void Draw() 
{
	// draw the map
	system("cls");
	//top of the map
	for (int i = 0; i < width+2; i++)
	{
		cout << "#";
	}
	cout << endl;
	//draw the rest of the map
	for (int i = 0; i < width; i++)
	{
		for (int j = 0; j < height; j++)
		{
			if(j == 0)
			{
				cout << "#";
			}
			//snake head
			if (i==y && j==x)
			{
				cout << "0";
			}
			else if (i==FruitY && j==FruitX)
			{
				cout << "F";//fruit
			}
			else
			{
				bool print = false;

				for (int k = 0; k < nTail; k++)
				{
					if (TailX[k] == j && TailY[k] == i)
					{
						cout << "o";
						print = true;
					}
				}
				
				if (!print)
					cout << " ";
			}
			
			if (j == height - 1)
			{
				cout << "#";
			}
		}
		cout << endl;
	}
	//bottom of the map
	for (int i = 0; i < width+2; i++)
	{
		cout << "#";
	}
	cout << endl;
	cout << "Score: " << score;
}

void Input()
{//check if the key is pressed
	if (_kbhit())
	{
		switch (_getch())//snake's is moving pressing w,a,s,d keys
		{
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
		}
	}
}

void Logic()
{
	//moving the tail along with the head
	int prevX = TailX[0];
	int prevY = TailY[0];
	int prev2X, prev2Y;
	TailX[0] = x;
	TailY[0] = y;
	for (int i = 1; i < nTail; i++)
	{
		prev2X = TailX[i];
		prev2Y = TailY[i];
		TailX[i] = prevX;
		TailY[i] = prevY;
		prevX = prev2X;
		prevY = prev2Y;
	}
	//switching direction
	switch (dir)
	{
	case UP:
		y--;
		break;
	case LEFT:
		x--;
		break;
	case DOWN:
		y++;
		break;
	case RIGHT:
		x++;
		break;
	default:
		break;
	}
	//if the snake hits the wall the game is over
	if (x > width || x < 0 || y < 0 || y > height)
	{
		gameOver = true;
	}
	// if the snake hits his tail the game is over
	for (int i = 0; i < nTail; i++)
	{
		if (TailX[i]==x && TailY[i]==y)
		{
			gameOver = true;
		}
	}
	//increase the tail of the snake when he got the fruit
	if (x==FruitX && y==FruitY)
	{
		//increase the tail
		nTail++;
		//score increases with 10 points
		score += 10;
		//the fruit will be spawned in the random position
		FruitX = rand() % width;
		FruitY = rand() % height;
	}
}

int main()
{
	Setup();

	while (!gameOver)
	{
		Draw();
		Input();
		Logic();
		Sleep(10);
	}
	return 0;
}