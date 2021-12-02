extern Game game;
extern Board board;
extern vector<unique_ptr<AbstractChessPiece>> pieces;
extern AbstractChessPiece* FindPiece(const Square& square);

class Pawn : public AbstractChessPiece {
	bool ConditionOfMove(const Square& newSquare) override {
		return (!game.isFinished and !game.pawnIsPromotion and getIsSelected() and newSquare.getIsEmpty() and getX() == newSquare.getX() and getColor() == game.turn
			and ((pow(-1, getColor()) * (getY() - newSquare.getY()) == 2 and board.Squares[getX()][getY() - (pow(-1, getColor()) * 1)].getIsEmpty() and getFirstMove())
				or pow(-1, getColor()) * (getY() - newSquare.getY()) == 1));
	};

	bool ConditionOfCapture(const Square& newSquare) override {
		return (!game.isFinished and !game.pawnIsPromotion and getIsSelected() and !newSquare.getIsEmpty() and getColor() == game.turn and newSquare.getColor() != game.turn and
			pow(-1, getColor()) * (getY() - newSquare.getY()) == 1 and abs(getX() - newSquare.getX()) == 1);
	}

	bool ConditionOfCastling(const Square& newSquare) override { return false; }

	void Castling_(const Square& square) {}
public:
	Pawn(Square& square, const bool& color) : AbstractChessPiece(square, color) {
		sprite.setOrigin(25, 42);
		setName(color ? "PawnB" : "PawnW");
		sprite.setTexture(*game.textureOfPieces[getName()]);
	}
};

class Castle : public AbstractChessPiece {
	bool ConditionOfMove(const Square& newSquare) override {
		if (!game.isFinished and !game.pawnIsPromotion and getIsSelected() and newSquare.getIsEmpty() and getColor() == game.turn) {
			int dir1Y = getY(),
				dir2X = getX(),
				dir3Y = getY(),
				dir4X = getX(),
				dir = 0; // direction

			if (newSquare.getX() == getX() and newSquare.getY() < getY())      dir = 1;
			else if (newSquare.getX() < getX() and newSquare.getY() == getY()) dir = 2;
			else if (newSquare.getX() == getX() and newSquare.getY() > getY()) dir = 3;
			else if (newSquare.getX() > getX() and newSquare.getY() == getY()) dir = 4;

			for (int i = 1; i < 8; ++i)
			{
				if (dir == 1 and getY() - i >= 0 and getY() - i <= 7) {
					if (board.Squares[getX()][getY() - i].getIsEmpty()) dir1Y = getY() - i; else break;
				}
				else if (dir == 2 and getX() - i >= 0 and getX() - i <= 7) {
					if (board.Squares[getX() - i][getY()].getIsEmpty()) dir2X = getX() - i; else break;
				}
				else if (dir == 3 and getY() + i >= 0 and getY() + i <= 7) {
					if (board.Squares[getX()][getY() + i].getIsEmpty()) dir3Y = getY() + i; else break;
				}
				else if (dir == 4 and getX() + i >= 0 and getX() + i <= 7) {
					if (board.Squares[getX() + i][getY()].getIsEmpty()) dir4X = getX() + i; else break;
				}
			}
			return ((dir == 1 and newSquare.getY() >= dir1Y) or
				(dir == 2 and newSquare.getX() >= dir2X) or
				(dir == 3 and newSquare.getY() <= dir3Y) or
				(dir == 4 and newSquare.getX() <= dir4X));
		}
		return false;
	}

	bool ConditionOfCapture(const Square& newSquare) override {
		if (!game.isFinished and !game.pawnIsPromotion and getIsSelected() and !newSquare.getIsEmpty() and newSquare.getColor() != game.turn and getColor() == game.turn) {
			int dir1Y = getY(),
				dir2X = getX(),
				dir3Y = getY(),
				dir4X = getX(),
				dir = 0; // direction

			if (newSquare.getX() == getX() and newSquare.getY() < getY())      dir = 1;
			else if (newSquare.getX() < getX() and newSquare.getY() == getY()) dir = 2;
			else if (newSquare.getX() == getX() and newSquare.getY() > getY()) dir = 3;
			else if (newSquare.getX() > getX() and newSquare.getY() == getY()) dir = 4;

			for (int i = 1; i < 8; ++i)
			{
				if (dir == 1 and getY() - i >= 0 and getY() - i <= 7) {
					dir1Y = getY() - i;
					if (board.Squares[getX()][dir1Y].getIsEmpty()) continue; else break;
				}
				else if (dir == 2 and getX() - i >= 0 and getX() - i <= 7) {
					dir2X = getX() - i;
					if (board.Squares[dir2X][getY()].getIsEmpty()) continue; else break;
				}
				else if (dir == 3 and getY() + i >= 0 and getY() + i <= 7) {
					dir3Y = getY() + i;
					if (board.Squares[getX()][dir3Y].getIsEmpty()) continue; else break;
				}
				else if (dir == 4 and getX() + i >= 0 and getX() + i <= 7) {
					dir4X = getX() + i;
					if (board.Squares[dir4X][getY()].getIsEmpty()) continue; else break;
				}
			}
			return ((dir == 1 and newSquare.getY() == dir1Y)
				or (dir == 2 and newSquare.getX() == dir2X)
				or (dir == 3 and newSquare.getY() == dir3Y)
				or (dir == 4 and newSquare.getX() == dir4X));
		}
		return false;
	}

	bool ConditionOfCastling(const Square& newSquare) override {
		if (!game.isFinished and !game.pawnIsPromotion and getIsSelected() and !newSquare.getIsEmpty() and getFirstMove() and getY() == newSquare.getY()) {
			bool shortÑastling = false, distantCastling = false;
			int shortÑastlingX = getX(), distantCastlingX = getX();
			for (auto& piece : pieces) {
				if (piece->getFirstMove() and piece->getX() == newSquare.getX() and piece->getY() == newSquare.getY() and (getColor() ? piece->getName() == "KingB" : piece->getName() == "KingW")) {
					if (piece->getX() > getX()) shortÑastling = true;
					else if (piece->getX() < getX()) distantCastling = true;

					for (int i = 1; i < 8; ++i)
					{
						if (shortÑastling and getX() + i >= 0 and getX() + i <= 7) {
							shortÑastlingX = getX() + i;
							if (board.Squares[shortÑastlingX][getY()].getIsEmpty()) continue; else break;
						}
						if (distantCastling and getX() - i >= 0 and getX() - i <= 7) {
							distantCastlingX = getX() - i;
							if (board.Squares[distantCastlingX][getY()].getIsEmpty()) continue; else break;
						}
					}
					return ((shortÑastling and newSquare.getX() == shortÑastlingX) or (distantCastling and newSquare.getX() == distantCastlingX));
				}
			}
		}
		return false;
	}

	void Castling_(const Square& square) {
		int newX = getX() + (square.getX() > getX() ? 3 : -2);
		Move_(board.Squares[newX][getY()]);

		AbstractChessPiece* piece = FindPiece(square);
		int newThisPieceX = getX() + (square.getX() > getX() ? -1 : 1);
		piece->Move_(board.Squares[newThisPieceX][getY()]);
	}

public:
	Castle(Square& square, const bool& color) : AbstractChessPiece(square, color) {
		sprite.setOrigin(33, 43);
		setName(color ? "CastleB" : "CastleW");
		sprite.setTexture(*game.textureOfPieces[getName()]);
	}
};

class Knight : public AbstractChessPiece {
	bool ConditionOfMove(const Square& newSquare) override {
		return (!game.isFinished and !game.pawnIsPromotion and getIsSelected() and newSquare.getIsEmpty() and getColor() == game.turn
			and abs((getX() - newSquare.getX()) * (getY() - newSquare.getY())) == 2);
	}

	bool ConditionOfCapture(const Square& newSquare) override {
		return (!game.isFinished and !game.pawnIsPromotion and getIsSelected() and !newSquare.getIsEmpty() and newSquare.getColor() != getColor() and getColor() == game.turn
			and abs((getX() - newSquare.getX()) * (getY() - newSquare.getY())) == 2);
	}

	bool ConditionOfCastling(const Square& newSquare) override { return false; }

	void Castling_(const Square& square) {}
public:
	Knight(Square& square, const bool& color) : AbstractChessPiece(square, color) {
		sprite.setOrigin(37, 45);
		setName(color ? "KnightB" : "KnightW");
		sprite.setTexture(*game.textureOfPieces[getName()]);
	}
};

class Bishop : public AbstractChessPiece {
	bool ConditionOfMove(const Square& newSquare) override {
		if (!game.isFinished and !game.pawnIsPromotion and getIsSelected() and newSquare.getIsEmpty() and abs(newSquare.getX() - getX()) == abs(newSquare.getY() - getY()) and getColor() == game.turn) {
			int dir1X = getX(), dir1Y = getY(),
				dir2X = getX(), dir2Y = getY(),
				dir3X = getX(), dir3Y = getY(),
				dir4X = getX(), dir4Y = getY(),
				dir = 0; // direction

			if (newSquare.getX() > getX() and newSquare.getY() < getY())      dir = 1;
			else if (newSquare.getX() < getX() and newSquare.getY() < getY()) dir = 2;
			else if (newSquare.getX() < getX() and newSquare.getY() > getY()) dir = 3;
			else if (newSquare.getX() > getX() and newSquare.getY() > getY()) dir = 4;

			for (int i = 1; i < 8; ++i)
			{
				if (dir == 1 and getX() + i >= 0 and getX() + i <= 7 and getY() - i >= 0 and getY() - i <= 7) {
					if (board.Squares[getX() + i][getY() - i].getIsEmpty()) {
						dir1X = getX() + i;
						dir1Y = getY() - i;
					}
					else break;
				}
				else if (dir == 2 and getX() - i >= 0 and getX() - i <= 7 and getY() - i >= 0 and getY() - i <= 7) {
					if (board.Squares[getX() - i][getY() - i].getIsEmpty()) {
						dir2X = getX() - i;
						dir2Y = getY() - i;
					}
					else break;
				}
				else if (dir == 3 and getX() - i >= 0 and getX() - i <= 7 and getY() + i >= 0 and getY() + i <= 7) {
					if (board.Squares[getX() - i][getY() + i].getIsEmpty()) {
						dir3X = getX() - i;
						dir3Y = getY() + i;
					}
					else break;
				}
				else if (dir == 4 and getX() + i >= 0 and getX() + i <= 7 and getY() + i >= 0 and getY() + i <= 7) {
					if (board.Squares[getX() + i][getY() + i].getIsEmpty()) {
						dir4X = getX() + i;
						dir4Y = getY() + i;
					}
					else break;
				}
			}

			return ((dir == 1 and newSquare.getX() <= dir1X and newSquare.getY() >= dir1Y) or
				(dir == 2 and newSquare.getX() >= dir2X and newSquare.getY() >= dir2Y) or
				(dir == 3 and newSquare.getX() >= dir3X and newSquare.getY() <= dir3Y) or
				(dir == 4 and newSquare.getX() <= dir4X and newSquare.getY() <= dir4Y));
		}
		return false;
	}

	bool ConditionOfCapture(const Square& newSquare) override {
		if (!game.isFinished and !game.pawnIsPromotion and getIsSelected() and !newSquare.getIsEmpty() and abs(newSquare.getX() - getX()) == abs(newSquare.getY() - getY()) and newSquare.getColor() != game.turn and getColor() == game.turn) {
			int dir1X = getX(), dir1Y = getY(),
				dir2X = getX(), dir2Y = getY(),
				dir3X = getX(), dir3Y = getY(),
				dir4X = getX(), dir4Y = getY(),
				dir = 0; // direction

			if (newSquare.getX() > getX() and newSquare.getY() < getY())      dir = 1;
			else if (newSquare.getX() < getX() and newSquare.getY() < getY()) dir = 2;
			else if (newSquare.getX() < getX() and newSquare.getY() > getY()) dir = 3;
			else if (newSquare.getX() > getX() and newSquare.getY() > getY()) dir = 4;

			for (int i = 1; i < 8; ++i)
			{
				if (dir == 1 and getX() + i >= 0 and getX() + i <= 7 and getY() - i >= 0 and getY() - i <= 7) {
					dir1X = getX() + i;
					dir1Y = getY() - i;
					if (board.Squares[dir1X][dir1Y].getIsEmpty()) continue;
					else break;
				}
				else if (dir == 2 and getX() - i >= 0 and getX() - i <= 7 and getY() - i >= 0 and getY() - i <= 7) {
					dir2X = getX() - i;
					dir2Y = getY() - i;
					if (board.Squares[dir2X][dir2Y].getIsEmpty()) continue;
					else break;
				}
				else if (dir == 3 and getX() - i >= 0 and getX() - i <= 7 and getY() + i >= 0 and getY() + i <= 7) {
					dir3X = getX() - i;
					dir3Y = getY() + i;
					if (board.Squares[dir3X][dir3Y].getIsEmpty()) continue;
					else break;
				}
				else if (dir == 4 and getX() + i >= 0 and getX() + i <= 7 and getY() + i >= 0 and getY() + i <= 7) {
					dir4X = getX() + i;
					dir4Y = getY() + i;
					if (board.Squares[dir4X][dir4Y].getIsEmpty()) continue;
					else break;
				}
			}
			return ((dir == 1 and newSquare.getX() == dir1X and newSquare.getY() == dir1Y)
				or (dir == 2 and newSquare.getX() == dir2X and newSquare.getY() == dir2Y)
				or (dir == 3 and newSquare.getX() == dir3X and newSquare.getY() == dir3Y)
				or (dir == 4 and newSquare.getX() == dir4X and newSquare.getY() == dir4Y));
		}
		return false;
	}

	bool ConditionOfCastling(const Square& newSquare) override { return false; }

	void Castling_(const Square& square) {}
public:
	Bishop(Square& square, const bool& color) : AbstractChessPiece(square, color) {
		sprite.setOrigin(42, 44);
		setName(color ? "BishopB" : "BishopW");
		sprite.setTexture(*game.textureOfPieces[getName()]);
	}
};

class Queen : public AbstractChessPiece {
	bool ConditionOfMove(const Square& newSquare) override {
		if (!game.isFinished and !game.pawnIsPromotion and getIsSelected() and newSquare.getIsEmpty() and getColor() == game.turn) {
			int dir1X = getX(),
				dir2X = getX(), dir2Y = getY(),
				dir3Y = getY(),
				dir4X = getX(), dir4Y = getY(),
				dir5X = getX(),
				dir6X = getX(), dir6Y = getY(),
				dir7Y = getY(),
				dir8X = getX(), dir8Y = getY(),
				dir = 0; // direction

			if (abs(newSquare.getX() - getX()) == abs(newSquare.getY() - getY())) { // diagonals
				if (newSquare.getX() > getX() and newSquare.getY() < getY())       dir = 2;
				else if (newSquare.getX() < getX() and newSquare.getY() < getY())  dir = 4;
				else if (newSquare.getX() < getX() and newSquare.getY() > getY())  dir = 6;
				else if (newSquare.getX() > getX() and newSquare.getY() > getY())  dir = 8;
			}
			else { // horizontal and vertical
				if (newSquare.getX() > getX() and newSquare.getY() == getY())      dir = 1;
				else if (newSquare.getX() == getX() and newSquare.getY() < getY()) dir = 3;
				else if (newSquare.getX() < getX() and newSquare.getY() == getY()) dir = 5;
				else if (newSquare.getX() == getX() and newSquare.getY() > getY()) dir = 7;
			}

			for (int i = 1; i < 8; ++i)
			{
				if (dir == 1 and getX() + i >= 0 and getX() + i <= 7) {
					if (board.Squares[getX() + i][getY()].getIsEmpty()) {
						dir1X = getX() + i;
						continue;
					}
					else break;
				}
				else if (dir == 2 and getX() + i >= 0 and getX() + i <= 7 and getY() - i >= 0 and getY() - i <= 7) {
					if (board.Squares[getX() + i][getY() - i].getIsEmpty()) {
						dir2X = getX() + i;
						dir2Y = getY() - i;
						continue;
					}
					else break;
				}
				else if (dir == 3 and getY() - i >= 0 and getY() - i <= 7) {
					if (board.Squares[getX()][getY() - i].getIsEmpty()) {
						dir3Y = getY() - i;
						continue;
					}
					else break;
				}
				else if (dir == 4 and getX() - i >= 0 and getX() - i <= 7 and getY() - i >= 0 and getY() - i <= 7) {
					if (board.Squares[getX() - i][getY() - i].getIsEmpty()) {
						dir4X = getX() - i;
						dir4Y = getY() - i;
						continue;
					}
					else break;
				}
				else if (dir == 5 and getX() - i >= 0 and getX() - i <= 7) {
					if (board.Squares[getX() - i][getY()].getIsEmpty()) {
						dir5X = getX() - i;
						continue;
					}
					else break;
				}
				else if (dir == 6 and getX() - i >= 0 and getX() - i <= 7 and getY() + i >= 0 and getY() + i <= 7) {
					if (board.Squares[getX() - i][getY() + i].getIsEmpty()) {
						dir6X = getX() - i;
						dir6Y = getY() + i;
						continue;
					}
					else break;
				}
				else if (dir == 7 and getY() + i >= 0 and getY() + i <= 7) {
					if (board.Squares[getX()][getY() + i].getIsEmpty()) {
						dir7Y = getY() + i;
						continue;
					}
					else break;
				}
				else if (dir == 8 and getX() + i >= 0 and getX() + i <= 7 and getY() + i >= 0 and getY() + i <= 7) {
					if (board.Squares[getX() + i][getY() + i].getIsEmpty()) {
						dir8X = getX() + i;
						dir8Y = getY() + i;
						continue;
					}
					else break;
				}
			}

			return ((dir == 1 and newSquare.getX() <= dir1X)
				or (dir == 2 and newSquare.getX() <= dir2X and newSquare.getY() >= dir2Y)
				or (dir == 3 and newSquare.getY() >= dir3Y)
				or (dir == 4 and newSquare.getX() >= dir4X and newSquare.getY() >= dir4Y)
				or (dir == 5 and newSquare.getX() >= dir5X)
				or (dir == 6 and newSquare.getX() >= dir6X and newSquare.getY() <= dir6Y)
				or (dir == 7 and newSquare.getY() <= dir7Y)
				or (dir == 8 and newSquare.getX() <= dir8X and newSquare.getY() <= dir8Y));
		}
		return false;
	}

	bool ConditionOfCapture(const Square& newSquare) override {
		if (!game.isFinished and !game.pawnIsPromotion and getIsSelected() and !newSquare.getIsEmpty() and newSquare.getColor() != game.turn and getColor() == game.turn) {
			int dir1X = getX(),
				dir2X = getX(), dir2Y = getY(),
				dir3Y = getY(),
				dir4X = getX(), dir4Y = getY(),
				dir5X = getX(),
				dir6X = getX(), dir6Y = getY(),
				dir7Y = getY(),
				dir8X = getX(), dir8Y = getY(),
				dir = 0;  // direction

			if (abs(newSquare.getX() - getX()) == abs(newSquare.getY() - getY())) { // diagonals
				if (newSquare.getX() > getX() and newSquare.getY() < getY())       dir = 2;
				else if (newSquare.getX() < getX() and newSquare.getY() < getY())  dir = 4;
				else if (newSquare.getX() < getX() and newSquare.getY() > getY())  dir = 6;
				else if (newSquare.getX() > getX() and newSquare.getY() > getY())  dir = 8;
			}
			else { // horizontal and vertical
				if (newSquare.getX() > getX() and newSquare.getY() == getY())      dir = 1;
				else if (newSquare.getX() == getX() and newSquare.getY() < getY()) dir = 3;
				else if (newSquare.getX() < getX() and newSquare.getY() == getY()) dir = 5;
				else if (newSquare.getX() == getX() and newSquare.getY() > getY()) dir = 7;
			}

			for (int i = 1; i < 8; ++i)
			{
				if (dir == 1 and getX() + i >= 0 and getX() + i <= 7) {
					dir1X = getX() + i;
					if (board.Squares[dir1X][getY()].getIsEmpty()) continue;
					else break;
				}
				else if (dir == 2 and getX() + i >= 0 and getX() + i <= 7 and getY() - i >= 0 and getY() - i <= 7) {
					dir2X = getX() + i;
					dir2Y = getY() - i;
					if (board.Squares[dir2X][dir2Y].getIsEmpty()) continue;
					else break;
				}
				else if (dir == 3 and getY() - i >= 0 and getY() - i <= 7) {
					dir3Y = getY() - i;
					if (board.Squares[getX()][dir3Y].getIsEmpty()) continue;
					else break;
				}
				else if (dir == 4 and getX() - i >= 0 and getX() - i <= 7 and getY() - i >= 0 and getY() - i <= 7) {
					dir4X = getX() - i;
					dir4Y = getY() - i;
					if (board.Squares[dir4X][dir4Y].getIsEmpty()) continue;
					else break;
				}
				else if (dir == 5 and getX() - i >= 0 and getX() - i <= 7) {
					dir5X = getX() - i;
					if (board.Squares[dir5X][getY()].getIsEmpty()) continue;
					else break;
				}
				else if (dir == 6 and getX() - i >= 0 and getX() - i <= 7 and getY() + i >= 0 and getY() + i <= 7) {
					dir6X = getX() - i;
					dir6Y = getY() + i;
					if (board.Squares[dir6X][dir6Y].getIsEmpty()) continue;
					else break;
				}
				else if (dir == 7 and getY() + i >= 0 and getY() + i <= 7) {
					dir7Y = getY() + i;
					if (board.Squares[getX()][dir7Y].getIsEmpty()) continue;
					else break;
				}
				else if (dir == 8 and getX() + i >= 0 and getX() + i <= 7 and getY() + i >= 0 and getY() + i <= 7) {
					dir8X = getX() + i;
					dir8Y = getY() + i;
					if (board.Squares[dir8X][dir8Y].getIsEmpty()) continue;
					else break;
				}
				else break;
			}

			return ((dir == 1 and newSquare.getX() == dir1X)
				or (dir == 2 and newSquare.getX() == dir2X and newSquare.getY() == dir2Y)
				or (dir == 3 and newSquare.getY() == dir3Y)
				or (dir == 4 and newSquare.getX() == dir4X and newSquare.getY() == dir4Y)
				or (dir == 5 and newSquare.getX() == dir5X)
				or (dir == 6 and newSquare.getX() == dir6X and newSquare.getY() == dir6Y)
				or (dir == 7 and newSquare.getY() == dir7Y)
				or (dir == 8 and newSquare.getX() == dir8X and newSquare.getY() == dir8Y));
		}
		return false;
	}

	bool ConditionOfCastling(const Square& newSquare) override { return false; }

	void Castling_(const Square& square) {}
public:
	Queen(Square& square, const bool& color) : AbstractChessPiece(square, color) {
		sprite.setOrigin(42, 45);
		setName(color ? "QueenB" : "QueenW");
		sprite.setTexture(*game.textureOfPieces[getName()]);
	}
};

class King : public AbstractChessPiece {
	bool ConditionOfMove(const Square& newSquare) override {
		return (!game.isFinished and !game.pawnIsPromotion and getIsSelected() and newSquare.getIsEmpty()
			and abs(newSquare.getX() - getX()) <= 1 and abs(newSquare.getY() - getY()) <= 1 and getColor() == game.turn);
	}

	bool ConditionOfCapture(const Square& newSquare) override {
		return (!game.isFinished and !game.pawnIsPromotion and getIsSelected() and !newSquare.getIsEmpty() and newSquare.getColor() != game.turn and getColor() == game.turn
			and abs(newSquare.getX() - getX()) <= 1 and abs(newSquare.getY() - getY()) <= 1
			and (newSquare.getX() != getX() or newSquare.getY() != getY()));
	}

	bool ConditionOfCastling(const Square& newSquare) override {
		if (!game.isFinished and !game.pawnIsPromotion and getIsSelected() and !newSquare.getIsEmpty() and getFirstMove() and getY() == newSquare.getY() and getColor() == game.turn) {
			bool shortÑastling = false, distantCastling = false;
			int shortÑastlingX = getX(), distantCastlingX = getX();
			for (auto& piece : pieces) {
				if (piece->getFirstMove() and piece->getX() == newSquare.getX() and piece->getY() == newSquare.getY() and (getColor() ? piece->getName() == "CastleB" : piece->getName() == "CastleW")) {
					if (piece->getX() > getX()) shortÑastling = true;
					else if (piece->getX() < getX()) distantCastling = true;

					for (int i = 1; i < 8; ++i)
					{
						if (shortÑastling and getX() + i >= 0 and getX() + i <= 7) {
							shortÑastlingX = getX() + i;
							if (board.Squares[shortÑastlingX][getY()].getIsEmpty()) continue; else break;
						}
						if (distantCastling and getX() - i >= 0 and getX() - i <= 7) {
							distantCastlingX = getX() - i;
							if (board.Squares[distantCastlingX][getY()].getIsEmpty()) continue; else break;
						}
					}
					return ((shortÑastling and newSquare.getX() == shortÑastlingX) or (distantCastling and newSquare.getX() == distantCastlingX));
				}
			}
		}
		return false;
	}

	void Castling_(const Square& square) {
		int newX = getX() + (square.getX() > getX() ? 2 : -2);
		Move_(board.Squares[newX][getY()]);

		AbstractChessPiece* piece = FindPiece(square);
		int newThisPieceX = getX() + (getX() < piece->getX() ? -1 : 1);
		piece->Move_(board.Squares[newThisPieceX][getY()]);
	}

public:
	King(Square& square, const bool& color) : AbstractChessPiece(square, color) {
		sprite.setOrigin(42, 44);
		setName(color ? "KingB" : "KingW");
		sprite.setTexture(*game.textureOfPieces[getName()]);
	}
};