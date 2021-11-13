#include <SFML/Graphics.hpp>
#include "AbstractFigure.h"
#include "Figures.h"
#include <vector>
#include <memory>

using namespace sf; // SFML namespace
using namespace std;

extern const int g_boardSize = 8, g_windowSizeX = 910, g_windowSizeY = 910;
extern const int g_squareSide = 112; // длина в пикселях
extern bool g_turn = false; // 0 / false - ход белых, 1 / true - ход черных
extern bool g_gameIsStopped = false;

extern RenderWindow window(VideoMode(g_windowSizeX, g_windowSizeY), "Chess", Style::Close);
vector<vector<Square>> squares; // двумерный массив клеток
vector<unique_ptr<AbstractFigure>> figures; // Массив всех фигур на доске

int boardArr[g_boardSize][g_boardSize] =
{ -1,-2,-3,-4,-5,-3,-2,-1,
  -6,-6,-6,-6,-6,-6,-6,-6,
   0, 0, 0, 0, 0, 0, 0, 0,
   0, 0, 0, 0, 0, 0, 0, 0,
   0, 0, 0, 0, 0, 0, 0, 0,
   0, 0, 0, 0, 0, 0, 0, 0,
   6, 6, 6, 6, 6, 6, 6, 6,
   1, 2, 3, 4, 5, 3, 2, 1
};

void Delete(Square& square);

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

	Image icon;
	icon.loadFromFile("icon.png");

	g_turn ? window.setTitle("Chess: turn of black") : window.setTitle("Chess: turn of white");
	window.setIcon(32, 32, icon.getPixelsPtr());

	for (int i = 0; i < g_boardSize; ++i) {
		vector<Square> temp;
		for (int j = 0; j < g_boardSize; ++j) {
			Square tempSquare(i, j, boardArr[j][i]);
			temp.push_back(tempSquare);
		}
		squares.push_back(temp);
	}

	// Расстановка фигур
	for (int i = 0; i < g_boardSize; ++i) {
		for (int j = 0; j < g_boardSize; ++j) {
			switch (boardArr[i][j])
			{
			case -1:
			{figures.push_back(unique_ptr<AbstractFigure>(new Castle(squares[j][i], true, texture_castle_b)));
			squares[j][i].setColor(true); }
			break;

			case 1:
			{figures.push_back(unique_ptr<AbstractFigure>(new Castle(squares[j][i], false, texture_castle_w)));
			squares[j][i].setColor(false); }
			break;

			case -2:
			{figures.push_back(unique_ptr<AbstractFigure>(new Knight(squares[j][i], true, texture_knight_b)));
			squares[j][i].setColor(true); }
			break;

			case 2:
			{figures.push_back(unique_ptr<AbstractFigure>(new Knight(squares[j][i], false, texture_knight_w)));
			squares[j][i].setColor(false); }
			break;

			case -3:
			{figures.push_back(unique_ptr<AbstractFigure>(new Bishop(squares[j][i], true, texture_bishop_b)));
			squares[j][i].setColor(true);  }
			break;

			case 3:
			{figures.push_back(unique_ptr<AbstractFigure>(new Bishop(squares[j][i], false, texture_bishop_w)));
			squares[j][i].setColor(false); }
			break;

			case -4:
			{figures.push_back(unique_ptr<AbstractFigure>(new Queen(squares[j][i], true, texture_queen_b)));
			squares[j][i].setColor(true); }
			break;

			case 4:
			{figures.push_back(unique_ptr<AbstractFigure>(new Queen(squares[j][i], false, texture_queen_w)));
			squares[j][i].setColor(false); }
			break;

			case -5:
			{figures.push_back(unique_ptr<AbstractFigure>(new King(squares[j][i], true, texture_king_b)));
			squares[j][i].setColor(true); }
			break;

			case 5:
			{figures.push_back(unique_ptr<AbstractFigure>(new King(squares[j][i], false, texture_king_w)));
			squares[j][i].setColor(false); }
			break;

			case -6:
			{figures.push_back(unique_ptr<AbstractFigure>(new Pawn(squares[j][i], true, texture_pawn_b)));
			squares[j][i].setColor(true); }
			break;

			case 6:
			{figures.push_back(unique_ptr<AbstractFigure>(new Pawn(squares[j][i], false, texture_pawn_w)));
			squares[j][i].setColor(false); }
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
		while (window.pollEvent(event)) {
			if (event.type == Event::Closed)
				window.close();

			// перетаскивание мышью
			if (event.type == Event::MouseButtonPressed && event.key.code == Mouse::Left) {
				for (int i = 0; i < figures.size(); ++i) {
					if (figures[i]->sprite.getGlobalBounds().contains(mousePos.x, mousePos.y)) {
						isMove = true;
						n = i; // figures[n] - та фигура, которую мы двигаем мышью
						dx = mousePos.x - figures[n]->sprite.getPosition().x;
						dy = mousePos.y - figures[n]->sprite.getPosition().y;
					}
				}
			}
		}

		if (event.type == Event::MouseButtonReleased && event.key.code == Mouse::Left) {
			isMove = false;
			int nearestX = 0, nearestY = 0;
			double maxDistance = 10000.;

			for (int i = 0; i < g_boardSize; ++i) {
				for (int j = 0; j < g_boardSize; ++j) {
					double dist = sqrt(pow(figures[n]->sprite.getPosition().x - squares[i][j].getXInPixel(), 2) + pow(figures[n]->sprite.getPosition().y - squares[i][j].getYInPixel(), 2)); // Расстояние до клетки
					if (dist < maxDistance) {
						maxDistance = dist;
						nearestX = i;
						nearestY = j;
					}
				}
			}

			if (!g_gameIsStopped && figures[n]->sprite.getPosition().x <= window.getSize().x && figures[n]->sprite.getPosition().x >= 0 // проверка границ
				&& figures[n]->sprite.getPosition().y <= window.getSize().y && figures[n]->sprite.getPosition().y >= 0)
			{
				figures[n]->Capture(squares[nearestX][nearestY]);
				figures[n]->Move(squares[nearestX][nearestY]);
			}
			else figures[n]->sprite.setPosition(squares[figures[n]->getX()][figures[n]->getY()].getXInPixel(),
				squares[figures[n]->getX()][figures[n]->getY()].getYInPixel()); // возврат обратно
		}

		if (isMove) figures[n]->sprite.setPosition(mousePos.x - dx, mousePos.y - dy); // меняем позицию только спрайта, т.к. перемещение еще не подтверждено

		window.clear();
		window.draw(board);

		if (!g_gameIsStopped) {
			for (int i = 0; i < g_boardSize; ++i) { // отображение клеток, в которые может сходить фигура
				for (int j = 0; j < g_boardSize; ++j) {
					if (figures[n]->ConditionOfMove(squares[i][j])) { // зеленый квадрат, если в эту клетку можно пойти
						squares[i][j].drawableRect.setFillColor(Color(0, 255, 0, 70));
						squares[i][j].draw(window);
					}
					else if (figures[n]->ConditionOfCapture(squares[i][j])) { // красный квадрат, если можно срубить
						squares[i][j].drawableRect.setFillColor(Color(255, 0, 0, 70));
						squares[i][j].draw(window);
					}
				}
			}
		}

		for (auto& figure : figures)
		{
			if (!figure->getIsDeleted()) figure->draw(window);
		}

		figures[n]->draw(window); // перемещаемая фигура рисуется в последнюю очередь (еще раз), для того чтобы она была поверх всех остальных
		window.display();
	}

	return 0;
}

void Castling() {};

void Delete(Square& square) {
	for (auto& figure : figures) {
		if (figure->getX() == square.getX() && figure->getY() == square.getY()) {
			figure->setIsDeleted(true);
			squares[figure->getX()][figure->getY()].setIsEmpty(true);
			figure->setX(-g_boardSize);
			figure->setY(-g_boardSize);
			figure->sprite.setPosition(-g_windowSizeX, -g_windowSizeY);
			figure->sprite.setColor(Color(0, 0, 0, 0));
			if (figure->getName() == "King") g_gameIsStopped = true;
			return;
		}
	}
};