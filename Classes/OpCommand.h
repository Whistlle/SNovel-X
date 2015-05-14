#define TEST_OP_COMMAND

#if defined(TEST_OP_COMMAND)\
	|| defined(DEBUG_ALL)
#define TEST_OP_COMMAND

#pragma once

#include "OpCode.h"
#include <vector>
#include "ScriptedValue.h"
#include "cocos2d.h"

USING_NS_CC;
class OpCommand
{
public:
	OpCommand(Opcode OpType):
	op(OpType)
	{

	}
	Opcode op;
	ValueMap params;
	std::vector<Opcode> additionalOp;
	int lineID;
};


#endif