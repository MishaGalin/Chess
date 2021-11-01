#pragma once
class Cell {
public:
	int x = 0, y = 0, xInPixel = 0, yInPixel = 0;
	bool isEmpty = true;

	Cell(const int& x, const int& y, const int& value, const int& cellSide) {
		this->x = x;
		this->y = y;
		this->xInPixel = cellSide / 2 + cellSide * x;
		this->yInPixel = cellSide / 2 + cellSide * y;

		value == 0 ? isEmpty = true : isEmpty = false;
	}
};

class AbstractFigure : public sf::Drawable
{
public:
	bool color = 0; // 0 - white, 1 - black
	int x = 0, y = 0, xInPixel = 0, yInPixel = 0;
	sf::Texture textures;
	sf::Sprite sprite;

	AbstractFigure() {};

	AbstractFigure(const int& posX, const int& posY, const bool& color, const sf::Texture& texture, const int& cellSide) {
		sprite.setTexture(texture);
		this->color = color;
		x = posX;
		y = posY;
		xInPixel = cellSide / 2 + cellSide * x;
		yInPixel = cellSide / 2 + cellSide * y;
		sprite.setPosition(xInPixel, yInPixel);
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

	virtual void Move(Cell& oldCell, Cell& newCell, const int& cellSide, bool& turn, sf::RenderWindow& window) = 0;
protected:
	void Move_(Cell& oldCell, Cell& newCell, bool& turn, sf::RenderWindow& window) {
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
