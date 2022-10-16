extern void AddPiece(Square& square, int value);

class Board : Drawable {
	Sprite sprite;

public:
	static const unsigned char size = 8;
	vector<vector<Square>> squares;

	char InitArray[size][size] =
	{ -1,-2,-3,-4,-5,-3,-2,-1,
	  -6,-6,-6,-6,-6,-6,-6,-6,
	   0, 0, 0, 0, 0, 0, 0, 0,
	   0, 0, 0, 0, 0, 0, 0, 0,
	   0, 0, 0, 0, 0, 0, 0, 0,
	   0, 0, 0, 0, 0, 0, 0, 0,
	   6, 6, 6, 6, 6, 6, 6, 6,
	   1, 2, 3, 4, 5, 3, 2, 1
	};

	void draw(RenderTarget& target, RenderStates states = RenderStates::Default) const {
		target.draw(sprite, states);
	}

	FloatRect getGlobalBounds() const {
		return sprite.getGlobalBounds();
	}

	Board() {
		sprite.setTexture(*game.textureOfPieces["board"]);

		for (int i = 0; i < size; ++i) {
			vector<Square> temp;
			for (int j = 0; j < size; ++j) {
				Square tempSquare(i, j);
				AddPiece(tempSquare, InitArray[j][i]); // Arrangement of pieces
				temp.push_back(tempSquare);
			}
			squares.push_back(temp);
		}
	};
};