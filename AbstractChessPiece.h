#pragma once
using namespace sf; // SFML namespace
using namespace std;

extern Game game;
extern RenderWindow window;
extern Board board;
void DeletePiece(const Square& square);

class AbstractChessPiece : public Drawable {
	bool color = false; // 0 - white, 1 - black
	bool firstMove = true; // Only relevant for pawns
	bool isSelected = false;
	int x = 0, y = 0;
	string name = "";

	// Directly moving from one square to another
	void Move_(Square& newSquare) {
		Changeover(board.Squares[x][y], newSquare);

		setFirstMove(false);
		setX(newSquare.getX());
		setY(newSquare.getY());
		setPosition(newSquare.getInPixel());

		game.ChangeOfTurn();
	};

	virtual bool ConditionOfMove(const Square& square) = 0;
	virtual bool ConditionOfCapture(const Square& square) = 0;
	virtual bool ConditionOfCastling(const Square& square) = 0;
	virtual void Castling_(const Square& square) = 0;

protected:
	Sprite sprite;
	AbstractChessPiece(const Square& square, const bool& color) {
		setPosition(square.getInPixel());
		setColor(color);
		setX(square.getX());
		setY(square.getY());
	}

	void Changeover(Square& oldSquare, Square& newSquare) {
		oldSquare.setIsEmpty(true);
		newSquare.setIsEmpty(false);
		oldSquare.setColor(!getColor());
		newSquare.setColor(getColor());
	}

public:
	void draw(RenderTarget& target, RenderStates states = RenderStates::Default) const { target.draw(sprite, states); }

	void ReturnToPrevPos() {
		setPosition(board.Squares[x][y].getInPixel());
	};

	void Move(Square& newSquare) {
		if (ConditionOfMove(newSquare)) Move_(newSquare);
		else ReturnToPrevPos();
	}

	void Capture(Square& newSquare) {
		if (ConditionOfCapture(newSquare)) {
			DeletePiece(newSquare);
			Move_(newSquare);
		}
		else ReturnToPrevPos();
	}

	void Castling(Square& newSquare) {
		if (ConditionOfCastling(newSquare)) Castling_(newSquare);
		else ReturnToPrevPos();
	}

	Square* SearchNearestSquare(Vector2i& mousePos) {
		double maxDistance = 10000., distance = 0.;
		int nearestX = 0, nearestY = 0;

		for (int i = 0; i < Board::Size; ++i) {
			for (int j = 0; j < Board::Size; ++j) {
				distance = sqrt(pow(mousePos.x - board.Squares[i][j].getXInPixel(), 2) + pow(mousePos.y - board.Squares[i][j].getYInPixel(), 2)); // Distance to the square
				if (distance < maxDistance) {
					maxDistance = distance;
					nearestX = i;
					nearestY = j;
				}
			}
		}
		return &board.Squares[nearestX][nearestY];
	}

	// Displaying the squares into which the piece can go
	void DrawPossibleSquares() {
		for (int i = 0; i < Board::Size; ++i) {
			for (int j = 0; j < Board::Size; ++j) {
				if (ConditionOfMove(board.Squares[i][j])) board.Squares[i][j].drawWithColor(Color(0, 255, 0, 60)); // Green square if you can go to this square
				else if (ConditionOfCapture(board.Squares[i][j])) board.Squares[i][j].drawWithColor(Color(255, 0, 0, 60)); // Red square if you can capture
				else if (ConditionOfCastling(board.Squares[i][j])) board.Squares[i][j].drawWithColor(Color(255, 255, 0, 60));
			}
		}
	}

	FloatRect getGlobalBounds() const { return sprite.getGlobalBounds(); }

	Vector2f getPosition() const { return sprite.getPosition(); }
	void setPosition(const int& x, const int& y) { sprite.setPosition(float(x), float(y)); }
	void setPosition(Vector2i newPos) { sprite.setPosition(float(newPos.x), float(newPos.y)); }

	bool getColor() const { return color; }
	void setColor(const bool& color) { this->color = color; }

	bool getIsSelected() const { return isSelected; }
	void setIsSelected(const bool& isSelected) { this->isSelected = isSelected; }

	bool getFirstMove() const { return firstMove; }
	void setFirstMove(const bool& firstMove) { this->firstMove = firstMove; }

	int getX() const { return x; }
	void setX(const int& x) { this->x = x; }

	int getY() const { return y; }
	void setY(const int& y) { this->y = y; }

	string getName() const { return name; }
	void setName(const string& name) { this->name = name; }
};
