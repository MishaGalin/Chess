class Board : Drawable {
	Texture texture;
	Sprite sprite;

public:
	static const int Size = 8;
	vector<vector<Square>> Squares;

	int InitArr[Size][Size] =
	{ -1,-2,-3,-4,-5,-3,-2,-1,
	  -6,-6,-6,-6,-6,-6,-6,-6,
	   0, 0, 0, 0, 0, 0, 0, 0,
	   0, 0, 0, 0, 0, 0, 0, 0,
	   0, 0, 0, 0, 0, 0, 0, 0,
	   0, 0, 0, 0, 0, 0, 0, 0,
	   6, 6, 6, 6, 6, 6, 6, 6,
	   1, 2, 3, 4, 5, 3, 2, 1
	};

	void draw(RenderTarget& target, RenderStates states = RenderStates::Default) const { target.draw(sprite, states); }

	FloatRect getGlobalBounds() { return sprite.getGlobalBounds(); }

	Board() {
		texture.loadFromFile("images/board.png");
		sprite.setTexture(texture);

		for (int i = 0; i < Size; ++i) {
			vector<Square> temp;
			for (int j = 0; j < Size; ++j) {
				Square tempSquare(i, j, InitArr[j][i]);
				temp.push_back(tempSquare);
			}
			Squares.push_back(temp);
		}
	};
};