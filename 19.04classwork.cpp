#include <iostream>
#include <vector>
#include <ctime>
using namespace std;

class Card {
protected:
	int value;
public:
	Card(int value = 0) {
		this->value = value;
	}
	Card(const Card &c) {
		this->value = c.value;
	}

	int get_value() {
		return this->value;
	}
	virtual ~Card() {
	}
	virtual void put()=0;
};

class Trump: public Card {
public:
	Trump(int value) :
			Card(value) {
	}
	~Trump() {
	}
	void put() override {
		cout << "Value is ";
		cout << this->value;
		cout << ". It's a trump card.";
		cout << endl;
	}
};

class NonTrump: public Card {
public:
	NonTrump(int value) :
			Card(value) {
	}
	~NonTrump() {
	}
	void put() override {
		cout << "Value is ";
		cout << this->value;
		cout << ". It's a non-trump card.";
		cout << endl;
	}
};

struct Vector3D {
	int x, y, z;
};

class Ammo {
private:
	Vector3D pos;
	Vector3D vector;
	int speed;
public:
	Ammo(Vector3D pos, Vector3D vector, int speed) {
		this->pos = pos;
		this->vector = vector;
		this->speed = speed;
	}

	void move() {
		pos.x += vector.x * speed;
		pos.y += vector.y * speed;
		pos.z += vector.z * speed;
	}

	virtual void spread() = 0;
};

class Ammo_AR: public Ammo {
public:

	Ammo_AR(Vector3D pos, Vector3D vector, int speed) :
			Ammo(pos, vector, speed) {
	}
	void spread() override {
		cout << "bang!" << endl;
	}
};

class Ammo_Shotgun: public Ammo {
public:
	Ammo_Shotgun(Vector3D pos, Vector3D vector, int speed) :
			Ammo(pos, vector, speed) {
	}
	void spread() override {
		cout << "bang!-bang!-bang!-bang!-bang!" << endl;
	}
};

class Gun {
protected:
	Vector3D pos;
	int calibre;
	int magazine;
public:
	Gun(Vector3D pos) {
		this->pos.x = pos.x;
		this->pos.y = pos.y;
		this->pos.z = pos.z;
	}
	virtual Ammo* shot() = 0;
	virtual void reload()=0;
};

class AR: public Gun {
public:
	AR(Vector3D pos) :
			Gun(pos) {
		calibre = 8;
		magazine = 30;
	}
	Ammo* shot() override {
		if (!magazine)
			this->reload();
		magazine--;
		return new Ammo_AR(pos, Vector3D { 1, 0, 0 }, 50 - calibre);
	}
	void reload() override {
		cout << "reloading..." << endl;
		this->magazine = 30;
	}
};

class Shotgun: public Gun {
public:
	Shotgun(Vector3D pos) :
			Gun(pos) {
		calibre = 40;
		magazine = 6;
	}
	Ammo* shot() override {
		if (!magazine)
			this->reload();
		magazine--;
		return new Ammo_Shotgun(pos, Vector3D { 1, 0, 0 }, 50 - calibre);
	}
	void reload() override {
		cout << "reloading..." << endl;
		this->magazine = 6;
	}
};

int main() {
	srand(time(0));
	vector<Card*> cards;
	for (int i = 0; i < 32; i++) {
		if (rand() % 100 < 30)
			cards.push_back(new Trump(rand() % 5 + 6));
		else
			cards.push_back(new NonTrump(rand() % 5 + 6));
	}
	int bj { };
	char c { };
	while (!cards.empty()) {
		cout << bj << endl;
		cout << "Take new card? [y/n]" << endl;
		cin >> c;
		if (c == 'y') {
			cards.back()->put();
			bj += cards.back()->get_value();
			cards.pop_back();
		} else if (c == 'n') {
			break;
		} else {
			cout << "Wrong command!" << endl;
		}
	}
	if (bj <= 21)
		cout << "Win!" << endl;
	else
		cout << "Bust" << endl;
	return 0;
}
