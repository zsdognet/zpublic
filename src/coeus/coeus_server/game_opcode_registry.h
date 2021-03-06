#ifndef __GAME_OPCODE_REGISTRY_H__
#define __GAME_OPCODE_REGISTRY_H__

#include "venus_net/opcode_registry.h"
#include "game_session.h"

OPCODE_REGISTER_BEGIN(GameOpcodeRegistry, GameSession)
	REGISTER_HANDLER(Opcodes::CSRegisterReq, registerHandler);
	REGISTER_HANDLER(Opcodes::CSLoginReq, loginHandler);
OPCODE_REGISTER_END()

#endif