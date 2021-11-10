#pragma once
using namespace sf; // SFML namespace
using namespace std;

extern vector<vector<Square>> squares;
extern bool turn;

class Pawn : public AbstractFigure {
public:
	Pawn(const Square& square, const bool& color, const Texture& texture) : AbstractFigure(square, color, texture) {
		sprite.setOrigin(18, 38);
		name = "Pawn";
	}

	bool ConditionOfMove(const Square& square) override {
		return (square.isEmpty && x == square.x && color == turn
			&& ((pow(-1, color) * (y - square.y) == 2 && squares[x][y - (pow(-1, color) * 1)].isEmpty && firstMove) || pow(-1, color) * (y - square.y) == 1));
	};

	void Move(Square& square) override {
		if (ConditionOfMove(square)) Move_(squares[x][y], square);
		else setPos(squares[x][y].xInPixel, squares[x][y].yInPixel);
	}

	bool ConditionOfCapture(const Square& square) override {
		return (!square.isEmpty && pow(-1, color) * (y - square.y) == 1 && abs(x - square.x) == 1 && square.color != turn && color == turn);
	}
};

class Castle : public AbstractFigure {
public:
	Castle(const Square& square, const bool& color, const Texture& texture) : AbstractFigure(square, color, texture) {
		sprite.setOrigin(26, 38);
		name = "Castle";
	}

	bool ConditionOfMove(const Square& square) override {
		if (square.isEmpty && color == turn) {
			int dir1Y = y,
				dir2X = x,
				dir3Y = y,
				dir4X = x;
			bool dir1 = false, dir2 = false, dir3 = false, dir4 = false;

			if (square.x == x && square.y < y) dir1 = true;
			else if (square.x < x && square.y == y) dir2 = true;
			else if (square.x == x && square.y > y) dir3 = true;
			else if (square.x > x && square.y == y) dir4 = true;

			for (int i = 1; i < 8; ++i)
			{
				if (dir1 && y - i >= 0 && y - i <= 7) {
					if (squares[x][y - i].isEmpty) dir1Y = y - i; else break;
				}
				else if (dir2 && x - i >= 0 && x - i <= 7) {
					if (squares[x - i][y].isEmpty) dir2X = x - i; else break;
				}
				else if (dir3 && y + i >= 0 && y + i <= 7) {
					if (squares[x][y + i].isEmpty) dir3Y = y + i; else break;
				}
				else if (dir4 && x + i >= 0 && x + i <= 7) {
					if (squares[x + i][y].isEmpty) dir4X = x + i; else break;
				}
			}
			return ((dir1 && square.y >= dir1Y) ||
				(dir2 && square.x >= dir2X) ||
				(dir3 && square.y <= dir3Y) ||
				(dir4 && square.x <= dir4X));
		}
		return false;
	}

	void Move(Square& square) override {
		if (ConditionOfMove(square)) Move_(squares[x][y], square);
		else setPos(squares[x][y].xInPixel, squares[x][y].yInPixel);
	}

	bool ConditionOfCapture(const Square& square) override {
		if (!square.isEmpty && square.color != turn && color == turn) {
			int dir1Y = y,
				dir2X = x,
				dir3Y = y,
				dir4X = x;
			bool dir1 = false, dir2 = false, dir3 = false, dir4 = false;

			if (square.x == x && square.y < y) dir1 = true;
			else if (square.x < x && square.y == y) dir2 = true;
			else if (square.x == x && square.y > y) dir3 = true;
			else if (square.x > x && square.y == y) dir4 = true;

			for (int i = 1; i < 8; ++i)
			{
				if (dir1 && y - i >= 0 && y - i <= 7) {
					dir1Y = y - i;
					if (squares[x][dir1Y].isEmpty) continue; else break;
				}
				else if (dir2 && x - i >= 0 && x - i <= 7) {
					dir2X = x - i;
					if (squares[dir2X][y].isEmpty) continue; else break;
				}
				else if (dir3 && y + i >= 0 && y + i <= 7) {
					dir3Y = y + i;
					if (squares[x][dir3Y].isEmpty) continue; else break;
				}
				else if (dir4 && x + i >= 0 && x + i <= 7) {
					dir4X = x + i;
					if (squares[dir4X][y].isEmpty) continue; else break;
				}
			}
			return ((dir1 && square.y == dir1Y) ||
				(dir2 && square.x == dir2X) ||
				(dir3 && square.y == dir3Y) ||
				(dir4 && square.x == dir4X));
		}
		return false;
	}
};

class Knight : public AbstractFigure {
public:
	Knight(const Square& square, const bool& color, const Texture& texture) : AbstractFigure(square, color, texture) {
		sprite.setOrigin(32, 40);
		name = "Knight";
	}

	bool ConditionOfMove(const Square& square) override {
		return (square.isEmpty && abs((x - square.x) * (y - square.y)) == 2 && color == turn);
	}

	void Move(Square& square) override {
		if (ConditionOfMove(square)) Move_(squares[x][y], square);
		else setPos(squares[x][y].xInPixel, squares[x][y].yInPixel);
	}

	bool ConditionOfCapture(const Square& square) override {
		return (!square.isEmpty && abs((x - square.x) * (y - square.y)) == 2 && square.color != turn && color == turn);
	}
};

class Bishop : public AbstractFigure {
public:
	Bishop(const Square& square, const bool& color, const Texture& texture) : AbstractFigure(square, color, texture) {
		sprite.setOrigin(34, 40);
		name = "Bishop";
	}

	bool ConditionOfMove(const Square& square) override {
		if (square.isEmpty && abs(square.x - x) == abs(square.y - y) && color == turn) {
			int dir1X = x, dir1Y = y,
				dir2X = x, dir2Y = y,
				dir3X = x, dir3Y = y,
				dir4X = x, dir4Y = y;
			bool dir1 = false, dir2 = false, dir3 = false, dir4 = false;

			if (square.x > x && square.y < y) dir1 = true;
			else if (square.x < x && square.y < y) dir2 = true;
			else if (square.x < x && square.y > y) dir3 = true;
			else if (square.x > x && square.y > y) dir4 = true;

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

			return ((dir1 && square.x <= dir1X && square.y >= dir1Y) ||
				(dir2 && square.x >= dir2X && square.y >= dir2Y) ||
				(dir3 && square.x >= dir3X && square.y <= dir3Y) ||
				(dir4 && square.x <= dir4X && square.y <= dir4Y));
		}
		return false;
	}

	void Move(Square& square) override {
		if (ConditionOfMove(square)) Move_(squares[x][y], square);
		else setPos(squares[x][y].xInPixel, squares[x][y].yInPixel);
	}

	bool ConditionOfCapture(const Square& square) override {
		if (!square.isEmpty && abs(square.x - x) == abs(square.y - y) && square.color != turn && color == turn) {
			int dir1X = x, dir1Y = y,
				dir2X = x, dir2Y = y,
				dir3X = x, dir3Y = y,
				dir4X = x, dir4Y = y;
			bool dir1 = false, dir2 = false, dir3 = false, dir4 = false;

			if (square.x > x && square.y < y) dir1 = true;
			else if (square.x < x && square.y < y) dir2 = true;
			else if (square.x < x && square.y > y) dir3 = true;
			else if (square.x > x && square.y > y) dir4 = true;

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
			return ((dir1 && square.x == dir1X && square.y == dir1Y) ||
				(dir2 && square.x == dir2X && square.y == dir2Y) ||
				(dir3 && square.x == dir3X && square.y == dir3Y) ||
				(dir4 && square.x == dir4X && square.y == dir4Y));
		}
		return false;
	}
};

class Queen : public AbstractFigure {
public:
	Queen(const Square& square, const bool& color, const Texture& texture) : AbstractFigure(square, color, texture) {
		sprite.setOrigin(35, 40);
		name = "Queen";
	}

	bool ConditionOfMove(const Square& square) override {
		if (square.isEmpty && color == turn) {
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

			if (abs(square.x - x) == abs(square.y - y)) { // диагонали
				if (square.x > x && square.y < y)  dir2 = true;
				else if (square.x < x && square.y < y)  dir4 = true;
				else if (square.x < x && square.y > y)  dir6 = true;
				else if (square.x > x && square.y > y)  dir8 = true;
			}
			else { // горизонтали и вертикали
				if (square.x > x && square.y == y) dir1 = true;
				else if (square.x == x && square.y < y) dir3 = true;
				else if (square.x < x && square.y == y) dir5 = true;
				else if (square.x == x && square.y > y) dir7 = true;
			}

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

			return ((dir1 && square.x <= dir1X) ||
				(dir2 && square.x <= dir2X && square.y >= dir2Y) ||
				(dir3 && square.y >= dir3Y) ||
				(dir4 && square.x >= dir4X && square.y >= dir4Y) ||
				(dir5 && square.x >= dir5X) ||
				(dir6 && square.x >= dir6X && square.y <= dir6Y) ||
				(dir7 && square.y <= dir7Y) ||
				(dir8 && square.x <= dir8X && square.y <= dir8Y));
		}
		return false;
	}

	void Move(Square& square) override {
		if (ConditionOfMove(square)) Move_(squares[x][y], square);
		else setPos(squares[x][y].xInPixel, squares[x][y].yInPixel);
	}

	bool ConditionOfCapture(const Square& square) override {
		if (!square.isEmpty && square.color != turn && color == turn) {
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

			if (abs(square.x - x) == abs(square.y - y)) { // диагонали
				if (square.x > x && square.y < y)  dir2 = true;
				else if (square.x < x && square.y < y)  dir4 = true;
				else if (square.x < x && square.y > y)  dir6 = true;
				else if (square.x > x && square.y > y)  dir8 = true;
			}
			else { // горизонтали и вертикали
				if (square.x > x && square.y == y) dir1 = true;
				else if (square.x == x && square.y < y) dir3 = true;
				else if (square.x < x && square.y == y) dir5 = true;
				else if (square.x == x && square.y > y) dir7 = true;
			}

			for (int i = 1; i < 8; ++i)
			{
				if (dir1 && x + i >= 0 && x + i <= 7) {
					dir1X = x + i;
					if (squares[x + i][y].isEmpty) continue; else break;
				}
				else if (dir2 && x + i >= 0 && x + i <= 7 && y - i >= 0 && y - i <= 7) {
					dir2X = x + i;
					dir2Y = y - i;
					if (squares[x + i][y - i].isEmpty) continue; else break;
				}
				else if (dir3 && y - i >= 0 && y - i <= 7) {
					dir3Y = y - i;
					if (squares[x][y - i].isEmpty) continue; else break;
				}
				else if (dir4 && x - i >= 0 && x - i <= 7 && y - i >= 0 && y - i <= 7) {
					dir4X = x - i;
					dir4Y = y - i;
					if (squares[x - i][y - i].isEmpty) continue; else break;
				}
				else if (dir5 && x - i >= 0 && x - i <= 7) {
					dir5X = x - i;
					if (squares[x - i][y].isEmpty) continue; else break;
				}
				else if (dir6 && x - i >= 0 && x - i <= 7 && y + i >= 0 && y + i <= 7) {
					dir6X = x - i;
					dir6Y = y + i;
					if (squares[x - i][y + i].isEmpty) continue; else break;
				}
				else if (dir7 && y + i >= 0 && y + i <= 7) {
					dir7Y = y + i;
					if (squares[x][y + i].isEmpty) continue; else break;
				}
				else if (dir8 && x + i >= 0 && x + i <= 7 && y + i >= 0 && y + i <= 7) {
					dir8X = x + i;
					dir8Y = y + i;
					if (squares[x + i][y + i].isEmpty) continue; else break;
				}
				else break;
			}

			return ((dir1 && square.x == dir1X) ||
				(dir2 && square.x == dir2X && square.y == dir2Y) ||
				(dir3 && square.y == dir3Y) ||
				(dir4 && square.x == dir4X && square.y == dir4Y) ||
				(dir5 && square.x == dir5X) ||
				(dir6 && square.x == dir6X && square.y == dir6Y) ||
				(dir7 && square.y == dir7Y) ||
				(dir8 && square.x == dir8X && square.y == dir8Y));
		}
		return false;
	}
};

class King : public AbstractFigure {
public:
	King(const Square& square, const bool& color, const Texture& texture) : AbstractFigure(square, color, texture) {
		sprite.setOrigin(35, 38);
		name = "King";
	}

	bool ConditionOfMove(const Square& square) override {
		return (square.isEmpty && abs(square.x - x) <= 1 && abs(square.y - y) <= 1 && color == turn);
	}

	void Move(Square& square) override {
		if (ConditionOfMove(square)) Move_(squares[x][y], square);
		else setPos(squares[x][y].xInPixel, squares[x][y].yInPixel);
	}

	bool ConditionOfCapture(const Square& square) override {
		return (!square.isEmpty && abs(square.x - x) <= 1 && abs(square.y - y) <= 1 && (square.x != x || square.y != y) && square.color != turn && color == turn);
	}
};
