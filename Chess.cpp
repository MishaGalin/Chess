#include <SFML/Graphics.hpp>
#include "AbstractChessPiece.h"
#include "ChessPieces.h"

using namespace sf; // SFML namespace
using namespace std;

const int g_boardSize = 8, g_windowSizeX = 910, g_windowSizeY = 910;
const int g_squareSide = 112; // Side length of a square in pixels
bool g_turn = false; // 0 - white move, 1 - black move
bool g_gameIsStopped = false;

Texture
texturePawnW,
texturePawnB,
textureCastleW,
textureCastleB,
textureKnightW,
textureKnightB,
textureBishopW,
textureBishopB,
textureQueenW,
textureQueenB,
textureKingW,
textureKingB;

RenderWindow window(VideoMode(g_windowSizeX, g_windowSizeY), "Chess", Style::Close);
vector<vector<Square>> board;
vector<unique_ptr<AbstractChessPiece>> pieces; // An array of all pieces on the board
map <string, Texture*> textureOfPieces = {
	{"PawnW", &texturePawnW },
	{"PawnB", &texturePawnB },
	{"CastleW", &textureCastleW },
	{"CastleB", &textureCastleB },
	{"KnightW", &textureKnightW },
	{"KnightB", &textureKnightB },
	{"BishopW", &textureBishopW },
	{"BishopB", &textureBishopB },
	{"QueenW", &textureQueenW },
	{"QueenB", &textureQueenB },
	{"KingW", &textureKingW },
	{"KingB", &textureKingB }
};

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

void Castling();

// Deleting a piece by known coordinates on the board
void Delete(Square& square);

int main()
{
	bool isMove = false;
	int dx = 0, dy = 0, n = 0;
	Event event;
	Vector2i mousePos, nearestSquare;

	texturePawnW.loadFromFile("images/pawn_w.png");
	texturePawnB.loadFromFile("images/pawn_b.png");
	textureCastleW.loadFromFile("images/castle_w.png");
	textureCastleB.loadFromFile("images/castle_b.png");
	textureKnightW.loadFromFile("images/knight_w.png");
	textureKnightB.loadFromFile("images/knight_b.png");
	textureBishopW.loadFromFile("images/bishop_w.png");
	textureBishopB.loadFromFile("images/bishop_b.png");
	textureQueenW.loadFromFile("images/queen_w.png");
	textureQueenB.loadFromFile("images/queen_b.png");
	textureKingW.loadFromFile("images/king_w.png");
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
			{pieces.push_back(unique_ptr<AbstractChessPiece>(new Castle(board[j][i], true)));
			board[j][i].setColor(true); }
			break;

			case 1:
			{pieces.push_back(unique_ptr<AbstractChessPiece>(new Castle(board[j][i], false)));
			board[j][i].setColor(false); }
			break;

			case -2:
			{pieces.push_back(unique_ptr<AbstractChessPiece>(new Knight(board[j][i], true)));
			board[j][i].setColor(true); }
			break;

			case 2:
			{pieces.push_back(unique_ptr<AbstractChessPiece>(new Knight(board[j][i], false)));
			board[j][i].setColor(false); }
			break;

			case -3:
			{pieces.push_back(unique_ptr<AbstractChessPiece>(new Bishop(board[j][i], true)));
			board[j][i].setColor(true);  }
			break;

			case 3:
			{pieces.push_back(unique_ptr<AbstractChessPiece>(new Bishop(board[j][i], false)));
			board[j][i].setColor(false); }
			break;

			case -4:
			{pieces.push_back(unique_ptr<AbstractChessPiece>(new Queen(board[j][i], true)));
			board[j][i].setColor(true); }
			break;

			case 4:
			{pieces.push_back(unique_ptr<AbstractChessPiece>(new Queen(board[j][i], false)));
			board[j][i].setColor(false); }
			break;

			case -5:
			{pieces.push_back(unique_ptr<AbstractChessPiece>(new King(board[j][i], true)));
			board[j][i].setColor(true); }
			break;

			case 5:
			{pieces.push_back(unique_ptr<AbstractChessPiece>(new King(board[j][i], false)));
			board[j][i].setColor(false); }
			break;

			case -6:
			{pieces.push_back(unique_ptr<AbstractChessPiece>(new Pawn(board[j][i], true)));
			board[j][i].setColor(true); }
			break;

			case 6:
			{pieces.push_back(unique_ptr<AbstractChessPiece>(new Pawn(board[j][i], false)));
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
					if (pieces[i]->getGlobalBounds().contains(mousePos.x, mousePos.y) && pieces[i]->getColor() == g_turn) {
						isMove = true;
						n = i; // pieces[n] - a piece that we move with the mouse
						dx = mousePos.x - pieces[n]->getPosition().x;
						dy = mousePos.y - pieces[n]->getPosition().y;
						pieces[n]->setIsSelected(true);
						break;
					}
					else pieces[i]->setIsSelected(false);
				}
			}

			if (event.type == Event::MouseButtonReleased && event.key.code == Mouse::Left) {
				isMove = false;
				nearestSquare = pieces[n]->SearchNearestSquare(mousePos);

				if (boardImage.getGlobalBounds().contains(pieces[n]->getPosition())) { // Check the piece exit outside the window
					pieces[n]->Capture(board[nearestSquare.x][nearestSquare.y]);
					pieces[n]->Move(board[nearestSquare.x][nearestSquare.y]);
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
			if (piece->getName() == "KingW" || piece->getName() == "KingB") g_gameIsStopped = true;
			return;
		}
	}
}