﻿#include <SFML/Graphics.hpp>
#include "map.hpp"
#include "view.hpp"
#include <iostream>
#include <sstream>

using namespace sf;

////////////////////////////////////////////////////2022 КЛАСС ИГРОКА 2022////////////////////////
class Player { 
	/* это задел на следующие уроки,прошу не обращать внимания)
private: float w, h, dx, dy, x, y, speed;
		 int dir, playerScore, health;
		 bool life;
		 */

public:
	float w, h, dx, dy, x, y, speed;
	int dir, playerScore, health;
	bool life, isMove, isSelect;//добавили переменные состояния движения и выбора объекта
	String File;
	Image image;
	Texture texture;
	Sprite sprite;
	Player(String F, float X, float Y, float W, float H) {
		dir = 0; speed = 0; playerScore = 0; health = 100; dx = 0; dy = 0;
		life = true; isMove = false; isSelect = false;
		File = F;
		w = W; h = H;
		image.loadFromFile("images/" + File);
		image.createMaskFromColor(Color(0, 0, 255));
		texture.loadFromImage(image);
		sprite.setTexture(texture);

		x = X; y = Y;
		sprite.setTextureRect(IntRect(0, 0, w, h));
		//sprite.setOrigin(w / 2, h / 2);
	}
	void update(float time)
	{
		switch (dir)
		{
		case 0: dx = speed; dy = 0; break;
		case 1: dx = -speed; dy = 0; break;
		case 2: dx = 0; dy = speed; break;
		case 3: dx = 0; dy = -speed; break;
		}

		x += dx * time;
		y += dy * time;
		if (!isMove) speed = 0;
		sprite.setPosition(x, y);
		interactionWithMap();
		if (health <= 0) { life = false; }

	}

	float getWidth() {//получить ширину объека
		return w;
	}
	void setWidth(float width) {//установить ширину объекта
		w = width;
	}

	float getHeight() {//взять ширину объекта
		return h;
	}
	void setHeight(float height) {//задать ширину объекта
		h = height;
	}

	float getX() {
		return x;
	}
	float getY() {
		return y;
	}


	void interactionWithMap()
	{

		for (int i = y / 32; i < (y + h) / 32; i++)
			for (int j = x / 32; j < (x + w) / 32; j++)
			{
				std::cout << i << '\t' << j << '\t' << x << '\t' << y << '\t' << x + w << '\t' << y + h << '\t' << health << std::endl;
				if (TileMap[i][j] == '0')
				{
					if (dy > 0)
					{
						y = i * 32 - h;
					}
					if (dy < 0)
					{
						y = i * 32 + 32;
					}
					if (dx > 0)
					{
						x = j * 32 - w;
					}
					if (dx < 0)
					{
						x = j * 32 + 32;
					}
				}

				if (TileMap[i][j] == 'c') {
					playerScore++;
					TileMap[i][j] = ' ';
				}

				if (TileMap[i][j] == 'f') {
					health -= 40;
					TileMap[i][j] = ' ';
				}

				if (TileMap[i][j] == 'h') {
					health += 20;
					TileMap[i][j] = ' ';
				}

			}
	}

};

class SpriteManager {//это задел на следующие уроки,прошу не обращать внимания на эти изменения)
public:
	Image image;
	Texture texture;
	Sprite sprite;
	String name;
	String file;
	int widthOfSprite;
	int heightOfSprite;
	SpriteManager(String File, String Name) {
		file = File;
		name = Name;
		image.loadFromFile("images/" + file);
		texture.loadFromImage(image);
		sprite.setTexture(texture);
	}
};


int main()
{


	RenderWindow window(VideoMode(640, 640), "Lesson 19. kychka-pc.ru");
	view.reset(FloatRect(0, 0, 640, 640));

	Font font;
	Text text("", font, 20);
	text.setFillColor(Color::Black);

	Image map_image;
	map_image.loadFromFile("images/map.png");
	map_image.createMaskFromColor(Color::Color(164, 35, 167));
	Texture map;
	map.loadFromImage(map_image);
	Sprite s_map;
	s_map.setTexture(map);

	//SpriteManager playerSprite("hero.png", "Hero");//это задел на следующие уроки,прошу не обращать внимания)

	Player p("GreenLion.png", 250, 250, 96, 96);

	float currentFrame = 0;
	Clock clock;
	float dX = 0;
	float dY = 0;
	int tempX = 0;//временная коорд Х.Снимаем ее после нажатия прав клав мыши
	int tempY = 0;//коорд Y
	float distance = 0;//это расстояние от объекта до тыка курсора

	randomMapGenerate('c', 15);
	randomMapGenerate('f', 15);
	randomMapGenerate('h', 10);

	while (window.isOpen())
	{

		float time = clock.getElapsedTime().asMicroseconds();

		clock.restart();
		time = time / 800;

		Vector2i pixelPos = Mouse::getPosition(window);//забираем коорд курсора
		Vector2f pos = window.mapPixelToCoords(pixelPos);//переводим их в игровые (уходим от коорд окна)


		Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window.close();

			if (event.type == Event::MouseButtonPressed) {//если нажата клавиша мыши
				if (event.key.code == Mouse::Left) {//а именно левая
					if (p.sprite.getGlobalBounds().contains(pos.x, pos.y))//и при этом координата курсора попадает в спрайт
					{
						p.sprite.setColor(Color::Green);//красим спрайт в зеленый,тем самым говоря игроку,что он выбрал персонажа и может сделать ход
						p.isSelect = true;
					}
				}


				if (p.isSelect)//если выбрали объект
					if (event.key.code == Mouse::Right) {//а именно правая
						p.isMove = true;//то начинаем движение
						p.isSelect = false;//объект уже не выбран
						p.sprite.setColor(Color::White);//возвращаем обычный цвет спрайту
						tempX = pos.x;//забираем координату нажатия курсора Х
						tempY = pos.y;//и Y
					}
			}
		}


		if (p.isMove) {
			distance = sqrt((tempX - p.x) * (tempX - p.x) + (tempY - p.y) * (tempY - p.y));//считаем дистанцию (расстояние от точки А до точки Б). используя формулу длины вектора

			if (distance > 2) {//этим условием убираем дергание во время конечной позиции спрайта

				p.x += 0.1 * time * (tempX - p.x) / distance;//идем по иксу с помощью вектора нормали
				p.y += 0.1 * time * (tempY - p.y) / distance;//идем по игреку так же
			}
			else { p.isMove = false; std::cout << "priehali\n"; }//говорим что уже никуда не идем и выводим веселое сообщение в консоль
		}



		/*				Поворот

		float dX = pos.x - p.x;//вектор , колинеарный прямой, которая пересекает спрайт и курсор
		float dY = pos.y - p.y;//он же, координата y
		float rotation = (atan2(dY, dX)) * 180 / 3.14159265;//получаем угол в радианах и переводим его в градусы
		std::cout << rotation << "\n";//смотрим на градусы в консольке
		p.sprite.setRotation(rotation);//поворачиваем спрайт на эти градусы
		*/

		///////////////////////////////////////////Управление персонажем с анимацией////////////////////////////////////////////////////////////////////////
		if (p.life) {
			if (Keyboard::isKeyPressed(Keyboard::A)) {
				p.dir = 1; p.speed = 0.1;
				currentFrame += 0.005 * time;
				if (currentFrame > 3) currentFrame -= 3;
				p.sprite.setTextureRect(IntRect(96 * int(currentFrame), 96, 96, 96));
			}

			else if (Keyboard::isKeyPressed(Keyboard::D)) {
				p.dir = 0; p.speed = 0.1;
				currentFrame += 0.005 * time;
				if (currentFrame > 3) currentFrame -= 3;
				p.sprite.setTextureRect(IntRect(96 * int(currentFrame), 192, 96, 96));
			}

			else if (Keyboard::isKeyPressed(Keyboard::W)) {
				p.dir = 3; p.speed = 0.1;
				currentFrame += 0.005 * time;
				if (currentFrame > 3) currentFrame -= 3;
				p.sprite.setTextureRect(IntRect(96 * int(currentFrame), 307, 96, 96));
			}

			else if (Keyboard::isKeyPressed(Keyboard::S)) {
				p.dir = 2; p.speed = 0.1;

				currentFrame += 0.005 * time;
				if (currentFrame > 3) currentFrame -= 3;
				p.sprite.setTextureRect(IntRect(96 * int(currentFrame), 0, 96, 96));
			}
			checkingCoord(p.getX(), p.getY());
		}
		else view.zoom(1.0015);

		p.update(time);


		window.setView(view);
		window.clear();

		window.getSystemHandle();

		for (int i = 0; i < HEIGHT_MAP; i++)
			for (int j = 0; j < WIDTH_MAP; j++)
			{
				s_map.setTextureRect(IntRect(0, 0, 32, 32));			//Space' '
				s_map.setPosition(j * 32, i * 32);
				window.draw(s_map);

				if (TileMap[i][j] == '0') s_map.setTextureRect(IntRect(64, 0, 32, 32));
				if (TileMap[i][j] == 'c') s_map.setTextureRect(IntRect(32, 0, 32, 32));
				if (TileMap[i][j] == 'f') s_map.setTextureRect(IntRect(96, 0, 32, 32));
				if (TileMap[i][j] == 'h') s_map.setTextureRect(IntRect(128, 0, 32, 32)); 
			
				s_map.setPosition(j * 32, i * 32);
				window.draw(s_map);
			}
		std::ostringstream OSHealth, OSCoins;
		OSHealth << "Всего жизней: " << p.health << std::endl;
		OSCoins << "Счёт: " << p.playerScore << std::endl;
		text.setString(OSHealth.str());
		text.setString(OSCoins.str());
		text.setPosition(view.getCenter().x - 250, view.getCenter().y - 250);

		window.draw(p.sprite);
		window.draw(text);
		window.display();
	}
	return 0;
}