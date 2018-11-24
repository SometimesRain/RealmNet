#include "stdafx.h"

#include <GameData/Constants.h>
#include <GameData/TypeManager.h>
#include "Packets/PacketWriter.h"
#include "Packets/PacketReader.h"
#include "Util/Random.h"

#include <Packets/Hello.h>

Hello::Hello(const String& buildVersion, const String& guid, const String& password, int gameId, int keyTime, const Array<byte>& key)
	: buildVersion(buildVersion), guid(guid), password(password), gameId(gameId), keyTime(keyTime), key(key),
	random1(Random::xorshf96() % 1'000'000'000), random2(Random::xorshf96() % 1'000'000'000),
	mapJSON(""), entryTag(""), gameNet("rotmg"), gameNetUserId(""), playPlatform("rotmg"), platformToken(""), userToken("")
{

}

Hello::Hello(const String& buildVersion, const String& guid, const String& password, const int gameId)
	: buildVersion(buildVersion), guid(guid), password(password), gameId(gameId), keyTime(-1),
	random1(Random::xorshf96() % 1'000'000'000), random2(Random::xorshf96() % 1'000'000'000),
	mapJSON(""), entryTag(""), gameNet("rotmg"), gameNetUserId(""), playPlatform("rotmg"), platformToken(""), userToken("")
{

}

Hello::Hello(byte* data)
{
	PacketReader r(data);

	r.read(buildVersion);
	r.read(gameId);
	r.read(guid);
	r.read(random1);
	r.read(password);
	r.read(random2);
	r.read(secret);
	r.read(keyTime);
	r.read(key);
	r.read32(mapJSON);
	r.read(entryTag);
	r.read(gameNet);
	r.read(gameNetUserId);
	r.read(playPlatform);
	r.read(platformToken);
	r.read(userToken);
}

void Hello::emplace(byte* buffer) const
{
	PacketWriter w(buffer, size(), TypeManager::typeToId[PacketType::Hello]);

	w.write(buildVersion);
	w.write(gameId);
	w.write(guid);
	w.write(random1);
	w.write(password);
	w.write(random2);
	w.write(secret);
	w.write(keyTime);
	w.write(key);
	w.write32(mapJSON);
	w.write(entryTag);
	w.write(gameNet);
	w.write(gameNetUserId);
	w.write(playPlatform);
	w.write(platformToken);
	w.write(userToken);
}

int Hello::size() const
{
	return 47 + buildVersion.length + guid.length + password.length + secret.length + key.length + mapJSON.length
		+ entryTag.length + gameNet.length + gameNetUserId.length + playPlatform.length + platformToken.length + userToken.length;
}

String Hello::toString() const
{
	return String("HELLO");
}