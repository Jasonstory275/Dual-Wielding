#pragma once

class ItemInstance;
class Player;

class Item {
public:
	virtual bool useOn(ItemInstance*, Player*, int, int, int, signed char, float, float, float);
};