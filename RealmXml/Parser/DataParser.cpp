#include "stdafx.h"

#include <DataStructures/ProjectileData.h>
#include <DataStructures/TileData.h>
#include <DataStructures/ItemData.h>
#include <DataStructures/CharacterData.h>
#include <GameData/Constants.h>
#include "DataParser.h"
#include "Util/Util.h"

//TODO
//rewrite this monstrosity

#define MAX_STRINGS 524288
#define MAX_PROJECTILES 8192
#define MAX_EFFECTS 8192

char* stringPool = new char[MAX_STRINGS];
int stringOffset = 0;
ProjectileData* projectiles = new ProjectileData[MAX_PROJECTILES];
int projectilesAmount = 0;
ConditionEffectData* effects = new ConditionEffectData[MAX_EFFECTS];
int effectsAmount = 0;

TileData* tiles;
int tilesAmount = 0;
ItemData* items;
int itemsAmount = 0;
CharacterData* characters;
int charactersAmount = 0;

std::map<std::string, byte> effectNameToId
{
	{ "Dead", 0 },
	{ "Quiet", 1 },
	{ "Weak", 2 },
	{ "Slowed", 3 },
	{ "Sick", 4 },
	{ "Dazed", 5 },
	{ "Stunned", 6 },
	{ "Blind", 7 },
	{ "Hallucinating", 8 },
	{ "Drunk", 9 },
	{ "Confused", 10 },
	{ "StunImmume", 11 },
	{ "Invisible", 12 },
	{ "Paralyzed", 13 },
	{ "Speedy", 14 },
	{ "Bleeding", 15 },
	{ "Healing", 17 },
	{ "Damaging", 18 },
	{ "Berserk", 19 },
	{ "Paused", 20 },
	{ "Stasis", 21 },
	{ "StasisImmune", 22 },
	{ "Invincible", 23 },
	{ "Invulnerable", 24 },
	{ "Armored", 25 },
	{ "ArmorBroken", 26 },
	{ "Hexed", 27 },
	{ "NinjaSpeedy", 28 },
	{ "Unstable", 29 },
	{ "Darkness", 30 },
	{ "SlowedImmune", 31 },
	{ "DazedImmune", 32 },
	{ "ParalyzedImmune", 33 },
	{ "Petrified", 34 },
	{ "PetrifiedImmune", 35 },
	{ "PetEffectIcon", 36 },
	{ "Curse", 37 },
	{ "CurseImmune", 38 },
	{ "HPBoost", 39 },
	{ "MPBoost", 40 },
	{ "AttBoost", 41 },
	{ "DefBoost", 42 },
	{ "SpdBoost", 43 },
	{ "VitBoost", 44 },
	{ "WisBoost", 45 },
	{ "DexBoost", 46 },
	{ "Silenced", 47 },
	{ "Exposed", 59 }
};

void parseTile(TileData& tile, rapidxml::xml_node<char>* objectNode);
void parseCharacter(CharacterData& character, rapidxml::xml_node<char>* objectNode);
void parseConditionEffect(ConditionEffectData& effect, rapidxml::xml_node<char>* objectNode);
void parseProjectile(ProjectileData& projectile, rapidxml::xml_node<char>* objectNode);
void parseItem(ItemData& item, rapidxml::xml_node<char>* objectNode);
void save();

void DataParser::parse()
{
	{ //-------------- TILES -----------------
		rapidxml::file<char> xmlFile("GroundTypes.xml");
		tilesAmount = Util::occurences(xmlFile.data(), "</Ground>"); //count occurences before parsing

		rapidxml::xml_document<char> doc;
		doc.parse<0>(xmlFile.data());

		tiles = new TileData[tilesAmount];
		rapidxml::xml_node<char>* rootNode = doc.first_node("GroundTypes");
		int i = 0;
		for (rapidxml::xml_node<char>* objectNode = rootNode->first_node("Ground"); objectNode; objectNode = objectNode->next_sibling())
		{
			parseTile(tiles[i++], objectNode);
		}
		printf("tiles %d/%d\n", i, tilesAmount);
	}

	{ //--------------- OBJECTS ----------------
		rapidxml::file<char> xmlFile("Objects.xml");
		itemsAmount = Util::occurences(xmlFile.data(), "<Item/>");
		charactersAmount = Util::occurences(xmlFile.data(), "<Class>Character</Class>");

		rapidxml::xml_document<char> doc;
		doc.parse<0>(xmlFile.data());

		//--------------- ITEMS ----------------
		items = new ItemData[itemsAmount];
		rapidxml::xml_node<char>* rootNode = doc.first_node("Objects");
		int i = 0;
		for (rapidxml::xml_node<char>* objectNode = rootNode->first_node("Object"); objectNode; objectNode = objectNode->next_sibling())
		{
			if (objectNode->first_node("Item"))
			{
				parseItem(items[i++], objectNode);
			}
		}
		printf("items %d/%d\n", i, itemsAmount);

		//-------------- CHARACTERS ---------------
		characters = new CharacterData[charactersAmount];
		i = 0;
		for (rapidxml::xml_node<char>* objectNode = rootNode->first_node("Object"); objectNode; objectNode = objectNode->next_sibling())
		{
			if (objectNode->first_node("Class") && strcmp(objectNode->first_node("Class")->value(), "Character") == 0)
			{
				parseCharacter(characters[i++], objectNode);
			}
		}
		printf("characters %d/%d\n", i, charactersAmount);
	}
	printf("strings %d/%d\nprojectiles %d/%d\neffects %d/%d\n",
		stringOffset, MAX_STRINGS,
		projectilesAmount, MAX_PROJECTILES,
		effectsAmount, MAX_EFFECTS);

	save();
}

void parseTile(TileData& tile, rapidxml::xml_node<char>* objectNode)
{
	tile.type = std::stoi(objectNode->first_attribute("type")->value(), nullptr, 16);

	char* name = objectNode->first_attribute("id")->value();
	int offset = strlen(name) + 1;
	memcpy(stringPool + stringOffset, name, offset);
	tile.name = (char*)stringOffset;
	stringOffset += offset;

	tile.noWalk = objectNode->first_node("NoWalk") != nullptr;
	tile.speed = ((objectNode->first_node("Speed") != nullptr) ? std::strtof(objectNode->first_node("Speed")->value(), nullptr) : 1);
	tile.sink = objectNode->first_node("Sink") != nullptr;
	tile.minDamage = (objectNode->first_node("MinDamage") != nullptr ? atoi(objectNode->first_node("MinDamage")->value()) : 0);
	tile.maxDamage = (objectNode->first_node("MaxDamage") != nullptr ? atoi(objectNode->first_node("MaxDamage")->value()) : 0);
}

void parseCharacter(CharacterData& character, rapidxml::xml_node<char>* objectNode)
{
	character.dataClass = DataClass::CharacterData;
	character.type = std::stoi(objectNode->first_attribute("type")->value(), nullptr, 16);

	char* name = (objectNode->first_node("DisplayId") != nullptr ? objectNode->first_node("DisplayId")->value() : objectNode->first_attribute("id")->value());
	int offset = strlen(name) + 1;
	memcpy(stringPool + stringOffset, name, offset);
	character.name = (char*)stringOffset;
	stringOffset += offset;

	character.maxHp = (objectNode->first_node("MaxHitPoints") ? atoi(objectNode->first_node("MaxHitPoints")->value()) : 0);
	character.defense = (objectNode->first_node("Defense") ? atoi(objectNode->first_node("Defense")->value()) : 0);
	character.enemy = objectNode->first_node("Enemy") != nullptr;
	int i = 0;
	character.projectiles = (ProjectileData*)projectilesAmount;
	for (rapidxml::xml_node<char>* projNode = objectNode->first_node("Projectile"); projNode && strcmp(projNode->name(), "Projectile") == 0; projNode = projNode->next_sibling())
	{
		parseProjectile(projectiles[projectilesAmount++], projNode);
		i++;
	}
	character.projectilesAmount = i;
	if (i == 0)
		character.projectiles = 0;
}

void parseConditionEffect(ConditionEffectData& effect, rapidxml::xml_node<char>* objectNode)
{
	effect.effect = effectNameToId[objectNode->value()];
	if (objectNode->first_attribute("effect")) //mistake in the xml
		effect.duration = (int)(std::strtof(objectNode->first_attribute("effect")->value(), nullptr) * 1000);
	else
		effect.duration = (int)(std::strtof(objectNode->first_attribute("duration")->value(), nullptr) * 1000);
}

void parseProjectile(ProjectileData& projectile, rapidxml::xml_node<char>* objectNode)
{
	projectile.id = (objectNode->first_attribute("id") != nullptr ? atoi(objectNode->first_attribute("id")->value()) : 0);
	projectile.damage = (objectNode->first_node("Damage") != nullptr ? atoi(objectNode->first_node("Damage")->value()) : 0);
	projectile.lifetime = (objectNode->first_node("LifetimeMS") != nullptr ? atoi(objectNode->first_node("LifetimeMS")->value()) : 0);
	projectile.speed = (objectNode->first_node("Speed") != nullptr ? atoi(objectNode->first_node("Speed")->value()) / 10000.0f : 0);
	projectile.maxDamage = (objectNode->first_node("MaxDamage") != nullptr ? atoi(objectNode->first_node("MaxDamage")->value()) : 0);
	projectile.minDamage = (objectNode->first_node("MinDamage") != nullptr ? atoi(objectNode->first_node("MinDamage")->value()) : 0);
	projectile.amplitude = ((objectNode->first_node("Amplitude") != nullptr) ? std::strtof(objectNode->first_node("Amplitude")->value(), nullptr) : 0);
	projectile.frequency = ((objectNode->first_node("Frequency") != nullptr) ? std::strtof(objectNode->first_node("Frequency")->value(), nullptr) : 0);
	projectile.magnitude = ((objectNode->first_node("Magnitude") != nullptr) ? std::strtof(objectNode->first_node("Magnitude")->value(), nullptr) : 0);
	projectile.multiHit = objectNode->first_node("MultiHit") != nullptr;
	projectile.passesCover = objectNode->first_node("PassesCover") != nullptr;
	projectile.armorPierce = objectNode->first_node("ArmorPiercing") != nullptr;
	projectile.boomerang = objectNode->first_node("Boomerang") != nullptr;
	projectile.parametric = objectNode->first_node("Parametric") != nullptr;
	projectile.wavy = objectNode->first_node("Wavy") != nullptr;

	int i = 0;
	projectile.effects = (ConditionEffectData*)effectsAmount;
	for (rapidxml::xml_node<char>* effectsNode = objectNode->first_node("ConditionEffect"); effectsNode && strcmp(effectsNode->name(), "ConditionEffect") == 0; effectsNode = effectsNode->next_sibling())
	{
		parseConditionEffect(effects[effectsAmount++], effectsNode);
		i++;
	}
	projectile.effectsAmount = i;
	if (i == 0)
		projectile.effects = 0;
}

void parseItem(ItemData& item, rapidxml::xml_node<char>* objectNode)
{
	item.type = std::stoi(objectNode->first_attribute("type")->value(), nullptr, 16);

	char* name = (objectNode->first_node("DisplayId") == nullptr ? objectNode->first_attribute("id")->value() : objectNode->first_node("DisplayId")->value());
	int offset = strlen(name) + 1;
	memcpy(stringPool + stringOffset, name, offset);
	item.name = (char*)stringOffset;
	stringOffset += offset;

	item.slotType = atoi(objectNode->first_node("SlotType")->value());
	item.tier = (objectNode->first_node("Tier") != nullptr ? atoi(objectNode->first_node("Tier")->value()) : 255);
	item.bagType = (objectNode->first_node("BagType") != nullptr ? atoi(objectNode->first_node("BagType")->value()) : 0);
	item.numProjectiles = (objectNode->first_node("NumProjectiles") != nullptr ? atoi(objectNode->first_node("NumProjectiles")->value()) : (objectNode->first_node("Projectile") != nullptr ? 1 : 0));
	item.soulbound = objectNode->first_node("Soulbound") != nullptr;
	item.consumable = objectNode->first_node("Consumable") != nullptr;

	rapidxml::xml_node<char>* activateNode = objectNode->first_node("Activate");
	item.buffDuration = (activateNode != nullptr && (strcmp(activateNode->value(), "ConditionEffectAura") == 0 || strcmp(activateNode->value(), "ConditionEffectSelf") == 0) ?
		(int)(std::strtof(activateNode->first_attribute("duration")->value(), nullptr) * 1000) : 0);

	item.manaCost = (objectNode->first_node("MpCost") != nullptr ? atoi(objectNode->first_node("MpCost")->value()) : 0);
	item.cooldown = (objectNode->first_node("Cooldown") != nullptr ? (int)(std::strtof(objectNode->first_node("Cooldown")->value(), nullptr) * 1000) : (objectNode->first_node("Usable") != nullptr ? 500 : 0));
	item.feedPower = (objectNode->first_node("feedPower") != nullptr ? atoi(objectNode->first_node("feedPower")->value()) : 0);
	item.fireRate = (objectNode->first_node("RateOfFire") != nullptr ? std::strtof(objectNode->first_node("RateOfFire")->value(), nullptr) : 0);

	int i = 0;
	item.projectiles = (ProjectileData*)projectilesAmount;
	for (rapidxml::xml_node<char>* projNode = objectNode->first_node("Projectile"); projNode && strcmp(projNode->name(), "Projectile") == 0; projNode = projNode->next_sibling())
	{
		parseProjectile(projectiles[projectilesAmount++], projNode);
		i++;
	}
	item.projectilesAmount = i;
	if (i == 0)
		item.projectiles = 0;
}

void save()
{
	std::fstream bin("data.bin", std::ios::out | std::ios::binary);

	bin.write((char*)&stringOffset, 4);
	bin.write(stringPool, stringOffset);

	bin.write((char*)&effectsAmount, 4);
	bin.write((char*)effects, effectsAmount * sizeof(ConditionEffectData));

	bin.write((char*)&projectilesAmount, 4);
	bin.write((char*)projectiles, projectilesAmount * sizeof(ProjectileData));

	bin.write((char*)&tilesAmount, 4);
	bin.write((char*)tiles, tilesAmount * sizeof(TileData));

	bin.write((char*)&itemsAmount, 4);
	bin.write((char*)items, itemsAmount * sizeof(ItemData));

	bin.write((char*)&charactersAmount, 4);
	bin.write((char*)characters, charactersAmount * sizeof(CharacterData));

	bin.close();
}