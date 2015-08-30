#pragma once

class CompoundTag;
class Item;
class Tile;

class ItemInstance {
public:
	short count;
	short data;
	CompoundTag* tag;
	Item* item;
	Tile* tile;

	ItemInstance();
	ItemInstance(const Tile*);
};