#include "hex.h"

HEX::HEX() {
	obj = new point[6];
	temp = new POINT[6];

	obj[0].x = 100;
	obj[0].y = 50;

	obj[1].x = 150;
	obj[1].y = 50;

	obj[2].x = 200;
	obj[2].y = 100;

	obj[3].x = 150;
	obj[3].y = 150;

	obj[4].x = 100;
	obj[4].y = 150;

	obj[5].x = 50;
	obj[5].y = 100;

	faces[0][0] = 0;
	faces[0][1] = 1;
	faces[0][2] = 2;

	faces[1][0] = 0;
	faces[1][1] = 2;
	faces[1][2] = 3;

	faces[2][0] = 0;
	faces[2][1] = 3;
	faces[2][2] = 4;

	faces[3][0] = 0;
	faces[3][1] = 5;
	faces[3][2] = 4;
}

HEX ::~HEX() {
	delete[] obj;
	delete[] temp;
}

void HEX::move(unsigned int axis, float speed) {
	switch (axis)
	{
	case 0:
		for (size_t i = 0; i < 6; i++) {
			obj[i].x += speed;
		}
		break;
		//по y
	case 1:
		for (size_t i = 0; i < 6; i++) {
			obj[i].y += speed;
		}
		break;
	default:
		break;
	}
}

void HEX::scale(float scale) {
	if (!(abs(obj[3].x - obj[0].x) < 1 && abs(obj[3].y - obj[0].y) < 1 && scale < 1)) {
		scale = ((scale - 1) / 2) + 1;
		float cX, cY;
		cX = (obj[0].x + obj[3].x) / 2;
		cY = (obj[0].y + obj[3].y) / 2;

		for (size_t i = 0; i < 6; i++) {
			obj[i].x = (obj[i].x - cX) * scale + cX;
			obj[i].y = (obj[i].y - cY) * scale + cY;
		}
	}
}

void HEX::rotate(double angle) {
	float cX, cY;
	cX = (obj[0].x + obj[3].x) / 2;
	cY = (obj[0].y + obj[3].y) / 2;

	float tempX;
	for (size_t i = 0; i < 6; i++) {
		tempX = obj[i].x;
		obj[i].x = (obj[i].x - cX) * cos(angle) - (obj[i].y - cY) * sin(angle) + cX;
		obj[i].y = (tempX - cX) * sin(angle) + (obj[i].y - cY) * cos(angle) + cY;
	}
}

POINT* HEX::getPoint() {
	for (size_t i = 0; i < 6; i++) {
		temp[i].x = static_cast<int>(obj[i].x);
		temp[i].y = static_cast<int>(obj[i].y);
	}
	return temp;
}

void HEX::showHex(HDC hdc) {
	for (size_t i = 0; i < 6; i++) {
		temp[i].x = static_cast<int>(obj[i].x);
		temp[i].y = static_cast<int>(obj[i].y);
	}
	HPEN hPen;
	hPen = CreatePen(PS_SOLID, 1, RGB(0, 0, 0));
	SelectObject(hdc, hPen);
	for (size_t i = 0, k = 1; i < 6; i++, k++) {
		MoveToEx(hdc, temp[i].x, temp[i].y, NULL);
		if (k == 6) k = 0;
		LineTo(hdc, temp[k].x, temp[k].y);
	}
	hPen = CreatePen(PS_SOLID, 1, RGB(255, 0, 0));
	SelectObject(hdc, hPen);
	shade(hdc);
}

void HEX::shade(HDC hdc) {
	for (size_t i = 0; i < 4; i++)	{
		long x = 0;
		long x1 = 0;

		if (temp[faces[i][0]].y > temp[faces[i][1]].y) std::swap(faces[i][0], faces[i][1]);
		if (temp[faces[i][1]].y > temp[faces[i][2]].y) std::swap(faces[i][1], faces[i][2]);
		if (temp[faces[i][0]].y > temp[faces[i][1]].y) std::swap(faces[i][0], faces[i][1]);
		unsigned int first = faces[i][0], last = faces[i][2], middle = faces[i][1];

		MoveToEx(hdc, temp[first].x, temp[first].y, NULL);
		LineTo(hdc, temp[last].x, temp[last].y);

		for (long y = temp[first].y ; y < temp[middle].y; y++)	{
			if ((temp[middle].y - temp[first].y)==0 || (temp[last].y - temp[first].y)==0) {
				continue;
			}
			x  = (((y - temp[first].y) * (temp[middle].x - temp[first].x)) / (temp[middle].y - temp[first].y) ) + temp[first].x;
			x1 = (((y - temp[first].y) * (temp[last].x - temp[first].x)) / (temp[last].y - temp[first].y)) + temp[first].x;
			MoveToEx(hdc, x, y, NULL);
			LineTo(hdc, x1, y);
		}

		for (long y = temp[middle].y ; y < temp[last].y; y++) {
			if ((temp[last].y - temp[middle].y) == 0 || (temp[last].y - temp[first].y) == 0) {
				continue;
			}
			x  = (((y - temp[middle].y) * (temp[last].x - temp[middle].x)) / (temp[last].y - temp[middle].y)) + temp[middle].x;
			x1 = (((y - temp[first].y) * (temp[last].x - temp[first].x)) / (temp[last].y - temp[first].y)) + temp[first].x;
			MoveToEx(hdc, x, y, NULL);
			LineTo(hdc, x1, y);
		}

	}
}