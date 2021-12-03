#include "Game.h"
#include "Square.h"
#include "Board.h"
#include "AbstractChessPiece.h"
#include "ChessPieces.h"

RenderWindow window(VideoMode(Game::windowSizeX, Game::windowSizeY), "Chess", Style::Close);
Board board;
Game game;
vector<unique_ptr<AbstractChessPiece>> pieces; // An array of all pieces on the board
int n = 0;

// Deleting a piece by known coordinates on the board
void DeletePiece(Square& square);

// Finding a piece by known coordinates on the board
AbstractChessPiece* FindPiece(const Square& square);

void AddPiece(Square& square, const int& value);

int main()
{
	int dx = 0, dy = 0;
	Square* nearestSquare;

	// Arrangement of pieces
	for (int i = 0; i < Board::Size; ++i) {
		for (int j = 0; j < Board::Size; ++j) {
			AddPiece(board.Squares[i][j], board.InitArr[j][i]);
		}
	}

	while (window.isOpen())
	{
		while (window.pollEvent(game.event))
		{
			game.mousePos = Mouse::getPosition(window);

			if (game.event.type == Event::Closed) window.close();

			if (game.event.type == Event::MouseButtonPressed and game.event.key.code == Mouse::Left) {
				nearestSquare = pieces[n]->SearchNearestSquare();
				for (int i = 0; i < pieces.size(); ++i) {
					if (pieces[i]->getGlobalBounds().contains(game.mousePos.x, game.mousePos.y)) {
						n = i; // pieces[n] - a piece that we move with the mouse

						pieces[n]->IsMove(true);
						pieces[n]->setIsSelected(true);

						dx = game.mousePos.x - (int)pieces[n]->getPosition().x;
						dy = game.mousePos.y - (int)pieces[n]->getPosition().y;
					}
					else pieces[i]->setIsSelected(false);
				}
			}

			if (game.event.type == Event::MouseButtonReleased and game.event.key.code == Mouse::Left) {
				pieces[n]->IsMove(false);

				if (board.getGlobalBounds().contains(pieces[n]->getPosition())) { // Check the piece exit outside the window
					if (pieces[n]->getIsPromotion() and board.Squares[pieces[n]->getX()][pieces[n]->getY()].getGlobalBounds().contains(game.mousePos.x, game.mousePos.y)) {
						int tempMousePosX = game.mousePos.x - pieces[n]->getX() * Square::sideLength,
							tempMousePosY = game.mousePos.y - pieces[n]->getY() * Square::sideLength;

						if (tempMousePosX > Square::sideLength / 2 and tempMousePosY < Square::sideLength / 2)	    pieces[n] = make_unique<Knight>(board.Squares[pieces[n]->getX()][pieces[n]->getY()], pieces[n]->getColor() ? true : false);
						else if (tempMousePosX < Square::sideLength / 2 and tempMousePosY < Square::sideLength / 2) pieces[n] = make_unique<Queen>(board.Squares[pieces[n]->getX()][pieces[n]->getY()], pieces[n]->getColor() ? true : false);
						else if (tempMousePosX < Square::sideLength / 2 and tempMousePosY > Square::sideLength / 2) pieces[n] = make_unique<Bishop>(board.Squares[pieces[n]->getX()][pieces[n]->getY()], pieces[n]->getColor() ? true : false);
						else if (tempMousePosX > Square::sideLength / 2 and tempMousePosY > Square::sideLength / 2) pieces[n] = make_unique<Castle>(board.Squares[pieces[n]->getX()][pieces[n]->getY()], pieces[n]->getColor() ? true : false);

						pieces[n]->setIsPromotion(false);
						pieces[n]->setIsMovable(true);
						game.pawnIsPromotion = false;
						game.ChangeOfTurn();
						continue;
					}
					nearestSquare = pieces[n]->SearchNearestSquare();

					pieces[n]->Castling(*nearestSquare); //
					pieces[n]->Capture(*nearestSquare);	 // Only one of the options is possible
					pieces[n]->Move(*nearestSquare);	 //
				}
				else pieces[n]->ReturnToPrevPos();
			}

			if (pieces[n]->getIsMovable() and pieces[n]->getIsMove()) pieces[n]->setPosition(game.mousePos.x - dx, game.mousePos.y - dy);
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
		if (piece->getX() == square.getX() and piece->getY() == square.getY()) return piece.get();
	}
	return 0;
}

void DeletePiece(Square& square) {
	for (auto piece = pieces.begin(); piece < pieces.end(); ++piece) {
		if ((*piece)->getX() == square.getX() and (*piece)->getY() == square.getY()) {
			square.setIsEmpty(true);
			if ((*piece)->getName() == "KingW" or (*piece)->getName() == "KingB") game.isFinished = true;
			pieces.erase(piece);
			n = pieces.size() - 1;
			return;
		}
	}
}

void AddPiece(Square& square, const int& value) {
	switch (value) {
	case -1:
	{pieces.push_back(unique_ptr<AbstractChessPiece>(make_unique<Castle>(square, true))); }
	break;

	case 1:
	{pieces.push_back(unique_ptr<AbstractChessPiece>(make_unique<Castle>(square, false))); }
	break;

	case -2:
	{pieces.push_back(unique_ptr<AbstractChessPiece>(make_unique<Knight>(square, true))); }
	break;

	case 2:
	{pieces.push_back(unique_ptr<AbstractChessPiece>(make_unique<Knight>(square, false))); }
	break;

	case -3:
	{pieces.push_back(unique_ptr<AbstractChessPiece>(make_unique<Bishop>(square, true))); }
	break;

	case 3:
	{pieces.push_back(unique_ptr<AbstractChessPiece>(make_unique<Bishop>(square, false))); }
	break;

	case -4:
	{pieces.push_back(unique_ptr<AbstractChessPiece>(make_unique<Queen>(square, true))); }
	break;

	case 4:
	{pieces.push_back(unique_ptr<AbstractChessPiece>(make_unique<Queen>(square, false))); }
	break;

	case -5:
	{pieces.push_back(unique_ptr<AbstractChessPiece>(make_unique<King>(square, true))); }
	break;

	case 5:
	{pieces.push_back(unique_ptr<AbstractChessPiece>(make_unique<King>(square, false))); }
	break;

	case -6:
	{pieces.push_back(unique_ptr<AbstractChessPiece>(make_unique<Pawn>(square, true))); }
	break;

	case 6:
	{pieces.push_back(unique_ptr<AbstractChessPiece>(make_unique<Pawn>(square, false))); }
	break;

	default:
		break;
	}
}