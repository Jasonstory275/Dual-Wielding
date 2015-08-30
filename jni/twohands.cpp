#include <jni.h>
#include <dlfcn.h>
#include <android/log.h>
#include <stdlib.h>
#include <substrate.h>

#include "mcpe/Item.h"
#include "mcpe/Tile.h"
#include "mcpe/ItemInstance.h"
#include "mcpe/Player.h"
#include "mcpe/ItemInHandRenderer.h"
#include "mcpe/Vec3.h"
#include "mcpe/MatrixStack.h"

static int USEITEM_VTABLE_OFFSET = 44; // TODO: Find this dynamically
ItemInstance LeftHandItem;


bool (*_Item$useOn)(Item*, ItemInstance*, Player*, int, int, int, signed char, float, float, float);
bool Item$useOn(Item* self, ItemInstance* usedItem, Player* player, int x, int y, int z, signed char side, float pixelX, float pixelY, float pixelZ) {

	// Compare the useOn vtable pointer of our right hand item with the default in Item
	// If they are the same then we use the left hand (because the right hand item does nothing)
	void** rightHandVtable = *((void***) usedItem->item);
	void* rightHandUseOn = rightHandVtable[USEITEM_VTABLE_OFFSET];
	void* defaultUseOn = (void*) &Item::useOn;
	if(rightHandUseOn == defaultUseOn || usedItem->item == NULL) {
		// Since the right hand item does nothing, use the left hand instead
		return LeftHandItem.item->useOn(&LeftHandItem, player, x, y, z, side, pixelX, pixelY, pixelZ);
	}
	// Use the right hand item if its class overrides Item::useOn
	return _Item$useOn(self, usedItem, player, x, y, z, side, pixelX, pixelY, pixelZ);
}

void (*_ItemInHandRenderer$render)(ItemInHandRenderer*, float);
void ItemInHandRenderer$render(ItemInHandRenderer* self, float partialTicks) {
	LeftHandItem = ItemInstance(Tile::rock); // TODO: Find a place for this and make it changeable

	_ItemInHandRenderer$render(self, partialTicks); // render the right hand

	MatrixStack::Ref matref = MatrixStack::World.push();
	matref.matrix->translate({-1.0F, 0.0F, 0.0F}); // move the render to the left side of the screen
	ItemInstance backup = self->itemToRender; // backup the item that's supposed to be rendered
	self->itemToRender = LeftHandItem;
	_ItemInHandRenderer$render(self, partialTicks); // render the left hand
	self->itemToRender = backup; // restore the intended item
}


JNIEXPORT jint JNI_OnLoad(JavaVM* vm, void* reserved) {
	MSHookFunction((void*) &ItemInHandRenderer::render, (void*) &ItemInHandRenderer$render, (void**) &_ItemInHandRenderer$render);
	MSHookFunction((void*) &Item::useOn, (void*) &Item$useOn, (void**) &_Item$useOn);
	return JNI_VERSION_1_2;
}
