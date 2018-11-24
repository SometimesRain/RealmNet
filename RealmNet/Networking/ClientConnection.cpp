#include "stdafx.h"

#include "ClientConnection.h"
#include "Proxy.h"
#include <GameData/Constants.h>
#include <GameData/ServerManager.h>
#include <Packets/ClientPackets.h>
#include <Packets/Reconnect.h>
#include "Data/SettingsFile.h"

ClientConnection::ClientConnection(Proxy* proxy, boost::asio::ip::tcp::socket* receiveSocket, boost::asio::ip::tcp::socket* sendSocket)
	: Connection(proxy, receiveSocket, sendSocket, RC4Cipher::key0)
{

}

void ClientConnection::onPacket()
{
	if (packetType == PacketType::Move)
	{
		Move p(receivePtr + headAccumulate);

		//update playerdata
		if (proxy.playerData.position.x != p.newPosition.x || proxy.playerData.position.y != p.newPosition.y)
			KeyHook::recentActivity = &proxy;
		proxy.playerData.position = p.newPosition;

		//update time
		proxy.previousTime = p.time;
		proxy.lastUpdate = std::chrono::steady_clock::now();

		fireCallbacks(p);
	}
	else if (packetType == PacketType::Escape)
	{
		//reconnect handler
		proxy.server.currentHost = proxy.server.defaultHost;
	}
	else if (packetType == PacketType::PlayerText)
	{
		PlayerText p(receivePtr + headAccumulate);

		//command hook
		if (p.text.c_str[0] == '/' && p.text.c_str[1] != ' ') //commands start with '/' followed by a non-space character
		{
			discardPacket(p);
			int argc = 0;
			int lastBegin = 1;
			const char** argv = (const char**)new char*[20]; //max 20 args

			for (size_t i = 1; i <= p.text.length; i++) //split to substrings (in-situ parsing = insert null terminators)
			{
				if (p.text.c_str[i] == ' ' || i == p.text.length)
				{
					p.text.c_str[i] = 0;
					argv[argc++] = p.text.c_str + lastBegin;
					lastBegin = i + 1;
				}
			}
			
			if (strcmp(argv[0], "go") == 0 && argc >= 2) //reconnect handler
			{
				for (size_t i = 0; i < Server::NUM_SERVERS; i++)
				{
					if (strcmp(argv[1], ServerManager::idToAbbr[i]) == 0)
					{
						//change server preference and reconnect
						proxy.server.defaultHost = ServerManager::idToAddr[i];
						proxy.server.currentHost = ServerManager::idToAddr[i];

						if (argc == 3 && strcmp(argv[2], "save") == 0)
						{
							SettingsFile::settings.defaultHost = ServerManager::idToAddr[i];
							SettingsFile::settings.save();
						}

						proxy.sendPacket(Reconnect("Proxy", "", -2));
					}
				}
			}
			else //plugin commands
			{
				for (auto& pair : proxy.commandCallbacks) //check and execute the command
				{
					if (strcmp(argv[0], pair.first) == 0)
						pair.second(argc, argv);
				}
			}

			//clean up
			delete[] argv;
		}

		fireCallbacks(p);
	}
	else if (packetType == PacketType::ClaimLoginReward)
	{
		ClaimLoginReward p(receivePtr + headAccumulate);

		//daily reward fix
		proxy.sendPacket(Reconnect("Proxy", "", -2));

		fireCallbacks(p);
	}
	else if (proxy.callbacks[packetType].size() == 0) return; //no packet instances need be created
	else if (packetType == PacketType::AcceptArenaDeath) { AcceptArenaDeath p(receivePtr + headAccumulate); fireCallbacks(p); }
	else if (packetType == PacketType::AcceptTrade) { AcceptTrade p(receivePtr + headAccumulate); fireCallbacks(p); }
	else if (packetType == PacketType::ActivePetUpdateRequest) { ActivePetUpdateRequest p(receivePtr + headAccumulate); fireCallbacks(p); }
	else if (packetType == PacketType::AoeAck) { AoeAck p(receivePtr + headAccumulate); fireCallbacks(p); }
	else if (packetType == PacketType::Buy) { Buy p(receivePtr + headAccumulate); fireCallbacks(p); }
	else if (packetType == PacketType::CancelTrade) { CancelTrade p(receivePtr + headAccumulate); fireCallbacks(p); }
	else if (packetType == PacketType::ChangeGuildRank) { ChangeGuildRank p(receivePtr + headAccumulate); fireCallbacks(p); }
	else if (packetType == PacketType::ChangePetSkin) { ChangePetSkin p(receivePtr + headAccumulate); fireCallbacks(p); }
	else if (packetType == PacketType::ChangeTrade) { ChangeTrade p(receivePtr + headAccumulate); fireCallbacks(p); }
	else if (packetType == PacketType::CheckCredits) { CheckCredits p(receivePtr + headAccumulate); fireCallbacks(p); }
	else if (packetType == PacketType::ChooseName) { ChooseName p(receivePtr + headAccumulate); fireCallbacks(p); }
	else if (packetType == PacketType::Create) { Create p(receivePtr + headAccumulate); fireCallbacks(p); }
	else if (packetType == PacketType::CreateGuild) { CreateGuild p(receivePtr + headAccumulate); fireCallbacks(p); }
	else if (packetType == PacketType::EditAccountList) { EditAccountList p(receivePtr + headAccumulate); fireCallbacks(p); }
	else if (packetType == PacketType::EnemyHit) { EnemyHit p(receivePtr + headAccumulate); fireCallbacks(p); }
	else if (packetType == PacketType::EnterArena) { EnterArena p(receivePtr + headAccumulate); fireCallbacks(p); }
	else if (packetType == PacketType::FetchQuest) { FetchQuest p(receivePtr + headAccumulate); fireCallbacks(p); }
	else if (packetType == PacketType::GotoAck) { GotoAck p(receivePtr + headAccumulate); fireCallbacks(p); }
	else if (packetType == PacketType::GotoQuestRoom) { GotoQuestRoom p(receivePtr + headAccumulate); fireCallbacks(p); }
	else if (packetType == PacketType::GroundDamage) { GroundDamage p(receivePtr + headAccumulate); fireCallbacks(p); }
	else if (packetType == PacketType::GuildInvite) { GuildInvite p(receivePtr + headAccumulate); fireCallbacks(p); }
	else if (packetType == PacketType::GuildRemove) { GuildRemove p(receivePtr + headAccumulate); fireCallbacks(p); }
	else if (packetType == PacketType::Hello) { Hello p(receivePtr + headAccumulate); fireCallbacks(p); }
	else if (packetType == PacketType::InvDrop) { InvDrop p(receivePtr + headAccumulate); fireCallbacks(p); }
	else if (packetType == PacketType::InvSwap) { InvSwap p(receivePtr + headAccumulate); fireCallbacks(p); }
	else if (packetType == PacketType::JoinGuild) { JoinGuild p(receivePtr + headAccumulate); fireCallbacks(p); }
	else if (packetType == PacketType::KeyInfoRequest) { KeyInfoRequest p(receivePtr + headAccumulate); fireCallbacks(p); }
	else if (packetType == PacketType::Load) { Load p(receivePtr + headAccumulate); fireCallbacks(p); }
	else if (packetType == PacketType::OtherHit) { OtherHit p(receivePtr + headAccumulate); fireCallbacks(p); }
	else if (packetType == PacketType::PetUpgradeRequest) { PetUpgradeRequest p(receivePtr + headAccumulate); fireCallbacks(p); }
	else if (packetType == PacketType::PlayerHit) { PlayerHit p(receivePtr + headAccumulate); fireCallbacks(p); }
	else if (packetType == PacketType::PlayerShoot) { PlayerShoot p(receivePtr + headAccumulate); fireCallbacks(p); }
	else if (packetType == PacketType::Pong) { Pong p(receivePtr + headAccumulate); fireCallbacks(p); }
	else if (packetType == PacketType::QuestRedeem) { QuestRedeem p(receivePtr + headAccumulate); fireCallbacks(p); }
	else if (packetType == PacketType::RequestTrade) { RequestTrade p(receivePtr + headAccumulate); fireCallbacks(p); }
	else if (packetType == PacketType::Reskin) { Reskin p(receivePtr + headAccumulate); fireCallbacks(p); }
	else if (packetType == PacketType::ReskinPet) { ReskinPet p(receivePtr + headAccumulate); fireCallbacks(p); }
	else if (packetType == PacketType::SetCondition) { SetCondition p(receivePtr + headAccumulate); fireCallbacks(p); }
	else if (packetType == PacketType::ShootAck) { ShootAck p(receivePtr + headAccumulate); fireCallbacks(p); }
	else if (packetType == PacketType::SquareHit) { SquareHit p(receivePtr + headAccumulate); fireCallbacks(p); }
	else if (packetType == PacketType::Teleport) { Teleport p(receivePtr + headAccumulate); fireCallbacks(p); }
	else if (packetType == PacketType::UpdateAck) { UpdateAck p(receivePtr + headAccumulate); fireCallbacks(p); }
	else if (packetType == PacketType::UseItem) { UseItem p(receivePtr + headAccumulate); fireCallbacks(p); }
	else if (packetType == PacketType::UsePortal) { UsePortal p(receivePtr + headAccumulate); fireCallbacks(p); }
	else if (packetType == PacketType::Escape) { auto p(Escape::Escape(receivePtr + headAccumulate)); fireCallbacks(p); } //a little trickery with the escape packet
}