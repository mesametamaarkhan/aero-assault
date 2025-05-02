#ifndef ENEMY_H
#define ENEMY_H

#include <SFML/Graphics.hpp>
#include <vector>
#include "bullet.h"
using namespace std;
using namespace sf;

class Enemy
{
public:
	Texture tex;
	Sprite sprite;
	float speed = 0.3;
	EnemyBullet* eB;
	bool bossMove;

	Enemy(std::string png_path, double x, double y)
	{
		tex.loadFromFile(png_path);
		sprite.setTexture(tex);
		sprite.setPosition(x, y);
		sprite.setScale(1.5, 1.5);
		eB = new EnemyBullet("img/enemy-bullet.png", x + 20, y + 33);
		bossMove = false;
	}

	void move(bool& fire)
	{
		float delta_x = 0, delta_y = 0;

		if (!bossMove) {
			delta_y += 1;
		}
		else {
			delta_y -= 1;
		}

		delta_y *= speed;

		if (sprite.getPosition().y <= 0)
		{
			bossMove = false;
		}
		else if (sprite.getPosition().y + 270 >= 720)
		{
			bossMove = true;
		}

		sprite.move(delta_x, delta_y);
		if (!fire) {
			eB->sprite.setPosition(sprite.getPosition().x, sprite.getPosition().y + 110);
		}
	}


	void setEnemies(vector<Enemy*>& e) {
		Enemy* e1 = new Enemy("img/enemy2.jpg", 1120, 0);
		e.push_back(e1);

		e1 = new Enemy("img/enemy2.jpg", 960, 100);
		e.push_back(e1);

		e1 = new Enemy("img/enemy2.jpg", 800, 200);
		e.push_back(e1);

		e1 = new Enemy("img/enemy2.jpg", 1120, 200);
		e.push_back(e1);

		e1 = new Enemy("img/enemy2.jpg", 640, 300);
		e.push_back(e1);

		e1 = new Enemy("img/enemy2.jpg", 960, 300);
		e.push_back(e1);

		e1 = new Enemy("img/enemy2.jpg", 800, 400);
		e.push_back(e1);

		e1 = new Enemy("img/enemy2.jpg", 1120, 400);
		e.push_back(e1);

		e1 = new Enemy("img/enemy2.jpg", 960, 500);
		e.push_back(e1);

		e1 = new Enemy("img/enemy2.jpg", 1120, 600);

		e.push_back(e1);
	}
};



#endif