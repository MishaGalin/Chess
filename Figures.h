#pragma once
class Pawn : public AbstractFigure
{
public:
	bool firstMove = true;

	Pawn(const Square& square, const bool& color, const sf::Texture& texture) : AbstractFigure(square, color, texture) {
		sprite.setOrigin(18, 38);
	}

	bool ConditionMove(const int& newX, const int& newY, bool& turn, std::vector<std::vector<Square>>& squares) override {
		if (squares[x][y].x == squares[newX][newY].x) {
			if (color == false) { // if white
				if (firstMove) {
					if ((squares[x][y].y - squares[newX][newY].y == 2 && squares[x][y - 1].isEmpty) || squares[x][y].y - squares[newX][newY].y == 1) {
						return true;
					}
				}
				else {
					if (squares[x][y].y - squares[newX][newY].y == 1) {
						return true;
					}
				}
			}
			else if (color == true) { // if black
				if (firstMove) {
					if ((squares[newX][newY].y - squares[x][y].y == 2 && squares[x][y + 1].isEmpty) || squares[newX][newY].y - squares[x][y].y == 1) {
						return true;
					}
				}
				else {
					if (squares[newX][newY].y - squares[x][y].y == 1) {
						return true;
					}
				}
			}
		}
		return false;
	};

	void Move(const int& newX, const int& newY, bool& turn, sf::RenderWindow& window, std::vector<std::vector<Square>>& squares) override
	{
		if (ConditionMove(newX, newY, turn, squares)) {
			Move_(squares[x][y], squares[newX][newY], turn, window);
			if (firstMove) firstMove = false;
		}
		else setPos(squares[x][y].xInPixel, squares[x][y].yInPixel);
	}

	bool Capture(const int& newX, const int& newY, bool& turn, sf::RenderWindow& window, std::vector<std::vector<Square>>& squares) override
	{
		if (!squares[newX][newY].isEmpty)
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

	bool ConditionMove(const int& newX, const int& newY, bool& turn, std::vector<std::vector<Square>>& squares) override {
		if (abs(squares[newX][newY].x - squares[x][y].x) == abs(squares[newX][newY].y - squares[x][y].y)) {
			int dir1X = x, dir1Y = y,
				dir2X = x, dir2Y = y,
				dir3X = x, dir3Y = y,
				dir4X = x, dir4Y = y;
			bool dir1 = true, dir2 = true, dir3 = true, dir4 = true;

			if (squares[newX][newY].x > squares[x][y].x) {
				dir2 = false;
				dir3 = false;
				squares[newX][newY].y > squares[x][y].y ? dir1 = false : dir4 = false;
			}
			else {
				dir1 = false;
				dir4 = false;
				squares[newX][newY].y < squares[x][y].y ? dir3 = false : dir2 = false;
			}

			for (int i = 1; i < 8; ++i)
			{
				if (dir1 && x + i >= 0 && x + i <= 7 && y - i >= 0 && y - i <= 7) {
					if (squares[x + i][y - i].isEmpty) {
						dir1X = x + i;
						dir1Y = y - i;
					}
					else break;
				}
				else if (dir2 && x - i >= 0 && x - i <= 7 && y - i >= 0 && y - i <= 7) {
					if (squares[x - i][y - i].isEmpty) {
						dir2X = x - i;
						dir2Y = y - i;
					}
					else break;
				}
				else if (dir3 && x - i >= 0 && x - i <= 7 && y + i >= 0 && y + i <= 7) {
					if (squares[x - i][y + i].isEmpty) {
						dir3X = x - i;
						dir3Y = y + i;
					}
					else break;
				}
				else if (dir4 && x + i >= 0 && x + i <= 7 && y + i >= 0 && y + i <= 7) {
					if (squares[x + i][y + i].isEmpty) {
						dir4X = x + i;
						dir4Y = y + i;
					}
					else break;
				}
			}
			if ((dir1 && squares[newX][newY].x <= dir1X && squares[newX][newY].y >= dir1Y) ||
				(dir2 && squares[newX][newY].x >= dir2X && squares[newX][newY].y >= dir2Y) ||
				(dir3 && squares[newX][newY].x >= dir3X && squares[newX][newY].y <= dir3Y) ||
				(dir4 && squares[newX][newY].x <= dir4X && squares[newX][newY].y <= dir4Y)) return true;
		}
		return false;
	}

	void Move(const int& newX, const int& newY, bool& turn, sf::RenderWindow& window, std::vector<std::vector<Square>>& squares) override
	{
		if (ConditionMove(newX, newY, turn, squares)) Move_(squares[x][y], squares[newX][newY], turn, window);
		else setPos(squares[x][y].xInPixel, squares[x][y].yInPixel);
	}

	bool Capture(const int& newX, const int& newY, bool& turn, sf::RenderWindow& window, std::vector<std::vector<Square>>& squares) override {
		if (!squares[newX][newY].isEmpty && abs(squares[newX][newY].x - squares[x][y].x) == abs(squares[newX][newY].y - squares[x][y].y) && squares[newX][newY].x - squares[x][y].x != 0) return true;
		return false;
	}
};

class Knight : public AbstractFigure {
public:
	Knight(const Square& square, const bool& color, const sf::Texture& texture) : AbstractFigure(square, color, texture) {
		sprite.setOrigin(32, 40);
	}

	bool ConditionMove(const int& newX, const int& newY, bool& turn, std::vector<std::vector<Square>>& squares) override {
		if (squares[newX][newY].isEmpty && abs((squares[x][y].x - squares[newX][newY].x) * (squares[x][y].y - squares[newX][newY].y)) == 2) return true;
		else return false;
	}

	void Move(const int& newX, const int& newY, bool& turn, sf::RenderWindow& window, std::vector<std::vector<Square>>& squares) override
	{
		if (ConditionMove(newX, newY, turn, squares)) Move_(squares[x][y], squares[newX][newY], turn, window);
		else setPos(squares[x][y].xInPixel, squares[x][y].yInPixel);
	}

	bool Capture(const int& newX, const int& newY, bool& turn, sf::RenderWindow& window, std::vector<std::vector<Square>>& squares) override {
		if (!squares[newX][newY].isEmpty && abs((squares[x][y].x - squares[newX][newY].x) * (squares[x][y].y - squares[newX][newY].y)) == 2) {
			return true;
		}
		return false;
	}
};

class Bishop : public AbstractFigure {
public:
	Bishop(const Square& square, const bool& color, const sf::Texture& texture) : AbstractFigure(square, color, texture) {
		sprite.setOrigin(34, 40);
	}

	bool ConditionMove(const int& newX, const int& newY, bool& turn, std::vector<std::vector<Square>>& squares) override {
		return false;
	}

	void Move(const int& newX, const int& newY, bool& turn, sf::RenderWindow& window, std::vector<std::vector<Square>>& squares) override {
		if (x == squares[newX][newY].x && squares[newX][newY].isEmpty) {
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

	bool ConditionMove(const int& newX, const int& newY, bool& turn, std::vector<std::vector<Square>>& squares) override {
		return false;
	}

	void Move(const int& newX, const int& newY, bool& turn, sf::RenderWindow& window, std::vector<std::vector<Square>>& squares) override {
		if (x == squares[newX][newY].x && squares[newX][newY].isEmpty) {
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

	bool ConditionMove(const int& newX, const int& newY, bool& turn, std::vector<std::vector<Square>>& squares) override {
		return false;
	}

	void Move(const int& newX, const int& newY, bool& turn, sf::RenderWindow& window, std::vector<std::vector<Square>>& squares) override
	{
		if (squares[x][y].x == squares[newX][newY].x && squares[newX][newY].isEmpty) {
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
