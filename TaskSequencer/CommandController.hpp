#pragma once

#include "cocos2d.h"
#include "CommandController.h"

namespace hex
{
	constexpr std::size_t CommandController::getRunningCmdCount() const {
		return m_runningCount;
	}


	constexpr std::size_t& CommandController::runningCount() {
		return m_runningCount;
	}


	inline void CommandController::push(Command pCmd)
	{
		if (pCmd.m_cmdState != CmdState::None) {
			return;
		}
		m_commands.push_back(std::move(pCmd));
		m_commandQ.push_back(m_commands.back());
		m_commands.back().m_cmdState = CmdState::Queued;
	}


	inline void CommandController::update()
	{
		int count = 0;
		while (!m_commands.empty() && m_commands.front().m_cmdState == CmdState::Expired) {
			m_commands.pop_front();
			count++;
		}
		if (count > 0) {
			CCLOG("Expired cmds count: %d", count);
		}
	}


	inline void CommandController::blockQ(const std::uint64_t pByCmdId, const bool pBlock)
	{
		if (pBlock) {
			if (!m_blockedByCmdId.has_value()) {
				m_blockedByCmdId = pByCmdId;
			}
		}
		else if (m_blockedByCmdId.has_value() &&  *m_blockedByCmdId == pByCmdId) {
			m_blockedByCmdId.reset();
		}
	}


	inline std::optional<std::reference_wrapper<Command>> CommandController::nextCmd()
	{
		if (m_blockedByCmdId.has_value() || m_commandQ.empty()) {
			return std::nullopt;
		}

		if (m_commandQ.front().get().m_blockQ == BlocksQ::Join && runningCount() != 0) {
			CCLOG("Waiting to finish executions, running count: { %lu }", runningCount());
			return std::nullopt;
		}

		auto& cmd = m_commandQ.front().get();
		cmd.m_cmdState = CmdState::Ready;
		m_commandQ.pop_front();
		return cmd;
	}
}