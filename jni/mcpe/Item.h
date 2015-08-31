#pragma once

#include <string>

class Tile;
class ItemInstance;
class TextureUVCoordinateSet;
class Entity;
class Player;
class Mob;
class Level;
class Tile;
namespace RakNet { class BitStream; };

class Item {
public:

	// Use the entire vtable so virtual calls work correctly :P

	virtual ~Item();
	virtual int getMaxStackSize(const ItemInstance*);
	virtual void setMaxStackSize(unsigned char);
	virtual bool canBeDepleted();
	virtual TextureUVCoordinateSet getIcon(int, int, bool) const;
	virtual int getIconYOffset() const;
	virtual void setIcon(std::string const&, int);
	virtual void setIcon(TextureUVCoordinateSet);
	virtual bool isMirroredArt() const;
	virtual void use(ItemInstance&, Player&);
	virtual bool useOn(ItemInstance*, Player*, int, int, int, signed char, float, float, float);
	virtual int getMaxUseDuration() const;
	virtual void useTimeDepleted(ItemInstance*, Level*, Player*);
	virtual int getUseAnimation() const;
	virtual void releaseUsing(ItemInstance*, Player*, int);
	virtual float getDestroySpeed(ItemInstance*, Tile*);
	virtual bool canDestroySpecial(const Tile*) const;
	virtual void* getLevelDataForAuxValue(int) const;
	virtual bool isStackedByData() const;
	virtual int getMaxDamage();
	virtual int getAttackDamage(Entity*);
	virtual void hurtEnemy(ItemInstance*, Mob*, Mob*);
	virtual void interactEnemy(ItemInstance*, Mob*, Player*);
	virtual void mineBlock(ItemInstance*, int, int, int, int, Mob*);
	virtual void handEquipped();
	virtual bool isHandEquipped() const;
	virtual bool isFood() const;
	virtual bool isSeed() const;
	virtual bool isArmor() const;
	virtual bool isDye() const;
	virtual bool isFoil(const ItemInstance*) const;
	virtual bool isThrowable() const;
	virtual bool isLiquidClipItem(int) const;
	virtual bool requiresInteract() const;
	virtual std::string getInteractText() const;
	virtual std::string getName(const ItemInstance*) const;
	virtual std::string getEffectName(const ItemInstance&) const;
	virtual void appendFormattedHovertext(std::string&, const ItemInstance&) const;
	virtual void setNameID(std::string const&);
	virtual void readUserData(ItemInstance*, RakNet::BitStream*) const;
	virtual void writeUserData(const ItemInstance*, RakNet::BitStream*, bool) const;
	virtual bool isEmissive(int) const;
	virtual int getAnimationFrameFor(Mob&) const;
	virtual bool isValidRepairItem(const ItemInstance&, const ItemInstance&);
	virtual int getEnchantSlot() const;
	virtual int getEnchantValue() const;

	static void initItems();

	static Item* items[512];
};
