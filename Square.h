extern Game game;
extern RenderWindow window;

class Square : public Drawable {
	bool color = false, isEmpty = true;
	int x = 0, y = 0, xInPixel = 0, yInPixel = 0;
	RectangleShape drawableRect;

	void draw(RenderTarget& target, RenderStates states = RenderStates::Default) const { target.draw(drawableRect, states); }
public:
	static const int sideLength = 112; // Side length of a square in pixels
	Square(const int& x, const int& y) {
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
	void setIsEmpty(const bool& isEmpty) { this->isEmpty = isEmpty; }

	bool getColor() const { return color; }
	void setColor(const bool& color) { this->color = color; }

	int getX() const { return x; }
	void setX(const int& x) { this->x = x; }

	int getY() const { return y; }
	void setY(const int& y) { this->y = y; }

	int getXInPixel() const { return xInPixel; }
	void setXInPixel(const int& xInPixel) { this->xInPixel = xInPixel; }

	int getYInPixel() const { return yInPixel; }
	void setYInPixel(const int& yInPixel) { this->yInPixel = yInPixel; }

	Vector2i getInPixel() const { return Vector2i(xInPixel, yInPixel); }

	bool operator==(const Square& square) {
		return (x == square.x and y == square.y);
	}
};