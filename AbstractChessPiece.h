extern Game game;
extern RenderWindow window;
extern Board board;
extern void DeletePiece(Square& square);

class AbstractChessPiece : public Drawable {
	virtual bool ConditionOfMove(const Square& square) = 0;
	virtual bool ConditionOfCapture(const Square& square) = 0;
	virtual bool ConditionOfCastling(const Square& square) = 0;
	virtual void Castling_(const Square& square) = 0;

protected:
	string name;
	bool color = false; // 0 - white, 1 - black
	bool firstMove = true, isSelected = false, isPromotion = false, isMovable = true, isMove = false;
	int x = 0, y = 0;
	Sprite sprite;

	AbstractChessPiece(Square& square, const bool& color) {
		this->color = color;
		x = square.getX();
		y = square.getY();
		setPosition(square.getInPixel());
		square.setColor(color);
		square.setIsEmpty(false);
	}

	void Changeover(Square& newSquare) {
		(*getSquare()).setIsEmpty(true);
		newSquare.setIsEmpty(false);

		(*getSquare()).setColor(!color);
		newSquare.setColor(color);
	}

public:
	// Directly moving from one square to another
	void Move_(Square& newSquare) {
		Changeover(newSquare);

		firstMove = false;
		setX(newSquare.getX());
		setY(newSquare.getY());
		setPosition(newSquare.getInPixel());
	};

	void draw(RenderTarget& target, RenderStates states = RenderStates::Default) const { target.draw(sprite, states); }

	void ReturnToPrevPos() { setPosition((*getSquare()).getInPixel()); };

	void Move(Square& newSquare) {
		if (ConditionOfMove(newSquare)) {
			Move_(newSquare);

			if ((name == "PawnW" and y == 0) or (name == "PawnB" and y == 7)) {
				IntRect tepmRect(Vector2i(0, 0), Vector2i(112, 112));

				sprite.setTextureRect(tepmRect);
				sprite.setTexture(*game.textureOfPieces[color ? "choiceB" : "choiceW"]);
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

			if ((name == "PawnW" and y == 0) or (name == "PawnB" and y == 7)) {
				IntRect tepmRect(Vector2i(0, 0), Vector2i(112, 112));

				sprite.setTextureRect(tepmRect);
				sprite.setTexture(*game.textureOfPieces[color ? "choiceB" : "choiceW"]);
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

		for (int i = 0; i < Board::size; ++i) {
			for (int j = 0; j < Board::size; ++j) {
				distance = sqrt(pow(game.mousePos.x - board.squares[i][j].getXInPixel(), 2) + pow(game.mousePos.y - board.squares[i][j].getYInPixel(), 2)); // Distance to the square
				if (distance < maxDistance) {
					maxDistance = distance;
					nearestX = i;
					nearestY = j;
				}
			}
		}
		return &board.squares[nearestX][nearestY];
	}

	// Displaying the squares into which the piece can go
	void DrawPossibleSquares() {
		for (int i = 0; i < Board::size; ++i) {
			for (int j = 0; j < Board::size; ++j) {
				if (ConditionOfMove(board.squares[i][j]))          board.squares[i][j].DrawWithColor(Color(0, 255, 0, 60));   // Green square if you can go to this square
				else if (ConditionOfCapture(board.squares[i][j]))  board.squares[i][j].DrawWithColor(Color(255, 0, 0, 60));   // Red square if you can capture
				else if (ConditionOfCastling(board.squares[i][j])) board.squares[i][j].DrawWithColor(Color(255, 255, 0, 60)); // Yellow square if castling can be done
			}
		}
	}

	FloatRect getGlobalBounds() const { return sprite.getGlobalBounds(); }

	Vector2f getPosition() const { return sprite.getPosition(); }
	void setPosition(const int& x, const int& y) { sprite.setPosition(float(x), float(y)); }
	void setPosition(const Vector2i& newPos) { sprite.setPosition(float(newPos.x), float(newPos.y)); }

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
	void setIsMove(const bool& IsMove) { this->isMove = IsMove; }

	bool getFirstMove() const { return firstMove; }
	void setFirstMove(const bool& firstMove) { this->firstMove = firstMove; }

	int getX() const { return x; }
	void setX(const int& x) { this->x = x; }

	int getY() const { return y; }
	void setY(const int& y) { this->y = y; }

	string getName() const { return name; }
	void setName(const string& name) { this->name = name; }

	Square* getSquare() const { return &board.squares[x][y]; }
};