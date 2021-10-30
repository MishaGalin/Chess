#pragma once
class Pawn : public AbstractFigure
{
public:
	bool firstMove = true;

	Pawn(const int& posX, const int& posY, const bool& color, const sf::Texture& texture, const int& cellSide) : AbstractFigure(posX, posY, color, texture, cellSide) {
		sprite.setOrigin(18, 38);
	}

	void Move(Cell& oldCell, Cell& newCell, const int& cellSide, bool* turn) override
	{
		if (*turn == color and oldCell.x == newCell.x and newCell.isEmpty) {
			if (color == 0) { // if white
				if (firstMove) {
					if (oldCell.y - newCell.y == 2 or oldCell.y - newCell.y == 1) {
						oldCell.isEmpty = true;
						newCell.isEmpty = false;
						firstMove = false;
						x = newCell.x;
						y = newCell.y;
						setPos(newCell.xInPixel, newCell.yInPixel);
						*turn = !*turn;
						return;
					}
				}
				else {
					if (oldCell.y - newCell.y == 1) {
						oldCell.isEmpty = true;
						newCell.isEmpty = false;
						x = newCell.x;
						y = newCell.y;
						setPos(newCell.xInPixel, newCell.yInPixel);
						*turn = !*turn;
						return;
					}
				}
			}
			else { // if black
				if (firstMove) {
					if (newCell.y - oldCell.y == 2 or newCell.y - oldCell.y == 1) {
						oldCell.isEmpty = true;
						newCell.isEmpty = false;
						firstMove = false;
						x = newCell.x;
						y = newCell.y;
						setPos(newCell.xInPixel, newCell.yInPixel);
						*turn = !*turn;
						return;
					}
				}
				else {
					if (newCell.y - oldCell.y == 1) {
						oldCell.isEmpty = true;
						newCell.isEmpty = false;
						x = newCell.x;
						y = newCell.y;
						setPos(newCell.xInPixel, newCell.yInPixel);
						*turn = !*turn;
						return;
					}
				}
			}
		}
		setPos(oldCell.xInPixel, oldCell.yInPixel);
	}
};

class Castle : public AbstractFigure {
public:
	Castle(const int& posX, const int& posY, const bool& color, const sf::Texture& texture, const int& cellSide) : AbstractFigure(posX, posY, color, texture, cellSide) {
		sprite.setOrigin(26, 38);
	}

	void Move(Cell& oldCell, Cell& newCell, const int& cellSide, bool* turn) override
	{
		if (*turn == color and newCell.x == x) {
			if (color == 0) { // if white
				if (y - newCell.y == 1) {
					y = newCell.y;
					*turn = !*turn;
				}
			}
		}
		else { // if black
			if (newCell.y - y == 1) {
				y = newCell.y;
				*turn = !*turn;
			}
		}
	}
};

class Knight : public AbstractFigure {
public:
	Knight(const int& posX, const int& posY, const bool& color, const sf::Texture& texture, const int& cellSide) : AbstractFigure(posX, posY, color, texture, cellSide) {
		sprite.setOrigin(32, 40);
	}

	void Move(Cell& oldCell, Cell& newCell, const int& cellSide, bool* turn) override
	{
		if (*turn == color and newCell.x == x) {
			if (color == 0) { // if white
				if (y - newCell.y == 1) {
					y = newCell.y;
					*turn = !*turn;
				}
			}
		}
		else { // if black
			if (newCell.y - y == 1) {
				y = newCell.y;
				*turn = !*turn;
			}
		}
	}
};

class Bishop : public AbstractFigure {
public:
	Bishop(const int& posX, const int& posY, const bool& color, const sf::Texture& texture, const int& cellSide) : AbstractFigure(posX, posY, color, texture, cellSide) {
		sprite.setOrigin(34, 40);
	}

	void Move(Cell& oldCell, Cell& newCell, const int& cellSide, bool* turn) override
	{
		if (*turn == color and newCell.x == x) {
			if (color == 0) { // if white
				if (y - newCell.y == 1) {
					y = newCell.y;
					*turn = !*turn;
				}
			}
		}
		else { // if black
			if (newCell.y - y == 1) {
				y = newCell.y;
				*turn = !*turn;
			}
		}
	}
};

class Queen : public AbstractFigure {
public:
	Queen(const int& posX, const int& posY, const bool& color, const sf::Texture& texture, const int& cellSide) : AbstractFigure(posX, posY, color, texture, cellSide) {
		sprite.setOrigin(35, 40);
	}

	void Move(Cell& oldCell, Cell& newCell, const int& cellSide, bool* turn) override
	{
		if (*turn == color and newCell.x == x) {
			if (color == 0) { // if white
				if (y - newCell.y == 1) {
					y = newCell.y;
					*turn = !*turn;
				}
			}
		}
		else { // if black
			if (newCell.y - y == 1) {
				y = newCell.y;
				*turn = !*turn;
			}
		}
	}
};

class King : public AbstractFigure {
public:
	King(const int& posX, const int& posY, const bool& color, const sf::Texture& texture, const int& cellSide) : AbstractFigure(posX, posY, color, texture, cellSide) {
		sprite.setOrigin(35, 38);
	}

	void Move(Cell& oldCell, Cell& newCell, const int& cellSide, bool* turn) override
	{
		if (*turn == color and newCell.x == x) {
			if (color == 0) { // if white
				if (y - newCell.y == 1) {
					y = newCell.y;
					*turn = !*turn;
				}
			}
		}
		else { // if black
			if (newCell.y - y == 1) {
				y = newCell.y;
				*turn = !*turn;
			}
		}
	}
};
