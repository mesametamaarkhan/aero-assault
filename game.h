#ifndef GAME_H
#define GAME_H

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <iostream>
#include <time.h>
#include "player.h"
#include "bullet.h"
#include "enemy.h"
using namespace sf;
using namespace std;

class Game {
public:
	Texture tex;
	Sprite background;
	Texture winTex;
	Sprite winBG;
	Texture loseTex;
	Sprite loseBG;	
	Player* p;
	Bullet* b;
	vector<Enemy*> e;
	vector<Enemy*> e2;
	Enemy* boss;
	FloatRect playerBounds;
	FloatRect bulletBounds;
	FloatRect enemyBulletBounds;
	vector<FloatRect> enemyBounds;
	FloatRect enemyBulletBoundsLevel2;
	vector<FloatRect> enemyBoundsLevel2;
	FloatRect bossBounds;
	FloatRect bossBulletBounds;
	vector<bool> enemyBool;
	vector<bool> enemyBoolLevel2;
	double x, y;
	int enemyCount;
	int score;
	int bossHP;
	bool enemyBulletOut;
	bool enemyBulletOutLevel2;
	int deadEnemyCount;
	int deadEnemyCountLevel2;
	int deadIndex[10];
	int deadIndexLevel2[10];
	bool deadIndexBool;
	bool gameOver;
	bool bulletMove;
	bool bossBulletMove;
	bool collision;
	Font font;
	Text scoring;
	Text healthDisplay;
	int bulletShootSequence[10] = { 5,7,3,4,1,0,6,2,8,9 };
	int level;
	bool enemiesSet;
	Music music;
	Sound shootingSound;
	SoundBuffer buffer;

	Game(string playerPath,float xScale, float yScale) {
		tex.loadFromFile("img/aerobackground.jpg");
		background.setTexture(tex);
		winTex.loadFromFile("img/win.png");
		winBG.setTexture(winTex);
		loseTex.loadFromFile("img/lose.png");
		loseBG.setTexture(loseTex);
		p = new Player(playerPath,xScale, yScale);
		b = new Bullet("img/bullet.png");
		x = 800;
		y = 0;
		enemyCount = 10;
		setEnemies(e);
		setEnemiesLevel2(e2);
		boss = new Enemy("img/e2.png", 780, 160);
		boss->sprite.setScale(2.5, 2.5);
		boss->eB = new EnemyBullet("img/bossBullet.png", 780, 270);
		boss->eB->sprite.setScale(1, 1);
		collision = false;
		enemyBulletOut = false;
		deadEnemyCount = 0;
		for (int i = 0; i < 10; i++) {
			deadIndex[i] = -1;
			deadIndexLevel2[i] = -1;
			bool a = true;
			enemyBool.push_back(a);
			enemyBoolLevel2.push_back(a);
		}
		deadIndexBool = false;
		score = 0;
		bossHP = 300;
		gameOver = false;
		bossBulletMove = false;
		playerBounds = { -1.0f, -1.0f, 0.0f, 0.0f };
		bulletBounds = { -1.0f, -1.0f, 0.0f, 0.0f };
		enemyBulletBounds = { -1.0f, -1.0f, 0.0f, 0.0f };
		gameOver = false;
		font.loadFromFile("fonts/Poppins-Medium.ttf");
		scoring.setCharacterSize(20);
		scoring.setFont(font);
		scoring.setPosition(70, 683);
		scoring.setFillColor(Color::Yellow);
		healthDisplay.setCharacterSize(20);
		healthDisplay.setFont(font);
		healthDisplay.setPosition(70, 663);
		healthDisplay.setFillColor(Color::Yellow);
		level = 1;
		deadEnemyCountLevel2 = 0;
		enemiesSet = false;
		music.openFromFile("music/bg_music.mp3");
		music.setLoop(1);
		buffer.loadFromFile("music/blstr.mp3");
		shootingSound.setBuffer(buffer);
		shootingSound.setVolume(100);
	}

	void run(RenderWindow& window) {
		srand(time(0));
		int index = rand() % enemyCount;
		int prevIndex = -1;
		Clock clock;
		float timer = 0;
		float bossBulletTimer = 0;
		music.play();

		Event E;
		while (window.isOpen())
		{
			float time = clock.getElapsedTime().asSeconds();
			clock.restart();
			timer += time;
			bossBulletTimer += time;

			while (window.pollEvent(E))
			{
				if (E.type == Event::Closed)
					window.close();
			}

			if (level == 1) {
				level1(window, E, index, prevIndex);
			}
			else if (level == 2) {
				level2(window, E, index, prevIndex);
			}
			else if (level == 3) {
				bossLevel(window, bossBulletTimer);
			}
		}
	}

	void level1(RenderWindow& window, Event &E, int& index, int& prevIndex) {

		checkEnemyBulletOut(index, prevIndex, deadIndexBool);

		if (Keyboard::isKeyPressed(Keyboard::Left)) //If left key is pressed
			p->move("l");
		if (Keyboard::isKeyPressed(Keyboard::Right))
			p->move("r");
		if (Keyboard::isKeyPressed(Keyboard::Up))
			p->move("u");
		if (Keyboard::isKeyPressed(Keyboard::Down))
			p->move("d");
		if (Keyboard::isKeyPressed(Keyboard::Space))
			bulletMove = true;

		

		if (!bulletMove) {
			b->sprite.setPosition(p->sprite.getPosition().x + 10, p->sprite.getPosition().y + 33);
		}
		if (bulletMove) {
			shootingSound.play();
			b->move(p->sprite.getPosition().x + 10, p->sprite.getPosition().y + 33, bulletMove);
		}
		if (e[index] != nullptr) {
			e[index]->eB->move(enemyBulletOut);
			prevIndex = index;
		}

		if (p->HP <= 0 || gameOver) {
			music.stop();
			gameOver = true;
		}

		setBulletAndEnemyBounds();
		checkPlayerBulletEnemyCollision();
		checkEnemyBulletPlayerCollision(index);
		scoring.setString("Score: " + to_string(score));
		healthDisplay.setString("Health: " + to_string(p->HP));

		if (gameOver) {
			music.stop();
			gameOverScreen(window);
		}

		if (deadEnemyCount == 10) {
			level = 2;
		}
		drawEverything(window);
	}

	void level2(RenderWindow& window, Event& E, int& index, int& prevIndex) {

		checkEnemyBulletOutLevel2(index, prevIndex, deadIndexBool);

		if (Keyboard::isKeyPressed(Keyboard::Left)) //If left key is pressed
			p->move("l");
		if (Keyboard::isKeyPressed(Keyboard::Right))
			p->move("r");
		if (Keyboard::isKeyPressed(Keyboard::Up))
			p->move("u");
		if (Keyboard::isKeyPressed(Keyboard::Down))
			p->move("d");
		if (Keyboard::isKeyPressed(Keyboard::Space))
			bulletMove = true;


		if (!bulletMove) {
			b->sprite.setPosition(p->sprite.getPosition().x + 40, p->sprite.getPosition().y + 50);
		}

		if (bulletMove) {
			shootingSound.play();
			b->move(p->sprite.getPosition().x + 40, p->sprite.getPosition().y + 50, bulletMove);
		}


		if (e2[index] != nullptr) {
			e2[index]->eB->move(enemyBulletOutLevel2);
			prevIndex = index;
		}

		if (p->HP <= 0) {
			gameOver = true;
		}

		setBulletAndEnemyBoundsLevel2();
		checkPlayerBulletEnemyCollisionLevel2();
		checkEnemyBulletPlayerCollisionLevel2(index);
		scoring.setString("Score: " + to_string(score));
		healthDisplay.setString("Health: " + to_string(p->HP));


		if (deadEnemyCountLevel2 == 10) {
			level = 3;
		}

		if (gameOver) {
			music.stop();
			gameOverScreen(window);
		}
		drawLevel2(window);
	}

	void bossLevel(RenderWindow& window, float& bossBulletTimer) {

		if (bossBulletTimer >= 1.5) {
			bossBulletMove = true;
			bossBulletTimer = 0;
		}

		if (Keyboard::isKeyPressed(Keyboard::Left)) //If left key is pressed
			p->move("l");
		if (Keyboard::isKeyPressed(Keyboard::Right))
			p->move("r");
		if (Keyboard::isKeyPressed(Keyboard::Up))
			p->move("u");
		if (Keyboard::isKeyPressed(Keyboard::Down))
			p->move("d");
		if (Keyboard::isKeyPressed(Keyboard::Space))
			bulletMove = true;


		if (!bulletMove) {
			b->sprite.setPosition(p->sprite.getPosition().x + 10, p->sprite.getPosition().y + 33);
		}

		if (bulletMove) {
			shootingSound.play();
			b->move(p->sprite.getPosition().x + 10, p->sprite.getPosition().y + 33, bulletMove);
		}


		boss->move(bossBulletMove);
		if (boss != nullptr) {
			boss->eB->bossBulletMove(bossBulletMove,boss->sprite.getPosition().x, boss->sprite.getPosition().y + 110);
		}

		if (p->HP <= 0) {
			gameOver = true;
		}

		setBulletAndEnemyBoundsLevel3();
		checkPlayerBulletEnemyCollisionLevel3();
		checkEnemyBulletPlayerCollisionLevel3();
		scoring.setString("Score: " + to_string(score));
		healthDisplay.setString("Health: " + to_string(p->HP));


		if (boss == nullptr || bossHP <= 0) {
			music.stop();
			gameOver = true;
		}

		if (gameOver) {
			gameOverScreen(window);
		}
		drawLevel3(window);
	}

	/*-----------------------------LEVEL 1----------------------------------------------------------*/

	void setEnemies(vector<Enemy*>& e) {
		Enemy* e1 = new Enemy("img/enemy.png", 1120, 0);
		e.push_back(e1);

		e1 = new Enemy("img/enemy.png", 960, 100);
		e.push_back(e1);

		e1 = new Enemy("img/enemy.png", 800, 200);
		e.push_back(e1);

		e1 = new Enemy("img/enemy.png", 1120, 200);
		e.push_back(e1);

		e1 = new Enemy("img/enemy.png", 640, 300);
		e.push_back(e1);

		e1 = new Enemy("img/enemy.png", 960, 300);
		e.push_back(e1);

		e1 = new Enemy("img/enemy.png", 800, 400);
		e.push_back(e1);

		e1 = new Enemy("img/enemy.png", 1120, 400);
		e.push_back(e1);

		e1 = new Enemy("img/enemy.png", 960, 500);
		e.push_back(e1);

		e1 = new Enemy("img/enemy.png", 1120, 600);

		e.push_back(e1);
	}
	
	void checkEnemyBulletOut(int& index, int& prevIndex, bool& deadIndexBool) {
		if (enemyBulletOut && deadEnemyCountLevel2 < 9) {
			while (index == prevIndex || deadIndexBool) {
				index = rand() % enemyCount;
				for (int i = 0; i < enemyCount; i++) {
					if (index == deadIndex[i]) {
						deadIndexBool = true;
						break;
					}
					deadIndexBool = false;
				}
			}
			enemyBulletOut = false;
		}
		prevIndex = index;
	}

	void setBulletAndEnemyBounds() {
		
		bulletBounds = b->sprite.getGlobalBounds();
		for (int i = 0; i < enemyCount; i++) {
			if (e[i] != nullptr) {
				FloatRect bounds = e[i]->sprite.getGlobalBounds();
				enemyBounds.push_back(bounds);
			}
			else {
				enemyBounds[i] = { -1.0f, -1.0f, 0.0f, 0.0f };
			}
		}
	}

	void checkPlayerBulletEnemyCollision() {
		for (int i = 0; i < enemyCount; i++) {
			if (bulletBounds.intersects(enemyBounds[i])) {
				e[i] = nullptr;
				b->sprite.setPosition(p->sprite.getPosition().x + 20, p->sprite.getPosition().y + 33);
				enemyBounds[i] = { -1.0f, -1.0f, 0.0f, 0.0f };
				enemyBool[i] = false;
				deadEnemyCount += 1;
				deadIndex[i] = i;
				score += 10;
			}
		}
	}

	void checkEnemyBulletPlayerCollision(int index) {
		playerBounds = p->sprite.getGlobalBounds();
		if (e[index] != nullptr) {
			enemyBulletBounds = e[index]->eB->sprite.getGlobalBounds();
		}

		if (e[index] != nullptr) {
			if (enemyBulletBounds.intersects(playerBounds)) {
				p->HP -= 13;
				e[index]->eB->sprite.setPosition(-120, -233);
			}
		}
	}

	void drawEverything(RenderWindow& window) {
		window.clear();
		window.draw(background);
		window.draw(b->sprite);
		window.draw(p->sprite);

		for (auto& enemy : e) {
			if (enemy != nullptr) {
				window.draw(enemy->eB->sprite);
				window.draw(enemy->sprite);
			}
		}
		window.draw(scoring);
		window.draw(healthDisplay);
		window.display();
	}
	/*----------------------------------------------------------------------------------------------*/

	/*-----------------------------LEVEL 2----------------------------------------------------------*/
	void setEnemiesLevel2(vector<Enemy*>& e) {
		e.clear();
		Enemy* e1 = new Enemy("img/enemy2.png", 1120, 0);
		e1->sprite.setScale(2, 2);
		e.push_back(e1);

		e1 = new Enemy("img/enemy2.png", 960, 100);
		e1->sprite.setScale(2, 2);
		e.push_back(e1);

		e1 = new Enemy("img/enemy2.png", 800, 200);
		e1->sprite.setScale(2, 2);
		e.push_back(e1);

		e1 = new Enemy("img/enemy2.png", 1120, 200);
		e1->sprite.setScale(2, 2);
		e.push_back(e1);

		e1 = new Enemy("img/enemy2.png", 640, 300);
		e1->sprite.setScale(2, 2);
		e.push_back(e1);

		e1 = new Enemy("img/enemy2.png", 960, 300);
		e1->sprite.setScale(2, 2);
		e.push_back(e1);

		e1 = new Enemy("img/enemy2.png", 800, 400);
		e1->sprite.setScale(2, 2);
		e.push_back(e1);

		e1 = new Enemy("img/enemy2.png", 1120, 400);
		e1->sprite.setScale(2, 2);
		e.push_back(e1);

		e1 = new Enemy("img/enemy2.png", 960, 500);
		e1->sprite.setScale(2, 2);
		e.push_back(e1);

		e1 = new Enemy("img/enemy2.png", 1120, 600);
		e1->sprite.setScale(2, 2);
		e.push_back(e1);
	}

	void checkEnemyBulletOutLevel2(int& index, int& prevIndex, bool& deadIndexBool) {
		if (enemyBulletOutLevel2) {
			while (index == prevIndex || deadIndexBool) {
				index = rand() % enemyCount;
				for (int i = 0; i < enemyCount; i++) {
					if (index == deadIndexLevel2[i]) {
						deadIndexBool = true;
						break;
					}
					deadIndexBool = false;
				}

			}
			enemyBulletOutLevel2 = false;
		}
		prevIndex = index;
	}

	void setBulletAndEnemyBoundsLevel2() {
		bulletBounds = b->sprite.getGlobalBounds();
		for (int i = 0; i < enemyCount; i++) {
			if (e2[i] != nullptr) {
				FloatRect bounds = e2[i]->sprite.getGlobalBounds();
				enemyBoundsLevel2.push_back(bounds);
			}
			else {
				enemyBoundsLevel2[i] = { -1.0f, -1.0f, 0.0f, 0.0f };
			}
		}
	}

	void checkPlayerBulletEnemyCollisionLevel2() {
		for (int i = 0; i < enemyCount; i++) {
			if (bulletBounds.intersects(enemyBoundsLevel2[i])) {
				e2[i] = nullptr;
				b->sprite.setPosition(p->sprite.getPosition().x + 20, p->sprite.getPosition().y + 33);
				enemyBoundsLevel2[i] = { -1.0f, -1.0f, 0.0f, 0.0f };
				enemyBoolLevel2[i] = false;
				deadEnemyCountLevel2 += 1;
				deadIndexLevel2[i] = i;
				score += 14;
			}
		}
	}

	void checkEnemyBulletPlayerCollisionLevel2(int index) {
		playerBounds = p->sprite.getGlobalBounds();
		if (e2[index] != nullptr) {
			enemyBulletBoundsLevel2 = e2[index]->eB->sprite.getGlobalBounds();
		}

		if (e2[index] != nullptr) {
			if (enemyBulletBoundsLevel2.intersects(playerBounds)) {
				p->HP -= 13;
				e2[index]->eB->sprite.setPosition(-120, -233);
			}
		}
	}

	void drawLevel2(RenderWindow& window) {
		window.clear();
		window.draw(background);
		window.draw(b->sprite);
		window.draw(p->sprite);

		for (auto& enemy : e2) {
			if (enemy != nullptr) {
				window.draw(enemy->eB->sprite);
				window.draw(enemy->sprite);
			}
		}
		window.draw(scoring);
		window.draw(healthDisplay);
		window.display();
	}
	/*----------------------------------------------------------------------------------------------*/

	void setBulletAndEnemyBoundsLevel3() {
		bulletBounds = b->sprite.getGlobalBounds();
		if (boss != nullptr) {
			bossBounds = boss->sprite.getGlobalBounds();
		}
		else {
			bossBounds = { -1.0f, -1.0f, 0.0f, 0.0f };
		}
	}

	void checkPlayerBulletEnemyCollisionLevel3() {
		if (bulletBounds.intersects(bossBounds)) {
			b->sprite.setPosition(p->sprite.getPosition().x + 20, p->sprite.getPosition().y + 33);
			bossHP -= 23;
		}
	}

	void checkEnemyBulletPlayerCollisionLevel3() {
		playerBounds = p->sprite.getGlobalBounds();
		if (boss != nullptr) {
			bossBulletBounds = boss->eB->sprite.getGlobalBounds();
		}

		if (boss != nullptr) {
			if (bossBulletBounds.intersects(playerBounds)) {
				p->HP -= 23;
				boss->eB->sprite.setPosition(-120, -233);
			}
		}
	}

	void drawLevel3(RenderWindow& window) {
		window.clear();
		window.draw(background);
		window.draw(b->sprite);
		window.draw(p->sprite);

		if (boss != nullptr) {
			if (!enemyBulletOut) {
				window.draw(boss->eB->sprite);
			}
			window.draw(boss->sprite);
		}
		window.draw(scoring);
		window.draw(healthDisplay);
		window.display();
	}



	void gameOverScreen(RenderWindow& window) {
		Event E;
		if (boss != nullptr) {
			Music loseMusic;
			loseMusic.openFromFile("music/gameover.mp3");
			loseMusic.play();
		}
		music.play();
		while (gameOver) {
			while (window.pollEvent(E))
			{
				if (E.type == Event::Closed)
					music.stop();
					window.close();
			}

			window.clear();
			if (boss == nullptr) {
				window.draw(winBG);
			}
			else {
				window.draw(loseBG);
			}
			scoring.setCharacterSize(50);
			scoring.setPosition(500, 320);
			scoring.setString("Final Score: " + to_string(score));
			window.draw(scoring);
			window.display();
			if (Keyboard::isKeyPressed(Keyboard::E)) {
				window.close();
				break;
			}
		}
	}
};



#endif