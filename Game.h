#pragma once
#include <SFML/Graphics.hpp>

using namespace sf; // SFML namespace
using namespace std;

extern RenderWindow window;

class Game {
	Image icon;

	Texture texturePawnW;
	Texture	texturePawnB;
	Texture	textureCastleW;
	Texture	textureCastleB;
	Texture	textureKnightW;
	Texture	textureKnightB;
	Texture	textureBishopW;
	Texture textureBishopB;
	Texture	textureQueenW;
	Texture	textureQueenB;
	Texture	textureKingW;
	Texture	textureKingB;

	Texture choicePieceW;
	Texture choicePieceB;

public:
	Vector2i mousePos = Vector2i(0, 0);
	bool turn = false; // 0 - white move, 1 - black move
	bool isFinished = false, pawnIsPromotion = false;
	static const int windowSizeX = 910, windowSizeY = 910;

	map <string, Texture*> textureOfPieces = {
		{"PawnW", &texturePawnW },
		{"PawnB", &texturePawnB },
		{"CastleW", &textureCastleW },
		{"CastleB", &textureCastleB },
		{"KnightW", &textureKnightW },
		{"KnightB", &textureKnightB },
		{"BishopW", &textureBishopW },
		{"BishopB", &textureBishopB },
		{"QueenW", &textureQueenW },
		{"QueenB", &textureQueenB },
		{"KingW", &textureKingW },
		{"KingB", &textureKingB },
		{"choiceW", &choicePieceW},
		{"choiceB", &choicePieceB}
	};

	void ChangeOfTurn() {
		turn = !turn;
		if (isFinished) window.setTitle(turn ? "Chess: WHITE WINS" : "Chess: BLACK WINS");
		else window.setTitle(turn ? "Chess: turn of black" : "Chess: turn of white");
	}

	Game() {
		window.setTitle(turn ? "Chess: turn of black" : "Chess: turn of white");
		window.setFramerateLimit(300);

		icon.loadFromFile("images/icon32.png");
		window.setIcon(32, 32, icon.getPixelsPtr());

		textureOfPieces["PawnW"]->loadFromFile("images/pawn_w.png");
		textureOfPieces["PawnB"]->loadFromFile("images/pawn_b.png");
		textureOfPieces["CastleW"]->loadFromFile("images/castle_w.png");
		textureOfPieces["CastleB"]->loadFromFile("images/castle_b.png");
		textureOfPieces["KnightW"]->loadFromFile("images/knight_w.png");
		textureOfPieces["KnightB"]->loadFromFile("images/knight_b.png");
		textureOfPieces["BishopW"]->loadFromFile("images/bishop_w.png");
		textureOfPieces["BishopB"]->loadFromFile("images/bishop_b.png");
		textureOfPieces["QueenW"]->loadFromFile("images/queen_w.png");
		textureOfPieces["QueenB"]->loadFromFile("images/queen_b.png");
		textureOfPieces["KingW"]->loadFromFile("images/king_w.png");
		textureOfPieces["KingB"]->loadFromFile("images/king_b.png");

		textureOfPieces["choiceW"]->loadFromFile("images/choicePieceW.png");
		textureOfPieces["choiceB"]->loadFromFile("images/choicePieceB.png");
	}
};