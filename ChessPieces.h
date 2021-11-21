#pragma once
using namespace sf; // SFML namespace
using namespace std;

extern bool g_turn, g_gameIsStopped;
extern vector<vector<Square>> board;
extern map <string, Texture*> textureOfPieces;
extern vector<unique_ptr<AbstractChessPiece>> pieces;
extern AbstractChessPiece* FindPiece(const Square& square);

class Pawn : public AbstractChessPiece {
	bool ConditionOfMove(const Square& square) override {
		return (!g_gameIsStopped && getIsSelected() && square.getIsEmpty() && getX() == square.getX() && getColor() == g_turn
			&& ((pow(-1, getColor()) * (getY() - square.getY()) == 2 && board[getX()][getY() - (pow(-1, getColor()) * 1)].getIsEmpty() && getFirstMove())
				|| pow(-1, getColor()) * (getY() - square.getY()) == 1));
	};

	bool ConditionOfCapture(const Square& square) override {
		return (!g_gameIsStopped && getIsSelected() && !square.getIsEmpty() && pow(-1, getColor()) * (getY() - square.getY()) == 1 && abs(getX() - square.getX()) == 1 && square.getColor() != g_turn && getColor() == g_turn);
	}

	bool ConditionOfCastling(const Square& square) override { return false; }

	void Castling_(const Square& square) { return; }
public:
	Pawn(const Square& square, const bool& color) : AbstractChessPiece(square, color) {
		sprite.setOrigin(25, 42);
		setName(color ? "PawnB" : "PawnW");
		sprite.setTexture(*textureOfPieces[getName()]);
	}
};

class Castle : public AbstractChessPiece {
	bool ConditionOfMove(const Square& square) override {
		if (!g_gameIsStopped && getIsSelected() && square.getIsEmpty() && getColor() == g_turn) {
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
					if (board[getX()][getY() - i].getIsEmpty()) dir1Y = getY() - i; else break;
				}
				else if (dir2 && getX() - i >= 0 && getX() - i <= 7) {
					if (board[getX() - i][getY()].getIsEmpty()) dir2X = getX() - i; else break;
				}
				else if (dir3 && getY() + i >= 0 && getY() + i <= 7) {
					if (board[getX()][getY() + i].getIsEmpty()) dir3Y = getY() + i; else break;
				}
				else if (dir4 && getX() + i >= 0 && getX() + i <= 7) {
					if (board[getX() + i][getY()].getIsEmpty()) dir4X = getX() + i; else break;
				}
			}
			return ((dir1 && square.getY() >= dir1Y) ||
				(dir2 && square.getX() >= dir2X) ||
				(dir3 && square.getY() <= dir3Y) ||
				(dir4 && square.getX() <= dir4X));
		}
		return false;
	}

	bool ConditionOfCapture(const Square& square) override {
		if (!g_gameIsStopped && getIsSelected() && !square.getIsEmpty() && square.getColor() != g_turn && getColor() == g_turn) {
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
					if (board[getX()][dir1Y].getIsEmpty()) continue; else break;
				}
				else if (dir2 && getX() - i >= 0 && getX() - i <= 7) {
					dir2X = getX() - i;
					if (board[dir2X][getY()].getIsEmpty()) continue; else break;
				}
				else if (dir3 && getY() + i >= 0 && getY() + i <= 7) {
					dir3Y = getY() + i;
					if (board[getX()][dir3Y].getIsEmpty()) continue; else break;
				}
				else if (dir4 && getX() + i >= 0 && getX() + i <= 7) {
					dir4X = getX() + i;
					if (board[dir4X][getY()].getIsEmpty()) continue; else break;
				}
			}
			return ((dir1 && square.getY() == dir1Y) ||
				(dir2 && square.getX() == dir2X) ||
				(dir3 && square.getY() == dir3Y) ||
				(dir4 && square.getX() == dir4X));
		}
		return false;
	}

	bool ConditionOfCastling(const Square& square) override {
		if (!g_gameIsStopped && getIsSelected() && !square.getIsEmpty() && getFirstMove() && getY() == square.getY()) {
			bool shortÑastling = false, distantCastling = false;
			int shortÑastlingX = getX(), distantCastlingX = getX();
			for (auto& piece : pieces) {
				if (piece->getFirstMove() && piece->getX() == square.getX() && piece->getY() == square.getY() && (getColor() ? piece->getName() == "KingB" : piece->getName() == "KingW")) {
					if (piece->getX() > getX()) shortÑastling = true;
					else if (piece->getX() < getX()) distantCastling = true;

					for (int i = 1; i < 8; ++i)
					{
						if (shortÑastling && getX() + i >= 0 && getX() + i <= 7) {
							shortÑastlingX = getX() + i;
							if (board[shortÑastlingX][getY()].getIsEmpty()) continue; else break;
						}
						if (distantCastling && getX() - i >= 0 && getX() - i <= 7) {
							distantCastlingX = getX() - i;
							if (board[distantCastlingX][getY()].getIsEmpty()) continue; else break;
						}
					}
					return ((shortÑastling && square.getX() == shortÑastlingX) || (distantCastling && square.getX() == distantCastlingX));
				}
			}
		}
		return false;
	}

	void Castling_(const Square& square) {
		int newX = getX() + (square.getX() > getX() ? 3 : -2);
		board[getX()][getY()].setIsEmpty(true);
		board[newX][getY()].setIsEmpty(false);
		board[getX()][getY()].setColor(!getColor());
		board[newX][getY()].setColor(getColor());

		setFirstMove(false);
		setX(newX);
		setPosition(board[getX()][getY()].getXInPixel(), board[getX()][getY()].getYInPixel());

		AbstractChessPiece* piece = FindPiece(square);
		if (piece->getX() == square.getX() && piece->getY() == square.getY()) {
			int newThisPieceX = getX() + (square.getX() > getX() ? -1 : 1);
			board[square.getX()][getY()].setIsEmpty(true);
			board[newThisPieceX][getY()].setIsEmpty(false);
			piece->setX(newThisPieceX);
			piece->setPosition(board[piece->getX()][getY()].getXInPixel(), board[piece->getX()][getY()].getYInPixel());
			piece->setFirstMove(false);
		}

		g_turn = !g_turn;
		window.setTitle(g_turn ? "Chess: turn of black" : "Chess: turn of white");
	}
public:
	Castle(const Square& square, const bool& color) : AbstractChessPiece(square, color) {
		sprite.setOrigin(33, 43);
		setName(color ? "CastleB" : "CastleW");
		sprite.setTexture(*textureOfPieces[getName()]);
	}
};

class Knight : public AbstractChessPiece {
	bool ConditionOfMove(const Square& square) override {
		return (!g_gameIsStopped && getIsSelected() && square.getIsEmpty() && abs((getX() - square.getX()) * (getY() - square.getY())) == 2 && getColor() == g_turn);
	}

	bool ConditionOfCapture(const Square& square) override {
		return (!g_gameIsStopped && getIsSelected() && !square.getIsEmpty() && abs((getX() - square.getX()) * (getY() - square.getY())) == 2 && square.getColor() != g_turn && getColor() == g_turn);
	}

	bool ConditionOfCastling(const Square& square) override { return false; }

	void Castling_(const Square& square) { return; }
public:
	Knight(const Square& square, const bool& color) : AbstractChessPiece(square, color) {
		sprite.setOrigin(37, 45);
		setName(color ? "KnightB" : "KnightW");
		sprite.setTexture(*textureOfPieces[getName()]);
	}
};

class Bishop : public AbstractChessPiece {
	bool ConditionOfMove(const Square& square) override {
		if (!g_gameIsStopped && getIsSelected() && square.getIsEmpty() && abs(square.getX() - getX()) == abs(square.getY() - getY()) && getColor() == g_turn) {
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
					if (board[getX() + i][getY() - i].getIsEmpty()) {
						dir1X = getX() + i;
						dir1Y = getY() - i;
					}
					else break;
				}
				else if (dir2 && getX() - i >= 0 && getX() - i <= 7 && getY() - i >= 0 && getY() - i <= 7) {
					if (board[getX() - i][getY() - i].getIsEmpty()) {
						dir2X = getX() - i;
						dir2Y = getY() - i;
					}
					else break;
				}
				else if (dir3 && getX() - i >= 0 && getX() - i <= 7 && getY() + i >= 0 && getY() + i <= 7) {
					if (board[getX() - i][getY() + i].getIsEmpty()) {
						dir3X = getX() - i;
						dir3Y = getY() + i;
					}
					else break;
				}
				else if (dir4 && getX() + i >= 0 && getX() + i <= 7 && getY() + i >= 0 && getY() + i <= 7) {
					if (board[getX() + i][getY() + i].getIsEmpty()) {
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

	bool ConditionOfCapture(const Square& square) override {
		if (!g_gameIsStopped && getIsSelected() && !square.getIsEmpty() && abs(square.getX() - getX()) == abs(square.getY() - getY()) && square.getColor() != g_turn && getColor() == g_turn) {
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
					if (board[getX() + i][getY() - i].getIsEmpty()) continue;
					else break;
				}
				else if (dir2 && getX() - i >= 0 && getX() - i <= 7 && getY() - i >= 0 && getY() - i <= 7) {
					dir2X = getX() - i;
					dir2Y = getY() - i;
					if (board[getX() - i][getY() - i].getIsEmpty()) continue;
					else break;
				}
				else if (dir3 && getX() - i >= 0 && getX() - i <= 7 && getY() + i >= 0 && getY() + i <= 7) {
					dir3X = getX() - i;
					dir3Y = getY() + i;
					if (board[getX() - i][getY() + i].getIsEmpty()) continue;
					else break;
				}
				else if (dir4 && getX() + i >= 0 && getX() + i <= 7 && getY() + i >= 0 && getY() + i <= 7) {
					dir4X = getX() + i;
					dir4Y = getY() + i;
					if (board[getX() + i][getY() + i].getIsEmpty()) continue;
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

	bool ConditionOfCastling(const Square& square) override { return false; }

	void Castling_(const Square& square) { return; }
public:
	Bishop(const Square& square, const bool& color) : AbstractChessPiece(square, color) {
		sprite.setOrigin(42, 44);
		setName(color ? "BishopB" : "BishopW");
		sprite.setTexture(*textureOfPieces[getName()]);
	}
};

class Queen : public AbstractChessPiece {
	bool ConditionOfMove(const Square& square) override {
		if (!g_gameIsStopped && getIsSelected() && square.getIsEmpty() && getColor() == g_turn) {
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

			if (abs(square.getX() - getX()) == abs(square.getY() - getY())) { // äèàãîíàëè
				if (square.getX() > getX() && square.getY() < getY())  dir2 = true;
				else if (square.getX() < getX() && square.getY() < getY())  dir4 = true;
				else if (square.getX() < getX() && square.getY() > getY())  dir6 = true;
				else if (square.getX() > getX() && square.getY() > getY())  dir8 = true;
			}
			else { // ãîðèçîíòàëè è âåðòèêàëè
				if (square.getX() > getX() && square.getY() == getY()) dir1 = true;
				else if (square.getX() == getX() && square.getY() < getY()) dir3 = true;
				else if (square.getX() < getX() && square.getY() == getY()) dir5 = true;
				else if (square.getX() == getX() && square.getY() > getY()) dir7 = true;
			}

			for (int i = 1; i < 8; ++i)
			{
				if (dir1 && getX() + i >= 0 && getX() + i <= 7) {
					if (board[getX() + i][getY()].getIsEmpty()) {
						dir1X = getX() + i;
						continue;
					}
					else break;
				}
				else if (dir2 && getX() + i >= 0 && getX() + i <= 7 && getY() - i >= 0 && getY() - i <= 7) {
					if (board[getX() + i][getY() - i].getIsEmpty()) {
						dir2X = getX() + i;
						dir2Y = getY() - i;
						continue;
					}
					else break;
				}
				else if (dir3 && getY() - i >= 0 && getY() - i <= 7) {
					if (board[getX()][getY() - i].getIsEmpty()) {
						dir3Y = getY() - i;
						continue;
					}
					else break;
				}
				else if (dir4 && getX() - i >= 0 && getX() - i <= 7 && getY() - i >= 0 && getY() - i <= 7) {
					if (board[getX() - i][getY() - i].getIsEmpty()) {
						dir4X = getX() - i;
						dir4Y = getY() - i;
						continue;
					}
					else break;
				}
				else if (dir5 && getX() - i >= 0 && getX() - i <= 7) {
					if (board[getX() - i][getY()].getIsEmpty()) {
						dir5X = getX() - i;
						continue;
					}
					else break;
				}
				else if (dir6 && getX() - i >= 0 && getX() - i <= 7 && getY() + i >= 0 && getY() + i <= 7) {
					if (board[getX() - i][getY() + i].getIsEmpty()) {
						dir6X = getX() - i;
						dir6Y = getY() + i;
						continue;
					}
					else break;
				}
				else if (dir7 && getY() + i >= 0 && getY() + i <= 7) {
					if (board[getX()][getY() + i].getIsEmpty()) {
						dir7Y = getY() + i;
						continue;
					}
					else break;
				}
				else if (dir8 && getX() + i >= 0 && getX() + i <= 7 && getY() + i >= 0 && getY() + i <= 7) {
					if (board[getX() + i][getY() + i].getIsEmpty()) {
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

	bool ConditionOfCapture(const Square& square) override {
		if (!g_gameIsStopped && getIsSelected() && !square.getIsEmpty() && square.getColor() != g_turn && getColor() == g_turn) {
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

			if (abs(square.getX() - getX()) == abs(square.getY() - getY())) { // äèàãîíàëè
				if (square.getX() > getX() && square.getY() < getY())  dir2 = true;
				else if (square.getX() < getX() && square.getY() < getY())  dir4 = true;
				else if (square.getX() < getX() && square.getY() > getY())  dir6 = true;
				else if (square.getX() > getX() && square.getY() > getY())  dir8 = true;
			}
			else { // ãîðèçîíòàëè è âåðòèêàëè
				if (square.getX() > getX() && square.getY() == getY()) dir1 = true;
				else if (square.getX() == getX() && square.getY() < getY()) dir3 = true;
				else if (square.getX() < getX() && square.getY() == getY()) dir5 = true;
				else if (square.getX() == getX() && square.getY() > getY()) dir7 = true;
			}

			for (int i = 1; i < 8; ++i)
			{
				if (dir1 && getX() + i >= 0 && getX() + i <= 7) {
					dir1X = getX() + i;
					if (board[getX() + i][getY()].getIsEmpty()) continue; else break;
				}
				else if (dir2 && getX() + i >= 0 && getX() + i <= 7 && getY() - i >= 0 && getY() - i <= 7) {
					dir2X = getX() + i;
					dir2Y = getY() - i;
					if (board[getX() + i][getY() - i].getIsEmpty()) continue; else break;
				}
				else if (dir3 && getY() - i >= 0 && getY() - i <= 7) {
					dir3Y = getY() - i;
					if (board[getX()][getY() - i].getIsEmpty()) continue; else break;
				}
				else if (dir4 && getX() - i >= 0 && getX() - i <= 7 && getY() - i >= 0 && getY() - i <= 7) {
					dir4X = getX() - i;
					dir4Y = getY() - i;
					if (board[getX() - i][getY() - i].getIsEmpty()) continue; else break;
				}
				else if (dir5 && getX() - i >= 0 && getX() - i <= 7) {
					dir5X = getX() - i;
					if (board[getX() - i][getY()].getIsEmpty()) continue; else break;
				}
				else if (dir6 && getX() - i >= 0 && getX() - i <= 7 && getY() + i >= 0 && getY() + i <= 7) {
					dir6X = getX() - i;
					dir6Y = getY() + i;
					if (board[getX() - i][getY() + i].getIsEmpty()) continue; else break;
				}
				else if (dir7 && getY() + i >= 0 && getY() + i <= 7) {
					dir7Y = getY() + i;
					if (board[getX()][getY() + i].getIsEmpty()) continue; else break;
				}
				else if (dir8 && getX() + i >= 0 && getX() + i <= 7 && getY() + i >= 0 && getY() + i <= 7) {
					dir8X = getX() + i;
					dir8Y = getY() + i;
					if (board[getX() + i][getY() + i].getIsEmpty()) continue; else break;
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

	bool ConditionOfCastling(const Square& square) override { return false; }

	void Castling_(const Square& square) { return; }
public:
	Queen(const Square& square, const bool& color) : AbstractChessPiece(square, color) {
		sprite.setOrigin(42, 45);
		setName(color ? "QueenB" : "QueenW");
		sprite.setTexture(*textureOfPieces[getName()]);
	}
};

class King : public AbstractChessPiece {
	bool ConditionOfMove(const Square& square) override {
		return (!g_gameIsStopped && getIsSelected() && square.getIsEmpty() && abs(square.getX() - getX()) <= 1 && abs(square.getY() - getY()) <= 1 && getColor() == g_turn);
	}

	bool ConditionOfCapture(const Square& square) override {
		return (!g_gameIsStopped && getIsSelected() && !square.getIsEmpty() && abs(square.getX() - getX()) <= 1 && abs(square.getY() - getY()) <= 1
			&& (square.getX() != getX() || square.getY() != getY()) && square.getColor() != g_turn && getColor() == g_turn);
	}

	bool ConditionOfCastling(const Square& square) override {
		if (!g_gameIsStopped && getIsSelected() && !square.getIsEmpty() && getFirstMove() && getY() == square.getY()) {
			bool shortÑastling = false, distantCastling = false;
			int shortÑastlingX = getX(), distantCastlingX = getX();
			for (auto& piece : pieces) {
				if (piece->getFirstMove() && piece->getX() == square.getX() && piece->getY() == square.getY() && (getColor() ? piece->getName() == "CastleB" : piece->getName() == "CastleW")) {
					if (piece->getX() > getX()) shortÑastling = true;
					else if (piece->getX() < getX()) distantCastling = true;

					for (int i = 1; i < 8; ++i)
					{
						if (shortÑastling && getX() + i >= 0 && getX() + i <= 7) {
							shortÑastlingX = getX() + i;
							if (board[shortÑastlingX][getY()].getIsEmpty()) continue; else break;
						}
						if (distantCastling && getX() - i >= 0 && getX() - i <= 7) {
							distantCastlingX = getX() - i;
							if (board[distantCastlingX][getY()].getIsEmpty()) continue; else break;
						}
					}
					return ((shortÑastling && square.getX() == shortÑastlingX) || (distantCastling && square.getX() == distantCastlingX));
				}
			}
		}
		return false;
	}

	void Castling_(const Square& square) {
		int newX = getX() + (square.getX() > getX() ? 2 : -2);
		board[getX()][getY()].setIsEmpty(true);
		board[newX][getY()].setIsEmpty(false);
		board[getX()][getY()].setColor(!getColor());
		board[newX][getY()].setColor(getColor());

		setFirstMove(false);
		setX(newX);
		setPosition(board[getX()][getY()].getXInPixel(), board[getX()][getY()].getYInPixel());

		AbstractChessPiece* piece = FindPiece(square);
		if (piece->getX() == square.getX() && piece->getY() == square.getY()) {
			int newThisPieceX = getX() + (getX() < piece->getX() ? -1 : 1);
			board[square.getX()][getY()].setIsEmpty(true);
			board[newThisPieceX][getY()].setIsEmpty(false);
			piece->setX(newThisPieceX);
			piece->setPosition(board[piece->getX()][getY()].getXInPixel(), board[piece->getX()][getY()].getYInPixel());
			piece->setFirstMove(false);
		}

		g_turn = !g_turn;
		window.setTitle(g_turn ? "Chess: turn of black" : "Chess: turn of white");
	}

public:
	King(const Square& square, const bool& color) : AbstractChessPiece(square, color) {
		sprite.setOrigin(42, 44);
		setName(color ? "KingB" : "KingW");
		sprite.setTexture(*textureOfPieces[getName()]);
	}
};
