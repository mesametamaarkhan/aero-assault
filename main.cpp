

#include <iostream>
#include <SFML/Graphics.hpp>
#include "menu.h"
using namespace sf;
using namespace std;

void setEnemies(vector<Enemy*>& e) {
	Enemy* e1 = new Enemy("img/enemy.png", 1120, 0);
	e.push_back(e1);

	e1 = new Enemy("img/enemy2.jpg", 960, 100);
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

int main() {
	Menu m;
	RenderWindow window(VideoMode(1280, 720), "Aero Assault");
	m.display_menu(window);
	return 0;
}



