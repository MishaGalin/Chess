extern Game game;
extern RenderWindow window;
extern Board board;
extern void DeletePiece(Square& square);
extern unsigned char selected;
extern short dx, dy;

class AbstractChessPiece : public Drawable {
	virtual bool ConditionOfMove(const Square& square) = 0;
	virtual bool ConditionOfCapture(const Square& square) = 0;
	virtual bool ConditionOfCastling(const Square& square) = 0;
	virtual void Castling_(const Square& square) = 0;

protected:
	Sprite sprite;
	string name;
	bool color = false; // 0 - white, 1 - black
	bool firstMove = true, isSelected = false, isPromotion = false, isMovable = true, isMove = false;
	char x = 0, y = 0;

	AbstractChessPiece(Square& square, bool color) {
		this->color = color;
		x = square.getX();
		y = square.getY();

		square.setColor(color);
		setPosition(square.getInPixel());
		square.setIsEmpty(false);
	}

	void Changeover(Square& newSquare) const {
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

	void draw(RenderTarget& target, RenderStates states = RenderStates::Default) const {
		target.draw(sprite, states);
	}

	void ReturnToPrevPos() {
		setPosition((*getSquare()).getInPixel());
	};

	void Move(Square& newSquare) {
		if (ConditionOfMove(newSquare)) {
			Move_(newSquare);

			if ((name == "PawnW" and y == 0) or (name == "PawnB" and y == 7)) {
				IntRect tepmRect(Vector2i(0, 0), Vector2i(Square::sideLength, Square::sideLength));

				sprite.setTextureRect(tepmRect);
				sprite.setTexture(*game.textureOfPieces[color ? "choiceB" : "choiceW"]);
				sprite.setOrigin(Square::sideLength / 2, Square::sideLength / 2);

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
				IntRect tepmRect(Vector2i(0, 0), Vector2i(Square::sideLength, Square::sideLength));

				sprite.setTextureRect(tepmRect);
				sprite.setTexture(*game.textureOfPieces[color ? "choiceB" : "choiceW"]);
				sprite.setOrigin(Square::sideLength / 2, Square::sideLength / 2);

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

	void Select(int i) {
		selected = i;
		isMove = true;
		isSelected = true;

		dx = game.mousePos.x - int(getPosition().x);
		dy = game.mousePos.y - int(getPosition().y);
	}

	inline void Unselect() {
		isMove = false;
		isSelected = false;
	}

	void MoveWithMouse() {
		game.mousePos = Mouse::getPosition(window);
		if (isMovable and isMove and isSelected and color == game.turn) setPosition(float(game.mousePos.x - dx), float(game.mousePos.y - dy));
	}

	inline bool ContainsMouse() const {
		return getGlobalBounds().contains(float(game.mousePos.x), float(game.mousePos.y));
	}

	Square* SearchNearestSquare() const {
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
				if (ConditionOfMove(board.squares[i][j]))          board.squares[i][j].DrawWithColor(Color(0, 215, 0, 70));   // Green square if you can go to this square
				else if (ConditionOfCapture(board.squares[i][j]))  board.squares[i][j].DrawWithColor(Color(215, 0, 0, 70));   // Red square if you can capture
				else if (ConditionOfCastling(board.squares[i][j])) board.squares[i][j].DrawWithColor(Color(215, 215, 0, 75)); // Yellow square if castling can be done
			}
		}
	}

	FloatRect getGlobalBounds() const {
		return sprite.getGlobalBounds();
	}

	Vector2f getPosition() const { return sprite.getPosition(); }
	void setPosition(float x, float y) { sprite.setPosition(x, y); }
	void setPosition(const Vector2i& newPos) { sprite.setPosition(float(newPos.x), float(newPos.y)); }

	// 0 - white, 1 - black
	bool getColor() const { return color; }
	void setColor(bool color) { this->color = color; }

	bool getIsPromotion() const { return isPromotion; }
	void setIsPromotion(bool isPromotion) { this->isPromotion = isPromotion; }

	bool getIsSelected() const { return isSelected; }
	void setIsSelected(bool isSelected) { this->isSelected = isSelected; }

	bool getIsMovable() const { return isMovable; }
	void setIsMovable(bool IsMovable) { this->isMovable = IsMovable; }

	bool getIsMove() const { return isMove; }
	void setIsMove(bool IsMove) { this->isMove = IsMove; }

	bool getFirstMove() const { return firstMove; }
	void setFirstMove(bool firstMove) { this->firstMove = firstMove; }

	int getX() const { return x; }
	void setX(int x) { this->x = x; }

	int getY() const { return y; }
	void setY(int y) { this->y = y; }

	string getName() const { return name; }
	void setName(string name) { this->name = name; }

	Square* getSquare() const { return &board.squares[x][y]; }
};