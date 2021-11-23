#pragma once

using namespace sf; // SFML namespace
using namespace std;

class Game {
	Texture texturePawnW,
		texturePawnB,
		textureCastleW,
		textureCastleB,
		textureKnightW,
		textureKnightB,
		textureBishopW,
		textureBishopB,
		textureQueenW,
		textureQueenB,
		textureKingW,
		textureKingB;
public:
	Vector2i mousePos = Vector2i(0, 0);
	bool turn = false; // 0 - white move, 1 - black move
	bool isStopped = false;
	static const int windowSizeX = 910, windowSizeY = 910;
	Image icon;

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
	{"KingB", &textureKingB }
	};

	Game() {
		icon.loadFromFile("images/icon.png");

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
	}
};
