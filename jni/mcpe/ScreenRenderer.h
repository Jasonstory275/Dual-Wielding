#pragma once

namespace mce { class MaterialPtr; };

class ScreenRenderer {
public:
	void blit(int x, int y, int iconX, int iconY, int iconXend, int iconYend, int width, int height, mce::MaterialPtr* material);
};
