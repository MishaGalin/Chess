#pragma once
class Square {
public:
	int x = 0, y = 0, xInPixel = 0, yInPixel = 0;
	bool isEmpty = true;
	bool color;
	sf::RectangleShape drawableRect;

	Square(const int& x, const int& y, const int& value, const int& squareSide) {
		this->x = x;
		this->y = y;
		this->xInPixel = squareSide / 2 + squareSide * x;
		this->yInPixel = squareSide / 2 + squareSide * y;
		drawableRect.setPosition(xInPixel, yInPixel);
		drawableRect.setSize(sf::Vector2f(squareSide, squareSide));
		drawableRect.setOrigin(squareSide / 2 - 7, squareSide / 2 - 7);

		value ? isEmpty = false : isEmpty = true;
	}
};

class AbstractFigure : public sf::Drawable {
public:
	bool color; // 0 - white, 1 - black
	bool isDeleted = false;
	int x = 0, y = 0;
	std::string name;
	sf::Texture textures;
	sf::Sprite sprite;

	AbstractFigure(const Square& square, const bool& color, const sf::Texture& texture) {
		this->sprite.setTexture(texture);
		this->color = color;
		this->x = square.x;
		this->y = square.y;
		this->sprite.setPosition(square.xInPixel, square.yInPixel);
	}

	void draw(sf::RenderTarget& target, sf::RenderStates states) const
	{
		target.draw(sprite, states);
	}

	sf::Vector2i getPos() {
		return sf::Vector2i(sprite.getPosition().x, sprite.getPosition().y);
	}

	void setPos(const int& xInPixel, const int& yInPixel) {
		this->sprite.setPosition(xInPixel, yInPixel);
	}

	virtual void Move(const int& newX, const int& newY, bool& turn, sf::RenderWindow& window, std::vector<std::vector<Square>>& squares) = 0;
	virtual bool Capture(const int& newX, const int& newY, bool& turn, sf::RenderWindow& window, std::vector<std::vector<Square>>& squares) = 0;
	virtual bool ConditionMove(const int& newX, const int& newY, bool& turn, std::vector<std::vector<Square>>& squares) = 0;

	void Move_(Square& oldSquare, Square& newSquare, bool& turn, sf::RenderWindow& window) {
		oldSquare.isEmpty = true;
		newSquare.isEmpty = false;
		newSquare.color = this->color;
		x = newSquare.x;
		y = newSquare.y;
		setPos(newSquare.xInPixel, newSquare.yInPixel);
		turn = !turn;
		turn ? window.setTitle("Chess: turn of black") : window.setTitle("Chess: turn of white");
	};
};
