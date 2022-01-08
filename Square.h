extern Game game;
extern RenderWindow window;

class Square : public Drawable {
	bool color = false, isEmpty = true;
	unsigned char x = 0, y = 0;
	unsigned short xInPixel = 0, yInPixel = 0;
	RectangleShape drawableRect;

	void draw(RenderTarget& target, RenderStates states = RenderStates::Default) const { target.draw(drawableRect, states); }

public:
	static const unsigned int sideLength = 112; // Side length of a square in pixels
	Square(int x, int y) {
		this->x = x;
		this->y = y;
		xInPixel = 7 + sideLength / 2 + sideLength * x;
		yInPixel = 7 + sideLength / 2 + sideLength * y;

		drawableRect.setPosition((float)xInPixel, (float)yInPixel);
		drawableRect.setSize(Vector2f(sideLength - 2, sideLength - 2));
		drawableRect.setOrigin((float)(sideLength / 2 - 1), (float)(sideLength / 2 - 1));
		drawableRect.setOutlineColor(Color::White);
		drawableRect.setOutlineThickness(2);
	}

	void DrawWithColor(const Color& color) {
		drawableRect.setFillColor(color);
		draw(window);
	}

	FloatRect getGlobalBounds() { return drawableRect.getGlobalBounds(); }

	bool getIsEmpty() const { return isEmpty; }
	void setIsEmpty(bool isEmpty) { this->isEmpty = isEmpty; }

	bool getColor() const { return color; }
	void setColor(bool color) { this->color = color; }

	int getX() const { return x; }
	void setX(int x) { this->x = x; }

	int getY() const { return y; }
	void setY(int y) { this->y = y; }

	int getXInPixel() const { return xInPixel; }
	void setXInPixel(int xInPixel) { this->xInPixel = xInPixel; }

	int getYInPixel() const { return yInPixel; }
	void setYInPixel(int yInPixel) { this->yInPixel = yInPixel; }

	Vector2i getInPixel() const { return Vector2i(xInPixel, yInPixel); }

	bool operator==(const Square& anotherSquare) {
		return x == anotherSquare.x and y == anotherSquare.y;
	}
};