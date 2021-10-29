#pragma once
class AbstractFigure : sf::Drawable
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

	//virtual void Move(const int& newPosX, const int& newPosY, bool& turn) = 0;
	//virtual void Capture() = 0;
};
