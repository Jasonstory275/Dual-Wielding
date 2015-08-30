#pragma once

#include "ItemInstance.h"

class ItemInHandRenderer {
public:
	char filler[52];
	ItemInstance itemToRender;
	
	void render(float);
};