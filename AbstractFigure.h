#pragma once
using namespace sf; // SFML namespace
using namespace std;

class Square {
public:
	int x = 0, y = 0, xInPixel = 0, yInPixel = 0;
	bool color, isEmpty = true;
	RectangleShape drawableRect;

	Square(const int& x, const int& y, const int& value, const int& squareSide) {
		this->x = x;
		this->y = y;
		this->xInPixel = squareSide / 2 + squareSide * this->x;
		this->yInPixel = squareSide / 2 + squareSide * this->y;
		this->color = false;
		this->drawableRect.setPosition(xInPixel, yInPixel);
		this->drawableRect.setSize(Vector2f(squareSide - 4, squareSide - 4));
		this->drawableRect.setOrigin(squareSide / 2 - 9, squareSide / 2 - 9);
		this->drawableRect.setOutlineColor(Color(255, 255, 255));
		this->drawableRect.setOutlineThickness(2);
		value ? this->isEmpty = false : this->isEmpty = true;
	}
};

class AbstractFigure : public Drawable {
public:
	bool color; // 0 - white, 1 - black
	bool isDeleted = false;
	bool firstMove = true; // учитывается только у пешек
	int x = 0, y = 0;
	string name;
	Texture textures;
	Sprite sprite;

	AbstractFigure(const Square& square, const bool& color, const Texture& texture) {
		this->sprite.setTexture(texture);
		this->sprite.setPosition(square.xInPixel, square.yInPixel);
		this->color = color;
		this->x = square.x;
		this->y = square.y;
	}

	void draw(RenderTarget& target, RenderStates states) const { target.draw(sprite, states); }

	Vector2i getPos() { return Vector2i(sprite.getPosition().x, sprite.getPosition().y); }

	void setPos(const int& xInPixel, const int& yInPixel) { this->sprite.setPosition(xInPixel, yInPixel); }

	virtual void Move(const int& newX, const int& newY, bool& turn, RenderWindow& window, vector<vector<Square>>& squares) = 0;
	virtual bool Capture(const int& newX, const int& newY, bool& turn, RenderWindow& window, vector<vector<Square>>& squares) = 0;
	virtual bool ConditionOfMove(const int& newX, const int& newY, bool& turn, vector<vector<Square>>& squares) = 0;

	void Move_(Square& oldSquare, Square& newSquare, bool& turn, RenderWindow& window) {
		oldSquare.isEmpty = true;
		newSquare.isEmpty = false;
		newSquare.color = this->color;
		oldSquare.color = !(this->color);
		this->x = newSquare.x;
		this->y = newSquare.y;
		this->setPos(newSquare.xInPixel, newSquare.yInPixel);
		turn = !turn;
		turn ? window.setTitle("Chess: turn of black") : window.setTitle("Chess: turn of white");
	};
};
