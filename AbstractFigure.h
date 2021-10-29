#pragma once
class AbstractFigure : public sf::Drawable
{
public:
	bool color = 0; // 0 - white, 1 - black
	short x = 0, y = 0, xInPixel = 0, yInPixel = 0;
	sf::Texture textures;
	sf::Sprite sprite;

	AbstractFigure() {};

	AbstractFigure(const int& posX, const int& posY, const sf::Texture& texture, const int& cellSide) {
		sprite.setTexture(texture);
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

	void setPos(const int& x, const int& y) {
		sprite.setPosition(x, y);
	}

	//virtual void Move(const int& newPosX, const int& newPosY, bool& turn) = 0;
	//virtual void Capture() = 0;
};
