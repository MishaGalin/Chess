#include <SFML/Graphics.hpp>
#include <iostream>
#include <vector>
#include <cmath>
#include "AbstractFigure.h"
#include "Figures.h"

using namespace sf; // SFML namespace
using namespace std;

const int boardSize = 8, windowSizeX = 910, windowSizeY = 910;
const int cellSide = 112; // length in pixels
bool turn = false; // 0 - ход белых, 1 - ход черных

int boardArr[boardSize][boardSize] =
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
	int dx = 0, dy = 0, n = 0;

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

	Texture boardTexture; // Текстура доски
	boardTexture.loadFromFile("images/board1.png");
	Sprite board(boardTexture);

	vector<vector<Cell>> cells; // Сетка центров клеток

	vector<AbstractFigure*> figures; // Массив всех фигур на доске

	Image icon;
	if (!icon.loadFromFile("icon.png"))
	{
		return 1;
	}

	RenderWindow window(VideoMode(windowSizeX, windowSizeY), "Chess: turn of white", sf::Style::Close);
	window.setIcon(32, 32, icon.getPixelsPtr());

	// Рассчет центров клеток
	for (int i = 0; i < boardSize; ++i) {
		vector<Cell> temp;
		for (int j = 0; j < boardSize; ++j) {
			Cell tempCell(i, j, boardArr[j][i], cellSide);
			temp.push_back(tempCell);
		}
		cells.push_back(temp);
	}

	// Расстановка фигур
	for (int i = 0; i < boardSize; ++i) {
		for (int j = 0; j < boardSize; ++j) {
			switch (boardArr[i][j])
			{
			case -1:
			{figures.push_back(new Castle(j, i, true, texture_castle_b, cellSide)); }
			break;

			case 1:
			{figures.push_back(new Castle(j, i, false, texture_castle_w, cellSide)); }
			break;

			case -2:
			{figures.push_back(new Knight(j, i, true, texture_knight_b, cellSide)); }
			break;

			case 2:
			{figures.push_back(new Knight(j, i, false, texture_knight_w, cellSide)); }
			break;

			case -3:
			{figures.push_back(new Bishop(j, i, true, texture_bishop_b, cellSide)); }
			break;

			case 3:
			{figures.push_back(new Bishop(j, i, false, texture_bishop_w, cellSide)); }
			break;

			case -4:
			{figures.push_back(new Queen(j, i, true, texture_queen_b, cellSide)); }
			break;

			case 4:
			{figures.push_back(new Queen(j, i, false, texture_queen_w, cellSide)); }
			break;

			case -5:
			{figures.push_back(new King(j, i, true, texture_king_b, cellSide)); }
			break;

			case 5:
			{figures.push_back(new King(j, i, false, texture_king_w, cellSide)); }
			break;

			case -6:
			{figures.push_back(new Pawn(j, i, true, texture_pawn_b, cellSide)); }
			break;

			case 6:
			{figures.push_back(new Pawn(j, i, false, texture_pawn_w, cellSide)); }
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
			if (event.type == Event::MouseButtonPressed && event.key.code == Mouse::Left) {
				for (int i = 0; i < figures.size(); ++i) {
					if (figures[i]->sprite.getGlobalBounds().contains(mousePos.x, mousePos.y))
					{
						isMove = true;
						n = i; // figures[n] - та фигура, которую мы двигаем мышью
						dx = mousePos.x - figures[n]->getPos().x;
						dy = mousePos.y - figures[n]->getPos().y;
					}
				}
			}
		}

		if (event.type == Event::MouseButtonReleased && event.key.code == Mouse::Left) {
			isMove = false;
			int cellX = 0, cellY = 0;
			double maxDistance = 10000.;

			for (int i = 0; i < boardSize; ++i) {
				for (int j = 0; j < boardSize; ++j) {
					double dist = sqrt(pow(figures[n]->sprite.getPosition().x - cells[i][j].xInPixel, 2) + pow(figures[n]->sprite.getPosition().y - cells[i][j].yInPixel, 2)); // Расстояние до клетки
					if (dist < maxDistance)
					{
						maxDistance = dist;
						cellX = i;
						cellY = j;
					}
				}
			}

			if (figures[n]->getPos().x <= window.getSize().x && figures[n]->getPos().x >= 0 // проверка границ
				&& figures[n]->getPos().y <= window.getSize().y && figures[n]->getPos().y >= 0)
			{
				figures[n]->Move(cells[figures[n]->x][figures[n]->y], cells[cellX][cellY], cellSide, turn, window);
			}
			else figures[n]->setPos(cells[figures[n]->x][figures[n]->y].xInPixel, cells[figures[n]->x][figures[n]->y].yInPixel); // возврат обратно
		}

		if (isMove) figures[n]->sprite.setPosition(mousePos.x - dx, mousePos.y - dy);

		window.clear();
		window.draw(board);
		for (auto figure : figures)
		{
			figure->draw(window, sf::RenderStates::Default);
		}
		figures[n]->draw(window, sf::RenderStates::Default);
		window.display();
	}

	for (auto figure : figures)
	{
		delete figure;
	}

	return 0;
}