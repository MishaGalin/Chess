extern GameData game;
extern Board board;
extern vector<unique_ptr<AbstractChessPiece>> pieces;
extern AbstractChessPiece* FindPiece(const Square& square);

class Pawn : public AbstractChessPiece {
	bool ConditionOfMove(const Square& newSquare) override {
		return (!game.isFinished and !game.pawnIsPromotion and newSquare.getIsEmpty() and isSelected and x == newSquare.getX() and color == game.turn
			and ((pow(-1, color) * (y - newSquare.getY()) == 2 and board.squares[x][int(y - pow(-1, color))].getIsEmpty() and getFirstMove())
				or pow(-1, color) * (y - newSquare.getY()) == 1));
	};

	bool ConditionOfCapture(const Square& newSquare) override {
		return (!game.isFinished and !game.pawnIsPromotion and isSelected and !newSquare.getIsEmpty() and color == game.turn and newSquare.getColor() != game.turn
			and pow(-1, color) * (y - newSquare.getY()) == 1 and abs(x - newSquare.getX()) == 1);
	}

	bool ConditionOfCastling(const Square& newSquare) override { return false; }
	void Castling_(const Square& square) {}

public:
	Pawn(Square& square, bool color) : AbstractChessPiece(square, color) {
		name = color ? "PawnB" : "PawnW";
		sprite.setTexture(*game.textureOfPieces[name]);
		sprite.setOrigin(round(getGlobalBounds().width / 2), round(getGlobalBounds().height / 2));
	}
};

class Castle : public AbstractChessPiece {
	bool ConditionOfMove(const Square& newSquare) override {
		if (!game.isFinished and isSelected and isSelected and color == game.turn and !game.pawnIsPromotion and newSquare.getIsEmpty()) {
			int tempX = x, tempY = y,
				dir = 0; // direction

			if (newSquare.getX() == x and newSquare.getY() < y)      dir = 1;
			else if (newSquare.getX() < x and newSquare.getY() == y) dir = 2;
			else if (newSquare.getX() == x and newSquare.getY() > y) dir = 3;
			else if (newSquare.getX() > x and newSquare.getY() == y) dir = 4;

			for (int i = 1; i < 8; ++i)
			{
				if (dir == 1 and y - i >= 0) {
					if (board.squares[x][y - i].getIsEmpty()) tempY = y - i; else break;
				}
				else if (dir == 2 and x - i >= 0) {
					if (board.squares[x - i][y].getIsEmpty()) tempX = x - i; else break;
				}
				else if (dir == 3 and y + i <= 7) {
					if (board.squares[x][y + i].getIsEmpty()) tempY = y + i; else break;
				}
				else if (dir == 4 and x + i <= 7) {
					if (board.squares[x + i][y].getIsEmpty()) tempX = x + i; else break;
				}
			}
			return ((dir == 1 and newSquare.getY() >= tempY) or
				(dir == 2 and newSquare.getX() >= tempX) or
				(dir == 3 and newSquare.getY() <= tempY) or
				(dir == 4 and newSquare.getX() <= tempX));
		}
		return false;
	}

	bool ConditionOfCapture(const Square& newSquare) override {
		if (!game.isFinished and !game.pawnIsPromotion and isSelected and !newSquare.getIsEmpty() and newSquare.getColor() != game.turn and color == game.turn) {
			int tempX = x, tempY = y,
				dir = 0; // direction

			if (newSquare.getX() == x and newSquare.getY() < y)      dir = 1;
			else if (newSquare.getX() < x and newSquare.getY() == y) dir = 2;
			else if (newSquare.getX() == x and newSquare.getY() > y) dir = 3;
			else if (newSquare.getX() > x and newSquare.getY() == y) dir = 4;

			for (int i = 1; i < 8; ++i)
			{
				if (dir == 1 and y - i >= 0) {
					tempY = y - i;
					if (board.squares[x][tempY].getIsEmpty()) continue; else break;
				}
				else if (dir == 2 and x - i >= 0) {
					tempX = x - i;
					if (board.squares[tempX][y].getIsEmpty()) continue; else break;
				}
				else if (dir == 3 and y + i <= 7) {
					tempY = y + i;
					if (board.squares[x][tempY].getIsEmpty()) continue; else break;
				}
				else if (dir == 4 and x + i <= 7) {
					tempX = x + i;
					if (board.squares[tempX][y].getIsEmpty()) continue; else break;
				}
			}
			return ((dir == 1 and newSquare.getY() == tempY)
				or (dir == 2 and newSquare.getX() == tempX)
				or (dir == 3 and newSquare.getY() == tempY)
				or (dir == 4 and newSquare.getX() == tempX));
		}
		return false;
	}

	bool ConditionOfCastling(const Square& newSquare) override {
		if (!game.isFinished and !game.pawnIsPromotion and color == game.turn and isSelected and !newSquare.getIsEmpty() and getFirstMove() and y == newSquare.getY() and newSquare.getColor() == game.turn) {
			bool shortÑastling = false, distantCastling = false;
			int tempX = x;
			AbstractChessPiece* piece = FindPiece(newSquare);
			if (piece->getFirstMove() and (piece->getName() == "KingB" or piece->getName() == "KingW")) {
				piece->getX() > x ? shortÑastling = true : distantCastling = true;

				for (int i = 1; i < 8; ++i) {
					if (shortÑastling and x + i <= 7) {
						tempX = x + i;
						if (board.squares[tempX][y].getIsEmpty()) continue;
						else break;
					}
					else if (distantCastling and x - i >= 0) {
						tempX = x - i;
						if (board.squares[tempX][y].getIsEmpty()) continue;
						else break;
					}
				}
				return newSquare.getX() == tempX;
			}
		}
		return false;
	}

	void Castling_(const Square& square) {
		Move_(board.squares[x + (square.getX() > x ? 3 : -2)][y]);

		AbstractChessPiece* piece = FindPiece(square);
		piece->Move_(board.squares[x + (piece->getX() > x ? -1 : 1)][y]);
	}

public:
	Castle(Square& square, bool color) : AbstractChessPiece(square, color) {
		name = color ? "CastleB" : "CastleW";
		sprite.setTexture(*game.textureOfPieces[name]);
		sprite.setOrigin(round(getGlobalBounds().width / 2), round(getGlobalBounds().height / 2));
	}
};

class Knight : public AbstractChessPiece {
	bool ConditionOfMove(const Square& newSquare) override {
		return (!game.isFinished and !game.pawnIsPromotion and isSelected and newSquare.getIsEmpty() and color == game.turn
			and abs((x - newSquare.getX()) * (y - newSquare.getY())) == 2);
	}

	bool ConditionOfCapture(const Square& newSquare) override {
		return (!game.isFinished and !game.pawnIsPromotion and isSelected and !newSquare.getIsEmpty() and newSquare.getColor() != color and color == game.turn
			and abs((x - newSquare.getX()) * (y - newSquare.getY())) == 2);
	}

	bool ConditionOfCastling(const Square& newSquare) override { return false; }
	void Castling_(const Square& square) {}

public:
	Knight(Square& square, bool color) : AbstractChessPiece(square, color) {
		name = color ? "KnightB" : "KnightW";
		sprite.setTexture(*game.textureOfPieces[name]);
		sprite.setOrigin(round(getGlobalBounds().width / 2), round(getGlobalBounds().height / 2));
	}
};

class Bishop : public AbstractChessPiece {
	bool ConditionOfMove(const Square& newSquare) override {
		if (!game.isFinished and !game.pawnIsPromotion and isSelected and newSquare.getIsEmpty() and abs(newSquare.getX() - x) == abs(newSquare.getY() - y) and color == game.turn) {
			int tempX = x, tempY = y,
				dir = 0; // direction

			if (newSquare.getX() > x and newSquare.getY() < y)      dir = 1;
			else if (newSquare.getX() < x and newSquare.getY() < y) dir = 2;
			else if (newSquare.getX() < x and newSquare.getY() > y) dir = 3;
			else if (newSquare.getX() > x and newSquare.getY() > y) dir = 4;

			for (int i = 1; i < 8; ++i)
			{
				if (dir == 1 and x + i <= 7 and y - i >= 0) {
					if (board.squares[x + i][y - i].getIsEmpty()) {
						tempX = x + i;
						tempY = y - i;
					}
					else break;
				}
				else if (dir == 2 and x - i >= 0 and y - i >= 0) {
					if (board.squares[x - i][y - i].getIsEmpty()) {
						tempX = x - i;
						tempY = y - i;
					}
					else break;
				}
				else if (dir == 3 and x - i >= 0 and y + i <= 7) {
					if (board.squares[x - i][y + i].getIsEmpty()) {
						tempX = x - i;
						tempY = y + i;
					}
					else break;
				}
				else if (dir == 4 and x + i <= 7 and y + i <= 7) {
					if (board.squares[x + i][y + i].getIsEmpty()) {
						tempX = x + i;
						tempY = y + i;
					}
					else break;
				}
			}

			return ((dir == 1 and newSquare.getX() <= tempX and newSquare.getY() >= tempY) or
				(dir == 2 and newSquare.getX() >= tempX and newSquare.getY() >= tempY) or
				(dir == 3 and newSquare.getX() >= tempX and newSquare.getY() <= tempY) or
				(dir == 4 and newSquare.getX() <= tempX and newSquare.getY() <= tempY));
		}
		return false;
	}

	bool ConditionOfCapture(const Square& newSquare) override {
		if (!game.isFinished and !game.pawnIsPromotion and isSelected and !newSquare.getIsEmpty() and abs(newSquare.getX() - x) == abs(newSquare.getY() - y) and newSquare.getColor() != game.turn and color == game.turn) {
			int tempX = x, tempY = y,
				dir = 0; // direction

			if (newSquare.getX() > x and newSquare.getY() < y)      dir = 1;
			else if (newSquare.getX() < x and newSquare.getY() < y) dir = 2;
			else if (newSquare.getX() < x and newSquare.getY() > y) dir = 3;
			else if (newSquare.getX() > x and newSquare.getY() > y) dir = 4;

			for (int i = 1; i < 8; ++i)
			{
				if (dir == 1 and x + i <= 7 and y - i >= 0) {
					tempX = x + i;
					tempY = y - i;
					if (board.squares[tempX][tempY].getIsEmpty()) continue;
					else break;
				}
				else if (dir == 2 and x - i >= 0 and y - i >= 0) {
					tempX = x - i;
					tempY = y - i;
					if (board.squares[tempX][tempY].getIsEmpty()) continue;
					else break;
				}
				else if (dir == 3 and x - i >= 0 and y + i <= 7) {
					tempX = x - i;
					tempY = y + i;
					if (board.squares[tempX][tempY].getIsEmpty()) continue;
					else break;
				}
				else if (dir == 4 and x + i <= 7 and y + i <= 7) {
					tempX = x + i;
					tempY = y + i;
					if (board.squares[tempX][tempY].getIsEmpty()) continue;
					else break;
				}
			}
			return ((dir == 1 and newSquare.getX() == tempX and newSquare.getY() == tempY)
				or (dir == 2 and newSquare.getX() == tempX and newSquare.getY() == tempY)
				or (dir == 3 and newSquare.getX() == tempX and newSquare.getY() == tempY)
				or (dir == 4 and newSquare.getX() == tempX and newSquare.getY() == tempY));
		}
		return false;
	}

	bool ConditionOfCastling(const Square& newSquare) override { return false; }
	void Castling_(const Square& square) {}

public:
	Bishop(Square& square, bool color) : AbstractChessPiece(square, color) {
		name = color ? "BishopB" : "BishopW";
		sprite.setTexture(*game.textureOfPieces[name]);
		sprite.setOrigin(round(getGlobalBounds().width / 2), round(getGlobalBounds().height / 2));
	}
};

class Queen : public AbstractChessPiece {
	bool ConditionOfMove(const Square& newSquare) override {
		if (!game.isFinished and !game.pawnIsPromotion and isSelected and newSquare.getIsEmpty() and color == game.turn) {
			int	tempX = x, tempY = y,
				dir = 0; // direction

			if (abs(newSquare.getX() - x) == abs(newSquare.getY() - y)) { // diagonals
				if (newSquare.getX() > x and newSquare.getY() < y)       dir = 2;
				else if (newSquare.getX() < x and newSquare.getY() < y)  dir = 4;
				else if (newSquare.getX() < x and newSquare.getY() > y)  dir = 6;
				else if (newSquare.getX() > x and newSquare.getY() > y)  dir = 8;
			}
			else { // horizontal and vertical
				if (newSquare.getX() > x and newSquare.getY() == y)      dir = 1;
				else if (newSquare.getX() == x and newSquare.getY() < y) dir = 3;
				else if (newSquare.getX() < x and newSquare.getY() == y) dir = 5;
				else if (newSquare.getX() == x and newSquare.getY() > y) dir = 7;
			}

			for (int i = 1; i < 8; ++i)
			{
				if (dir == 1 and x + i <= 7) {
					if (board.squares[x + i][y].getIsEmpty()) {
						tempX = x + i;
						continue;
					}
					else break;
				}
				else if (dir == 2 and x + i <= 7 and y - i >= 0) {
					if (board.squares[x + i][y - i].getIsEmpty()) {
						tempX = x + i;
						tempY = y - i;
						continue;
					}
					else break;
				}
				else if (dir == 3 and y - i >= 0) {
					if (board.squares[x][y - i].getIsEmpty()) {
						tempY = y - i;
						continue;
					}
					else break;
				}
				else if (dir == 4 and x - i >= 0 and y - i >= 0) {
					if (board.squares[x - i][y - i].getIsEmpty()) {
						tempX = x - i;
						tempY = y - i;
						continue;
					}
					else break;
				}
				else if (dir == 5 and x - i >= 0) {
					if (board.squares[x - i][y].getIsEmpty()) {
						tempX = x - i;
						continue;
					}
					else break;
				}
				else if (dir == 6 and x - i >= 0 and y + i <= 7) {
					if (board.squares[x - i][y + i].getIsEmpty()) {
						tempX = x - i;
						tempY = y + i;
						continue;
					}
					else break;
				}
				else if (dir == 7 and y + i <= 7) {
					if (board.squares[x][y + i].getIsEmpty()) {
						tempY = y + i;
						continue;
					}
					else break;
				}
				else if (dir == 8 and x + i <= 7 and y + i <= 7) {
					if (board.squares[x + i][y + i].getIsEmpty()) {
						tempX = x + i;
						tempY = y + i;
						continue;
					}
					else break;
				}
			}

			return ((dir == 1 and newSquare.getX() <= tempX)
				or (dir == 2 and newSquare.getX() <= tempX and newSquare.getY() >= tempY)
				or (dir == 3 and newSquare.getY() >= tempY)
				or (dir == 4 and newSquare.getX() >= tempX and newSquare.getY() >= tempY)
				or (dir == 5 and newSquare.getX() >= tempX)
				or (dir == 6 and newSquare.getX() >= tempX and newSquare.getY() <= tempY)
				or (dir == 7 and newSquare.getY() <= tempY)
				or (dir == 8 and newSquare.getX() <= tempX and newSquare.getY() <= tempY));
		}
		return false;
	}

	bool ConditionOfCapture(const Square& newSquare) override {
		if (!game.isFinished and !game.pawnIsPromotion and isSelected and !newSquare.getIsEmpty() and newSquare.getColor() != game.turn and color == game.turn) {
			int	tempX = x, tempY = y,
				dir = 0;  // direction

			if (abs(newSquare.getX() - x) == abs(newSquare.getY() - y)) { // diagonals
				if (newSquare.getX() > x and newSquare.getY() < y)       dir = 2;
				else if (newSquare.getX() < x and newSquare.getY() < y)  dir = 4;
				else if (newSquare.getX() < x and newSquare.getY() > y)  dir = 6;
				else if (newSquare.getX() > x and newSquare.getY() > y)  dir = 8;
			}
			else { // horizontal and vertical
				if (newSquare.getX() > x and newSquare.getY() == y)      dir = 1;
				else if (newSquare.getX() == x and newSquare.getY() < y) dir = 3;
				else if (newSquare.getX() < x and newSquare.getY() == y) dir = 5;
				else if (newSquare.getX() == x and newSquare.getY() > y) dir = 7;
			}

			for (int i = 1; i < 8; ++i)
			{
				if (dir == 1 and x + i <= 7) {
					tempX = x + i;
					if (board.squares[tempX][y].getIsEmpty()) continue;
					else break;
				}
				else if (dir == 2 and x + i <= 7 and y - i >= 0) {
					tempX = x + i;
					tempY = y - i;
					if (board.squares[tempX][tempY].getIsEmpty()) continue;
					else break;
				}
				else if (dir == 3 and y - i >= 0) {
					tempY = y - i;
					if (board.squares[x][tempY].getIsEmpty()) continue;
					else break;
				}
				else if (dir == 4 and x - i >= 0 and y - i >= 0) {
					tempX = x - i;
					tempY = y - i;
					if (board.squares[tempX][tempY].getIsEmpty()) continue;
					else break;
				}
				else if (dir == 5 and x - i >= 0) {
					tempX = x - i;
					if (board.squares[tempX][y].getIsEmpty()) continue;
					else break;
				}
				else if (dir == 6 and x - i >= 0 and y + i <= 7) {
					tempX = x - i;
					tempY = y + i;
					if (board.squares[tempX][tempY].getIsEmpty()) continue;
					else break;
				}
				else if (dir == 7 and y + i <= 7) {
					tempY = y + i;
					if (board.squares[x][tempY].getIsEmpty()) continue;
					else break;
				}
				else if (dir == 8 and x + i <= 7 and y + i <= 7) {
					tempX = x + i;
					tempY = y + i;
					if (board.squares[tempX][tempY].getIsEmpty()) continue;
					else break;
				}
				else break;
			}

			return ((dir == 1 and newSquare.getX() == tempX)
				or (dir == 2 and newSquare.getX() == tempX and newSquare.getY() == tempY)
				or (dir == 3 and newSquare.getY() == tempY)
				or (dir == 4 and newSquare.getX() == tempX and newSquare.getY() == tempY)
				or (dir == 5 and newSquare.getX() == tempX)
				or (dir == 6 and newSquare.getX() == tempX and newSquare.getY() == tempY)
				or (dir == 7 and newSquare.getY() == tempY)
				or (dir == 8 and newSquare.getX() == tempX and newSquare.getY() == tempY));
		}
		return false;
	}

	bool ConditionOfCastling(const Square& newSquare) override { return false; }
	void Castling_(const Square& square) {}

public:
	Queen(Square& square, bool color) : AbstractChessPiece(square, color) {
		name = color ? "QueenB" : "QueenW";
		sprite.setTexture(*game.textureOfPieces[name]);
		sprite.setOrigin(round(getGlobalBounds().width / 2), round(getGlobalBounds().height / 2));
	}
};

class King : public AbstractChessPiece {
	bool ConditionOfMove(const Square& newSquare) override {
		return (!game.isFinished and !game.pawnIsPromotion and isSelected and color == game.turn and newSquare.getIsEmpty()
			and abs(newSquare.getX() - x) <= 1 and abs(newSquare.getY() - y) <= 1);
	}

	bool ConditionOfCapture(const Square& newSquare) override {
		return (!game.isFinished and !game.pawnIsPromotion and isSelected and !newSquare.getIsEmpty() and newSquare.getColor() != game.turn and color == game.turn
			and abs(newSquare.getX() - x) <= 1 and abs(newSquare.getY() - y) <= 1);
	}

	bool ConditionOfCastling(const Square& newSquare) override {
		if (!game.isFinished and !game.pawnIsPromotion and color == game.turn and isSelected and !newSquare.getIsEmpty() and getFirstMove() and y == newSquare.getY() and newSquare.getColor() == game.turn) {
			bool shortÑastling = false, distantCastling = false;
			int tempX = x;

			AbstractChessPiece* piece = FindPiece(newSquare);
			if (piece->getFirstMove() and (piece->getName() == "CastleB" or piece->getName() == "CastleW")) {
				piece->getX() > x ? shortÑastling = true : distantCastling = true;

				for (int i = 1; i < 8; ++i) {
					if (shortÑastling and x + i <= 7) {
						tempX = x + i;
						if (board.squares[tempX][y].getIsEmpty()) continue;
						else break;
					}
					else if (distantCastling and x - i >= 0) {
						tempX = x - i;
						if (board.squares[tempX][y].getIsEmpty()) continue;
						else break;
					}
				}
				return newSquare.getX() == tempX;
			}
		}
		return false;
	}

	void Castling_(const Square& square) {
		Move_(board.squares[x + (square.getX() > x ? 2 : -2)][y]);

		AbstractChessPiece* piece = FindPiece(square);
		piece->Move_(board.squares[x + (x < piece->getX() ? -1 : 1)][y]);
	}

public:
	King(Square& square, bool color) : AbstractChessPiece(square, color) {
		name = color ? "KingB" : "KingW";
		sprite.setTexture(*game.textureOfPieces[name]);
		sprite.setOrigin(round(getGlobalBounds().width / 2), round(getGlobalBounds().height / 2));
	}
};