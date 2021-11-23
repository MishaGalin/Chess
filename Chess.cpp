#include <SFML/Graphics.hpp>
#include "Game.h"
#include "Square.h"
#include "Board.h"
#include "AbstractChessPiece.h"
#include "ChessPieces.h"

using namespace sf; // SFML namespace
using namespace std;

RenderWindow window(VideoMode(Game::windowSizeX, Game::windowSizeY), "Chess", Style::Close);
Board board;
Game game;
vector<unique_ptr<AbstractChessPiece>> pieces; // An array of all pieces on the board

// Deleting a piece by known coordinates on the board
void DeletePiece(const Square& square);

// Finding a piece by known coordinates on the board
AbstractChessPiece* FindPiece(const Square& square);

int main()
{
	bool isMove = false;
	int dx = 0, dy = 0, n = 0;
	Event event;
	Square* nearestSquare;

	// Arrangement of pieces
	for (int i = 0; i < Board::Size; ++i) {
		for (int j = 0; j < Board::Size; ++j) {
			switch (board.boardArr[i][j])
			{
			case -1:
			{pieces.push_back(unique_ptr<AbstractChessPiece>(make_unique<Castle>(board.Squares[j][i], true)));
			board.Squares[j][i].setColor(true); }
			break;

			case 1:
			{pieces.push_back(unique_ptr<AbstractChessPiece>(make_unique<Castle>(board.Squares[j][i], false)));
			board.Squares[j][i].setColor(false); }
			break;

			case -2:
			{pieces.push_back(unique_ptr<AbstractChessPiece>(make_unique<Knight>(board.Squares[j][i], true)));
			board.Squares[j][i].setColor(true); }
			break;

			case 2:
			{pieces.push_back(unique_ptr<AbstractChessPiece>(make_unique<Knight>(board.Squares[j][i], false)));
			board.Squares[j][i].setColor(false); }
			break;

			case -3:
			{pieces.push_back(unique_ptr<AbstractChessPiece>(make_unique<Bishop>(board.Squares[j][i], true)));
			board.Squares[j][i].setColor(true); }
			break;

			case 3:
			{pieces.push_back(unique_ptr<AbstractChessPiece>(make_unique<Bishop>(board.Squares[j][i], false)));
			board.Squares[j][i].setColor(false); }
			break;

			case -4:
			{pieces.push_back(unique_ptr<AbstractChessPiece>(make_unique<Queen>(board.Squares[j][i], true)));
			board.Squares[j][i].setColor(true); }
			break;

			case 4:
			{pieces.push_back(unique_ptr<AbstractChessPiece>(make_unique<Queen>(board.Squares[j][i], false)));
			board.Squares[j][i].setColor(false); }
			break;

			case -5:
			{pieces.push_back(unique_ptr<AbstractChessPiece>(make_unique<King>(board.Squares[j][i], true)));
			board.Squares[j][i].setColor(true); }
			break;

			case 5:
			{pieces.push_back(unique_ptr<AbstractChessPiece>(make_unique<King>(board.Squares[j][i], false)));
			board.Squares[j][i].setColor(false); }
			break;

			case -6:
			{pieces.push_back(unique_ptr<AbstractChessPiece>(make_unique<Pawn>(board.Squares[j][i], true)));
			board.Squares[j][i].setColor(true); }
			break;

			case 6:
			{pieces.push_back(unique_ptr<AbstractChessPiece>(make_unique<Pawn>(board.Squares[j][i], false)));
			board.Squares[j][i].setColor(false); }
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
			game.mousePos = Mouse::getPosition(window);

			if (event.type == Event::Closed) window.close();

			if (event.type == Event::MouseButtonPressed && event.key.code == Mouse::Left) {
				nearestSquare = pieces[n]->SearchNearestSquare(game.mousePos);
				for (int i = 0; i < pieces.size(); ++i) {
					if (pieces[i]->getGlobalBounds().contains(game.mousePos.x, game.mousePos.y) && pieces[i]->getColor() == game.turn) {
						isMove = true;
						n = i; // pieces[n] - a piece that we move with the mouse
						pieces[n]->Castling(*nearestSquare);
						dx = game.mousePos.x - (int)pieces[n]->getPosition().x;
						dy = game.mousePos.y - (int)pieces[n]->getPosition().y;
						pieces[n]->setIsSelected(true);
						break;
					}
					else {
						pieces[n]->Castling(*nearestSquare);
						pieces[n]->Capture(*nearestSquare);
						pieces[n]->Move(*nearestSquare);
						pieces[n]->setIsSelected(false);
					}
				}
			}

			else if (event.type == Event::MouseButtonReleased && event.key.code == Mouse::Left) {
				nearestSquare = pieces[n]->SearchNearestSquare(game.mousePos);
				isMove = false;

				if (board.getGlobalBounds().contains(pieces[n]->getPosition())) { // Check the piece exit outside the window
					pieces[n]->Castling(*nearestSquare);
					pieces[n]->Capture(*nearestSquare);
					pieces[n]->Move(*nearestSquare);
				}
				else pieces[n]->ReturnToPrevPos();
			}

			if (isMove) pieces[n]->setPosition(game.mousePos.x - dx, game.mousePos.y - dy);
		}

		window.clear();
		board.draw(window);
		pieces[n]->DrawPossibleSquares();
		for (auto& piece : pieces) { piece->draw(window); }
		pieces[n]->draw(window); // The piece that is being moved is drawn a second time so that it is on top of all the others
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
			board.Squares[(*piece)->getX()][(*piece)->getY()].setIsEmpty(true);
			if ((*piece)->getName() == "KingW" || (*piece)->getName() == "KingB") game.isStopped = true;
			pieces.erase(piece);
			return;
		}
	}
}