#include "stdafx.h"

#include "ServerConnection.h"
#include "Proxy.h"
#include <GameData/Constants.h>
#include <Packets/ServerPackets.h>

ServerConnection::ServerConnection(Proxy* proxy, boost::asio::ip::tcp::socket* receiveSocket, boost::asio::ip::tcp::socket* sendSocket)
	: Connection(proxy, receiveSocket, sendSocket, RC4Cipher::key1)
{

}

void ServerConnection::closeSocket()
{
	receiveSocket->close();
}

void ServerConnection::onPacket()
{
	if (packetType == PacketType::Update)
	{
		Update p(receivePtr + headAccumulate);

		//update playerdata
		for (size_t i = 0; i < p.newObjs.length; i++)
		{
			if (p.newObjs[i].status.objectId == proxy.playerData.objectId)
			{
				proxy.playerData.objectType = p.newObjs[i].objectType;
				updateStatData(p.newObjs[i].status.data);
			}
		}

		fireCallbacks(p);
	}
	else if (packetType == PacketType::NewTick)
	{
		NewTick p(receivePtr + headAccumulate);

		//update playerdata
		for (size_t i = 0; i < p.statuses.length; i++)
			if (p.statuses[i].objectId == proxy.playerData.objectId)
				updateStatData(p.statuses[i].data);

		fireCallbacks(p);
	}
	else if (packetType == PacketType::CreateSuccess)
	{
		CreateSuccess p(receivePtr + headAccumulate);

		//update playerdata
		proxy.playerData.objectId = p.objectId;

		fireCallbacks(p);
	}
	else if (packetType == PacketType::Reconnect)
	{
		Reconnect p(receivePtr + headAccumulate);

		//reconnect handler
		if (p.host != "")
		{
			proxy.server.currentHost = p.host;
			p.host = "";
			updatePacket(p);
		}

		fireCallbacks(p);
	}
	else if (packetType == PacketType::Failure)
	{
		Failure p(receivePtr + headAccumulate);

		printf("FAILURE %d: %s\n", p.errorId, p.message.c_str);

		fireCallbacks(p);
	}
	else if (proxy.callbacks[packetType].size() == 0) return; //no packet instances need be created
	else if (packetType == PacketType::AccountList) { AccountList p(receivePtr + headAccumulate); fireCallbacks(p); }
	else if (packetType == PacketType::ActivePetUpdate) { ActivePetUpdate p(receivePtr + headAccumulate); fireCallbacks(p); }
	else if (packetType == PacketType::AllyShoot) { AllyShoot p(receivePtr + headAccumulate); fireCallbacks(p); }
	else if (packetType == PacketType::Aoe) { Aoe p(receivePtr + headAccumulate); fireCallbacks(p); }
	else if (packetType == PacketType::ArenaDeath) { ArenaDeath p(receivePtr + headAccumulate); fireCallbacks(p); }
	else if (packetType == PacketType::ArenaNextWave) { ArenaNextWave p(receivePtr + headAccumulate); fireCallbacks(p); }
	else if (packetType == PacketType::BuyResult) { BuyResult p(receivePtr + headAccumulate); fireCallbacks(p); }
	else if (packetType == PacketType::ClaimLoginRewardResponse) { ClaimLoginRewardResponse p(receivePtr + headAccumulate); fireCallbacks(p); }
	else if (packetType == PacketType::ClientStat) { ClientStat p(receivePtr + headAccumulate); fireCallbacks(p); }
	else if (packetType == PacketType::Damage) { Damage p(receivePtr + headAccumulate); fireCallbacks(p); }
	else if (packetType == PacketType::Death) { Death p(receivePtr + headAccumulate); fireCallbacks(p); }
	else if (packetType == PacketType::EnemyShoot) { EnemyShoot p(receivePtr + headAccumulate); fireCallbacks(p); }
	else if (packetType == PacketType::FetchQuestResponse) { FetchQuestResponse p(receivePtr + headAccumulate); fireCallbacks(p); }
	else if (packetType == PacketType::File) { File p(receivePtr + headAccumulate); fireCallbacks(p); }
	else if (packetType == PacketType::GlobalNotification) { GlobalNotification p(receivePtr + headAccumulate); fireCallbacks(p); }
	else if (packetType == PacketType::Goto) { Goto p(receivePtr + headAccumulate); fireCallbacks(p); }
	else if (packetType == PacketType::GuildResult) { GuildResult p(receivePtr + headAccumulate); fireCallbacks(p); }
	else if (packetType == PacketType::InvitedToGuild) { InvitedToGuild p(receivePtr + headAccumulate); fireCallbacks(p); }
	else if (packetType == PacketType::InvResult) { InvResult p(receivePtr + headAccumulate); fireCallbacks(p); }
	else if (packetType == PacketType::KeyInfoResponse) { KeyInfoResponse p(receivePtr + headAccumulate); fireCallbacks(p); }
	else if (packetType == PacketType::MapInfo) { MapInfo p(receivePtr + headAccumulate); fireCallbacks(p); }
	else if (packetType == PacketType::NameResult) { NameResult p(receivePtr + headAccumulate); fireCallbacks(p); }
	else if (packetType == PacketType::NewAbilityUnlocked) { NewAbilityUnlocked p(receivePtr + headAccumulate); fireCallbacks(p); }
	else if (packetType == PacketType::Notification) { Notification p(receivePtr + headAccumulate); fireCallbacks(p); }
	else if (packetType == PacketType::PasswordPrompt) { PasswordPrompt p(receivePtr + headAccumulate); fireCallbacks(p); }
	else if (packetType == PacketType::PetDeleted) { PetDeleted p(receivePtr + headAccumulate); fireCallbacks(p); }
	else if (packetType == PacketType::PetEvolved) { PetEvolved p(receivePtr + headAccumulate); fireCallbacks(p); }
	else if (packetType == PacketType::PetHatched) { PetHatched p(receivePtr + headAccumulate); fireCallbacks(p); }
	else if (packetType == PacketType::PetYardUpdate) { PetYardUpdate p(receivePtr + headAccumulate); fireCallbacks(p); }
	else if (packetType == PacketType::Pic) { Pic p(receivePtr + headAccumulate); fireCallbacks(p); }
	else if (packetType == PacketType::Ping) { Ping p(receivePtr + headAccumulate); fireCallbacks(p); }
	else if (packetType == PacketType::PlaySound) { PlaySound p(receivePtr + headAccumulate); fireCallbacks(p); }
	else if (packetType == PacketType::QuestObjId) { QuestObjId p(receivePtr + headAccumulate); fireCallbacks(p); }
	else if (packetType == PacketType::QuestRedeemResponse) { QuestRedeemResponse p(receivePtr + headAccumulate); fireCallbacks(p); }
	else if (packetType == PacketType::ReskinUnlock) { ReskinUnlock p(receivePtr + headAccumulate); fireCallbacks(p); }
	else if (packetType == PacketType::ServerPlayerShoot) { ServerPlayerShoot p(receivePtr + headAccumulate); fireCallbacks(p); }
	else if (packetType == PacketType::ShowEffect) { ShowEffect p(receivePtr + headAccumulate); fireCallbacks(p); }
	else if (packetType == PacketType::Text) { Text p(receivePtr + headAccumulate); fireCallbacks(p); }
	else if (packetType == PacketType::TradeAccepted) { TradeAccepted p(receivePtr + headAccumulate); fireCallbacks(p); }
	else if (packetType == PacketType::TradeChanged) { TradeChanged p(receivePtr + headAccumulate); fireCallbacks(p); }
	else if (packetType == PacketType::TradeDone) { TradeDone p(receivePtr + headAccumulate); fireCallbacks(p); }
	else if (packetType == PacketType::TradeRequested) { TradeRequested p(receivePtr + headAccumulate); fireCallbacks(p); }
	else if (packetType == PacketType::TradeStart) { TradeStart p(receivePtr + headAccumulate); fireCallbacks(p); }
	else if (packetType == PacketType::VerifyEmail) { VerifyEmail p(receivePtr + headAccumulate); fireCallbacks(p); }
}

void ServerConnection::updateStatData(const Array<StatData>& data)
{
	for (size_t i = 0; i < data.length; i++)
	{
		//inventory
		if (data[i].id >= Stat::Inventory0 && data[i].id <= Stat::Inventory11)
			proxy.playerData.inventory[data[i].id - Stat::Inventory0] = data[i].intValue;
		else if (data[i].id >= Stat::Backpack0 && data[i].id <= Stat::Backpack7)
			proxy.playerData.inventory[data[i].id - Stat::Backpack0 + 12] = data[i].intValue;
		else if (data[i].id == Stat::HasBackpack && data[i].intValue == 0)
			memset(proxy.playerData.inventory + 12, 0, 8 * sizeof(int));
		//effects
		else if (data[i].id == Stat::Effects)
			proxy.playerData.effects = data[i].intValue;
		else if (data[i].id == Stat::Effects2)
			proxy.playerData.effects2 = data[i].intValue;
		//stats
		else if (data[i].id == Stat::MaximumHP)
			proxy.playerData.maxHp = data[i].intValue;
		else if (data[i].id == Stat::HP)
			proxy.playerData.hp = data[i].intValue;
		else if (data[i].id == Stat::MaximumMP)
			proxy.playerData.maxMp = data[i].intValue;
		else if (data[i].id == Stat::MP)
			proxy.playerData.mp = data[i].intValue;
		else if (data[i].id == Stat::Attack)
			proxy.playerData.attack = data[i].intValue;
		else if (data[i].id == Stat::Defense)
			proxy.playerData.defense = data[i].intValue;
		else if (data[i].id == Stat::Speed)
			proxy.playerData.speed = data[i].intValue;
		else if (data[i].id == Stat::Dexterity)
			proxy.playerData.dexterity = data[i].intValue;
		else if (data[i].id == Stat::Wisdom)
			proxy.playerData.wisdom = data[i].intValue;
		else if (data[i].id == Stat::Vitality)
			proxy.playerData.vitality = data[i].intValue;
		//dungeon specific
		else if (data[i].id == Stat::OxygenBar)
			proxy.playerData.oxygen = data[i].intValue;
		else if (data[i].id == Stat::SinkLevel)
			proxy.playerData.sinkLevel = data[i].intValue;
		//name
		else if (data[i].id == Stat::Name)
			proxy.playerData.name = data[i].stringValue;
	}
}

/*
	unimplemented (remove when added):
		Size = 2,
		NextLevelExperience = 5,
		Experience = 6,
		Level = 7,
		Stars = 30,
		Texture1 = 32,
		Texture2 = 33,
		MerchandiseType = 34,
		Credits = 35,
		MerchandisePrice = 36,
		PortalUsable = 37,
		AccountId = 38,
		AccountFame = 39,
		MerchandiseCurrency = 40,
		ObjectConnection = 41,
		MerchandiseRemainingCount = 42,
		MerchandiseRemainingMinutes = 43,
		MerchandiseDiscount = 44,
		MerchandiseRankRequirement = 45,
		HealthBonus = 46,
		ManaBonus = 47,
		AttackBonus = 48,
		DefenseBonus = 49,
		SpeedBonus = 50,
		VitalityBonus = 51,
		WisdomBonus = 52,
		DexterityBonus = 53,
		OwnerAccountId = 54,
		RankRequired = 55,
		NameChosen = 56,
		CharacterFame = 57,
		CharacterFameGoal = 58,
		Glowing = 59,
		AltTextureIndex = 61,
		GuildName = 62,
		GuildRank = 63,
		XpBoosterActive = 65,
		XpBoostTime = 66,
		LootDropBoostTime = 67,
		LootTierBoostTime = 68,
		HealthPotionCount = 69,
		MagicPotionCount = 70,
		Skin = 80,
		PetInstanceId = 81,
		PetName = 82,
		PetType = 83,
		PetRarity = 84,
		PetMaximumLevel = 85,
		PetFamily = 86,
		PetPoints0 = 87,
		PetPoints1 = 88,
		PetPoints2 = 89,
		PetLevel0 = 90,
		PetLevel1 = 91,
		PetLevel2 = 92,
		PetAbilityType0 = 93,
		PetAbilityType1 = 94,
		PetAbilityType2 = 95,
		FortuneTokens = 97
*/