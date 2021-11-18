#pragma once
using namespace sf; // SFML namespace
using namespace std;

extern bool g_turn, g_gameIsStopped;
extern const int g_squareSide, g_boardSize;
extern RenderWindow window;

class Square : public Drawable {
	bool color = false, isEmpty = true;
	int x = 0, y = 0, xInPixel = 0, yInPixel = 0;
	RectangleShape drawableRect;

public:
	Square(const int& x, const int& y, const int& value) {
		setX(x);
		setY(y);
		setXInPixel(7 + g_squareSide / 2 + g_squareSide * getX());
		setYInPixel(7 + g_squareSide / 2 + g_squareSide * getY());
		setColor(false);
		value ? setIsEmpty(false) : setIsEmpty(true);

		drawableRect.setPosition(xInPixel, yInPixel);
		drawableRect.setSize(Vector2f(g_squareSide - 2, g_squareSide - 2));
		drawableRect.setOrigin(g_squareSide / 2 - 1, g_squareSide / 2 - 1);
		drawableRect.setOutlineColor(Color::White);
		drawableRect.setOutlineThickness(2);
	}

	void draw(RenderTarget& target, RenderStates states = RenderStates::Default) const { target.draw(drawableRect, states); }

	void drawWithColor(Color color) {
		drawableRect.setFillColor(color);
		draw(window);
	}

	bool getIsEmpty() const { return isEmpty; }
	void setIsEmpty(const bool& isEmpty) { this->isEmpty = isEmpty; }

	bool getColor() const { return color; }
	void setColor(const bool& color) { this->color = color; }

	int getX() const { return x; }
	void setX(const int& x) { this->x = x; }

	int getY() const { return y; }
	void setY(const int& y) { this->y = y; }

	int getXInPixel() const { return xInPixel; }
	void setXInPixel(const int& xInPixel) { this->xInPixel = xInPixel; }

	int getYInPixel() const { return yInPixel; }
	void setYInPixel(const int& yInPixel) { this->yInPixel = yInPixel; }
};

extern vector<vector<Square>> board;
extern void Delete(Square& square);

class AbstractChessPiece : public Drawable {
	bool color = false; // 0 - white, 1 - black
	bool firstMove = true; // Only relevant for pawns
	bool isDeleted = false, isSelected = false;
	int x = 0, y = 0;
	string name = "";

	// Directly moving from one square to another
	void Move_(Square& oldSquare, Square& newSquare) {
		oldSquare.setIsEmpty(true);
		newSquare.setIsEmpty(false);
		oldSquare.setColor(!getColor());
		newSquare.setColor(getColor());

		if (getFirstMove()) setFirstMove(false);
		setX(newSquare.getX());
		setY(newSquare.getY());
		setPosition(newSquare.getXInPixel(), newSquare.getYInPixel());

		g_turn = !g_turn;
		if (g_gameIsStopped) g_turn ? window.setTitle("Chess: WHITE WINS") : window.setTitle("Chess: BLACK WINS");
		else g_turn ? window.setTitle("Chess: turn of black") : window.setTitle("Chess: turn of white");
	};

	virtual bool ConditionOfMove(const Square& square) = 0;
	virtual bool ConditionOfCapture(const Square& square) = 0;

protected:
	Sprite sprite;
	AbstractChessPiece(const Square& square, const bool& color) {
		setPosition(square.getXInPixel(), square.getYInPixel());
		setColor(color);
		setX(square.getX());
		setY(square.getY());
	}

public:
	void draw(RenderTarget& target, RenderStates states = RenderStates::Default) const { target.draw(sprite, states); }

	void ReturnToPrevPos() {
		sprite.setPosition(board[x][y].getXInPixel(), board[x][y].getYInPixel());
	};

	void Move(Square& square) {
		if (ConditionOfMove(square)) Move_(board[x][y], square);
		else ReturnToPrevPos();
	}

	void Capture(Square& square) {
		if (ConditionOfCapture(square)) {
			Delete(square);
			Move_(board[x][y], square);
		}
		else ReturnToPrevPos();
	}

	Vector2i SearchNearestSquare(Vector2i& mousePos) {
		double maxDistance = 10000., distance = 0.;
		int nearestX = 0, nearestY = 0;

		for (int i = 0; i < g_boardSize; ++i) {
			for (int j = 0; j < g_boardSize; ++j) {
				distance = sqrt(pow(mousePos.x - board[i][j].getXInPixel(), 2) + pow(mousePos.y - board[i][j].getYInPixel(), 2)); // Distance to the square
				if (distance < maxDistance) {
					maxDistance = distance;
					nearestX = i;
					nearestY = j;
				}
			}
		}
		return Vector2i(nearestX, nearestY);
	}

	// Displaying the squares into which the piece can go
	void DrawPossibleSquares() {
		for (int i = 0; i < g_boardSize; ++i) {
			for (int j = 0; j < g_boardSize; ++j) {
				if (ConditionOfMove(board[i][j]) && getIsSelected()) board[i][j].drawWithColor(Color(0, 255, 0, 70)); // Green square if you can go to this square
				else if (ConditionOfCapture(board[i][j]) && getIsSelected()) board[i][j].drawWithColor(Color(255, 0, 0, 70)); // Red square if you can capture
			}
		}
	}

	FloatRect getGlobalBounds() const { return sprite.getGlobalBounds(); }

	Vector2f getPosition() const { return sprite.getPosition(); }
	void setPosition(const int& x, const int& y) { sprite.setPosition(float(x), float(y)); }

	bool getColor() const { return color; }
	void setColor(const bool& color) { this->color = color; }

	bool getIsSelected() const { return isSelected; }
	void setIsSelected(const bool& isSelected) { this->isSelected = isSelected; }

	bool getFirstMove() const { return firstMove; }
	void setFirstMove(const bool& firstMove) { this->firstMove = firstMove; }

	bool getIsDeleted() const { return isDeleted; }
	void setIsDeleted(const bool& isDeleted) { this->isDeleted = isDeleted; }

	int getX() const { return x; }
	void setX(const int& x) { this->x = x; }

	int getY() const { return y; }
	void setY(const int& y) { this->y = y; }

	string getName() const { return name; }
	void setName(const string& name) { this->name = name; }
};
