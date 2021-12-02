extern Game game;
extern RenderWindow window;
extern Board board;
extern void DeletePiece(Square& square);

class AbstractChessPiece : public Drawable {
	bool color = false; // 0 - white, 1 - black
	bool firstMove = true, isSelected = false, isPromotion = false, isMovable = true, isMove = false;
	int x = 0, y = 0, ID = 0;
	string name = "";

	virtual bool ConditionOfMove(const Square& square) = 0;
	virtual bool ConditionOfCapture(const Square& square) = 0;
	virtual bool ConditionOfCastling(const Square& square) = 0;
	virtual void Castling_(const Square& square) = 0;

protected:
	Sprite sprite;

	AbstractChessPiece(Square& square, const bool& color) {
		setPosition(square.getInPixel());
		setColor(color);
		square.setColor(color);
		square.setIsEmpty(false);
		setX(square.getX());
		setY(square.getY());
	}

	void Changeover(Square& newSquare) {
		board.Squares[x][y].setIsEmpty(true);
		newSquare.setIsEmpty(false);

		board.Squares[x][y].setColor(!getColor());
		newSquare.setColor(getColor());
	}

public:
	// Directly moving from one square to another
	void Move_(Square& newSquare) {
		Changeover(newSquare);

		setFirstMove(false);
		setX(newSquare.getX());
		setY(newSquare.getY());
		setPosition(newSquare.getInPixel());
	};

	void draw(RenderTarget& target, RenderStates states = RenderStates::Default) const { target.draw(sprite, states); }

	void ReturnToPrevPos() { setPosition(board.Squares[x][y].getInPixel()); };

	void Move(Square& newSquare) {
		if (ConditionOfMove(newSquare)) {
			Move_(newSquare);

			if ((getName() == "PawnW" and getY() == 0) or (getName() == "PawnB" and getY() == 7)) {
				IntRect tepmRect(Vector2i(0, 0), Vector2i(112, 112));

				sprite.setTextureRect(tepmRect);
				sprite.setTexture(*game.textureOfPieces[getColor() ? "choiceB" : "choiceW"]);
				sprite.setOrigin(56, 56);

				isPromotion = true;
				isMovable = false;
				game.pawnIsPromotion = true;
				return;
			}

			game.ChangeOfTurn();
		}
		else ReturnToPrevPos();
	}

	void Capture(Square& newSquare) {
		if (ConditionOfCapture(newSquare)) {
			DeletePiece(newSquare);
			Move_(newSquare);

			if ((getName() == "PawnW" and getY() == 0) or (getName() == "PawnB" and getY() == 7)) {
				IntRect tepmRect(Vector2i(0, 0), Vector2i(112, 112));

				sprite.setTextureRect(tepmRect);
				sprite.setTexture(*game.textureOfPieces[getColor() ? "choiceB" : "choiceW"]);
				sprite.setOrigin(56, 56);

				isPromotion = true;
				isMovable = false;
				game.pawnIsPromotion = true;
				return;
			}

			game.ChangeOfTurn();
		}
		else ReturnToPrevPos();
	}

	void Castling(Square& newSquare) {
		if (ConditionOfCastling(newSquare)) {
			Castling_(newSquare);
			game.ChangeOfTurn();
		}
		else ReturnToPrevPos();
	}

	Square* SearchNearestSquare() {
		double maxDistance = 10000., distance = 0.;
		int nearestX = 0, nearestY = 0;

		for (int i = 0; i < Board::Size; ++i) {
			for (int j = 0; j < Board::Size; ++j) {
				distance = sqrt(pow(game.mousePos.x - board.Squares[i][j].getXInPixel(), 2) + pow(game.mousePos.y - board.Squares[i][j].getYInPixel(), 2)); // Distance to the square
				if (distance < maxDistance) {
					maxDistance = distance;
					nearestX = i;
					nearestY = j;
				}
			}
		}
		return &board.Squares[nearestX][nearestY];
	}

	// Displaying the squares into which the piece can go
	void DrawPossibleSquares() {
		for (int i = 0; i < Board::Size; ++i) {
			for (int j = 0; j < Board::Size; ++j) {
				if (ConditionOfMove(board.Squares[i][j]))          board.Squares[i][j].drawWithColor(Color(0, 255, 0, 60)); // Green square if you can go to this square
				else if (ConditionOfCapture(board.Squares[i][j]))  board.Squares[i][j].drawWithColor(Color(255, 0, 0, 60)); // Red square if you can capture
				else if (ConditionOfCastling(board.Squares[i][j])) board.Squares[i][j].drawWithColor(Color(255, 255, 0, 60));
			}
		}
	}

	FloatRect getGlobalBounds() const { return sprite.getGlobalBounds(); }

	Vector2f getPosition() const { return sprite.getPosition(); }
	void setPosition(const int& x, const int& y) { sprite.setPosition(float(x), float(y)); }
	void setPosition(Vector2i newPos) { sprite.setPosition(float(newPos.x), float(newPos.y)); }

	// 0 - white, 1 - black
	bool getColor() const { return color; }
	void setColor(const bool& color) { this->color = color; }

	bool getIsPromotion() const { return isPromotion; }
	void setIsPromotion(const bool& isPromotion) { this->isPromotion = isPromotion; }

	bool getIsSelected() const { return isSelected; }
	void setIsSelected(const bool& isSelected) { this->isSelected = isSelected; }

	bool getIsMovable() const { return isMovable; }
	void setIsMovable(const bool& IsMovable) { this->isMovable = IsMovable; }

	bool getIsMove() const { return isMove; }
	void IsMove(const bool& IsMove) { this->isMove = IsMove; }

	bool getFirstMove() const { return firstMove; }
	void setFirstMove(const bool& firstMove) { this->firstMove = firstMove; }

	int getX() const { return x; }
	void setX(const int& x) { this->x = x; }

	int getY() const { return y; }
	void setY(const int& y) { this->y = y; }

	string getName() const { return name; }
	void setName(const string& name) { this->name = name; }
};
