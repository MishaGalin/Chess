#pragma once
using namespace sf; // SFML namespace
using namespace std;

extern bool g_turn;
extern const int g_squareSide;
extern bool g_gameIsStopped;

extern RenderWindow window;

class Square : private Drawable {
	bool color, isEmpty = true;
	int x = 0, y = 0, xInPixel = 0, yInPixel = 0;

public:
	RectangleShape drawableRect;

	Square(const int& x, const int& y, const int& value) {
		this->x = x;
		this->y = y;
		this->xInPixel = 7 + g_squareSide / 2 + g_squareSide * this->x;
		this->yInPixel = 7 + g_squareSide / 2 + g_squareSide * this->y;
		this->color = false;
		this->drawableRect.setPosition(xInPixel, yInPixel);
		this->drawableRect.setSize(Vector2f(g_squareSide - 2, g_squareSide - 2));
		this->drawableRect.setOrigin(g_squareSide / 2 - 1, g_squareSide / 2 - 1);
		this->drawableRect.setOutlineColor(Color::White);
		this->drawableRect.setOutlineThickness(2);
		value ? this->isEmpty = false : this->isEmpty = true;
	}

	void draw(RenderTarget& target, RenderStates states = RenderStates::Default) const { target.draw(drawableRect, states); }

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

class AbstractFigure : private Drawable {
	bool color = false; // 0 - white, 1 - black
	bool firstMove = true; // учитывается только у пешек
	bool isDeleted = false;
	int x = 0, y = 0;

protected:
	void Move_(Square& oldSquare, Square& newSquare) {
		oldSquare.setIsEmpty(true);
		newSquare.setIsEmpty(false);
		newSquare.setColor(this->color);
		oldSquare.setColor(!this->color);
		if (this->firstMove) this->firstMove = false;
		this->x = newSquare.getX();
		this->y = newSquare.getY();
		this->sprite.setPosition(newSquare.getXInPixel(), newSquare.getYInPixel());
		g_turn = !g_turn;
		if (g_gameIsStopped) g_turn ? window.setTitle("Chess: WHITE WINS") : window.setTitle("Chess: BLACK WINS");
		else g_turn ? window.setTitle("Chess: turn of black") : window.setTitle("Chess: turn of white");
	};

public:
	Sprite sprite;
	string name;
	Texture texture;

	virtual void Move(Square& square) = 0;
	virtual bool ConditionOfMove(const Square& square) = 0;
	virtual void Capture(Square& square) = 0;
	virtual bool ConditionOfCapture(const Square& square) = 0;

	AbstractFigure(const Square& square, const bool& color, const Texture& texture) {
		this->sprite.setTexture(texture);
		this->sprite.setPosition(square.getXInPixel(), square.getYInPixel());
		this->color = color;
		this->x = square.getX();
		this->y = square.getY();
	}

	void draw(RenderTarget& target, RenderStates states = RenderStates::Default) const { target.draw(sprite, states); }
	bool getColor() const { return color; }
	void setColor(const bool& color) { this->color = color; }

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
