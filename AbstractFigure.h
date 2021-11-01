#pragma once
class Square {
public:
	int x = 0, y = 0, xInPixel = 0, yInPixel = 0;
	bool isEmpty = true;

	Square(const int& x, const int& y, const int& value, const int& cellSide) {
		this->x = x;
		this->y = y;
		this->xInPixel = cellSide / 2 + cellSide * x;
		this->yInPixel = cellSide / 2 + cellSide * y;

		value ? isEmpty = false : isEmpty = true;
	}
};

class AbstractFigure : public sf::Drawable
{
public:
	bool color = 0; // 0 - white, 1 - black
	int x = 0, y = 0, xInPixel = 0, yInPixel = 0;
	sf::Texture textures;
	sf::Sprite sprite;

	AbstractFigure(const Square& square, const bool& color, const sf::Texture& texture) {
		this->sprite.setTexture(texture);
		this->color = color;
		this->x = square.x;
		this->y = square.y;
		this->xInPixel = square.xInPixel;
		this->yInPixel = square.yInPixel;
		this->sprite.setPosition(xInPixel, yInPixel);
	}

	void draw(sf::RenderTarget& target, sf::RenderStates states) const
	{
		target.draw(sprite, states);
	}

	sf::Vector2i getPos() {
		return sf::Vector2i(sprite.getPosition().x, sprite.getPosition().y);
	}

	void setPos(const int& xInPixel, const int& yInPixel) {
		this->xInPixel = xInPixel;
		this->yInPixel = xInPixel;
		this->sprite.setPosition(xInPixel, yInPixel);
	}

	virtual void Move(Square& oldCell, Square& newCell, bool& turn, sf::RenderWindow& window) = 0;

protected:
	void Move_(Square& oldCell, Square& newCell, bool& turn, sf::RenderWindow& window) {
		oldCell.isEmpty = true;
		newCell.isEmpty = false;
		x = newCell.x;
		y = newCell.y;
		setPos(newCell.xInPixel, newCell.yInPixel);
		turn = !turn;
		turn ? window.setTitle("Chess: turn of black") : window.setTitle("Chess: turn of white");
	};
	//virtual void Capture() = 0;
};
