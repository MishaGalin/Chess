#pragma once
class Square {
public:
	int x = 0, y = 0, xInPixel = 0, yInPixel = 0;
	bool isEmpty = true;

	Square() {}

	Square(const int& x, const int& y, const int& value, const int& cellSide) {
		this->x = x;
		this->y = y;
		this->xInPixel = cellSide / 2 + cellSide * x;
		this->yInPixel = cellSide / 2 + cellSide * y;

		value ? isEmpty = false : isEmpty = true;
	}
};

class AbstractFigure : public sf::Drawable {
public:
	bool color = false; // 0 - white, 1 - black
	bool isDeleted = false;
	int x = 0, y = 0;
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

	//void self_delete(std::vector<std::vector<Square>>& squares) {
	//	sprite.setColor(sf::Color(0, 0, 0, 0));
	//	squares[x][y].isEmpty = true;
	//}

	virtual void Move(const int& newX, const int& newY, bool& turn, sf::RenderWindow& window, std::vector<std::vector<Square>>& squares) = 0;
	virtual bool Capture(const int& newX, const int& newY, bool& turn, sf::RenderWindow& window, std::vector<std::vector<Square>>& squares) = 0;

	void Move_(Square& oldSquare, Square& newSquare, bool& turn, sf::RenderWindow& window) {
		oldSquare.isEmpty = true;
		newSquare.isEmpty = false;
		x = newSquare.x;
		y = newSquare.y;
		setPos(newSquare.xInPixel, newSquare.yInPixel);
		turn = !turn;
		turn ? window.setTitle("Chess: turn of black") : window.setTitle("Chess: turn of white");
	};
};
