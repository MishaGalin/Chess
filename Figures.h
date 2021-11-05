#pragma once
class Pawn : public AbstractFigure
{
public:

	Pawn(const Square& square, const bool& color, const sf::Texture& texture) : AbstractFigure(square, color, texture) {
		sprite.setOrigin(18, 38);
		name = "Pawn";
	}

	bool ConditionOfMove(const int& newX, const int& newY, bool& turn, std::vector<std::vector<Square>>& squares) override {
		if (squares[newX][newY].isEmpty) {
			if (x == newX) {
				if (color == false) { // if white
					if (firstMove) {
						if ((y - newY == 2 && squares[x][y - 1].isEmpty) || y - newY == 1) {
							return true;
						}
					}
					else {
						if (y - newY == 1) {
							return true;
						}
					}
				}
				else if (color == true) { // if black
					if (firstMove) {
						if ((newY - y == 2 && squares[x][y + 1].isEmpty) || newY - y == 1) {
							return true;
						}
					}
					else {
						if (newY - y == 1) {
							return true;
						}
					}
				}
			}
		}
		return false;
	};

	void Move(const int& newX, const int& newY, bool& turn, sf::RenderWindow& window, std::vector<std::vector<Square>>& squares) override
	{
		if (ConditionOfMove(newX, newY, turn, squares)) {
			Move_(squares[x][y], squares[newX][newY], turn, window);
			if (firstMove) firstMove = false;
		}
		else setPos(squares[x][y].xInPixel, squares[x][y].yInPixel);
	}

	bool Capture(const int& newX, const int& newY, bool& turn, sf::RenderWindow& window, std::vector<std::vector<Square>>& squares) override
	{
		if (!squares[newX][newY].isEmpty) {
			if (color == 0) { // if white
				if (y - newY == 1 && abs(x - newX) == 1) {
					return true;
				}
			}
			else {
				if (newY - y == 1 && abs(newX - x) == 1) {
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
		name = "Castle";
	}

	bool ConditionOfMove(const int& newX, const int& newY, bool& turn, std::vector<std::vector<Square>>& squares) override {
		if (squares[newX][newY].isEmpty) {
			int dir1Y = y,
				dir2X = x,
				dir3Y = y,
				dir4X = x;
			bool dir1 = false, dir2 = false, dir3 = false, dir4 = false;

			if (newX == x && newY < y) dir1 = true;
			if (newX < x && newY == y) dir2 = true;
			if (newX == x && newY > y) dir3 = true;
			if (newX > x && newY == y) dir4 = true;

			for (int i = 1; i < 8; ++i)
			{
				if (dir1 && y - i >= 0 && y - i <= 7) {
					if (squares[x][y - i].isEmpty) dir1Y = y - i;
					else break;
				}
				else if (dir2 && x - i >= 0 && x - i <= 7) {
					if (squares[x - i][y].isEmpty) dir2X = x - i;
					else break;
				}
				else if (dir3 && y + i >= 0 && y + i <= 7) {
					if (squares[x][y + i].isEmpty) dir3Y = y + i;
					else break;
				}
				else if (dir4 && x + i >= 0 && x + i <= 7) {
					if (squares[x + i][y].isEmpty) dir4X = x + i;
					else break;
				}
			}
			if ((dir1 && newY >= dir1Y) ||
				(dir2 && newX >= dir2X) ||
				(dir3 && newY <= dir3Y) ||
				(dir4 && newX <= dir4X)) return true;
			else return false;
		}
		return false;
	}

	void Move(const int& newX, const int& newY, bool& turn, sf::RenderWindow& window, std::vector<std::vector<Square>>& squares) override
	{
		if (ConditionOfMove(newX, newY, turn, squares)) Move_(squares[x][y], squares[newX][newY], turn, window);
		else setPos(squares[x][y].xInPixel, squares[x][y].yInPixel);
	}

	bool Capture(const int& newX, const int& newY, bool& turn, sf::RenderWindow& window, std::vector<std::vector<Square>>& squares) override {
		if (!squares[newX][newY].isEmpty) {
			int dir1Y = y,
				dir2X = x,
				dir3Y = y,
				dir4X = x;
			bool dir1 = false, dir2 = false, dir3 = false, dir4 = false;

			if (newX == x && newY < y) dir1 = true;
			if (newX < x && newY == y) dir2 = true;
			if (newX == x && newY > y) dir3 = true;
			if (newX > x && newY == y) dir4 = true;

			for (int i = 1; i < 8; ++i)
			{
				if (dir1 && y - i >= 0 && y - i <= 7) {
					dir1Y = y - i;
					if (squares[x][dir1Y].isEmpty) continue;
					else break;
				}
				else if (dir2 && x - i >= 0 && x - i <= 7) {
					dir2X = x - i;
					if (squares[dir2X][y].isEmpty) continue;
					else break;
				}
				else if (dir3 && y + i >= 0 && y + i <= 7) {
					dir3Y = y + i;
					if (squares[x][dir3Y].isEmpty) continue;
					else break;
				}
				else if (dir4 && x + i >= 0 && x + i <= 7) {
					dir4X = x + i;
					if (squares[dir4X][y].isEmpty) continue;
					else break;
				}
				else break;
			}
			if ((dir1 && newY == dir1Y) ||
				(dir2 && newX == dir2X) ||
				(dir3 && newY == dir3Y) ||
				(dir4 && newX == dir4X)) return true;
		}
		return false;
	}
};

class Knight : public AbstractFigure {
public:
	Knight(const Square& square, const bool& color, const sf::Texture& texture) : AbstractFigure(square, color, texture) {
		sprite.setOrigin(32, 40);
		name = "Knight";
	}

	bool ConditionOfMove(const int& newX, const int& newY, bool& turn, std::vector<std::vector<Square>>& squares) override {
		if (squares[newX][newY].isEmpty && abs((x - newX) * (y - newY)) == 2) return true;
		else return false;
	}

	void Move(const int& newX, const int& newY, bool& turn, sf::RenderWindow& window, std::vector<std::vector<Square>>& squares) override
	{
		if (ConditionOfMove(newX, newY, turn, squares)) Move_(squares[x][y], squares[newX][newY], turn, window);
		else setPos(squares[x][y].xInPixel, squares[x][y].yInPixel);
	}

	bool Capture(const int& newX, const int& newY, bool& turn, sf::RenderWindow& window, std::vector<std::vector<Square>>& squares) override {
		if (!squares[newX][newY].isEmpty && abs((x - newX) * (y - newY)) == 2) return true;
		return false;
	}
};

class Bishop : public AbstractFigure {
public:
	Bishop(const Square& square, const bool& color, const sf::Texture& texture) : AbstractFigure(square, color, texture) {
		sprite.setOrigin(34, 40);
		name = "Bishop";
	}

	bool ConditionOfMove(const int& newX, const int& newY, bool& turn, std::vector<std::vector<Square>>& squares) override {
		if (squares[newX][newY].isEmpty && abs(newX - x) == abs(newY - y)) {
			int dir1X = x, dir1Y = y,
				dir2X = x, dir2Y = y,
				dir3X = x, dir3Y = y,
				dir4X = x, dir4Y = y;
			bool dir1 = false, dir2 = false, dir3 = false, dir4 = false;

			if (newX > x && newY < y) dir1 = true;
			if (newX < x && newY < y) dir2 = true;
			if (newX < x && newY > y) dir3 = true;
			if (newX > x && newY > y) dir4 = true;

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
			if ((dir1 && newX <= dir1X && newY >= dir1Y) ||
				(dir2 && newX >= dir2X && newY >= dir2Y) ||
				(dir3 && newX >= dir3X && newY <= dir3Y) ||
				(dir4 && newX <= dir4X && newY <= dir4Y)) return true;
		}
		return false;
	}

	void Move(const int& newX, const int& newY, bool& turn, sf::RenderWindow& window, std::vector<std::vector<Square>>& squares) override {
		if (ConditionOfMove(newX, newY, turn, squares)) Move_(squares[x][y], squares[newX][newY], turn, window);
		else setPos(squares[x][y].xInPixel, squares[x][y].yInPixel);
	}

	bool Capture(const int& newX, const int& newY, bool& turn, sf::RenderWindow& window, std::vector<std::vector<Square>>& squares) override {
		if (!squares[newX][newY].isEmpty && abs(newX - x) == abs(newY - y)) {
			int dir1X = x, dir1Y = y,
				dir2X = x, dir2Y = y,
				dir3X = x, dir3Y = y,
				dir4X = x, dir4Y = y;
			bool dir1 = false, dir2 = false, dir3 = false, dir4 = false;

			if (newX > x && newY < y) dir1 = true;
			else if (newX < x && newY < y) dir2 = true;
			else if (newX < x && newY > y) dir3 = true;
			else if (newX > x && newY > y) dir4 = true;

			for (int i = 1; i < 8; ++i)
			{
				if (dir1 && x + i >= 0 && x + i <= 7 && y - i >= 0 && y - i <= 7) {
					dir1X = x + i;
					dir1Y = y - i;
					if (squares[x + i][y - i].isEmpty) continue;
					else break;
				}
				else if (dir2 && x - i >= 0 && x - i <= 7 && y - i >= 0 && y - i <= 7) {
					dir2X = x - i;
					dir2Y = y - i;
					if (squares[x - i][y - i].isEmpty) continue;
					else break;
				}
				else if (dir3 && x - i >= 0 && x - i <= 7 && y + i >= 0 && y + i <= 7) {
					dir3X = x - i;
					dir3Y = y + i;
					if (squares[x - i][y + i].isEmpty) continue;
					else break;
				}
				else if (dir4 && x + i >= 0 && x + i <= 7 && y + i >= 0 && y + i <= 7) {
					dir4X = x + i;
					dir4Y = y + i;
					if (squares[x + i][y + i].isEmpty) continue;
					else break;
				}
			}
			if ((dir1 && newX == dir1X && newY == dir1Y) ||
				(dir2 && newX == dir2X && newY == dir2Y) ||
				(dir3 && newX == dir3X && newY == dir3Y) ||
				(dir4 && newX == dir4X && newY == dir4Y)) return true;
		}
		return false;
	}
};

class Queen : public AbstractFigure {
public:
	Queen(const Square& square, const bool& color, const sf::Texture& texture) : AbstractFigure(square, color, texture) {
		sprite.setOrigin(35, 40);
		name = "Queen";
	}

	bool ConditionOfMove(const int& newX, const int& newY, bool& turn, std::vector<std::vector<Square>>& squares) override {
		if (squares[newX][newY].isEmpty) {
			int dir1X = x, 						   // 1 - вправо
				dir2X = x, dir2Y = y,			   // 2 - по диагонали вправо-вверх
				dir3Y = y,						   // 3 - вверх
				dir4X = x, dir4Y = y,			   // и т.д. против часовой стрелки
				dir5X = x,						   //
				dir6X = x, dir6Y = y,			   //
				dir7Y = y,						   //
				dir8X = x, dir8Y = y;			   //
			bool dir1 = false, dir2 = false, dir3 = false, dir4 = false,
				dir5 = false, dir6 = false, dir7 = false, dir8 = false;

			if (abs(newX - x) == abs(newY - y)) {
				if (newX > x && newY < y)  dir2 = true;
				if (newX < x && newY < y)  dir4 = true;
				if (newX < x && newY > y)  dir6 = true;
				if (newX > x && newY > y)  dir8 = true;
			}

			if (newX > x && newY == y) dir1 = true;
			if (newX == x && newY < y) dir3 = true;
			if (newX < x && newY == y) dir5 = true;
			if (newX == x && newY > y) dir7 = true;

			for (int i = 1; i < 8; ++i)
			{
				if (dir1 && x + i >= 0 && x + i <= 7) {
					if (squares[x + i][y].isEmpty) {
						dir1X = x + i;
						continue;
					}
					else break;
				}
				else if (dir2 && x + i >= 0 && x + i <= 7 && y - i >= 0 && y - i <= 7) {
					if (squares[x + i][y - i].isEmpty) {
						dir2X = x + i;
						dir2Y = y - i;
						continue;
					}
					else break;
				}
				else if (dir3 && y - i >= 0 && y - i <= 7) {
					if (squares[x][y - i].isEmpty) {
						dir3Y = y - i;
						continue;
					}
					else break;
				}
				else if (dir4 && x - i >= 0 && x - i <= 7 && y - i >= 0 && y - i <= 7) {
					if (squares[x - i][y - i].isEmpty) {
						dir4X = x - i;
						dir4Y = y - i;
						continue;
					}
					else break;
				}
				else if (dir5 && x - i >= 0 && x - i <= 7) {
					if (squares[x - i][y].isEmpty) {
						dir5X = x - i;
						continue;
					}
					else break;
				}
				else if (dir6 && x - i >= 0 && x - i <= 7 && y + i >= 0 && y + i <= 7) {
					if (squares[x - i][y + i].isEmpty) {
						dir6X = x - i;
						dir6Y = y + i;
						continue;
					}
					else break;
				}
				else if (dir7 && y + i >= 0 && y + i <= 7) {
					if (squares[x][y + i].isEmpty) {
						dir7Y = y + i;
						continue;
					}
					else break;
				}
				else if (dir8 && x + i >= 0 && x + i <= 7 && y + i >= 0 && y + i <= 7) {
					if (squares[x + i][y + i].isEmpty) {
						dir8X = x + i;
						dir8Y = y + i;
						continue;
					}
					else break;
				}
			}

			if ((dir1 && newX <= dir1X) ||
				(dir2 && newX <= dir2X && newY >= dir2Y) ||
				(dir3 && newY >= dir3Y) ||
				(dir4 && newX >= dir4X && newY >= dir4Y) ||
				(dir5 && newX >= dir5X) ||
				(dir6 && newX >= dir6X && newY <= dir6Y) ||
				(dir7 && newY <= dir7Y) ||
				(dir8 && newX <= dir8X && newY <= dir8Y)) return true;
		}
		return false;
	}

	void Move(const int& newX, const int& newY, bool& turn, sf::RenderWindow& window, std::vector<std::vector<Square>>& squares) override {
		if (ConditionOfMove(newX, newY, turn, squares)) Move_(squares[x][y], squares[newX][newY], turn, window);
		else setPos(squares[x][y].xInPixel, squares[x][y].yInPixel);
	}

	bool Capture(const int& newX, const int& newY, bool& turn, sf::RenderWindow& window, std::vector<std::vector<Square>>& squares) override {
		if (!squares[newX][newY].isEmpty) {
			int dir1X = x, 						   // 1 - вправо
				dir2X = x, dir2Y = y,			   // 2 - по диагонали вправо-вверх
				dir3Y = y,						   // 3 - вверх
				dir4X = x, dir4Y = y,			   // и т.д. против часовой стрелки
				dir5X = x,						   //
				dir6X = x, dir6Y = y,			   //
				dir7Y = y,						   //
				dir8X = x, dir8Y = y;			   //
			bool dir1 = false, dir2 = false, dir3 = false, dir4 = false,
				dir5 = false, dir6 = false, dir7 = false, dir8 = false;

			if (abs(newX - x) == abs(newY - y)) { // диагонали
				if (newX > x && newY < y)  dir2 = true;
				if (newX < x && newY < y)  dir4 = true;
				if (newX < x && newY > y)  dir6 = true;
				if (newX > x && newY > y)  dir8 = true;
			}

			if (newX > x && newY == y) dir1 = true;
			if (newX == x && newY < y) dir3 = true;
			if (newX < x && newY == y) dir5 = true;
			if (newX == x && newY > y) dir7 = true;

			for (int i = 1; i < 8; ++i)
			{
				if (dir1 && x + i >= 0 && x + i <= 7) {
					dir1X = x + i;
					if (squares[x + i][y].isEmpty) continue;
					else break;
				}
				else if (dir2 && x + i >= 0 && x + i <= 7 && y - i >= 0 && y - i <= 7) {
					dir2X = x + i;
					dir2Y = y - i;
					if (squares[x + i][y - i].isEmpty) continue;
					else break;
				}
				else if (dir3 && y - i >= 0 && y - i <= 7) {
					dir3Y = y - i;
					if (squares[x][y - i].isEmpty) continue;
					else break;
				}
				else if (dir4 && x - i >= 0 && x - i <= 7 && y - i >= 0 && y - i <= 7) {
					dir4X = x - i;
					dir4Y = y - i;
					if (squares[x - i][y - i].isEmpty) continue;
					else break;
				}
				else if (dir5 && x - i >= 0 && x - i <= 7) {
					dir5X = x - i;
					if (squares[x - i][y].isEmpty) continue;
					else break;
				}
				else if (dir6 && x - i >= 0 && x - i <= 7 && y + i >= 0 && y + i <= 7) {
					dir6X = x - i;
					dir6Y = y + i;
					if (squares[x - i][y + i].isEmpty) continue;
					else break;
				}
				else if (dir7 && y + i >= 0 && y + i <= 7) {
					dir7Y = y + i;
					if (squares[x][y + i].isEmpty) continue;
					else break;
				}
				else if (dir8 && x + i >= 0 && x + i <= 7 && y + i >= 0 && y + i <= 7) {
					dir8X = x + i;
					dir8Y = y + i;
					if (squares[x + i][y + i].isEmpty) continue;
					else break;
				}
				else break;
			}

			if ((dir1 && newX == dir1X) ||
				(dir2 && newX == dir2X && newY == dir2Y) ||
				(dir3 && newY == dir3Y) ||
				(dir4 && newX == dir4X && newY == dir4Y) ||
				(dir5 && newX == dir5X) ||
				(dir6 && newX == dir6X && newY == dir6Y) ||
				(dir7 && newY == dir7Y) ||
				(dir8 && newX == dir8X && newY == dir8Y)) return true;
		}
		return false;
	}
};

class King : public AbstractFigure {
public:
	King(const Square& square, const bool& color, const sf::Texture& texture) : AbstractFigure(square, color, texture) {
		sprite.setOrigin(35, 38);
		name = "King";
	}

	bool ConditionOfMove(const int& newX, const int& newY, bool& turn, std::vector<std::vector<Square>>& squares) override {
		if (squares[newX][newY].isEmpty && abs(newX - x) <= 1 && abs(newY - y) <= 1) return true;
		return false;
	}

	void Move(const int& newX, const int& newY, bool& turn, sf::RenderWindow& window, std::vector<std::vector<Square>>& squares) override
	{
		if (ConditionOfMove(newX, newY, turn, squares)) Move_(squares[x][y], squares[newX][newY], turn, window);
		else setPos(squares[x][y].xInPixel, squares[x][y].yInPixel);
	}

	bool Capture(const int& newX, const int& newY, bool& turn, sf::RenderWindow& window, std::vector<std::vector<Square>>& squares) override {
		if (!squares[newX][newY].isEmpty && abs(newX - x) <= 1 && abs(newY - y) <= 1) return true;
		return false;
	}
};
