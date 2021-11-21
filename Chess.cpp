#include <SFML/Graphics.hpp>
#include "Square.h"
#include "AbstractChessPiece.h"
#include "ChessPieces.h"
#include <vector>

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
   1, 0, 0, 0, 5, 0, 0, 1
};

// Deleting a piece by known coordinates on the board
void DeletePiece(const Square& square);

// Finding a piece by known coordinates on the board
AbstractChessPiece* FindPiece(const Square& square);

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
			{pieces.push_back(unique_ptr<AbstractChessPiece>(make_unique<Castle>(board[j][i], true)));
			board[j][i].setColor(true); }
			break;

			case 1:
			{pieces.push_back(unique_ptr<AbstractChessPiece>(make_unique<Castle>(board[j][i], false)));
			board[j][i].setColor(false); }
			break;

			case -2:
			{pieces.push_back(unique_ptr<AbstractChessPiece>(make_unique<Knight>(board[j][i], true)));
			board[j][i].setColor(true); }
			break;

			case 2:
			{pieces.push_back(unique_ptr<AbstractChessPiece>(make_unique<Knight>(board[j][i], false)));
			board[j][i].setColor(false); }
			break;

			case -3:
			{pieces.push_back(unique_ptr<AbstractChessPiece>(make_unique<Bishop>(board[j][i], true)));
			board[j][i].setColor(true); }
			break;

			case 3:
			{pieces.push_back(unique_ptr<AbstractChessPiece>(make_unique<Bishop>(board[j][i], false)));
			board[j][i].setColor(false); }
			break;

			case -4:
			{pieces.push_back(unique_ptr<AbstractChessPiece>(make_unique<Queen>(board[j][i], true)));
			board[j][i].setColor(true); }
			break;

			case 4:
			{pieces.push_back(unique_ptr<AbstractChessPiece>(make_unique<Queen>(board[j][i], false)));
			board[j][i].setColor(false); }
			break;

			case -5:
			{pieces.push_back(unique_ptr<AbstractChessPiece>(make_unique<King>(board[j][i], true)));
			board[j][i].setColor(true); }
			break;

			case 5:
			{pieces.push_back(unique_ptr<AbstractChessPiece>(make_unique<King>(board[j][i], false)));
			board[j][i].setColor(false); }
			break;

			case -6:
			{pieces.push_back(unique_ptr<AbstractChessPiece>(make_unique<Pawn>(board[j][i], true)));
			board[j][i].setColor(true); }
			break;

			case 6:
			{pieces.push_back(unique_ptr<AbstractChessPiece>(make_unique<Pawn>(board[j][i], false)));
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
				nearestSquare = pieces[n]->SearchNearestSquare(mousePos);
				for (int i = 0; i < pieces.size(); ++i) {
					if (pieces[i]->getGlobalBounds().contains(mousePos.x, mousePos.y) && pieces[i]->getColor() == g_turn) {
						isMove = true;
						n = i; // pieces[n] - a piece that we move with the mouse
						pieces[n]->Castling(board[nearestSquare.x][nearestSquare.y]);
						dx = mousePos.x - (int)pieces[n]->getPosition().x;
						dy = mousePos.y - (int)pieces[n]->getPosition().y;
						pieces[n]->setIsSelected(true);
						break;
					}
					else {
						pieces[n]->Castling(board[nearestSquare.x][nearestSquare.y]);
						pieces[n]->Capture(board[nearestSquare.x][nearestSquare.y]);
						pieces[n]->Move(board[nearestSquare.x][nearestSquare.y]);
						pieces[n]->setIsSelected(false);
					}
				}
			}

			else if (event.type == Event::MouseButtonReleased && event.key.code == Mouse::Left) {
				nearestSquare = pieces[n]->SearchNearestSquare(mousePos);
				isMove = false;

				if (boardImage.getGlobalBounds().contains(pieces[n]->getPosition())) { // Check the piece exit outside the window
					pieces[n]->Castling(board[nearestSquare.x][nearestSquare.y]);
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
		for (auto& piece : pieces) { piece->draw(window); }
		pieces[n]->draw(window); // The shape that is being moved is drawn a second time so that it is on top of all the others
		window.display();
	}
	return 0;
}

AbstractChessPiece* FindPiece(const Square& square) {
	for (auto& piece : pieces) {
		if (piece->getX() == square.getX() && piece->getY() == square.getY()) return piece.get();
	}
	return 0;
}

void DeletePiece(const Square& square) {
	for (auto piece = pieces.begin(); piece < pieces.end(); ++piece) {
		if ((*piece)->getX() == square.getX() && (*piece)->getY() == square.getY()) {
			board[(*piece)->getX()][(*piece)->getY()].setIsEmpty(true);
			if ((*piece)->getName() == "KingW" || (*piece)->getName() == "KingB") g_gameIsStopped = true;
			pieces.erase(piece);
			return;
		}
	}
}