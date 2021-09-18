#pragma once
#include <WorldDataParser.h>
#include <Item.h>
#include "ClientActor.h"
//분류 1 :
//분류 2 :
//용도 :
//설명 :

class ClientItem : public Item, public ClientActor
{
private: // static var

public: // static func

private: // mem var

public: // constructor destructor
	ClientItem();
	~ClientItem();

public: // delete constructor

	ClientItem(const ClientItem& _other) = delete;
	ClientItem(const ClientItem&& _other) = delete;

public: // delete operator
	ClientItem& operator=(const ClientItem& _other) = delete;
	ClientItem& operator=(const ClientItem&& _other) = delete;

public: // mem func
	void CollisionPrev();
};

