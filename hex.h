#ifndef HEX_H
#define HEX_H

#include <windows.h>
#include <cmath>
#include <iostream>
#define PI 3.14159265358979323846
#define gradToRad(x) x * PI/180 

struct point {
	float x, y;
};

class HEX {
public:
	HEX();
	~HEX();
	void move(unsigned int axis, float speed);
	void rotate(double angle);
	void scale(float scale);
	POINT* getPoint();
	POINT** getTri();
	void showHex(HDC hdc);

protected:
	void shade(HDC hdc);

private:
	unsigned int faces[4][3];
	point* obj = nullptr;
	POINT* temp = nullptr;
};

#endif // !HEX_H
