#pragma once
using namespace sf; // SFML namespace
using namespace std;

extern bool g_turn;

extern vector<vector<Square>> squares;

void Delete(Square& square);

class Pawn : public AbstractFigure {
public:
	Pawn(const Square& square, const bool& color, const Texture& texture) : AbstractFigure(square, color, texture) {
		sprite.setOrigin(25, 42);
		name = "Pawn";
	}

	bool ConditionOfMove(const Square& square) override {
		return (square.getIsEmpty() && getX() == square.getX()
			&& getColor() == g_turn
			&& ((pow(-1, getColor()) * (getY() - square.getY()) == 2 && squares[getX()][getY() - (pow(-1, getColor()) * 1)].getIsEmpty() && getFirstMove())
				|| pow(-1, getColor()) * (getY() - square.getY()) == 1));
	};

	void Move(Square& square) override {
		if (ConditionOfMove(square)) Move_(squares[getX()][getY()], square);
		else sprite.setPosition(squares[getX()][getY()].getXInPixel(), squares[getX()][getY()].getYInPixel());
	}

	bool ConditionOfCapture(const Square& square) override {
		return (!square.getIsEmpty() && pow(-1, getColor()) * (getY() - square.getY()) == 1 && abs(getX() - square.getX()) == 1 && square.getColor() != g_turn && getColor() == g_turn);
	}

	void Capture(Square& square) override {
		if (ConditionOfCapture(square)) {
			Delete(square);
			Move_(squares[getX()][getY()], square);
		}
		else sprite.setPosition(squares[getX()][getY()].getXInPixel(), squares[getX()][getY()].getYInPixel());
	}
};

class Castle : public AbstractFigure {
public:
	Castle(const Square& square, const bool& color, const Texture& texture) : AbstractFigure(square, color, texture) {
		sprite.setOrigin(33, 43);
		name = "Castle";
	}

	bool ConditionOfMove(const Square& square) override {
		if (square.getIsEmpty() && getColor() == g_turn) {
			int dir1Y = getY(),
				dir2X = getX(),
				dir3Y = getY(),
				dir4X = getX();
			bool dir1 = false, dir2 = false, dir3 = false, dir4 = false;

			if (square.getX() == getX() && square.getY() < getY()) dir1 = true;
			else if (square.getX() < getX() && square.getY() == getY()) dir2 = true;
			else if (square.getX() == getX() && square.getY() > getY()) dir3 = true;
			else if (square.getX() > getX() && square.getY() == getY()) dir4 = true;

			for (int i = 1; i < 8; ++i)
			{
				if (dir1 && getY() - i >= 0 && getY() - i <= 7) {
					if (squares[getX()][getY() - i].getIsEmpty()) dir1Y = getY() - i; else break;
				}
				else if (dir2 && getX() - i >= 0 && getX() - i <= 7) {
					if (squares[getX() - i][getY()].getIsEmpty()) dir2X = getX() - i; else break;
				}
				else if (dir3 && getY() + i >= 0 && getY() + i <= 7) {
					if (squares[getX()][getY() + i].getIsEmpty()) dir3Y = getY() + i; else break;
				}
				else if (dir4 && getX() + i >= 0 && getX() + i <= 7) {
					if (squares[getX() + i][getY()].getIsEmpty()) dir4X = getX() + i; else break;
				}
			}
			return ((dir1 && square.getY() >= dir1Y) ||
				(dir2 && square.getX() >= dir2X) ||
				(dir3 && square.getY() <= dir3Y) ||
				(dir4 && square.getX() <= dir4X));
		}
		return false;
	}

	void Move(Square& square) override {
		if (ConditionOfMove(square)) Move_(squares[getX()][getY()], square);
		else sprite.setPosition(squares[getX()][getY()].getXInPixel(), squares[getX()][getY()].getYInPixel());
	}

	bool ConditionOfCapture(const Square& square) override {
		if (!square.getIsEmpty() && square.getColor() != g_turn && getColor() == g_turn) {
			int dir1Y = getY(),
				dir2X = getX(),
				dir3Y = getY(),
				dir4X = getX();
			bool dir1 = false, dir2 = false, dir3 = false, dir4 = false;

			if (square.getX() == getX() && square.getY() < getY()) dir1 = true;
			else if (square.getX() < getX() && square.getY() == getY()) dir2 = true;
			else if (square.getX() == getX() && square.getY() > getY()) dir3 = true;
			else if (square.getX() > getX() && square.getY() == getY()) dir4 = true;

			for (int i = 1; i < 8; ++i)
			{
				if (dir1 && getY() - i >= 0 && getY() - i <= 7) {
					dir1Y = getY() - i;
					if (squares[getX()][dir1Y].getIsEmpty()) continue; else break;
				}
				else if (dir2 && getX() - i >= 0 && getX() - i <= 7) {
					dir2X = getX() - i;
					if (squares[dir2X][getY()].getIsEmpty()) continue; else break;
				}
				else if (dir3 && getY() + i >= 0 && getY() + i <= 7) {
					dir3Y = getY() + i;
					if (squares[getX()][dir3Y].getIsEmpty()) continue; else break;
				}
				else if (dir4 && getX() + i >= 0 && getX() + i <= 7) {
					dir4X = getX() + i;
					if (squares[dir4X][getY()].getIsEmpty()) continue; else break;
				}
			}
			return ((dir1 && square.getY() == dir1Y) ||
				(dir2 && square.getX() == dir2X) ||
				(dir3 && square.getY() == dir3Y) ||
				(dir4 && square.getX() == dir4X));
		}
		return false;
	}

	void Capture(Square& square) override {
		if (ConditionOfCapture(square)) {
			Delete(square);
			Move_(squares[getX()][getY()], square);
		}
		else sprite.setPosition(squares[getX()][getY()].getXInPixel(), squares[getX()][getY()].getYInPixel());
	}
};

class Knight : public AbstractFigure {
public:
	Knight(const Square& square, const bool& color, const Texture& texture) : AbstractFigure(square, color, texture) {
		sprite.setOrigin(37, 45);
		name = "Knight";
	}

	bool ConditionOfMove(const Square& square) override {
		return (square.getIsEmpty() && abs((getX() - square.getX()) * (getY() - square.getY())) == 2 && getColor() == g_turn);
	}

	void Move(Square& square) override {
		if (ConditionOfMove(square)) Move_(squares[getX()][getY()], square);
		else sprite.setPosition(squares[getX()][getY()].getXInPixel(), squares[getX()][getY()].getYInPixel());
	}

	bool ConditionOfCapture(const Square& square) override {
		return (!square.getIsEmpty() && abs((getX() - square.getX()) * (getY() - square.getY())) == 2 && square.getColor() != g_turn && getColor() == g_turn);
	}

	void Capture(Square& square) override {
		if (ConditionOfCapture(square)) {
			Delete(square);
			Move_(squares[getX()][getY()], square);
		}
		else sprite.setPosition(squares[getX()][getY()].getXInPixel(), squares[getX()][getY()].getYInPixel());
	}
};

class Bishop : public AbstractFigure {
public:
	Bishop(const Square& square, const bool& color, const Texture& texture) : AbstractFigure(square, color, texture) {
		sprite.setOrigin(42, 44);
		name = "Bishop";
	}

	bool ConditionOfMove(const Square& square) override {
		if (square.getIsEmpty() && abs(square.getX() - getX()) == abs(square.getY() - getY()) && getColor() == g_turn) {
			int dir1X = getX(), dir1Y = getY(),
				dir2X = getX(), dir2Y = getY(),
				dir3X = getX(), dir3Y = getY(),
				dir4X = getX(), dir4Y = getY();
			bool dir1 = false, dir2 = false, dir3 = false, dir4 = false;

			if (square.getX() > getX() && square.getY() < getY()) dir1 = true;
			else if (square.getX() < getX() && square.getY() < getY()) dir2 = true;
			else if (square.getX() < getX() && square.getY() > getY()) dir3 = true;
			else if (square.getX() > getX() && square.getY() > getY()) dir4 = true;

			for (int i = 1; i < 8; ++i)
			{
				if (dir1 && getX() + i >= 0 && getX() + i <= 7 && getY() - i >= 0 && getY() - i <= 7) {
					if (squares[getX() + i][getY() - i].getIsEmpty()) {
						dir1X = getX() + i;
						dir1Y = getY() - i;
					}
					else break;
				}
				else if (dir2 && getX() - i >= 0 && getX() - i <= 7 && getY() - i >= 0 && getY() - i <= 7) {
					if (squares[getX() - i][getY() - i].getIsEmpty()) {
						dir2X = getX() - i;
						dir2Y = getY() - i;
					}
					else break;
				}
				else if (dir3 && getX() - i >= 0 && getX() - i <= 7 && getY() + i >= 0 && getY() + i <= 7) {
					if (squares[getX() - i][getY() + i].getIsEmpty()) {
						dir3X = getX() - i;
						dir3Y = getY() + i;
					}
					else break;
				}
				else if (dir4 && getX() + i >= 0 && getX() + i <= 7 && getY() + i >= 0 && getY() + i <= 7) {
					if (squares[getX() + i][getY() + i].getIsEmpty()) {
						dir4X = getX() + i;
						dir4Y = getY() + i;
					}
					else break;
				}
			}

			return ((dir1 && square.getX() <= dir1X && square.getY() >= dir1Y) ||
				(dir2 && square.getX() >= dir2X && square.getY() >= dir2Y) ||
				(dir3 && square.getX() >= dir3X && square.getY() <= dir3Y) ||
				(dir4 && square.getX() <= dir4X && square.getY() <= dir4Y));
		}
		return false;
	}

	void Move(Square& square) override {
		if (ConditionOfMove(square)) Move_(squares[getX()][getY()], square);
		else sprite.setPosition(squares[getX()][getY()].getXInPixel(), squares[getX()][getY()].getYInPixel());
	}

	bool ConditionOfCapture(const Square& square) override {
		if (!square.getIsEmpty() && abs(square.getX() - getX()) == abs(square.getY() - getY()) && square.getColor() != g_turn && getColor() == g_turn) {
			int dir1X = getX(), dir1Y = getY(),
				dir2X = getX(), dir2Y = getY(),
				dir3X = getX(), dir3Y = getY(),
				dir4X = getX(), dir4Y = getY();
			bool dir1 = false, dir2 = false, dir3 = false, dir4 = false;

			if (square.getX() > getX() && square.getY() < getY()) dir1 = true;
			else if (square.getX() < getX() && square.getY() < getY()) dir2 = true;
			else if (square.getX() < getX() && square.getY() > getY()) dir3 = true;
			else if (square.getX() > getX() && square.getY() > getY()) dir4 = true;

			for (int i = 1; i < 8; ++i)
			{
				if (dir1 && getX() + i >= 0 && getX() + i <= 7 && getY() - i >= 0 && getY() - i <= 7) {
					dir1X = getX() + i;
					dir1Y = getY() - i;
					if (squares[getX() + i][getY() - i].getIsEmpty()) continue;
					else break;
				}
				else if (dir2 && getX() - i >= 0 && getX() - i <= 7 && getY() - i >= 0 && getY() - i <= 7) {
					dir2X = getX() - i;
					dir2Y = getY() - i;
					if (squares[getX() - i][getY() - i].getIsEmpty()) continue;
					else break;
				}
				else if (dir3 && getX() - i >= 0 && getX() - i <= 7 && getY() + i >= 0 && getY() + i <= 7) {
					dir3X = getX() - i;
					dir3Y = getY() + i;
					if (squares[getX() - i][getY() + i].getIsEmpty()) continue;
					else break;
				}
				else if (dir4 && getX() + i >= 0 && getX() + i <= 7 && getY() + i >= 0 && getY() + i <= 7) {
					dir4X = getX() + i;
					dir4Y = getY() + i;
					if (squares[getX() + i][getY() + i].getIsEmpty()) continue;
					else break;
				}
			}
			return ((dir1 && square.getX() == dir1X && square.getY() == dir1Y) ||
				(dir2 && square.getX() == dir2X && square.getY() == dir2Y) ||
				(dir3 && square.getX() == dir3X && square.getY() == dir3Y) ||
				(dir4 && square.getX() == dir4X && square.getY() == dir4Y));
		}
		return false;
	}

	void Capture(Square& square)override {
		if (ConditionOfCapture(square)) {
			Delete(square);
			Move_(squares[getX()][getY()], square);
		}
		else sprite.setPosition(squares[getX()][getY()].getXInPixel(), squares[getX()][getY()].getYInPixel());
	}
};

class Queen : public AbstractFigure {
public:
	Queen(const Square& square, const bool& color, const Texture& texture) : AbstractFigure(square, color, texture) {
		sprite.setOrigin(42, 45);
		name = "Queen";
	}

	bool ConditionOfMove(const Square& square) override {
		if (square.getIsEmpty() && getColor() == g_turn) {
			int dir1X = getX(), 						   // 1 - вправо
				dir2X = getX(), dir2Y = getY(),			   // 2 - по диагонали вправо-вверх
				dir3Y = getY(),						   // 3 - вверх
				dir4X = getX(), dir4Y = getY(),			   // и т.д. против часовой стрелки
				dir5X = getX(),						   //
				dir6X = getX(), dir6Y = getY(),			   //
				dir7Y = getY(),						   //
				dir8X = getX(), dir8Y = getY();			   //
			bool dir1 = false, dir2 = false, dir3 = false, dir4 = false,
				dir5 = false, dir6 = false, dir7 = false, dir8 = false;

			if (abs(square.getX() - getX()) == abs(square.getY() - getY())) { // диагонали
				if (square.getX() > getX() && square.getY() < getY())  dir2 = true;
				else if (square.getX() < getX() && square.getY() < getY())  dir4 = true;
				else if (square.getX() < getX() && square.getY() > getY())  dir6 = true;
				else if (square.getX() > getX() && square.getY() > getY())  dir8 = true;
			}
			else { // горизонтали и вертикали
				if (square.getX() > getX() && square.getY() == getY()) dir1 = true;
				else if (square.getX() == getX() && square.getY() < getY()) dir3 = true;
				else if (square.getX() < getX() && square.getY() == getY()) dir5 = true;
				else if (square.getX() == getX() && square.getY() > getY()) dir7 = true;
			}

			for (int i = 1; i < 8; ++i)
			{
				if (dir1 && getX() + i >= 0 && getX() + i <= 7) {
					if (squares[getX() + i][getY()].getIsEmpty()) {
						dir1X = getX() + i;
						continue;
					}
					else break;
				}
				else if (dir2 && getX() + i >= 0 && getX() + i <= 7 && getY() - i >= 0 && getY() - i <= 7) {
					if (squares[getX() + i][getY() - i].getIsEmpty()) {
						dir2X = getX() + i;
						dir2Y = getY() - i;
						continue;
					}
					else break;
				}
				else if (dir3 && getY() - i >= 0 && getY() - i <= 7) {
					if (squares[getX()][getY() - i].getIsEmpty()) {
						dir3Y = getY() - i;
						continue;
					}
					else break;
				}
				else if (dir4 && getX() - i >= 0 && getX() - i <= 7 && getY() - i >= 0 && getY() - i <= 7) {
					if (squares[getX() - i][getY() - i].getIsEmpty()) {
						dir4X = getX() - i;
						dir4Y = getY() - i;
						continue;
					}
					else break;
				}
				else if (dir5 && getX() - i >= 0 && getX() - i <= 7) {
					if (squares[getX() - i][getY()].getIsEmpty()) {
						dir5X = getX() - i;
						continue;
					}
					else break;
				}
				else if (dir6 && getX() - i >= 0 && getX() - i <= 7 && getY() + i >= 0 && getY() + i <= 7) {
					if (squares[getX() - i][getY() + i].getIsEmpty()) {
						dir6X = getX() - i;
						dir6Y = getY() + i;
						continue;
					}
					else break;
				}
				else if (dir7 && getY() + i >= 0 && getY() + i <= 7) {
					if (squares[getX()][getY() + i].getIsEmpty()) {
						dir7Y = getY() + i;
						continue;
					}
					else break;
				}
				else if (dir8 && getX() + i >= 0 && getX() + i <= 7 && getY() + i >= 0 && getY() + i <= 7) {
					if (squares[getX() + i][getY() + i].getIsEmpty()) {
						dir8X = getX() + i;
						dir8Y = getY() + i;
						continue;
					}
					else break;
				}
			}

			return ((dir1 && square.getX() <= dir1X) ||
				(dir2 && square.getX() <= dir2X && square.getY() >= dir2Y) ||
				(dir3 && square.getY() >= dir3Y) ||
				(dir4 && square.getX() >= dir4X && square.getY() >= dir4Y) ||
				(dir5 && square.getX() >= dir5X) ||
				(dir6 && square.getX() >= dir6X && square.getY() <= dir6Y) ||
				(dir7 && square.getY() <= dir7Y) ||
				(dir8 && square.getX() <= dir8X && square.getY() <= dir8Y));
		}
		return false;
	}

	void Move(Square& square) override {
		if (ConditionOfMove(square)) Move_(squares[getX()][getY()], square);
		else sprite.setPosition(squares[getX()][getY()].getXInPixel(), squares[getX()][getY()].getYInPixel());
	}

	bool ConditionOfCapture(const Square& square) override {
		if (!square.getIsEmpty() && square.getColor() != g_turn && getColor() == g_turn) {
			int dir1X = getX(), 						   // 1 - вправо
				dir2X = getX(), dir2Y = getY(),			   // 2 - по диагонали вправо-вверх
				dir3Y = getY(),						   // 3 - вверх
				dir4X = getX(), dir4Y = getY(),			   // и т.д. против часовой стрелки
				dir5X = getX(),						   //
				dir6X = getX(), dir6Y = getY(),			   //
				dir7Y = getY(),						   //
				dir8X = getX(), dir8Y = getY();			   //
			bool dir1 = false, dir2 = false, dir3 = false, dir4 = false,
				dir5 = false, dir6 = false, dir7 = false, dir8 = false;

			if (abs(square.getX() - getX()) == abs(square.getY() - getY())) { // диагонали
				if (square.getX() > getX() && square.getY() < getY())  dir2 = true;
				else if (square.getX() < getX() && square.getY() < getY())  dir4 = true;
				else if (square.getX() < getX() && square.getY() > getY())  dir6 = true;
				else if (square.getX() > getX() && square.getY() > getY())  dir8 = true;
			}
			else { // горизонтали и вертикали
				if (square.getX() > getX() && square.getY() == getY()) dir1 = true;
				else if (square.getX() == getX() && square.getY() < getY()) dir3 = true;
				else if (square.getX() < getX() && square.getY() == getY()) dir5 = true;
				else if (square.getX() == getX() && square.getY() > getY()) dir7 = true;
			}

			for (int i = 1; i < 8; ++i)
			{
				if (dir1 && getX() + i >= 0 && getX() + i <= 7) {
					dir1X = getX() + i;
					if (squares[getX() + i][getY()].getIsEmpty()) continue; else break;
				}
				else if (dir2 && getX() + i >= 0 && getX() + i <= 7 && getY() - i >= 0 && getY() - i <= 7) {
					dir2X = getX() + i;
					dir2Y = getY() - i;
					if (squares[getX() + i][getY() - i].getIsEmpty()) continue; else break;
				}
				else if (dir3 && getY() - i >= 0 && getY() - i <= 7) {
					dir3Y = getY() - i;
					if (squares[getX()][getY() - i].getIsEmpty()) continue; else break;
				}
				else if (dir4 && getX() - i >= 0 && getX() - i <= 7 && getY() - i >= 0 && getY() - i <= 7) {
					dir4X = getX() - i;
					dir4Y = getY() - i;
					if (squares[getX() - i][getY() - i].getIsEmpty()) continue; else break;
				}
				else if (dir5 && getX() - i >= 0 && getX() - i <= 7) {
					dir5X = getX() - i;
					if (squares[getX() - i][getY()].getIsEmpty()) continue; else break;
				}
				else if (dir6 && getX() - i >= 0 && getX() - i <= 7 && getY() + i >= 0 && getY() + i <= 7) {
					dir6X = getX() - i;
					dir6Y = getY() + i;
					if (squares[getX() - i][getY() + i].getIsEmpty()) continue; else break;
				}
				else if (dir7 && getY() + i >= 0 && getY() + i <= 7) {
					dir7Y = getY() + i;
					if (squares[getX()][getY() + i].getIsEmpty()) continue; else break;
				}
				else if (dir8 && getX() + i >= 0 && getX() + i <= 7 && getY() + i >= 0 && getY() + i <= 7) {
					dir8X = getX() + i;
					dir8Y = getY() + i;
					if (squares[getX() + i][getY() + i].getIsEmpty()) continue; else break;
				}
				else break;
			}

			return ((dir1 && square.getX() == dir1X) ||
				(dir2 && square.getX() == dir2X && square.getY() == dir2Y) ||
				(dir3 && square.getY() == dir3Y) ||
				(dir4 && square.getX() == dir4X && square.getY() == dir4Y) ||
				(dir5 && square.getX() == dir5X) ||
				(dir6 && square.getX() == dir6X && square.getY() == dir6Y) ||
				(dir7 && square.getY() == dir7Y) ||
				(dir8 && square.getX() == dir8X && square.getY() == dir8Y));
		}
		return false;
	}

	void Capture(Square& square)override {
		if (ConditionOfCapture(square)) {
			Delete(square);
			Move_(squares[getX()][getY()], square);
		}
		else sprite.setPosition(squares[getX()][getY()].getXInPixel(), squares[getX()][getY()].getYInPixel());
	}
};

class King : public AbstractFigure {
public:
	King(const Square& square, const bool& color, const Texture& texture) : AbstractFigure(square, color, texture) {
		sprite.setOrigin(42, 44);
		name = "King";
	}

	bool ConditionOfMove(const Square& square) override {
		return (square.getIsEmpty() && abs(square.getX() - getX()) <= 1 && abs(square.getY() - getY()) <= 1 && getColor() == g_turn);
	}

	void Move(Square& square) override {
		if (ConditionOfMove(square)) Move_(squares[getX()][getY()], square);
		else sprite.setPosition(squares[getX()][getY()].getXInPixel(), squares[getX()][getY()].getYInPixel());
	}

	bool ConditionOfCapture(const Square& square) override {
		return (!square.getIsEmpty() && abs(square.getX() - getX()) <= 1 && abs(square.getY() - getY()) <= 1
			&& (square.getX() != getX() || square.getY() != getY()) && square.getColor() != g_turn && getColor() == g_turn);
	}

	void Capture(Square& square)override {
		if (ConditionOfCapture(square)) {
			Delete(square);
			Move_(squares[getX()][getY()], square);
		}
		else sprite.setPosition(squares[getX()][getY()].getXInPixel(), squares[getX()][getY()].getYInPixel());
	}
};
