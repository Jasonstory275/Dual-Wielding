#include <jni.h>
#include <dlfcn.h>
#include <android/log.h>
#include <stdlib.h>
#include <substrate.h>

#include "mcpe/Item.h"
#include "mcpe/ItemInstance.h"
#include "mcpe/Player.h"
#include "mcpe/ItemInHandRenderer.h"
#include "mcpe/Vec3.h"
#include "mcpe/MatrixStack.h"
#include "mcpe/Gui.h"
#include "mcpe/MaterialPtr.h"


ItemInstance LeftHandItem;


void (*_Item$initItems)();
void Item$initItems() {
	_Item$initItems();
	
	LeftHandItem = ItemInstance(Item::items[5]); // Enter desired item/block id between these brackets
	// TODO: Find a better place for this and make it changeable
}

bool (*_Item$useOn)(Item*, ItemInstance*, Player*, int, int, int, signed char, float, float, float);
bool Item$useOn(Item* self, ItemInstance* usedItem, Player* player, int x, int y, int z, signed char side, float pixelX, float pixelY, float pixelZ) {
	// If this gets called then the right hand item is useless so we use the left hand item instead
	return LeftHandItem.item->useOn(&LeftHandItem, player, x, y, z, side, pixelX, pixelY, pixelZ);
}

void (*_ItemInHandRenderer$render)(ItemInHandRenderer*, float);
void ItemInHandRenderer$render(ItemInHandRenderer* self, float partialTicks) {
	_ItemInHandRenderer$render(self, partialTicks); // render the right hand

	MatrixStack::Ref matref = MatrixStack::Projection.push(); // Use MatrixStack::Projection instead of MatrixStack::World so it doesn't break ingame UI?
	matref.matrix->scale({-1.0F, 1.0F, -1.0F}); // so we don't have two right hands :P
	matref.matrix->translate({0.0F, 0.0F, 1.5F}); // fix backface culling issue
	ItemInstance backup = self->itemToRender; // backup the item that's supposed to be rendered
	self->itemToRender = LeftHandItem;
	_ItemInHandRenderer$render(self, partialTicks); // render the left hand
	self->itemToRender = backup; // restore the intended item
}

void (*_Gui$renderSlot)(Gui*, int, int, int, float);
void Gui$renderSlot(Gui* self, int id, int x, int y, float f) {
	_Gui$renderSlot(self, id, x, y, f);
	//self->blit(50, 50, 1, 1, 20, 20, 20, 20, self->mat);
	
}


JNIEXPORT jint JNI_OnLoad(JavaVM* vm, void* reserved) {
	MSHookFunction((void*) &ItemInHandRenderer::render, (void*) &ItemInHandRenderer$render, (void**) &_ItemInHandRenderer$render);
	MSHookFunction((void*) &Item::initItems, (void*) &Item$initItems, (void**) &_Item$initItems);
	MSHookFunction((void*) &Item::useOn, (void*) &Item$useOn, (void**) &_Item$useOn);
	//MSHookFunction((void*) &Gui::renderSlot, (void*) &Gui$renderSlot, (void**) &_Gui$renderSlot);
	return JNI_VERSION_1_2;
}
