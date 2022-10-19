#include <SFML/Graphics.hpp>
#include "Game.h"
#include "Square.h"
#include "Board.h"
#include "AbstractChessPiece.h"
#include "ChessPieces.h"

RenderWindow window(VideoMode(GameData::windowSizeX, GameData::windowSizeY), "", Style::Close);
GameData game;
Board board;
vector<unique_ptr<AbstractChessPiece>> pieces; // An array of all pieces on the board
unsigned char selected = 0;
float dx = 0.f, dy = 0.f;

// Deleting a piece by known coordinates on the board
void DeletePiece(Square& square);

// Finding a piece by known coordinates on the board
AbstractChessPiece* FindPiece(const Square& square);

void AddPiece(Square& square, int value);
void UpdateWindow();
void Promotion();

int main() {
	Event event;
	while (window.isOpen()) {
		while (window.pollEvent(event)) {
			if (event.type == Event::Closed) window.close();

			if (event.type == Event::MouseButtonPressed and event.key.code == Mouse::Left) {
				for (int i = 0; i < pieces.size(); ++i) {
					if (pieces[i]->ContainsMouse()) {
						pieces[i]->Select();
						selected = i;
						break;
					}
				}
			}

			if (event.type == Event::MouseButtonReleased and event.key.code == Mouse::Left) {
				if (board.getGlobalBounds().contains(pieces[selected]->getPosition())) { // Check the piece exit outside the window
					Square* nearestSquare = pieces[selected]->SearchNearestSquare();

					pieces[selected]->Capture(*nearestSquare);	// Only one of the options is possible
					pieces[selected]->Move(*nearestSquare);	    //
					pieces[selected]->Castling(*nearestSquare); //
					Promotion();						        //
				}
				else pieces[selected]->ReturnToPreviousPos();

				pieces[selected]->ResetSelection();
			}
		}

		pieces[selected]->MoveWithMouse();
		UpdateWindow();
	}
}

AbstractChessPiece* FindPiece(const Square& square) {
	for (const auto& piece : pieces) {
		if ((*piece->getSquare()) == square) return piece.get();
	}
}

void DeletePiece(Square& square) {
	for (auto piece = pieces.begin(); piece < pieces.end(); ++piece) {
		if ((*(*piece)->getSquare()) == square) {
			square.setIsEmpty(true);
			if ((*piece)->getName() == "KingW" or (*piece)->getName() == "KingB") game.isFinished = true;
			pieces.erase(piece);
			selected = static_cast<char>(pieces.size()) - 1;
			return;
		}
	}
}

void AddPiece(Square& square, int value) {
	switch (abs(value)) {
	case 1:
		pieces.push_back(unique_ptr<AbstractChessPiece>(make_unique<Castle>(square, value < 0)));
		break;

	case 2:
		pieces.push_back(unique_ptr<AbstractChessPiece>(make_unique<Knight>(square, value < 0)));
		break;

	case 3:
		pieces.push_back(unique_ptr<AbstractChessPiece>(make_unique<Bishop>(square, value < 0)));
		break;

	case 4:
		pieces.push_back(unique_ptr<AbstractChessPiece>(make_unique<Queen>(square, value < 0)));
		break;

	case 5:
		pieces.push_back(unique_ptr<AbstractChessPiece>(make_unique<King>(square, value < 0)));
		break;

	case 6:
		pieces.push_back(unique_ptr<AbstractChessPiece>(make_unique<Pawn>(square, value < 0)));
		break;

	default:
		break;
	}
}

void Promotion() {
	if (pieces[selected]->getIsPromotion() and pieces[selected]->ContainsMouse()) {
		int mousePosXInSquare = int(game.mousePos.x - pieces[selected]->getX() * Square::sideLength),
			mousePosYInSquare = int(game.mousePos.y - pieces[selected]->getY() * Square::sideLength);

		if (mousePosXInSquare > Square::sideLength / 2 and mousePosYInSquare < Square::sideLength / 2)
			pieces[selected] = make_unique<Knight>(*pieces[selected]->getSquare(), pieces[selected]->getColor());

		else if (mousePosXInSquare < Square::sideLength / 2 and mousePosYInSquare < Square::sideLength / 2)
			pieces[selected] = make_unique<Queen>(*pieces[selected]->getSquare(), pieces[selected]->getColor());

		else if (mousePosXInSquare < Square::sideLength / 2 and mousePosYInSquare > Square::sideLength / 2)
			pieces[selected] = make_unique<Bishop>(*pieces[selected]->getSquare(), pieces[selected]->getColor());

		else if (mousePosXInSquare > Square::sideLength / 2 and mousePosYInSquare > Square::sideLength / 2)
			pieces[selected] = make_unique<Castle>(*pieces[selected]->getSquare(), pieces[selected]->getColor());

		pieces[selected]->setIsPromotion(false);
		pieces[selected]->setIsMovable(true);
		game.pawnIsPromotion = false;
		game.ChangeOfTurn();
	}
};

void UpdateWindow() {
	window.clear();

	board.draw(window);
	pieces[selected]->DrawPossibleSquares();
	for (auto& piece : pieces) { piece->draw(window); }
	pieces[selected]->draw(window); // The moved piece is drawn twice so that it is on top of all others.

	window.display();
}