#pragma once
class Pawn : public AbstractFigure
{
public:
	bool firstMove = true;

	Pawn(const Square& square, const bool& color, const sf::Texture& texture) : AbstractFigure(square, color, texture) {
		sprite.setOrigin(18, 38);
	}

	void Move(Square& oldSquare, Square& newSquare, bool& turn, sf::RenderWindow& window) override
	{
		if (turn == color && oldSquare.x == newSquare.x && newSquare.isEmpty) {
			if (color == 0) { // if white
				if (firstMove) {
					if (oldSquare.y - newSquare.y == 2 || oldSquare.y - newSquare.y == 1) {
						Move_(oldSquare, newSquare, turn, window);
						return;
					}
				}
				else {
					if (oldSquare.y - newSquare.y == 1) {
						Move_(oldSquare, newSquare, turn, window);
						return;
					}
				}
			}
			else { // if black
				if (firstMove) {
					if (newSquare.y - oldSquare.y == 2 || newSquare.y - oldSquare.y == 1) {
						Move_(oldSquare, newSquare, turn, window);
						return;
					}
				}
				else {
					if (newSquare.y - oldSquare.y == 1) {
						Move_(oldSquare, newSquare, turn, window);
						return;
					}
				}
			}
		}
		setPos(oldSquare.xInPixel, oldSquare.yInPixel);
	}
};

class Castle : public AbstractFigure {
public:
	Castle(const Square& square, const bool& color, const sf::Texture& texture) : AbstractFigure(square, color, texture) {
		sprite.setOrigin(26, 38);
	}

	void Move(Square& oldSquare, Square& newSquare, bool& turn, sf::RenderWindow& window) override
	{
		if (turn == color && oldSquare.x == newSquare.x && newSquare.isEmpty) {
			if (color == 0) { // if white
				if (oldSquare.y - newSquare.y == 1) {
					Move_(oldSquare, newSquare, turn, window);
					return;
				}
			}
			else { // if black
				if (newSquare.y - oldSquare.y == 1) {
					Move_(oldSquare, newSquare, turn, window);
					return;
				}
			}
		}
		setPos(oldSquare.xInPixel, oldSquare.yInPixel);
	}
};

class Knight : public AbstractFigure {
public:
	Knight(const Square& square, const bool& color, const sf::Texture& texture) : AbstractFigure(square, color, texture) {
		sprite.setOrigin(32, 40);
	}

	void Move(Square& oldSquare, Square& newSquare, bool& turn, sf::RenderWindow& window) override
	{
		if (turn == color && oldSquare.x == newSquare.x && newSquare.isEmpty) {
			if (color == 0) { // if white
				if (oldSquare.y - newSquare.y == 1) {
					Move_(oldSquare, newSquare, turn, window);
					return;
				}
			}
			else { // if black
				if (newSquare.y - oldSquare.y == 1) {
					Move_(oldSquare, newSquare, turn, window);
					return;
				}
			}
		}
		setPos(oldSquare.xInPixel, oldSquare.yInPixel);
	}
};

class Bishop : public AbstractFigure {
public:
	Bishop(const Square& square, const bool& color, const sf::Texture& texture) : AbstractFigure(square, color, texture) {
		sprite.setOrigin(34, 40);
	}

	void Move(Square& oldSquare, Square& newSquare, bool& turn, sf::RenderWindow& window) override
	{
		if (turn == color && oldSquare.x == newSquare.x && newSquare.isEmpty) {
			if (color == 0) { // if white
				if (oldSquare.y - newSquare.y == 1) {
					Move_(oldSquare, newSquare, turn, window);
					return;
				}
			}

			else { // if black
				if (newSquare.y - oldSquare.y == 1) {
					Move_(oldSquare, newSquare, turn, window);
					return;
				}
			}
		}
		setPos(oldSquare.xInPixel, oldSquare.yInPixel);
	}
};

class Queen : public AbstractFigure {
public:
	Queen(const Square& square, const bool& color, const sf::Texture& texture) : AbstractFigure(square, color, texture) {
		sprite.setOrigin(35, 40);
	}

	void Move(Square& oldCell, Square& newSquare, bool& turn, sf::RenderWindow& window) override
	{
		if (turn == color && oldCell.x == newSquare.x && newSquare.isEmpty) {
			if (color == 0) { // if white
				if (oldCell.y - newSquare.y == 1) {
					Move_(oldCell, newSquare, turn, window);
					return;
				}
			}
			else { // if black
				if (newSquare.y - oldCell.y == 1) {
					Move_(oldCell, newSquare, turn, window);
					return;
				}
			}
		}
		setPos(oldCell.xInPixel, oldCell.yInPixel);
	}
};

class King : public AbstractFigure {
public:
	King(const Square& square, const bool& color, const sf::Texture& texture) : AbstractFigure(square, color, texture) {
		sprite.setOrigin(35, 38);
	}

	void Move(Square& oldSquare, Square& newSquare, bool& turn, sf::RenderWindow& window) override
	{
		if (turn == color && oldSquare.x == newSquare.x && newSquare.isEmpty) {
			if (color == 0) { // if white
				if (oldSquare.y - newSquare.y == 1) {
					Move_(oldSquare, newSquare, turn, window);
					return;
				}
			}
			else { // if black
				if (newSquare.y - oldSquare.y == 1) {
					Move_(oldSquare, newSquare, turn, window);
					return;
				}
			}
		}
		setPos(oldSquare.xInPixel, oldSquare.yInPixel);
	}
};
