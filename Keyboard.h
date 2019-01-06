#pragma once
#include "Camera.h"

class Keyboard {
private:
	bool key_s = true;
	bool key_l = true;
	bool key_n = true;
	bool key_c = true;

public:
	bool getKey(char c) {
		switch (c) {
		case('s'):
			return key_s;
			break;
		case('l'):
			return key_l;
			break;
		case('n'):
			return key_n;
			break;
		case('c'):
			return key_c;
			break;
		}
	}

	void setKey(char c) {
		switch (c) {
		case('s'):
			key_s = !key_s;
			break;
		case('l'):
			key_s = !key_l;
			break;
		case('n'):
			key_s = !key_n;
			break;
		case('c'):
			key_s = !key_c;
			break;
		}
	}
};