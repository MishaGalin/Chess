extern GameData game;
extern RenderWindow window;

class Square : public Drawable {
	bool color = false, isEmpty = true;
	unsigned char x = 0, y = 0;
	float xInPixel = 0, yInPixel = 0;
	RectangleShape drawableRect;

	void draw(RenderTarget& target, RenderStates states = RenderStates::Default) const {
		target.draw(drawableRect, states);
	}

public:
	static const unsigned int sideLength = 112; // Side length of a square in pixels
	Square(int x, int y) {
		this->x = x;
		this->y = y;
		xInPixel = 7.f + sideLength / 2.f + sideLength * x;
		yInPixel = 7.f + sideLength / 2.f + sideLength * y;

		drawableRect.setPosition(xInPixel, yInPixel);
		drawableRect.setSize(Vector2f(sideLength - 2.f, sideLength - 2.f));
		drawableRect.setOrigin(sideLength / 2.f - 1.f, sideLength / 2.f - 1.f);
		drawableRect.setOutlineColor(Color::White);
		drawableRect.setOutlineThickness(2.f);
	}

	void DrawWithColor(const Color& color) {
		drawableRect.setFillColor(color);
		draw(window);
	}

	FloatRect getGlobalBounds() const {
		return drawableRect.getGlobalBounds();
	}

	bool getIsEmpty() const { return isEmpty; }
	void setIsEmpty(bool isEmpty) { this->isEmpty = isEmpty; }

	bool getColor() const { return color; }
	void setColor(bool color) { this->color = color; }

	int getX() const { return x; }
	void setX(int x) { this->x = x; }

	int getY() const { return y; }
	void setY(int y) { this->y = y; }

	float getXInPixel() const { return xInPixel; }
	void setXInPixel(float xInPixel) { this->xInPixel = xInPixel; }

	float getYInPixel() const { return yInPixel; }
	void setYInPixel(float yInPixel) { this->yInPixel = yInPixel; }

	Vector2f getInPixel() const { return Vector2f(xInPixel, yInPixel); }

	bool operator==(const Square& anotherSquare) {
		return x == anotherSquare.x and y == anotherSquare.y;
	}
};