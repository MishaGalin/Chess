#include <SFML/Graphics.hpp>
#include <iostream>
#include <vector>
#include <cmath>
#include "AbstractFigure.h"
#include "Figures.h"

using namespace sf; // SFML namespace
using namespace std;

const unsigned char boardSize = 8;
const unsigned short cellSide = 112; // length in pixels
bool turn = 0; // 0 - ход белых, 1 - ход черных

short boardArr[boardSize][boardSize] =
{ -1,-2,-3,-4,-5,-3,-2,-1,
  -6,-6,-6,-6,-6,-6,-6,-6,
   0, 0, 0, 0, 0, 0, 0, 0,
   0, 0, 0, 0, 0, 0, 0, 0,
   0, 0, 0, 0, 0, 0, 0, 0,
   0, 0, 0, 0, 0, 0, 0, 0,
   6, 6, 6, 6, 6, 6, 6, 6,
   1, 2, 3, 4, 5, 3, 2, 1
};

int main()
{
	bool isMove = false;
	int dx = 0, dy = 0;
	int n = 0;

	Texture texture_pawn_w; // Текстура белой пешки
	texture_pawn_w.loadFromFile("images/pawn_w.png");

	Texture texture_pawn_b; // Текстура черной пешки
	texture_pawn_b.loadFromFile("images/pawn_b.png");

	Texture texture_castle_w; // Текстура белой ладьи
	texture_castle_w.loadFromFile("images/castle_w.png");

	Texture texture_castle_b; // Текстура черной ладьи
	texture_castle_b.loadFromFile("images/castle_b.png");

	Texture texture_knight_w; // Текстура белого коня
	texture_knight_w.loadFromFile("images/knight_w.png");

	Texture texture_knight_b; // Текстура черного коня
	texture_knight_b.loadFromFile("images/knight_b.png");

	Texture texture_bishop_w; // Текстура белого слона
	texture_bishop_w.loadFromFile("images/bishop_w.png");

	Texture texture_bishop_b; // Текстура черного слона
	texture_bishop_b.loadFromFile("images/bishop_b.png");

	Texture texture_queen_w; // Текстура белой королевы
	texture_queen_w.loadFromFile("images/queen_w.png");

	Texture texture_queen_b; // Текстура черной королевы
	texture_queen_b.loadFromFile("images/queen_b.png");

	Texture texture_king_w; // Текстура белого короля
	texture_king_w.loadFromFile("images/king_w.png");

	Texture texture_king_b; // Текстура черного короля
	texture_king_b.loadFromFile("images/king_b.png");

	Texture boardTexture;
	boardTexture.loadFromFile("images/board1.png");
	Sprite board(boardTexture);

	vector<vector<Cell>> cells; // Сетка центров клеток

	vector<AbstractFigure*> figures; // Массив всех фигур на доске

	RenderWindow window(VideoMode(910, 910), "Chess");

	// Рассчет центров клеток
	for (int i = 0; i < boardSize; i++) {
		vector<Cell> temp;
		for (int j = 0; j < boardSize; j++) {
			Cell tempCell(j, i, boardArr[j][i], cellSide);
			tempCell.x = i;
			tempCell.y = j;
			tempCell.xInPixel = cellSide / 2 + cellSide * i;
			tempCell.yInPixel = cellSide / 2 + cellSide * j;
			temp.push_back(tempCell);
		}
		cells.push_back(temp);
	}

	// Расстановка фигур
	for (int i = 0; i < boardSize; i++) {
		for (int j = 0; j < boardSize; j++) {
			switch (boardArr[i][j])
			{
			case -1:
			{figures.push_back(new Castle(j, i, texture_castle_b, cellSide)); }
			break;

			case 1:
			{figures.push_back(new Castle(j, i, texture_castle_w, cellSide)); }
			break;

			case -2:
			{figures.push_back(new Knight(j, i, texture_knight_b, cellSide)); }
			break;

			case 2:
			{figures.push_back(new Knight(j, i, texture_knight_w, cellSide)); }
			break;

			case -3:
			{figures.push_back(new Bishop(j, i, texture_bishop_b, cellSide)); }
			break;

			case 3:
			{figures.push_back(new Bishop(j, i, texture_bishop_w, cellSide)); }
			break;

			case -4:
			{figures.push_back(new Queen(j, i, texture_queen_b, cellSide)); }
			break;

			case 4:
			{figures.push_back(new Queen(j, i, texture_queen_w, cellSide)); }
			break;

			case -5:
			{figures.push_back(new King(j, i, texture_king_b, cellSide)); }
			break;

			case 5:
			{figures.push_back(new King(j, i, texture_king_w, cellSide)); }
			break;

			case -6:
			{figures.push_back(new Pawn(j, i, texture_pawn_b, cellSide)); }
			break;

			case 6:
			{figures.push_back(new Pawn(j, i, texture_pawn_w, cellSide)); }
			break;

			default:
				break;
			}
		}
	}

	while (window.isOpen())
	{
		Vector2i mousePos = Mouse::getPosition(window);

		Event event;
		while (window.pollEvent(event))
		{
			if (event.type == Event::Closed)
				window.close();

			// перетаскивание мышью
			if (event.type == Event::MouseButtonPressed and event.key.code == Mouse::Left) {
				for (int i = 0; i < figures.size(); i++) {
					if (figures[i]->sprite.getGlobalBounds().contains(mousePos.x, mousePos.y)) {
						isMove = true;
						n = i; // figures[n] - та фигура, которую мы двигаем мышью
						dx = mousePos.x - figures[n]->getPos().x;
						dy = mousePos.y - figures[n]->getPos().y;
					}
				}
			}
		}

		if (event.type == Event::MouseButtonReleased and event.key.code == Mouse::Left) {
			isMove = false;
			unsigned short cellX = 0, cellY = 0;
			double maxDistance = 10000.;

			for (int i = 0; i < boardSize; i++) {
				for (int j = 0; j < boardSize; j++) {
					double dist = sqrt(pow(figures[n]->getPos().x - cells[i][j].xInPixel, 2) + pow(figures[n]->getPos().y - cells[i][j].yInPixel, 2)); // Расстояние до клетки
					if (dist < maxDistance) {
						maxDistance = dist;
						cellX = i;
						cellY = j;
					}
				}
			}

			if (cells[cellX][cellY].isEmpty) { // Проверка не занята ли клетка
				cells[figures[n]->x][figures[n]->y].isEmpty = true;
				cells[cellX][cellY].isEmpty = false;
				figures[n]->setPos(cells[cellX][cellY].xInPixel, cells[cellX][cellY].yInPixel);
				figures[n]->x = cellX;
				figures[n]->y = cellY;
			}
			else {
				figures[n]->setPos(cells[figures[n]->x][figures[n]->y].xInPixel, cells[figures[n]->x][figures[n]->y].yInPixel);
			}
		}

		if (isMove) figures[n]->setPos(mousePos.x - dx, mousePos.y - dy);

		window.clear();
		window.draw(board);
		for (int i = 0; i < figures.size(); i++) {
			figures[i]->draw(window, sf::RenderStates::Default);
		}
		window.display();
	}

	return 0;
}