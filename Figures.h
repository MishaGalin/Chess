#pragma once
class Pawn : public AbstractFigure
{
public:
	bool firstMove = true;

	Pawn(const int& posX, const int& posY, const bool& color, const int& cellSide) {
		color ? textures.loadFromFile("images/pawn_b.png") : textures.loadFromFile("images/pawn_w.png");

		sprite.setTexture(textures);
		sprite.setOrigin(18, 38);
		sprite.setPosition(cellSide / 2 + cellSide * posX, cellSide / 2 + cellSide * posY);
	}

	//void Move(const int& newPosX, const int& newPosY, bool& turn) override
	//{
	//	if (turn == color and newPosX == posX) {
	//		if (color == 0) { // if white
	//			if (firstMove) {
	//				if (posY - newPosY <= 2 and posY - newPosY >= 1) {
	//					posY = newPosY;
	//					firstMove = false;
	//					turn = !turn;
	//				}
	//			}
	//			else {
	//				if (posY - newPosY == 1) {
	//					posY = newPosY;
	//					turn = !turn;
	//				}
	//			}
	//		}
	//		else { // if black
	//			if (firstMove) {
	//				if (newPosY - posY <= 2 and newPosY - posY >= 1) {
	//					posY = newPosY;
	//					firstMove = false;
	//					turn = !turn;
	//				}
	//			}
	//			else {
	//				if (newPosY - posY == 1) {
	//					posY = newPosY;
	//					turn = !turn;
	//				}
	//			}
	//		}
	//	}
	//}
};
