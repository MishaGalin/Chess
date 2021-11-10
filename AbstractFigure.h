#pragma once
using namespace sf; // SFML namespace
using namespace std;

extern RenderWindow window;
extern bool turn;
extern const int squareSide;
extern bool gameIsStopped;

class Square : public Drawable {
public:
	bool color, isEmpty = true;
	int x = 0, y = 0, xInPixel = 0, yInPixel = 0;
	RectangleShape drawableRect;

	void draw(RenderTarget& target, RenderStates states = RenderStates::Default) const { target.draw(drawableRect, states); }

	Square(const int& x, const int& y, const int& value) {
		this->x = x;
		this->y = y;
		this->xInPixel = squareSide / 2 + squareSide * this->x;
		this->yInPixel = squareSide / 2 + squareSide * this->y;
		this->color = false;
		this->drawableRect.setPosition(xInPixel, yInPixel);
		this->drawableRect.setSize(Vector2f(squareSide - 2, squareSide - 2));
		this->drawableRect.setOrigin(squareSide / 2 - 8, squareSide / 2 - 8);
		this->drawableRect.setOutlineColor(Color::White);
		this->drawableRect.setOutlineThickness(2);
		value ? this->isEmpty = false : this->isEmpty = true;
	}
};

class AbstractFigure : public Drawable {
public:
	bool color; // 0 - white, 1 - black
	bool firstMove = true; // учитывается только у пешек
	bool isDeleted = false;
	int x = 0, y = 0;
	Sprite sprite;
	string name;
	Texture texture;

	AbstractFigure(const Square& square, const bool& color, const Texture& texture) {
		this->sprite.setTexture(texture);
		this->sprite.setPosition(square.xInPixel, square.yInPixel);
		this->color = color;
		this->x = square.x;
		this->y = square.y;
	}

	void draw(RenderTarget& target, RenderStates states = RenderStates::Default) const { target.draw(sprite, states); }

	Vector2i getPos() { return Vector2i(sprite.getPosition().x, sprite.getPosition().y); }

	void setPos(const int& xInPixel, const int& yInPixel) { this->sprite.setPosition(xInPixel, yInPixel); }

	virtual void Move(Square& square) = 0;
	virtual bool ConditionOfCapture(const Square& square) = 0;
	virtual bool ConditionOfMove(const Square& square) = 0;

	void Move_(Square& oldSquare, Square& newSquare) {
		oldSquare.isEmpty = true;
		newSquare.isEmpty = false;
		newSquare.color = this->color;
		oldSquare.color = !(this->color);
		if (this->firstMove) this->firstMove = false;
		this->x = newSquare.x;
		this->y = newSquare.y;
		this->setPos(newSquare.xInPixel, newSquare.yInPixel);
		turn = !turn;
		if (gameIsStopped) turn ? window.setTitle("Chess: WHITE WIN") : window.setTitle("Chess: BLACK WIN");
		else turn ? window.setTitle("Chess: turn of black") : window.setTitle("Chess: turn of white");
	};
};
