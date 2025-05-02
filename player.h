#ifndef PLAYER_H
#define PLAYER_H

#include <SFML/Graphics.hpp>
using namespace sf;

class Player {
public:
	Texture tex;
	Sprite sprite;
	int HP = 100;
	float speed = 0.75;

	Player(std::string filePath, float xScale, float yScale) {
		tex.loadFromFile(filePath);
		sprite.setTexture(tex);
		sprite.setPosition(100, 200);
		sprite.setScale(xScale, yScale); //0.25
	}

	void move(std::string s)
	{
		float delta_x = 0, delta_y = 0;
		if (s == "l")
			delta_x -= 1;

		else if (s == "r")
			delta_x += 1;
		else if (s == "u")
			delta_y = -1;
		else if (s == "d")
			delta_y += 1;

		delta_x *= speed;
		delta_y *= speed;

		if (sprite.getPosition().y < 0)
		{
			sprite.setPosition(sprite.getPosition().x, 720);
		}
		else if (sprite.getPosition().x < 0)
		{
			sprite.setPosition(1280, sprite.getPosition().y);
		}
		else if (sprite.getPosition().y > 720)
		{
			sprite.setPosition(sprite.getPosition().x, 0);
		}
		else if (sprite.getPosition().x > 1280)
		{
			sprite.setPosition(0, sprite.getPosition().y);
		}

		sprite.move(delta_x, delta_y);

	}
};


#endif

