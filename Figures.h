#pragma once
class Pawn : public AbstractFigure
{
public:
	bool firstMove = true;

	Pawn(const int& posX, const int& posY, const sf::Texture& texture, const unsigned short& cellSide) : AbstractFigure(posX, posY, texture, cellSide) {
		sprite.setOrigin(18, 38);
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
	Castle(const int& posX, const int& posY, const sf::Texture& texture, const unsigned short& cellSide) : AbstractFigure(posX, posY, texture, cellSide) {
		sprite.setOrigin(26, 38);
	}
};

class Knight : public AbstractFigure {
public:
	Knight(const int& posX, const int& posY, const sf::Texture& texture, const unsigned short& cellSide) : AbstractFigure(posX, posY, texture, cellSide) {
		sprite.setOrigin(32, 40);
	}
};

class Bishop : public AbstractFigure {
public:
	Bishop(const int& posX, const int& posY, const sf::Texture& texture, const unsigned short& cellSide) : AbstractFigure(posX, posY, texture, cellSide) {
		sprite.setOrigin(34, 40);
	}
};

class Queen : public AbstractFigure {
public:
	Queen(const int& posX, const int& posY, const sf::Texture& texture, const unsigned short& cellSide) : AbstractFigure(posX, posY, texture, cellSide) {
		sprite.setOrigin(35, 40);
	}
};

class King : public AbstractFigure {
public:
	King(const int& posX, const int& posY, const sf::Texture& texture, const unsigned short& cellSide) : AbstractFigure(posX, posY, texture, cellSide) {
		sprite.setOrigin(35, 38);
	}
};

class Cell {
public:
	short x = 0, y = 0, xInPixel = 0, yInPixel = 0;
	bool isEmpty = true;

	Cell(const short& x, const short& y, const short& value, const unsigned short& cellSide) {
		this->x = x;
		this->y = y;

		value == 0 ? isEmpty = true : isEmpty = false;
	}
};
