#pragma once
class Pawn : public AbstractFigure
{
public:
	bool firstMove = true;

	Pawn(const int& posX, const int& posY, const bool& color, const sf::Texture& texture, const int& cellSide) : AbstractFigure(posX, posY, color, texture, cellSide) {
		sprite.setOrigin(18, 38);
	}

	void Move(Cell& oldCell, Cell& newCell, const int& cellSide, bool& turn, sf::RenderWindow& window) override
	{
		if (turn == color && oldCell.x == newCell.x && newCell.isEmpty) {
			if (color == 0) { // if white
				if (firstMove) {
					if (oldCell.y - newCell.y == 2 || oldCell.y - newCell.y == 1) {
						Move_(oldCell, newCell, turn, window);
						return;
					}
				}
				else {
					if (oldCell.y - newCell.y == 1) {
						Move_(oldCell, newCell, turn, window);
						return;
					}
				}
			}
			else { // if black
				if (firstMove) {
					if (newCell.y - oldCell.y == 2 || newCell.y - oldCell.y == 1) {
						Move_(oldCell, newCell, turn, window);
						return;
					}
				}
				else {
					if (newCell.y - oldCell.y == 1) {
						Move_(oldCell, newCell, turn, window);
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

	void Move(Cell& oldCell, Cell& newCell, const int& cellSide, bool& turn, sf::RenderWindow& window) override
	{
		if (turn == color && oldCell.x == newCell.x && newCell.isEmpty) {
			if (color == 0) { // if white
				if (oldCell.y - newCell.y == 1) {
					Move_(oldCell, newCell, turn, window);
					return;
				}
			}
			else { // if black
				if (newCell.y - oldCell.y == 1) {
					Move_(oldCell, newCell, turn, window);
					return;
				}
			}
		}
		setPos(oldCell.xInPixel, oldCell.yInPixel);
	}
};

class Knight : public AbstractFigure {
public:
	Knight(const int& posX, const int& posY, const bool& color, const sf::Texture& texture, const int& cellSide) : AbstractFigure(posX, posY, color, texture, cellSide) {
		sprite.setOrigin(32, 40);
	}

	void Move(Cell& oldCell, Cell& newCell, const int& cellSide, bool& turn, sf::RenderWindow& window) override
	{
		if (turn == color && oldCell.x == newCell.x && newCell.isEmpty) {
			if (color == 0) { // if white
				if (oldCell.y - newCell.y == 1) {
					Move_(oldCell, newCell, turn, window);
					return;
				}
			}
			else { // if black
				if (newCell.y - oldCell.y == 1) {
					Move_(oldCell, newCell, turn, window);
					return;
				}
			}
		}
		setPos(oldCell.xInPixel, oldCell.yInPixel);
	}
};

class Bishop : public AbstractFigure {
public:
	Bishop(const int& posX, const int& posY, const bool& color, const sf::Texture& texture, const int& cellSide) : AbstractFigure(posX, posY, color, texture, cellSide) {
		sprite.setOrigin(34, 40);
	}

	void Move(Cell& oldCell, Cell& newCell, const int& cellSide, bool& turn, sf::RenderWindow& window) override
	{
		if (turn == color && oldCell.x == newCell.x && newCell.isEmpty) {
			if (color == 0) { // if white
				if (oldCell.y - newCell.y == 1) {
					Move_(oldCell, newCell, turn, window);
					return;
				}
			}

			else { // if black
				if (newCell.y - oldCell.y == 1) {
					Move_(oldCell, newCell, turn, window);
					return;
				}
			}
		}
		setPos(oldCell.xInPixel, oldCell.yInPixel);
	}
};

class Queen : public AbstractFigure {
public:
	Queen(const int& posX, const int& posY, const bool& color, const sf::Texture& texture, const int& cellSide) : AbstractFigure(posX, posY, color, texture, cellSide) {
		sprite.setOrigin(35, 40);
	}

	void Move(Cell& oldCell, Cell& newCell, const int& cellSide, bool& turn, sf::RenderWindow& window) override
	{
		if (turn == color && oldCell.x == newCell.x && newCell.isEmpty) {
			if (color == 0) { // if white
				if (oldCell.y - newCell.y == 1) {
					Move_(oldCell, newCell, turn, window);
					return;
				}
			}
			else { // if black
				if (newCell.y - oldCell.y == 1) {
					Move_(oldCell, newCell, turn, window);
					return;
				}
			}
		}
		setPos(oldCell.xInPixel, oldCell.yInPixel);
	}
};

class King : public AbstractFigure {
public:
	King(const int& posX, const int& posY, const bool& color, const sf::Texture& texture, const int& cellSide) : AbstractFigure(posX, posY, color, texture, cellSide) {
		sprite.setOrigin(35, 38);
	}

	void Move(Cell& oldCell, Cell& newCell, const int& cellSide, bool& turn, sf::RenderWindow& window) override
	{
		if (turn == color && oldCell.x == newCell.x && newCell.isEmpty) {
			if (color == 0) { // if white
				if (oldCell.y - newCell.y == 1) {
					Move_(oldCell, newCell, turn, window);
					return;
				}
			}
			else { // if black
				if (newCell.y - oldCell.y == 1) {
					Move_(oldCell, newCell, turn, window);
					return;
				}
			}
		}
		setPos(oldCell.xInPixel, oldCell.yInPixel);
	}
};
