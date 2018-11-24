#include "stdafx.h"

#include "ServerParser.h"

#define MAX_SERVERS 32

void ServerParser::parse()
{
	rapidxml::file<char> xmlFile("CharList.xml");

	rapidxml::xml_document<char> doc;
	doc.parse<0>(xmlFile.data());

	char addresses[1024];
	int offsets[MAX_SERVERS];
	int offset = 0;

	rapidxml::xml_node<char>* rootNode = doc.first_node("Chars")->first_node("Servers");
	int offsetsAmount = 0;
	for (rapidxml::xml_node<char>* topNode = rootNode->first_node("Server"); topNode; topNode = topNode->next_sibling())
	{
		char* address = topNode->first_node("DNS")->value();
		int size = strlen(address) + 1;
		memcpy(addresses + offset, address, size);
		offsets[offsetsAmount++] = offset;
		offset += size;
	}
	printf("servers %d/%d\n", offsetsAmount, MAX_SERVERS);

	std::fstream bin("servers.bin", std::ios::out | std::ios::binary);

	bin.write((char*)&offset, 4);
	bin.write(addresses, offset);

	bin.write((char*)&offsetsAmount, 4);
	bin.write((char*)offsets, offsetsAmount * sizeof(int));

	bin.close();
}