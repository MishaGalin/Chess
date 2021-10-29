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
	int dx = 0, dy = 0;
	int n = 0;
	int b;

	Texture boardTexture;
	boardTexture.loadFromFile("images/board1.png");
	Sprite board(boardTexture);

	vector<vector<Vector2i>> cellCenters;
	for (int i = 0; i < boardSize; i++) {
		vector<Vector2i> temp;
		for (int j = 0; j < boardSize; j++) {
			Vector2i tempCenter;
			tempCenter.x = cellSide / 2 + cellSide * j;
			tempCenter.y = cellSide / 2 + cellSide * i;
			temp.push_back(tempCenter);
		}
		cellCenters.push_back(temp);
	}

	vector<Pawn*> pawns_w;
	//vector<Pawn> pawns_b;

	for (int i = 0; i < boardSize; i++) {
		for (int j = 0; j < boardSize; j++) {
			switch (boardArr[i][j])
			{
			case 6:
			{pawns_w.push_back(new Pawn(j, i, 0, cellSide)); }
			break;

			default:
				break;
			}
		}
	}

	RenderWindow window(VideoMode(910, 910), "Chess");
	window.setFramerateLimit(200);

	while (window.isOpen())
	{
		Vector2i mousePos = Mouse::getPosition(window);

		Event event;
		while (window.pollEvent(event))
		{
			if (event.type == Event::Closed)
				window.close();

			// перетаскивание мышью
			if (event.type == Event::MouseButtonPressed) {
				if (event.key.code == Mouse::Left) {
					for (int i = 0; i < pawns_w.size(); i++) {
						if (pawns_w[i]->sprite.getGlobalBounds().contains(mousePos.x, mousePos.y)) {
							isMove = true;
							n = i;
							dx = mousePos.x - pawns_w[i]->sprite.getPosition().x;
							dy = mousePos.y - pawns_w[i]->sprite.getPosition().y;
						}
					}
					//for (const auto& pawn : pawns_b) {
					//	if (pawn.sprite.getGlobalBounds().contains(mousePos.x, mousePos.y)) {
					//		isMove = true;
					//		dx = mousePos.x - pawn.sprite.getPosition().x;
					//		dy = mousePos.y - pawn.sprite.getPosition().y;
					//	}
				}
			}
		}

		if (event.type == Event::MouseButtonReleased) {
			if (event.key.code == Mouse::Left) {
				isMove = false;
				unsigned short cellX = 0, cellY = 0;
				double maxDistance = 10000.;
				for (int i = 0; i < boardSize; i++) {
					for (int j = 0; j < boardSize; j++) {
						double dist = sqrt(pow(pawns_w[n]->sprite.getPosition().x - cellCenters[i][j].x, 2) + pow(pawns_w[n]->sprite.getPosition().y - cellCenters[i][j].y, 2));
						if (dist < maxDistance) {
							maxDistance = dist;
							cellX = i;
							cellY = j;
						}
					}
				}
				pawns_w[n]->sprite.setPosition(cellCenters[cellX][cellY].x, cellCenters[cellX][cellY].y);
			}
		}

		if (isMove) pawns_w[n]->sprite.setPosition(mousePos.x - dx, mousePos.y - dy);

		window.clear();
		window.draw(board);
		for (int i = 0; i < pawns_w.size(); i++) {
			window.draw(pawns_w[i]->sprite);
		}
		window.display();
	}

	return 0;
}