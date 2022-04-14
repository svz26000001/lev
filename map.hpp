#include <SFML/Graphics.hpp>
#include <iostream>
const int HEIGHT_MAP = 24;
const int WIDTH_MAP = 24;


sf::String TileMap[HEIGHT_MAP] = {
	"000000000000000000000000",
	"0                      0",
	"0                      0",
	"0                      0",
	"0                      0",
	"0                      0",
	"0                      0",
	"0                      0",
	"0                      0",
	"0                      0",
	"0                      0",
	"0                      0",
	"0                      0",
	"0                      0",
	"0                      0",
	"0                      0",
	"0                      0",
	"0                      0",
	"0                      0",
	"0                      0",
	"0                      0",
	"0                      0",
	"0                      0",
	"000000000000000000000000",
};

void randomMapGenerate(char el, int count) {//�������� ����������� �����


	int randomElementX = 0;//��������� ������� �� �����������
	int randomElementY = 0;//���� ��-� �� ���������
	srand(time(0));//������	

	while (count > 0) {
		randomElementX = 1 + rand() % (WIDTH_MAP - 1);//��������� �� ���� �� 1 �� ������ �����-1, ����� �� �������� ����� ������� �����
		randomElementY = 1 + rand() % (HEIGHT_MAP - 1);//�� ������ ��� ��
		if (TileMap[randomElementY][randomElementX] == ' ') {//���� ��������� ������ ������, 
			TileMap[randomElementY][randomElementX] = el; //�� ������ ���� ������.
			//std::cout << "coordinate of Stone X:" << randomElementX << "\n" << "coordinate of Stone Y:" << randomElementY << "\n\n";
			count--;//������� ������=>������� ������ ����� "������� ����� 1"
		}
	}
}