#pragma once
class AbstractFigure : public sf::Drawable
{
public:
	bool color = 0; // 0 - white, 1 - black
	int posX = 0, posY = 0;
	sf::Texture textures;
	sf::Sprite sprite;

	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const
	{
		target.draw(sprite, states);
	}

	sf::Vector2i getPos() {
		return sf::Vector2i(sprite.getPosition().x, sprite.getPosition().y);
	}

	void setPos(const int& pos_x, const int& pos_y) {
		sprite.setPosition(pos_x, pos_y);
	}

	//virtual void Move(const int& newPosX, const int& newPosY, bool& turn) = 0;
	//virtual void Capture() = 0;
};
