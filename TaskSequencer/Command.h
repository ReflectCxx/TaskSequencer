#pragma once

#include <functional>
#include "Constants.h"

namespace hex
{
	class CommandController;

	class Command final
	{
		friend CommandController;

		inline static std::uint32_t m_counter{ 0 };

		const BlocksQ m_blockQ;
		const std::size_t m_cmdId;
		std::function<void(Command&)> m_command;

		CmdState m_cmdState;
		CommandController& m_controller;

		Command(const Command&) = delete;
		Command& operator=(Command&&) = delete;
		Command& operator=(const Command&) = delete;

	public:
		
		void ends();
		void execute();
		void unblockQ();

		Command(Command&&) noexcept;
		Command(BlocksQ pBlockQ, CommandController& pCC,
				std::function<void(Command&)> pCmd);
	};
}

#include "Command.hpp"
#include "CommandController.hpp"