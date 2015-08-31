#pragma once

#include "ScreenRenderer.h"
namespace mce { class MaterialPtr; };

class Gui : public ScreenRenderer {
public:
	char filler[52];
	mce::MaterialPtr* mat;
	
	void renderSlot(int, int, int, float);
	void renderToolBar(float, float);
};
