#pragma once

#include "Command.h"
#include "CommandController.hpp"

namespace hex
{
	inline Command::Command(BlocksQ pBlockQ, CommandController& pCC,
							std::function<void(Command&)> pCmd)
		: m_blockQ(pBlockQ)
		, m_cmdId(m_counter++)
		, m_command(std::move(pCmd))
		, m_cmdState(CmdState::None)
		, m_controller(pCC) {
	}


	inline Command::Command(Command&& pOther) noexcept
		: m_blockQ(pOther.m_blockQ)
		, m_cmdId(pOther.m_cmdId)
		, m_command(std::move(pOther.m_command))
		, m_controller(pOther.m_controller)
		, m_cmdState(pOther.m_cmdState) {
		pOther.m_cmdState = CmdState::Expired;
	}

	
	inline void Command::ends()
	{
		if (m_cmdState != CmdState::Running) {
			return;
		}
		unblockQ();
		m_controller.runningCount()--;
		m_cmdState = CmdState::Expired;
	}

	
	inline void Command::unblockQ()
	{
		if (m_cmdState != CmdState::Running) {
			return;
		}
		if (m_blockQ == BlocksQ::Yes || m_blockQ == BlocksQ::Join) {
			m_controller.blockQ(m_cmdId, false);
		}
	}


	inline void Command::execute()
	{
		if (m_cmdState != CmdState::Ready) {
			return;
		}
		m_cmdState = CmdState::Running;
		m_controller.runningCount()++;
		if (m_blockQ == BlocksQ::Yes || m_blockQ == BlocksQ::Join) {
			m_controller.blockQ(m_cmdId, true);
		}
		CCASSERT(m_command, "Command callback cannot be empty.");
		m_command(*this);
	}
}