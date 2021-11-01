#pragma once
class Pawn : public AbstractFigure
{
public:
	bool firstMove = true;

	Pawn(const Square& square, const bool& color, const sf::Texture& texture) : AbstractFigure(square, color, texture) {
		sprite.setOrigin(18, 38);
	}

	void Move(const int& newX, const int& newY, bool& turn, sf::RenderWindow& window, std::vector<std::vector<Square>>& squares) override
	{
		if (turn == color && squares[x][y].x == squares[newX][newY].x && squares[newX][newY].isEmpty) {
			if (color == 0) { // if white
				if (firstMove) {
					if ((squares[x][y].y - squares[newX][newY].y == 2 || squares[x][y].y - squares[newX][newY].y == 1) && squares[x][y - 1].isEmpty) {
						firstMove = false;
						Move_(squares[x][y], squares[newX][newY], turn, window);
						return;
					}
				}
				else {
					if (squares[x][y].y - squares[newX][newY].y == 1) {
						Move_(squares[x][y], squares[newX][newY], turn, window);
						return;
					}
				}
			}
			else { // if black
				if (firstMove) {
					if ((squares[newX][newY].y - squares[x][y].y == 2 || squares[newX][newY].y - squares[x][y].y == 1) && squares[x][y + 1].isEmpty) {
						firstMove = false;
						Move_(squares[x][y], squares[newX][newY], turn, window);
						return;
					}
				}
				else {
					if (squares[newX][newY].y - squares[x][y].y == 1) {
						Move_(squares[x][y], squares[newX][newY], turn, window);
						return;
					}
				}
			}
		}
		setPos(squares[x][y].xInPixel, squares[x][y].yInPixel);
	}

	bool Capture(const int& newX, const int& newY, bool& turn, sf::RenderWindow& window, std::vector<std::vector<Square>>& squares) override
	{
		if (turn == color && !squares[newX][newY].isEmpty)
		{
			if (color == 0) { // if white
				if (squares[x][y].y - squares[newX][newY].y == 1 && abs(squares[x][y].x - squares[newX][newY].x) == 1) {
					return true;
				}
			}
			else {
				if (squares[newX][newY].y - squares[x][y].y == 1 && abs(squares[newX][newY].x - squares[x][y].x) == 1) {
					return true;
				}
			}
		}
		return false;
	}
};

class Castle : public AbstractFigure {
public:
	Castle(const Square& square, const bool& color, const sf::Texture& texture) : AbstractFigure(square, color, texture) {
		sprite.setOrigin(26, 38);
	}

	void Move(const int& newX, const int& newY, bool& turn, sf::RenderWindow& window, std::vector<std::vector<Square>>& squares) override
	{
		if (turn == color && squares[x][y].x == squares[newX][newY].x && squares[newX][newY].isEmpty) {
			if (color == 0) { // if white
				if (squares[x][y].y - squares[newX][newY].y == 1) {
					Move_(squares[x][y], squares[newX][newY], turn, window);
					return;
				}
			}
			else { // if black
				if (squares[newX][newY].y - y == 1) {
					Move_(squares[x][y], squares[newX][newY], turn, window);
					return;
				}
			}
		}
		setPos(squares[x][y].xInPixel, squares[x][y].yInPixel);
	}

	bool Capture(const int& newX, const int& newY, bool& turn, sf::RenderWindow& window, std::vector<std::vector<Square>>& squares) override { return false; }
};

class Knight : public AbstractFigure {
public:
	Knight(const Square& square, const bool& color, const sf::Texture& texture) : AbstractFigure(square, color, texture) {
		sprite.setOrigin(32, 40);
	}

	void Move(const int& newX, const int& newY, bool& turn, sf::RenderWindow& window, std::vector<std::vector<Square>>& squares) override
	{
		if (turn == color && x == squares[newX][newY].x && squares[newX][newY].isEmpty) {
			if (color == 0) { // if white
				if (y - squares[newX][newY].y == 1) {
					Move_(squares[x][y], squares[newX][newY], turn, window);
					return;
				}
			}
			else { // if black
				if (squares[newX][newY].y - y == 1) {
					Move_(squares[x][y], squares[newX][newY], turn, window);
					return;
				}
			}
		}
		setPos(squares[x][y].xInPixel, squares[x][y].yInPixel);
	}

	bool Capture(const int& newX, const int& newY, bool& turn, sf::RenderWindow& window, std::vector<std::vector<Square>>& squares) override { return false; }
};

class Bishop : public AbstractFigure {
public:
	Bishop(const Square& square, const bool& color, const sf::Texture& texture) : AbstractFigure(square, color, texture) {
		sprite.setOrigin(34, 40);
	}

	void Move(const int& newX, const int& newY, bool& turn, sf::RenderWindow& window, std::vector<std::vector<Square>>& squares) override {
		if (turn == color && x == squares[newX][newY].x && squares[newX][newY].isEmpty) {
			if (color == 0) { // if white
				if (y - squares[newX][newY].y == 1) {
					Move_(squares[x][y], squares[newX][newY], turn, window);
					return;
				}
			}

			else { // if black
				if (squares[newX][newY].y - y == 1) {
					Move_(squares[x][y], squares[newX][newY], turn, window);
					return;
				}
			}
		}
		setPos(squares[x][y].xInPixel, squares[x][y].yInPixel);
	}

	bool Capture(const int& newX, const int& newY, bool& turn, sf::RenderWindow& window, std::vector<std::vector<Square>>& squares) override { return false; }
};

class Queen : public AbstractFigure {
public:
	Queen(const Square& square, const bool& color, const sf::Texture& texture) : AbstractFigure(square, color, texture) {
		sprite.setOrigin(35, 40);
	}

	void Move(const int& newX, const int& newY, bool& turn, sf::RenderWindow& window, std::vector<std::vector<Square>>& squares) override {
		if (turn == color && x == squares[newX][newY].x && squares[newX][newY].isEmpty) {
			if (color == 0) { // if white
				if (y - squares[newX][newY].y == 1) {
					Move_(squares[x][y], squares[newX][newY], turn, window);
					return;
				}
			}
			else { // if black
				if (squares[newX][newY].y - squares[x][y].y == 1) {
					Move_(squares[x][y], squares[newX][newY], turn, window);
					return;
				}
			}
		}
		setPos(squares[x][y].xInPixel, squares[x][y].yInPixel);
	}

	bool Capture(const int& newX, const int& newY, bool& turn, sf::RenderWindow& window, std::vector<std::vector<Square>>& squares) override { return false; }
};

class King : public AbstractFigure {
public:
	King(const Square& square, const bool& color, const sf::Texture& texture) : AbstractFigure(square, color, texture) {
		sprite.setOrigin(35, 38);
	}

	void Move(const int& newX, const int& newY, bool& turn, sf::RenderWindow& window, std::vector<std::vector<Square>>& squares) override
	{
		if (turn == color && squares[x][y].x == squares[newX][newY].x && squares[newX][newY].isEmpty) {
			if (color == 0) { // if white
				if (y - squares[newX][newY].y == 1) {
					Move_(squares[x][y], squares[newX][newY], turn, window);
					return;
				}
			}
			else { // if black
				if (squares[newX][newY].y - y == 1) {
					Move_(squares[x][y], squares[newX][newY], turn, window);
					return;
				}
			}
		}
		setPos(squares[x][y].xInPixel, squares[x][y].yInPixel);
	}

	bool Capture(const int& newX, const int& newY, bool& turn, sf::RenderWindow& window, std::vector<std::vector<Square>>& squares) override { return false; }
};
