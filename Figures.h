#pragma once
class Pawn : public AbstractFigure
{
public:
	bool firstMove = true;

	Pawn(const int& posX, const int& posY, const sf::Texture& texture, const int& cellSide) {
		sprite.setTexture(texture);
		sprite.setOrigin(18, 38);
		sprite.setPosition(cellSide / 2 + cellSide * posX, cellSide / 2 + cellSide * posY);
	}

	void draw(sf::RenderTarget& target, sf::RenderStates states) const override
	{
		target.draw(sprite);
	}

	//void Move(const int& newPosX, const int& newPosY, bool& turn) override
	//{
	//	if (turn == color and newPosX == posX) {
	//		if (color == 0) { // if white
	//			if (firstMove) {
	//				if (posY - newPosY <= 2 and posY - newPosY >= 1) {
	//					posY = newPosY;
	//					firstMove = false;
	//					turn = !turn;
	//				}
	//			}
	//			else {
	//				if (posY - newPosY == 1) {
	//					posY = newPosY;
	//					turn = !turn;
	//				}
	//			}
	//		}
	//		else { // if black
	//			if (firstMove) {
	//				if (newPosY - posY <= 2 and newPosY - posY >= 1) {
	//					posY = newPosY;
	//					firstMove = false;
	//					turn = !turn;
	//				}
	//			}
	//			else {
	//				if (newPosY - posY == 1) {
	//					posY = newPosY;
	//					turn = !turn;
	//				}
	//			}
	//		}
	//	}
	//}
};

class Castle : public AbstractFigure {
public:
	Castle(const int& posX, const int& posY, const sf::Texture& texture, const int& cellSide) {
		sprite.setTexture(texture);
		sprite.setOrigin(26, 38);
		sprite.setPosition(cellSide / 2 + cellSide * posX, cellSide / 2 + cellSide * posY);
	}

	void draw(sf::RenderTarget& target, sf::RenderStates states) const override
	{
		target.draw(sprite);
	}
};

class Knight : public AbstractFigure {
public:
	Knight(const int& posX, const int& posY, const sf::Texture& texture, const int& cellSide) {
		sprite.setTexture(texture);
		sprite.setOrigin(32, 40);
		sprite.setPosition(cellSide / 2 + cellSide * posX, cellSide / 2 + cellSide * posY);
	}

	void draw(sf::RenderTarget& target, sf::RenderStates states) const override
	{
		target.draw(sprite);
	}
};

class Bishop : public AbstractFigure {
public:
	Bishop(const int& posX, const int& posY, const sf::Texture& texture, const int& cellSide) {
		sprite.setTexture(texture);
		sprite.setOrigin(34, 40);
		sprite.setPosition(cellSide / 2 + cellSide * posX, cellSide / 2 + cellSide * posY);
	}

	void draw(sf::RenderTarget& target, sf::RenderStates states) const override
	{
		target.draw(sprite);
	}
};

class Queen : public AbstractFigure {
public:
	Queen(const int& posX, const int& posY, const sf::Texture& texture, const int& cellSide) {
		sprite.setTexture(texture);
		sprite.setOrigin(35, 40);
		sprite.setPosition(cellSide / 2 + cellSide * posX, cellSide / 2 + cellSide * posY);
	}

	void draw(sf::RenderTarget& target, sf::RenderStates states) const override
	{
		target.draw(sprite);
	}
};

class King : public AbstractFigure {
public:
	King(const int& posX, const int& posY, const sf::Texture& texture, const int& cellSide) {
		sprite.setTexture(texture);
		sprite.setOrigin(35, 38);
		sprite.setPosition(cellSide / 2 + cellSide * posX, cellSide / 2 + cellSide * posY);
	}

	void draw(sf::RenderTarget& target, sf::RenderStates states) const override
	{
		target.draw(sprite);
	}
};