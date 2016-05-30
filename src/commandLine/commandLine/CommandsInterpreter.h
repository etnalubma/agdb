/**
 * Copyright © 2016 Daniel Gutson, Aurelio Remonda, Leonardo Boquillón,
 *                  Francisco Herrero, Emanuel Bringas, Gustavo Ojeda,
 *                  Taller Technologies.
 *
 * @file        CommandsInterpreter.h
 * @author      Daniel Gutson, Emanuel Bringas, Leonardo Boquillon
 * @date        2016-05-04
 * @brief
 *
 * This file is part of agdb
 *
 * agdb is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * agdb is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with agdb.  If not, see <http://www.gnu.org/licenses/>.
 */

#ifndef COMMANDS_INTERPRETER_H
#define COMMANDS_INTERPRETER_H

#include <string>
#include <unordered_map>
#include <vector>
#include <sstream>
#include <iostream>
#include "debuggingContext/Context.h"
#include "commands/ICommand.h"
#include "commands/RaiseLocalCommand.h"
#include "commands/RaiseRemoteCommand.h"
#include "commands/printCommand.h"
#include "commands/listCommand.h"
#include "commands/backtraceCommand.h"
#include "commands/instanceCommand.h"
#include "commands/MultiBreakpointCommand.h"
#include "commands/breakpointCommand.h"
#include "commands/MultiContinueCommand.h"
#include "commands/ContinueCommand.h"
#include "commands/FwdCommand.h"
#include "commands/multiInterruptCommand.h"
#include "commands/nextCommand.h"
#include "commands/stepCommand.h"
#include "commands/baseCommands.h"


namespace NSCommandLine
{

using namespace NSCommands; // TODO: Avoid this

class HelpCommand : public NSCommands::NoArgsCommand
{
    void execute(NSDebuggingContext::Context& ctx) override;
};

class Interpreter
{
public:
    inline Interpreter(NSDebuggingContext::Context& ctx);

    void execute(const std::string& line);

private:
#define SEPARATOR   ;
#define COMMANDS_TABLE(cmd, name, desc)   cmd cmd##_instance
#include "commandLine/CommandList.h"

    const std::unordered_map<std::string, ICommand*> _commands;
    NSDebuggingContext::Context& _ctx;

    static Arguments processArguments(std::string&& str);
};

} // namespace NSCommandLine

#define COMMANDS_INTERPRETER_INLINE_H
#include "CommandsInterpreterInline.h"
#undef COMMANDS_INTERPRETER_INLINE_H

#endif // COMMANDS_INTERPRETER_H