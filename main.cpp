#include <SFML/Graphics.hpp>
#include <iostream>
#include "Map.h"

using namespace sf;
using namespace std;



int main() {
	RenderWindow win(VideoMode(WIN_SIZE_W, WIN_SIZE_H), L"ɨ��");
	Texture t;
	t.loadFromFile("mine.png");
	Sprite s(t);
	Map mp;

	mp.init(&win, &s);
	
	while (win.isOpen()) {
		Event e;
		Vector2i pos = Mouse::getPosition(win);
		int x = pos.x / GRID_SIZE;
		int y = pos.y / GRID_SIZE;

		while (win.pollEvent(e)) {
			if (e.type == Event::Closed) {
				cout << "���¹رհ�ť" << endl;
				win.close();
			}
			mp.handleMouseEvent(e, x, y);
		}
		mp.draw(x, y);
		win.display();
	}
	return 0;
}