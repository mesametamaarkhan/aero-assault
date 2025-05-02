#ifndef BULLET_H
#define BULLET_H

#include <SFML/Graphics.hpp>
using namespace sf;

class Bullet {
public:
	Texture tex;
	Sprite sprite;
	float yInc = 40.0f;
	float speed = 1;

	Bullet(std::string filePath /*float yIncrement*/) {
		tex.loadFromFile(filePath);
		sprite.setTexture(tex);
		sprite.setPosition(140, 233); //120,233
		sprite.setScale(1, 1);
		//yInc = yIncrement;
	}

	void move(int tempX, int tempY, bool& bulletMove)
	{
		float delta_x = 0, delta_y = 0;
		delta_x += 1;
		delta_x *= speed;
		if (sprite.getPosition().y < 0) {
			sprite.setPosition(tempX + 100.0f, tempY + 40.0f);
			bulletMove = false;
		}
		else if (sprite.getPosition().y > 720) {
			sprite.setPosition(tempX + 100.0f, tempY + 70.0f);
			bulletMove = false;
		}
		else if (sprite.getPosition().x > 1280) {
			sprite.setPosition(tempX, tempY);
			bulletMove = false;
		}
		else if (sprite.getPosition().x < 0) {
			sprite.setPosition(tempX + 80.0f, tempY + 40.0f);
			bulletMove = false;
		}
		sprite.move(delta_x, delta_y);
	}


};

class EnemyBullet {
public:
	Texture tex;
	Sprite sprite;
	int tempX;
	int tempY;
	float speed = 1;

	EnemyBullet(std::string filePath,double x, double y) {
		tex.loadFromFile(filePath);
		sprite.setTexture(tex);
		sprite.setPosition(x + 35,y + 5); //120,233
		sprite.setScale(1, 0.75);
		tempX = x;
		tempY = y;
	}

	void move(bool& out)
	{
		float delta_x = 0, delta_y = 0;
		delta_x -= 1;
		delta_x *= speed;
		if (sprite.getPosition().y < 0)
			sprite.setPosition(tempX, tempY);
		else if (sprite.getPosition().y > 720) {
			sprite.setPosition(tempX, tempY);
		}
		else if (sprite.getPosition().x > 1280)
			sprite.setPosition(tempX, tempY);
		else if (sprite.getPosition().x < 0) {
			sprite.setPosition(tempX + 35, tempY + 5);
			out = true;
		}
		sprite.move(delta_x, delta_y);
	}

	void bossBulletMove(bool& out, double x, double y) {
		float delta_x = 0, delta_y = 0;
		delta_x -= 1;
		delta_x *= speed;
		if (sprite.getPosition().y < 0)
			sprite.setPosition(x, y);
		else if (sprite.getPosition().y > 720) {
			sprite.setPosition(x, y);
		}
		else if (sprite.getPosition().x > 1280)
			sprite.setPosition(x, y);
		else if (sprite.getPosition().x < 0) {
			sprite.setPosition(x, y);
			out = true;
		}
		sprite.move(delta_x, delta_y);
	}
};

#endif

