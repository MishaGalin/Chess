#include <SFML/Graphics.hpp>
#include "AbstractChessPiece.h"
#include "ChessPieces.h"

using namespace sf; // SFML namespace
using namespace std;

const int g_boardSize = 8, g_windowSizeX = 910, g_windowSizeY = 910;
const int g_squareSide = 112; // Side length of a square in pixels
bool g_turn = false; // 0 - white move, 1 - black move
bool g_gameIsStopped = false;

RenderWindow window(VideoMode(g_windowSizeX, g_windowSizeY), "Chess", Style::Close);
vector<vector<Square>> board;
vector<unique_ptr<AbstractChessPiece>> pieces; // An array of all pieces on the board

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

// Deleting a piece by known coordinates on the board
void Castling();

void Delete(Square& square);

int main()
{
	bool isMove = false;
	int dx = 0, dy = 0, n = 0, nearestX = 0, nearestY = 0;
	double maxDistance = 10000., distance = 0.;
	Event event;
	Vector2i mousePos;

	Texture texturePawnW;
	texturePawnW.loadFromFile("images/pawn_w.png");

	Texture texturePawnB;
	texturePawnB.loadFromFile("images/pawn_b.png");

	Texture textureCastleW;
	textureCastleW.loadFromFile("images/castle_w.png");

	Texture textureCastleB;
	textureCastleB.loadFromFile("images/castle_b.png");

	Texture textureKnightW;
	textureKnightW.loadFromFile("images/knight_w.png");

	Texture textureKnightB;
	textureKnightB.loadFromFile("images/knight_b.png");

	Texture textureBishopW;
	textureBishopW.loadFromFile("images/bishop_w.png");

	Texture textureBishopB;
	textureBishopB.loadFromFile("images/bishop_b.png");

	Texture textureQueenW;
	textureQueenW.loadFromFile("images/queen_w.png");

	Texture textureQueenB;
	textureQueenB.loadFromFile("images/queen_b.png");

	Texture textureKingW;
	textureKingW.loadFromFile("images/king_w.png");

	Texture textureKingB;
	textureKingB.loadFromFile("images/king_b.png");

	Texture boardTexture;
	boardTexture.loadFromFile("images/board1.png");
	Sprite boardImage(boardTexture);

	Image icon;
	icon.loadFromFile("images/icon.png");

	g_turn ? window.setTitle("Chess: turn of black") : window.setTitle("Chess: turn of white");
	window.setIcon(32, 32, icon.getPixelsPtr());
	window.setFramerateLimit(300);

	for (int i = 0; i < g_boardSize; ++i) {
		vector<Square> temp;
		for (int j = 0; j < g_boardSize; ++j) {
			Square tempSquare(i, j, boardArr[j][i]);
			temp.push_back(tempSquare);
		}
		board.push_back(temp);
	}

	// Arrangement of pieces
	for (int i = 0; i < g_boardSize; ++i) {
		for (int j = 0; j < g_boardSize; ++j) {
			switch (boardArr[i][j])
			{
			case -1:
			{pieces.push_back(unique_ptr<AbstractChessPiece>(new Castle(board[j][i], true, textureCastleB)));
			board[j][i].setColor(true); }
			break;

			case 1:
			{pieces.push_back(unique_ptr<AbstractChessPiece>(new Castle(board[j][i], false, textureCastleW)));
			board[j][i].setColor(false); }
			break;

			case -2:
			{pieces.push_back(unique_ptr<AbstractChessPiece>(new Knight(board[j][i], true, textureKnightB)));
			board[j][i].setColor(true); }
			break;

			case 2:
			{pieces.push_back(unique_ptr<AbstractChessPiece>(new Knight(board[j][i], false, textureKnightW)));
			board[j][i].setColor(false); }
			break;

			case -3:
			{pieces.push_back(unique_ptr<AbstractChessPiece>(new Bishop(board[j][i], true, textureBishopB)));
			board[j][i].setColor(true);  }
			break;

			case 3:
			{pieces.push_back(unique_ptr<AbstractChessPiece>(new Bishop(board[j][i], false, textureBishopW)));
			board[j][i].setColor(false); }
			break;

			case -4:
			{pieces.push_back(unique_ptr<AbstractChessPiece>(new Queen(board[j][i], true, textureQueenB)));
			board[j][i].setColor(true); }
			break;

			case 4:
			{pieces.push_back(unique_ptr<AbstractChessPiece>(new Queen(board[j][i], false, textureQueenW)));
			board[j][i].setColor(false); }
			break;

			case -5:
			{pieces.push_back(unique_ptr<AbstractChessPiece>(new King(board[j][i], true, textureKingB)));
			board[j][i].setColor(true); }
			break;

			case 5:
			{pieces.push_back(unique_ptr<AbstractChessPiece>(new King(board[j][i], false, textureKingW)));
			board[j][i].setColor(false); }
			break;

			case -6:
			{pieces.push_back(unique_ptr<AbstractChessPiece>(new Pawn(board[j][i], true, texturePawnB)));
			board[j][i].setColor(true); }
			break;

			case 6:
			{pieces.push_back(unique_ptr<AbstractChessPiece>(new Pawn(board[j][i], false, texturePawnW)));
			board[j][i].setColor(false); }
			break;

			default:
				break;
			}
		}
	}

	while (window.isOpen())
	{
		while (window.pollEvent(event))
		{
			mousePos = Mouse::getPosition(window);

			if (event.type == Event::Closed) window.close();

			if (event.type == Event::MouseButtonPressed && event.key.code == Mouse::Left) {
				for (int i = 0; i < pieces.size(); ++i) {
					if (pieces[i]->getGlobalBounds().contains(mousePos.x, mousePos.y)) {
						isMove = true;
						n = i; // pieces[n] - a piece that we move with the mouse
						dx = mousePos.x - pieces[n]->getPosition().x;
						dy = mousePos.y - pieces[n]->getPosition().y;
					}
				}
			}

			if (event.type == Event::MouseButtonReleased && event.key.code == Mouse::Left) {
				isMove = false;
				maxDistance = 10000.;
				distance = 0.;

				for (int i = 0; i < g_boardSize; ++i) {
					for (int j = 0; j < g_boardSize; ++j) {
						distance = sqrt(pow(pieces[n]->getPosition().x - board[i][j].getXInPixel(), 2) + pow(pieces[n]->getPosition().y - board[i][j].getYInPixel(), 2)); // Distance to the square
						if (distance < maxDistance) {
							maxDistance = distance;
							nearestX = i;
							nearestY = j;
						}
					}
				}

				if (boardImage.getGlobalBounds().contains(pieces[n]->getPosition())) { // Check the piece exit outside the window
					pieces[n]->Capture(board[nearestX][nearestY]);
					pieces[n]->Move(board[nearestX][nearestY]);
				}
				else pieces[n]->ReturnToPrevPos();
			}

			if (isMove) pieces[n]->setPosition(mousePos.x - dx, mousePos.y - dy);
		}

		window.clear();
		window.draw(boardImage);

		pieces[n]->DrawPossibleSquares();

		for (auto& piece : pieces) {
			if (!piece->getIsDeleted()) piece->draw(window);
		}

		pieces[n]->draw(window); // The shape that is being moved is drawn a second time so that it is on top of all the others
		window.display();
	}

	return 0;
}

void Castling() {}

void Delete(Square& square) {
	for (auto& piece : pieces) {
		if (piece->getX() == square.getX() && piece->getY() == square.getY()) {
			piece->setIsDeleted(true);
			board[piece->getX()][piece->getY()].setIsEmpty(true);
			piece->setX(-g_boardSize);
			piece->setY(-g_boardSize);
			piece->setPosition(-g_windowSizeX, -g_windowSizeY);
			if (piece->getName() == "King") g_gameIsStopped = true;
			return;
		}
	}
}