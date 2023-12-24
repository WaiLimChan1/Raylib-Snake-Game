#include"raylib.h"
#include<vector>
#include<cstdlib>
#include<time.h>
#include <iostream>

using namespace std;

/* Keybinds
* W,A,S,D To Move The Snake
* Press Space To Play Again
*/


class Point {
private:
	int x, y;
public:
	Point();
	Point(int x, int y);
	int getX();
	int getY();
	void setX(int x);
	void setY(int y);
};
Point::Point() {}
Point::Point(int x, int y) : x(x), y(y) {}
int Point::getX() { return x; }
int Point::getY() { return y; }
void Point::setX(int x) { this->x = x; }
void Point::setY(int y) { this->y = y; }

//Global Const Variables
//-------------------------------------
const int screenWidth = 1000;
const int screenHeight = 900;

const int boardWidth = 20;
const int boardHeight = 15;
char board[boardHeight][boardWidth];

const int boxWidth = 40;
const int paddingWidth = 6;
const int borderWidth = 10;

vector<Point> Snake(1);

enum Direction{STOP, UP, DOWN, LEFT, RIGHT};
Direction dir;

int fruitX, fruitY;
bool tailIncrease;
bool gameOver;
//-------------------------------------

void SetUp()
{
	if (Snake.size() > 1)
		Snake.erase(Snake.begin() + 1, Snake.begin() + Snake.size());

	Snake.at(0).setX(boardWidth / 2);
	Snake.at(0).setY(boardHeight / 2);

	dir = STOP;

	fruitX = rand() % boardWidth;
	fruitY = rand() % boardHeight;
	tailIncrease = false;
	gameOver = false;
}

void Store()
{
	for (int row = 0; row < boardHeight; row++)
		for (int column = 0; column < boardWidth; column++)
			board[row][column] = ' ';
	board[fruitY][fruitX] = 'F';
	board[Snake.at(0).getY()][Snake.at(0).getX()] = 'X';
	for (int i = 1; i < Snake.size(); i++)
		board[Snake.at(i).getY()][Snake.at(i).getX()] = 'x';
}

void Draw()
{
	BeginDrawing();
	ClearBackground(BLACK);
	if (!gameOver)
	{
		int offSetX = (GetScreenWidth() - ((boxWidth + paddingWidth) * boardWidth)) / 2;
		int offSetY = (GetScreenHeight() - ((boxWidth + paddingWidth) * boardHeight)) / 2;
		DrawRectangle(offSetX - boardWidth, offSetY - paddingWidth - borderWidth, borderWidth, ((boxWidth + paddingWidth) * boardHeight) + borderWidth * 2, WHITE);
		DrawRectangle(offSetX - boardWidth, offSetY - paddingWidth - borderWidth, ((boxWidth + paddingWidth) * boardWidth) - paddingWidth + boardWidth * 2, borderWidth, WHITE);
		for (int row = 0; row < boardHeight; row++)
		{
			for (int column = 0; column < boardWidth; column++)
			{
				if (board[row][column] == ' ')
					DrawRectangle(offSetX, offSetY, boxWidth, boxWidth, GRAY);
				else if (board[row][column] == 'X')
					DrawRectangle(offSetX, offSetY, boxWidth, boxWidth, DARKGREEN);
				else if (board[row][column] == 'x')
					DrawRectangle(offSetX, offSetY, boxWidth, boxWidth, GREEN);
				else if (board[row][column] == 'F')
					DrawRectangle(offSetX, offSetY, boxWidth, boxWidth, RED);
				offSetX += boxWidth + paddingWidth;
			}
			if (row == 0)
				DrawRectangle(offSetX + paddingWidth, offSetY - paddingWidth - borderWidth, borderWidth, ((boxWidth + paddingWidth) * boardHeight) + borderWidth * 3, WHITE);
			offSetX = (GetScreenWidth() - ((boxWidth + paddingWidth) * boardWidth)) / 2;
			offSetY += boxWidth + paddingWidth;
		}
		DrawRectangle(offSetX - boardWidth, offSetY - paddingWidth + borderWidth, ((boxWidth + paddingWidth) * boardWidth) - paddingWidth + boardWidth * 2, borderWidth, WHITE);
	}
	else
	{
		if (Snake.size() == boardWidth * boardHeight)
		{
			int offSetX = (GetScreenWidth() - ((boxWidth + paddingWidth) * boardWidth)) / 2;
			int offSetY = (GetScreenHeight() - ((boxWidth + paddingWidth) * boardHeight)) / 2;
			DrawRectangle(offSetX - boardWidth, offSetY - paddingWidth - borderWidth, borderWidth, ((boxWidth + paddingWidth) * boardHeight) + borderWidth * 2, WHITE);
			DrawRectangle(offSetX - boardWidth, offSetY - paddingWidth - borderWidth, ((boxWidth + paddingWidth) * boardWidth) - paddingWidth + boardWidth * 2, borderWidth, WHITE);
			for (int row = 0; row < boardHeight; row++)
			{
				for (int column = 0; column < boardWidth; column++)
				{
					if (board[row][column] == ' ')
						DrawRectangle(offSetX, offSetY, boxWidth, boxWidth, GRAY);
					else if (board[row][column] == 'X')
						DrawRectangle(offSetX, offSetY, boxWidth, boxWidth, DARKGREEN);
					else if (board[row][column] == 'x')
						DrawRectangle(offSetX, offSetY, boxWidth, boxWidth, GREEN);
					else if (board[row][column] == 'F')
						DrawRectangle(offSetX, offSetY, boxWidth, boxWidth, RED);
					offSetX += boxWidth + paddingWidth;
				}
				if (row == 0)
					DrawRectangle(offSetX + paddingWidth, offSetY - paddingWidth - borderWidth, borderWidth, ((boxWidth + paddingWidth) * boardHeight) + borderWidth * 3, WHITE);
				offSetX = (GetScreenWidth() - ((boxWidth + paddingWidth) * boardWidth)) / 2;
				offSetY += boxWidth + paddingWidth;
			}
			DrawRectangle(offSetX - boardWidth, offSetY - paddingWidth + borderWidth, ((boxWidth + paddingWidth) * boardWidth) - paddingWidth + boardWidth * 2, borderWidth, WHITE);

			int textWidth = MeasureText("You Win", 60);
			DrawText("You Win", GetScreenWidth() / 2 - textWidth / 2, GetScreenHeight() / 2 - 60, 60, YELLOW);
		}
		else
		{
			int textWidth = MeasureText("Game over", 60);
			DrawText("Game over", GetScreenWidth() / 2 - textWidth / 2, GetScreenHeight() / 2 - 60, 60, YELLOW);
		}

		if (IsKeyDown(KEY_SPACE))
		{
			SetUp();
		}
	}
	EndDrawing();
}

void Input()
{
	if (IsKeyPressed(KEY_W) || IsKeyDown(KEY_W))
	{
		if (Snake.size() == 1 || dir != DOWN)
			dir = UP;
	}
	else if (IsKeyPressed(KEY_A) || IsKeyDown(KEY_A))
	{
		if (Snake.size() == 1 || dir != RIGHT)
			dir = LEFT;
	}
	else if (IsKeyPressed(KEY_S) || IsKeyDown(KEY_S))
	{
		if (Snake.size() == 1 || dir != UP)
			dir = DOWN;
	}
	else if (IsKeyPressed(KEY_D) || IsKeyDown(KEY_D))
	{
		if (Snake.size() == 1 || dir != LEFT)
			dir = RIGHT;
	}
}

void AiInput()
{
	if (dir == STOP)
		dir = UP;

	if (Snake.at(0).getY() == 0)
		if (dir == LEFT)
			dir = DOWN;
		else
			dir = LEFT;
	if (Snake.at(0).getY() == boardHeight - 1)
		if (dir == DOWN)
			dir = LEFT;
		else if (dir == LEFT)
			dir = UP;
}

void Logic()
{
	//New tail
	Point lastTail = Point(Snake.at(Snake.size() - 1).getX(), Snake.at(Snake.size() - 1).getY());

	//Tail Follows Snake Head
	for (int i = Snake.size() - 1; i > 0; i--)
	{
		Snake.at(i).setX(Snake.at(i - 1).getX());
		Snake.at(i).setY(Snake.at(i - 1).getY());
	}

	//Snake default move 
	switch (dir)
	{
	case UP:
		Snake.at(0).setY(Snake.at(0).getY() - 1);
		if (Snake.at(0).getY() < 0)
			Snake.at(0).setY(boardHeight - 1);
		break;
	case LEFT:
		Snake.at(0).setX(Snake.at(0).getX() - 1);
		if (Snake.at(0).getX() < 0)
			Snake.at(0).setX(boardWidth - 1);
		break;
	case DOWN:
		Snake.at(0).setY(Snake.at(0).getY() + 1);
		if (Snake.at(0).getY() >= boardHeight)
			Snake.at(0).setY(0);
		break;
	case RIGHT:
		Snake.at(0).setX(Snake.at(0).getX() + 1);
		if (Snake.at(0).getX() >= boardWidth)
			Snake.at(0).setX(0);
		break;
	}

	//New tail
	if (tailIncrease)
	{
		Snake.push_back(lastTail);
		tailIncrease = false;
	}

	//Snake hits fruit
	for (int i = 0; i < Snake.size(); i++)
	{
		if (Snake.at(i).getX() == fruitX && Snake.at(i).getY() == fruitY)
		{
			fruitX = rand() % boardWidth;
			fruitY = rand() % boardHeight;
			tailIncrease = true;
			break;
		}
	}

	//Snake hits body
	for (int i = 1; i < Snake.size(); i++)
	{
		if (Snake.at(0).getX() == Snake.at(i).getX() && Snake.at(0).getY() == Snake.at(i).getY())
		{
			gameOver = true;
			break;
		}
	}
	

}

int main()
{
	InitWindow(screenWidth, screenHeight, "Snake Raylib");
	SetTargetFPS(8);
	srand(time(0));

	SetUp();
	while (!WindowShouldClose())
	{
		Store();
		Draw();
		if (!gameOver)
		{
			Input();
			//AiInput();
			Logic();

		}
	}

	CloseWindow();
	return 0;
}