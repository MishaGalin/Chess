#pragma once
using namespace sf; // SFML namespace
using namespace std;

extern Game game;
extern Board board;
extern vector<unique_ptr<AbstractChessPiece>> pieces;
extern AbstractChessPiece* FindPiece(const Square& square);

class Pawn : public AbstractChessPiece {
	bool ConditionOfMove(const Square& newSquare) override {
		return (!game.isStopped && getIsSelected() && newSquare.getIsEmpty() && getX() == newSquare.getX() && getColor() == game.turn
			&& ((pow(-1, getColor()) * (getY() - newSquare.getY()) == 2 && board.Squares[getX()][getY() - (pow(-1, getColor()) * 1)].getIsEmpty() && getFirstMove())
				|| pow(-1, getColor()) * (getY() - newSquare.getY()) == 1));
	};

	bool ConditionOfCapture(const Square& newSquare) override {
		return (!game.isStopped && getIsSelected() && !newSquare.getIsEmpty() && getColor() == game.turn && newSquare.getColor() != game.turn &&
			pow(-1, getColor()) * (getY() - newSquare.getY()) == 1 && abs(getX() - newSquare.getX()) == 1);
	}

	bool ConditionOfCastling(const Square& newSquare) override { return false; }

	void Castling_(const Square& square) { return; }
public:
	Pawn(const Square& square, const bool& color) : AbstractChessPiece(square, color) {
		sprite.setOrigin(25, 42);
		setName(color ? "PawnB" : "PawnW");
		sprite.setTexture(*game.textureOfPieces[getName()]);
	}
};

class Castle : public AbstractChessPiece {
	bool ConditionOfMove(const Square& newSquare) override {
		if (!game.isStopped && getIsSelected() && newSquare.getIsEmpty() && getColor() == game.turn) {
			int dir1Y = getY(),
				dir2X = getX(),
				dir3Y = getY(),
				dir4X = getX();
			bool dir1 = false, dir2 = false, dir3 = false, dir4 = false;

			if (newSquare.getX() == getX() && newSquare.getY() < getY()) dir1 = true;
			else if (newSquare.getX() < getX() && newSquare.getY() == getY()) dir2 = true;
			else if (newSquare.getX() == getX() && newSquare.getY() > getY()) dir3 = true;
			else if (newSquare.getX() > getX() && newSquare.getY() == getY()) dir4 = true;

			for (int i = 1; i < 8; ++i)
			{
				if (dir1 && getY() - i >= 0 && getY() - i <= 7) {
					if (board.Squares[getX()][getY() - i].getIsEmpty()) dir1Y = getY() - i; else break;
				}
				else if (dir2 && getX() - i >= 0 && getX() - i <= 7) {
					if (board.Squares[getX() - i][getY()].getIsEmpty()) dir2X = getX() - i; else break;
				}
				else if (dir3 && getY() + i >= 0 && getY() + i <= 7) {
					if (board.Squares[getX()][getY() + i].getIsEmpty()) dir3Y = getY() + i; else break;
				}
				else if (dir4 && getX() + i >= 0 && getX() + i <= 7) {
					if (board.Squares[getX() + i][getY()].getIsEmpty()) dir4X = getX() + i; else break;
				}
			}
			return ((dir1 && newSquare.getY() >= dir1Y) ||
				(dir2 && newSquare.getX() >= dir2X) ||
				(dir3 && newSquare.getY() <= dir3Y) ||
				(dir4 && newSquare.getX() <= dir4X));
		}
		return false;
	}

	bool ConditionOfCapture(const Square& newSquare) override {
		if (!game.isStopped && getIsSelected() && !newSquare.getIsEmpty() && newSquare.getColor() != game.turn && getColor() == game.turn) {
			int dir1Y = getY(),
				dir2X = getX(),
				dir3Y = getY(),
				dir4X = getX();
			bool dir1 = false, dir2 = false, dir3 = false, dir4 = false;

			if (newSquare.getX() == getX() && newSquare.getY() < getY()) dir1 = true;
			else if (newSquare.getX() < getX() && newSquare.getY() == getY()) dir2 = true;
			else if (newSquare.getX() == getX() && newSquare.getY() > getY()) dir3 = true;
			else if (newSquare.getX() > getX() && newSquare.getY() == getY()) dir4 = true;

			for (int i = 1; i < 8; ++i)
			{
				if (dir1 && getY() - i >= 0 && getY() - i <= 7) {
					dir1Y = getY() - i;
					if (board.Squares[getX()][dir1Y].getIsEmpty()) continue; else break;
				}
				else if (dir2 && getX() - i >= 0 && getX() - i <= 7) {
					dir2X = getX() - i;
					if (board.Squares[dir2X][getY()].getIsEmpty()) continue; else break;
				}
				else if (dir3 && getY() + i >= 0 && getY() + i <= 7) {
					dir3Y = getY() + i;
					if (board.Squares[getX()][dir3Y].getIsEmpty()) continue; else break;
				}
				else if (dir4 && getX() + i >= 0 && getX() + i <= 7) {
					dir4X = getX() + i;
					if (board.Squares[dir4X][getY()].getIsEmpty()) continue; else break;
				}
			}
			return ((dir1 && newSquare.getY() == dir1Y) ||
				(dir2 && newSquare.getX() == dir2X) ||
				(dir3 && newSquare.getY() == dir3Y) ||
				(dir4 && newSquare.getX() == dir4X));
		}
		return false;
	}

	bool ConditionOfCastling(const Square& newSquare) override {
		if (!game.isStopped && getIsSelected() && !newSquare.getIsEmpty() && getFirstMove() && getY() == newSquare.getY()) {
			bool shortÑastling = false, distantCastling = false;
			int shortÑastlingX = getX(), distantCastlingX = getX();
			for (auto& piece : pieces) {
				if (piece->getFirstMove() && piece->getX() == newSquare.getX() && piece->getY() == newSquare.getY() && (getColor() ? piece->getName() == "KingB" : piece->getName() == "KingW")) {
					if (piece->getX() > getX()) shortÑastling = true;
					else if (piece->getX() < getX()) distantCastling = true;

					for (int i = 1; i < 8; ++i)
					{
						if (shortÑastling && getX() + i >= 0 && getX() + i <= 7) {
							shortÑastlingX = getX() + i;
							if (board.Squares[shortÑastlingX][getY()].getIsEmpty()) continue; else break;
						}
						if (distantCastling && getX() - i >= 0 && getX() - i <= 7) {
							distantCastlingX = getX() - i;
							if (board.Squares[distantCastlingX][getY()].getIsEmpty()) continue; else break;
						}
					}
					return ((shortÑastling && newSquare.getX() == shortÑastlingX) || (distantCastling && newSquare.getX() == distantCastlingX));
				}
			}
		}
		return false;
	}

	void Castling_(const Square& square) {
		int newX = getX() + (square.getX() > getX() ? 3 : -2);
		Changeover(board.Squares[getX()][getY()], board.Squares[newX][getY()]);

		setFirstMove(false);
		setX(newX);
		setPosition(board.Squares[getX()][getY()].getInPixel());

		AbstractChessPiece* piece = FindPiece(square);
		if (piece->getX() == square.getX() && piece->getY() == square.getY()) {
			int newThisPieceX = getX() + (square.getX() > getX() ? -1 : 1);
			Changeover(board.Squares[square.getX()][getY()], board.Squares[newThisPieceX][getY()]);
			piece->setX(newThisPieceX);
			piece->setPosition(board.Squares[piece->getX()][getY()].getInPixel());
			piece->setFirstMove(false);
		}

		game.ChangeOfTurn();
	}
public:
	Castle(const Square& square, const bool& color) : AbstractChessPiece(square, color) {
		sprite.setOrigin(33, 43);
		setName(color ? "CastleB" : "CastleW");
		sprite.setTexture(*game.textureOfPieces[getName()]);
	}
};

class Knight : public AbstractChessPiece {
	bool ConditionOfMove(const Square& newSquare) override {
		return (!game.isStopped && getIsSelected() && newSquare.getIsEmpty() && abs((getX() - newSquare.getX()) * (getY() - newSquare.getY())) == 2 && getColor() == game.turn);
	}

	bool ConditionOfCapture(const Square& newSquare) override {
		return (!game.isStopped && getIsSelected() && !newSquare.getIsEmpty() && abs((getX() - newSquare.getX()) * (getY() - newSquare.getY())) == 2 && newSquare.getColor() != game.turn && getColor() == game.turn);
	}

	bool ConditionOfCastling(const Square& newSquare) override { return false; }

	void Castling_(const Square& square) { return; }
public:
	Knight(const Square& square, const bool& color) : AbstractChessPiece(square, color) {
		sprite.setOrigin(37, 45);
		setName(color ? "KnightB" : "KnightW");
		sprite.setTexture(*game.textureOfPieces[getName()]);
	}
};

class Bishop : public AbstractChessPiece {
	bool ConditionOfMove(const Square& newSquare) override {
		if (!game.isStopped && getIsSelected() && newSquare.getIsEmpty() && abs(newSquare.getX() - getX()) == abs(newSquare.getY() - getY()) && getColor() == game.turn) {
			int dir1X = getX(), dir1Y = getY(),
				dir2X = getX(), dir2Y = getY(),
				dir3X = getX(), dir3Y = getY(),
				dir4X = getX(), dir4Y = getY();
			bool dir1 = false, dir2 = false, dir3 = false, dir4 = false;

			if (newSquare.getX() > getX() && newSquare.getY() < getY()) dir1 = true;
			else if (newSquare.getX() < getX() && newSquare.getY() < getY()) dir2 = true;
			else if (newSquare.getX() < getX() && newSquare.getY() > getY()) dir3 = true;
			else if (newSquare.getX() > getX() && newSquare.getY() > getY()) dir4 = true;

			for (int i = 1; i < 8; ++i)
			{
				if (dir1 && getX() + i >= 0 && getX() + i <= 7 && getY() - i >= 0 && getY() - i <= 7) {
					if (board.Squares[getX() + i][getY() - i].getIsEmpty()) {
						dir1X = getX() + i;
						dir1Y = getY() - i;
					}
					else break;
				}
				else if (dir2 && getX() - i >= 0 && getX() - i <= 7 && getY() - i >= 0 && getY() - i <= 7) {
					if (board.Squares[getX() - i][getY() - i].getIsEmpty()) {
						dir2X = getX() - i;
						dir2Y = getY() - i;
					}
					else break;
				}
				else if (dir3 && getX() - i >= 0 && getX() - i <= 7 && getY() + i >= 0 && getY() + i <= 7) {
					if (board.Squares[getX() - i][getY() + i].getIsEmpty()) {
						dir3X = getX() - i;
						dir3Y = getY() + i;
					}
					else break;
				}
				else if (dir4 && getX() + i >= 0 && getX() + i <= 7 && getY() + i >= 0 && getY() + i <= 7) {
					if (board.Squares[getX() + i][getY() + i].getIsEmpty()) {
						dir4X = getX() + i;
						dir4Y = getY() + i;
					}
					else break;
				}
			}

			return ((dir1 && newSquare.getX() <= dir1X && newSquare.getY() >= dir1Y) ||
				(dir2 && newSquare.getX() >= dir2X && newSquare.getY() >= dir2Y) ||
				(dir3 && newSquare.getX() >= dir3X && newSquare.getY() <= dir3Y) ||
				(dir4 && newSquare.getX() <= dir4X && newSquare.getY() <= dir4Y));
		}
		return false;
	}

	bool ConditionOfCapture(const Square& newSquare) override {
		if (!game.isStopped && getIsSelected() && !newSquare.getIsEmpty() && abs(newSquare.getX() - getX()) == abs(newSquare.getY() - getY()) && newSquare.getColor() != game.turn && getColor() == game.turn) {
			int dir1X = getX(), dir1Y = getY(),
				dir2X = getX(), dir2Y = getY(),
				dir3X = getX(), dir3Y = getY(),
				dir4X = getX(), dir4Y = getY();
			bool dir1 = false, dir2 = false, dir3 = false, dir4 = false;

			if (newSquare.getX() > getX() && newSquare.getY() < getY()) dir1 = true;
			else if (newSquare.getX() < getX() && newSquare.getY() < getY()) dir2 = true;
			else if (newSquare.getX() < getX() && newSquare.getY() > getY()) dir3 = true;
			else if (newSquare.getX() > getX() && newSquare.getY() > getY()) dir4 = true;

			for (int i = 1; i < 8; ++i)
			{
				if (dir1 && getX() + i >= 0 && getX() + i <= 7 && getY() - i >= 0 && getY() - i <= 7) {
					dir1X = getX() + i;
					dir1Y = getY() - i;
					if (board.Squares[dir1X][dir1Y].getIsEmpty()) continue;
					else break;
				}
				else if (dir2 && getX() - i >= 0 && getX() - i <= 7 && getY() - i >= 0 && getY() - i <= 7) {
					dir2X = getX() - i;
					dir2Y = getY() - i;
					if (board.Squares[dir2X][dir2Y].getIsEmpty()) continue;
					else break;
				}
				else if (dir3 && getX() - i >= 0 && getX() - i <= 7 && getY() + i >= 0 && getY() + i <= 7) {
					dir3X = getX() - i;
					dir3Y = getY() + i;
					if (board.Squares[dir3X][dir3Y].getIsEmpty()) continue;
					else break;
				}
				else if (dir4 && getX() + i >= 0 && getX() + i <= 7 && getY() + i >= 0 && getY() + i <= 7) {
					dir4X = getX() + i;
					dir4Y = getY() + i;
					if (board.Squares[dir4X][dir4Y].getIsEmpty()) continue;
					else break;
				}
			}
			return ((dir1 && newSquare.getX() == dir1X && newSquare.getY() == dir1Y) ||
				(dir2 && newSquare.getX() == dir2X && newSquare.getY() == dir2Y) ||
				(dir3 && newSquare.getX() == dir3X && newSquare.getY() == dir3Y) ||
				(dir4 && newSquare.getX() == dir4X && newSquare.getY() == dir4Y));
		}
		return false;
	}

	bool ConditionOfCastling(const Square& newSquare) override { return false; }

	void Castling_(const Square& square) { return; }
public:
	Bishop(const Square& square, const bool& color) : AbstractChessPiece(square, color) {
		sprite.setOrigin(42, 44);
		setName(color ? "BishopB" : "BishopW");
		sprite.setTexture(*game.textureOfPieces[getName()]);
	}
};

class Queen : public AbstractChessPiece {
	bool ConditionOfMove(const Square& newSquare) override {
		if (!game.isStopped && getIsSelected() && newSquare.getIsEmpty() && getColor() == game.turn) {
			int dir1X = getX(), 						   // 1 - âïðàâî
				dir2X = getX(), dir2Y = getY(),			   // 2 - ïî äèàãîíàëè âïðàâî-ââåðõ
				dir3Y = getY(),						   // 3 - ââåðõ
				dir4X = getX(), dir4Y = getY(),			   // è ò.ä. ïðîòèâ ÷àñîâîé ñòðåëêè
				dir5X = getX(),						   //
				dir6X = getX(), dir6Y = getY(),			   //
				dir7Y = getY(),						   //
				dir8X = getX(), dir8Y = getY();			   //
			bool dir1 = false, dir2 = false, dir3 = false, dir4 = false,
				dir5 = false, dir6 = false, dir7 = false, dir8 = false;

			if (abs(newSquare.getX() - getX()) == abs(newSquare.getY() - getY())) { // äèàãîíàëè
				if (newSquare.getX() > getX() && newSquare.getY() < getY())  dir2 = true;
				else if (newSquare.getX() < getX() && newSquare.getY() < getY())  dir4 = true;
				else if (newSquare.getX() < getX() && newSquare.getY() > getY())  dir6 = true;
				else if (newSquare.getX() > getX() && newSquare.getY() > getY())  dir8 = true;
			}
			else { // ãîðèçîíòàëè è âåðòèêàëè
				if (newSquare.getX() > getX() && newSquare.getY() == getY()) dir1 = true;
				else if (newSquare.getX() == getX() && newSquare.getY() < getY()) dir3 = true;
				else if (newSquare.getX() < getX() && newSquare.getY() == getY()) dir5 = true;
				else if (newSquare.getX() == getX() && newSquare.getY() > getY()) dir7 = true;
			}

			for (int i = 1; i < 8; ++i)
			{
				if (dir1 && getX() + i >= 0 && getX() + i <= 7) {
					if (board.Squares[getX() + i][getY()].getIsEmpty()) {
						dir1X = getX() + i;
						continue;
					}
					else break;
				}
				else if (dir2 && getX() + i >= 0 && getX() + i <= 7 && getY() - i >= 0 && getY() - i <= 7) {
					if (board.Squares[getX() + i][getY() - i].getIsEmpty()) {
						dir2X = getX() + i;
						dir2Y = getY() - i;
						continue;
					}
					else break;
				}
				else if (dir3 && getY() - i >= 0 && getY() - i <= 7) {
					if (board.Squares[getX()][getY() - i].getIsEmpty()) {
						dir3Y = getY() - i;
						continue;
					}
					else break;
				}
				else if (dir4 && getX() - i >= 0 && getX() - i <= 7 && getY() - i >= 0 && getY() - i <= 7) {
					if (board.Squares[getX() - i][getY() - i].getIsEmpty()) {
						dir4X = getX() - i;
						dir4Y = getY() - i;
						continue;
					}
					else break;
				}
				else if (dir5 && getX() - i >= 0 && getX() - i <= 7) {
					if (board.Squares[getX() - i][getY()].getIsEmpty()) {
						dir5X = getX() - i;
						continue;
					}
					else break;
				}
				else if (dir6 && getX() - i >= 0 && getX() - i <= 7 && getY() + i >= 0 && getY() + i <= 7) {
					if (board.Squares[getX() - i][getY() + i].getIsEmpty()) {
						dir6X = getX() - i;
						dir6Y = getY() + i;
						continue;
					}
					else break;
				}
				else if (dir7 && getY() + i >= 0 && getY() + i <= 7) {
					if (board.Squares[getX()][getY() + i].getIsEmpty()) {
						dir7Y = getY() + i;
						continue;
					}
					else break;
				}
				else if (dir8 && getX() + i >= 0 && getX() + i <= 7 && getY() + i >= 0 && getY() + i <= 7) {
					if (board.Squares[getX() + i][getY() + i].getIsEmpty()) {
						dir8X = getX() + i;
						dir8Y = getY() + i;
						continue;
					}
					else break;
				}
			}

			return ((dir1 && newSquare.getX() <= dir1X) ||
				(dir2 && newSquare.getX() <= dir2X && newSquare.getY() >= dir2Y) ||
				(dir3 && newSquare.getY() >= dir3Y) ||
				(dir4 && newSquare.getX() >= dir4X && newSquare.getY() >= dir4Y) ||
				(dir5 && newSquare.getX() >= dir5X) ||
				(dir6 && newSquare.getX() >= dir6X && newSquare.getY() <= dir6Y) ||
				(dir7 && newSquare.getY() <= dir7Y) ||
				(dir8 && newSquare.getX() <= dir8X && newSquare.getY() <= dir8Y));
		}
		return false;
	}

	bool ConditionOfCapture(const Square& newSquare) override {
		if (!game.isStopped && getIsSelected() && !newSquare.getIsEmpty() && newSquare.getColor() != game.turn && getColor() == game.turn) {
			int dir1X = getX(), 					   // 1 - âïðàâî
				dir2X = getX(), dir2Y = getY(),		   // 2 - ïî äèàãîíàëè âïðàâî-ââåðõ
				dir3Y = getY(),						   // 3 - ââåðõ
				dir4X = getX(), dir4Y = getY(),		   // è ò.ä. ïðîòèâ ÷àñîâîé ñòðåëêè
				dir5X = getX(),						   //
				dir6X = getX(), dir6Y = getY(),		   //
				dir7Y = getY(),						   //
				dir8X = getX(), dir8Y = getY();		   //
			bool dir1 = false, dir2 = false, dir3 = false, dir4 = false,
				dir5 = false, dir6 = false, dir7 = false, dir8 = false;

			if (abs(newSquare.getX() - getX()) == abs(newSquare.getY() - getY())) { // äèàãîíàëè
				if (newSquare.getX() > getX() && newSquare.getY() < getY())  dir2 = true;
				else if (newSquare.getX() < getX() && newSquare.getY() < getY())  dir4 = true;
				else if (newSquare.getX() < getX() && newSquare.getY() > getY())  dir6 = true;
				else if (newSquare.getX() > getX() && newSquare.getY() > getY())  dir8 = true;
			}
			else { // ãîðèçîíòàëè è âåðòèêàëè
				if (newSquare.getX() > getX() && newSquare.getY() == getY()) dir1 = true;
				else if (newSquare.getX() == getX() && newSquare.getY() < getY()) dir3 = true;
				else if (newSquare.getX() < getX() && newSquare.getY() == getY()) dir5 = true;
				else if (newSquare.getX() == getX() && newSquare.getY() > getY()) dir7 = true;
			}

			for (int i = 1; i < 8; ++i)
			{
				if (dir1 && getX() + i >= 0 && getX() + i <= 7) {
					dir1X = getX() + i;
					if (board.Squares[dir1X][getY()].getIsEmpty()) continue;
					else break;
				}
				else if (dir2 && getX() + i >= 0 && getX() + i <= 7 && getY() - i >= 0 && getY() - i <= 7) {
					dir2X = getX() + i;
					dir2Y = getY() - i;
					if (board.Squares[dir2X][dir2Y].getIsEmpty()) continue;
					else break;
				}
				else if (dir3 && getY() - i >= 0 && getY() - i <= 7) {
					dir3Y = getY() - i;
					if (board.Squares[getX()][dir3Y].getIsEmpty()) continue;
					else break;
				}
				else if (dir4 && getX() - i >= 0 && getX() - i <= 7 && getY() - i >= 0 && getY() - i <= 7) {
					dir4X = getX() - i;
					dir4Y = getY() - i;
					if (board.Squares[dir4X][dir4Y].getIsEmpty()) continue;
					else break;
				}
				else if (dir5 && getX() - i >= 0 && getX() - i <= 7) {
					dir5X = getX() - i;
					if (board.Squares[dir5X][getY()].getIsEmpty()) continue;
					else break;
				}
				else if (dir6 && getX() - i >= 0 && getX() - i <= 7 && getY() + i >= 0 && getY() + i <= 7) {
					dir6X = getX() - i;
					dir6Y = getY() + i;
					if (board.Squares[dir6X][dir6Y].getIsEmpty()) continue;
					else break;
				}
				else if (dir7 && getY() + i >= 0 && getY() + i <= 7) {
					dir7Y = getY() + i;
					if (board.Squares[getX()][dir7Y].getIsEmpty()) continue;
					else break;
				}
				else if (dir8 && getX() + i >= 0 && getX() + i <= 7 && getY() + i >= 0 && getY() + i <= 7) {
					dir8X = getX() + i;
					dir8Y = getY() + i;
					if (board.Squares[dir8X][dir8Y].getIsEmpty()) continue;
					else break;
				}
				else break;
			}

			return ((dir1 && newSquare.getX() == dir1X) ||
				(dir2 && newSquare.getX() == dir2X && newSquare.getY() == dir2Y) ||
				(dir3 && newSquare.getY() == dir3Y) ||
				(dir4 && newSquare.getX() == dir4X && newSquare.getY() == dir4Y) ||
				(dir5 && newSquare.getX() == dir5X) ||
				(dir6 && newSquare.getX() == dir6X && newSquare.getY() == dir6Y) ||
				(dir7 && newSquare.getY() == dir7Y) ||
				(dir8 && newSquare.getX() == dir8X && newSquare.getY() == dir8Y));
		}
		return false;
	}

	bool ConditionOfCastling(const Square& newSquare) override { return false; }

	void Castling_(const Square& square) { return; }
public:
	Queen(const Square& square, const bool& color) : AbstractChessPiece(square, color) {
		sprite.setOrigin(42, 45);
		setName(color ? "QueenB" : "QueenW");
		sprite.setTexture(*game.textureOfPieces[getName()]);
	}
};

class King : public AbstractChessPiece {
	bool ConditionOfMove(const Square& newSquare) override {
		return (!game.isStopped && getIsSelected() && newSquare.getIsEmpty() && abs(newSquare.getX() - getX()) <= 1 && abs(newSquare.getY() - getY()) <= 1 && getColor() == game.turn);
	}

	bool ConditionOfCapture(const Square& newSquare) override {
		return (!game.isStopped && getIsSelected() && !newSquare.getIsEmpty() && abs(newSquare.getX() - getX()) <= 1 && abs(newSquare.getY() - getY()) <= 1
			&& (newSquare.getX() != getX() || newSquare.getY() != getY()) && newSquare.getColor() != game.turn && getColor() == game.turn);
	}

	bool ConditionOfCastling(const Square& newSquare) override {
		if (!game.isStopped && getIsSelected() && !newSquare.getIsEmpty() && getFirstMove() && getY() == newSquare.getY()) {
			bool shortÑastling = false, distantCastling = false;
			int shortÑastlingX = getX(), distantCastlingX = getX();
			for (auto& piece : pieces) {
				if (piece->getFirstMove() && piece->getX() == newSquare.getX() && piece->getY() == newSquare.getY() && (getColor() ? piece->getName() == "CastleB" : piece->getName() == "CastleW")) {
					if (piece->getX() > getX()) shortÑastling = true;
					else if (piece->getX() < getX()) distantCastling = true;

					for (int i = 1; i < 8; ++i)
					{
						if (shortÑastling && getX() + i >= 0 && getX() + i <= 7) {
							shortÑastlingX = getX() + i;
							if (board.Squares[shortÑastlingX][getY()].getIsEmpty()) continue; else break;
						}
						if (distantCastling && getX() - i >= 0 && getX() - i <= 7) {
							distantCastlingX = getX() - i;
							if (board.Squares[distantCastlingX][getY()].getIsEmpty()) continue; else break;
						}
					}
					return ((shortÑastling && newSquare.getX() == shortÑastlingX) || (distantCastling && newSquare.getX() == distantCastlingX));
				}
			}
		}
		return false;
	}

	void Castling_(const Square& square) {
		int newX = getX() + (square.getX() > getX() ? 2 : -2);
		Changeover(board.Squares[getX()][getY()], board.Squares[newX][getY()]);

		setFirstMove(false);
		setX(newX);
		setPosition(board.Squares[getX()][getY()].getXInPixel(), board.Squares[getX()][getY()].getYInPixel());

		AbstractChessPiece* piece = FindPiece(square);
		if (piece->getX() == square.getX() && piece->getY() == square.getY()) {
			int newThisPieceX = getX() + (getX() < piece->getX() ? -1 : 1);
			piece->setX(newThisPieceX);
			piece->setX(newThisPieceX);
			piece->setPosition(board.Squares[piece->getX()][getY()].getXInPixel(), board.Squares[piece->getX()][getY()].getYInPixel());
			piece->setFirstMove(false);
		}

		game.ChangeOfTurn();
	}

public:
	King(const Square& square, const bool& color) : AbstractChessPiece(square, color) {
		sprite.setOrigin(42, 44);
		setName(color ? "KingB" : "KingW");
		sprite.setTexture(*game.textureOfPieces[getName()]);
	}
};
