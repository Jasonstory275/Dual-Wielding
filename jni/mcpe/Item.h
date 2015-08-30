#pragma once

class ItemInstance;
class Player;

class Item {
public:
	virtual void useOn(ItemInstance*, Player*, int, int, int, signed char, float, float, float);
};