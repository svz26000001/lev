#include <SFML/Graphics.hpp>
using namespace sf;

sf::View view;//�������� sfml ������ "���", ������� � �������� �������

void checkingCoord(float x, float y) { //������� ��� ���������� ��������� ������
	float tempX = x; float tempY = y;//��������� ����� ������ � ��������� ��, ����� ������ ����

	if (x < 320) tempX = 320;//������� �� ���� ����� �������
	if (y < 320) tempY = 320;//������� �������
	if (y > 528) tempY = 528;//������ �������	

	view.setCenter(tempX, tempY); //������ �� �������, ��������� ��� ����������. 

}