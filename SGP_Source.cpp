#include<iostream>
#include<conio.h>
#include<windows.h>
#include<string>

using namespace std;

bool gameOver;

bool introScreen();
bool gameOverScreen();
void gameScreen();
void setup();
void draw();
void input();
void logic();

const int width = 20;
const int height = 20;
string choice;
int x, y, fruitX, fruitY, score;
int tailX[100], tailY[100], ntail;
enum eDirection { Stop = 0, Left, Right, Up, Down };
eDirection dir;

int main()
{
	setup();
	bool x = introScreen();
	if (x == false)
		if (gameOverScreen() == false)
		{
			cout << endl;
			cout << "     Thanks For Playing! - Tyrone B." << endl;
			system("pause");
		}
	else if (x == true)
		gameScreen();
	
}

bool introScreen()
{
	// Drawing ceiling
	for (int i = 0; i < width*2; i++)
		cout << "-";
	cout << endl;
	// Displaying welcome sign
	for (int i = 0; i < width/2; i++)
		cout << " ";
	cout << "Welcome to SNAKE!" << endl << endl;
	// Displaying the controls
	for (int i = 0; i < width-9; i++)
		cout << " ";
	cout << "CONTROLS KEYS:" << endl;
	for (int i = 0; i < width-6; i++)
		cout << " "; cout << "W - Up" << endl;
	for (int i = 0; i < width-6; i++)
		cout << " "; cout << "S - Down" << endl;
	for (int i = 0; i < width-6; i++)
		cout << " "; cout << "A - Left" << endl;
	for (int i = 0; i < width-6; i++)
		cout << " "; cout << "D - Right" << endl << endl;
	// Explaing the rules
	for (int i = 0; i < 12; i++)
		cout << " ";
	cout << "INFORMATION:" << endl;
	for (int i = 0; i < 10; i++)
		cout << " ";
	cout << "Eat the fruit 'F'!" << endl;
	for (int i = 0; i < 4; i++)
		cout << " ";
	cout << "You can go through the walls." << endl;
	for (int i = 0; i < 4; i++)
		cout << " ";
	cout << "Each fruit is worth 10 points." << endl;

	for (int i = 0; i < width * 2; i++)
		cout << "-";
	cout << endl << endl;
	cout << "ooooO Are you ready to play? [y/n] Ooooo" << endl;
	cout << "           >> "; cin >> choice;
	if (choice == "y")
		return true;
	else
		return false;
}

void gameScreen()
{
	while (!gameOver)
	{
		draw();
		input();
		logic();
		Sleep(60); //Slows down the game a little bit
	}
	gameOverScreen();
}

bool gameOverScreen()
{
	system("cls");
	for (int i = 0; i < width*2; i++)
		cout << "-";
	cout << "-" <<endl;

	for (int i = 0; i < 8; i++)
		cout << "> ";
	cout << "GAME OVER ";
	for (int i = 0; i < 8; i++)
		cout << "< ";
	cout << endl << endl;

	for (int i = 0; i < width-6; i++)
		cout << " ";
	cout << "Your Score: " << score << endl;
	for (int i = 0; i < width - 6; i++)
		cout << " ";
	cout << "Tail length: " << score / 10 << endl;

	for (int i = 0; i < width * 2; i++)
		cout << "-";
	cout << "-" << endl << endl;

	for (int i = 0; i < 4 ; i++)
		cout << " ";
	cout << "ooooO Play again? [y/n] Ooooo" << endl;
	cout << "           >> "; cin >> choice;
	if (choice == 'y')
		return true;
	else
		return false;
	
}

void setup()
{
	gameOver = false;
	dir = Stop;
	x = width / 2;
	y = height / 2;
	fruitX = rand() % width; // Creates a random number from 0 to width-1
	fruitY = rand() % height;
	score = 0;
}

void draw()
{
	system("cls");
	for (int i = 0; i < width + 2; i++)
		cout << "#";
	cout << endl;

	for (int i = 0; i < height; i++)
	{
		for (int j = 0; j < width; j++)
		{
			if (j == 0)
				cout << "#";
			if (i == y & j == x)
				cout << "O";
			else if (i == fruitY && j == fruitX)
				cout << "F";
			else
			{
				bool print = false;
				for (int k = 0; k < ntail; k++)
				{
					if (tailX[k] == j && tailY[k] == i)
					{
						cout << "o";
						print = true;
					}
				}
				if (!print)
					cout << " ";
			}

			if (j == width - 1)
				cout << "#";
		}
		cout << endl;
	}

	for (int i = 0; i < width + 2; i++)
		cout << "#";
	cout << endl;
	cout << "Score: " << score << endl;
}

void input()
{
	/// Keyboard inputs to control the snake
	if (_kbhit())
	{
		switch (_getch())
		{
		case 'a':
			dir = Left;
			break;
		case 'd':
			dir = Right;
			break;
		case 'w':
			dir = Up;
			break;
		case 's':
			dir = Down;
			break;
		case 'x':
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
	tailX[0] = x;
	tailY[0] = y;
	
	/// Generates your extended tail to follow your previous location
	for (int i = 1; i < ntail; i++)
	{
		prev2X = tailX[i];
		prev2Y = tailY[i];
		tailX[i] = prevX;
		tailY[i] = prevY;
		prevX = prev2X;
		prevY = prev2Y;
	}
	
	switch (dir)
	{
	case Left:
		x--;
		break;
	case Right:
		x++;
		break;
	case Up:
		y--;
		break;
	case Down:
		y++;
		break;
	default:
		break;
	}
	/// If you hit the walls it's game over
	//if (x > width || x < 0 || y > height || y < 0)
	//	gameOver = true;

	/// You can go through the walls and come out on the over side
	if (x >= width)
		x = 0;
	else if (x < 0)
		x = width - 1;
	if (y >= height)
		y = 0;
	else if
		(y < 0) y = height - 1;

	for (int i = 0; i < ntail; i++)
		if (tailX[i] == x && tailY[i] == y)
			gameOver = true;
	
	/// If your head lands on the fruit you gain points and a longer tail
	if (x == fruitX && y == fruitY)
	{
		score += 10;
		fruitX = rand() % width; // Creates a random number from 0 to width-1
		fruitY = rand() % height;
		ntail++;
	}

	/// Just messing with the speed
	/*
	if (score >= 50)
		Sleep(25);
	else if (score == 40)
		Sleep(10);
	else if (score == 30)
		Sleep(60);
	else if (score == 20)
		Sleep(10);
	else if (score == 10)
		Sleep(70);
	else
		Sleep(10);
		*/
}