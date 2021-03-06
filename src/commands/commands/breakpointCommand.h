/**
 * Copyright © 2016 Daniel Gutson, Aurelio Remonda, Leonardo Boquillón,
 *                  Francisco Herrero, Emanuel Bringas, Gustavo Ojeda,
 *                  Taller Technologies.
 *
 * @file        breakpointCommand.h
 * @author      Emanuel Bringas
 * @author      Francisco Herrero
 * @date        2016-05-04
 * @brief       Breakpoint commands declaration.
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

#ifndef BREAKPOINT_COMMAND_INCLUDE_H_
#define BREAKPOINT_COMMAND_INCLUDE_H_

#include "debuggingContext/Context.h"
#include "commands/ICommand.h"

namespace NSCommands
{

/**
 * @brief Breakpoint command.
 * @details Registers new breakpoint on current instance.
 */
class BreakpointCommand : public ICommand
{
private:

    /** @brief Index of arguments */
    enum ArgsIndex
    {
        Location,
        IfWord,
        Condition,
        // leave this at the end
        NumberOfArgs
    };

    /** ICommand interface implementation */
    void execute(const Arguments& args, NSDebuggingContext::Context& ctx) override;

    static const char IF_WORD[];
};

/**
 * @brief Enable breakpoint command.
 * @details Enables a breakpoint in current instance.
 */
class EnableBreakpointCommand : public ICommand
{
private:

    /** @brief Index of arguments */
    enum ArgsIndex
    {
        BrNumber,
        // leave this at the end
        NumberOfArgs
    };

    /** ICommand interface implementation */
    void execute(const Arguments& args, NSDebuggingContext::Context& ctx) override;
};

/**
 * @brief Disable breakpoint command.
 * @details Disables a breakpoint in current instance.
 */
class DisableBreakpointCommand : public ICommand
{
private:

    /** @brief Index of arguments */
    enum ArgsIndex
    {
        BrNumber,
        // leave this at the end
        NumberOfArgs
    };

    /** ICommand interface implementation */
    void execute(const Arguments& args, NSDebuggingContext::Context& ctx) override;
};

/**
 * @brief Ignore breakpoint command.
 * @details Ignores a breakpoint for determined times in current instance.
 */
class IgnoreBreakpointCommand : public ICommand
{
private:

    /** @brief Index of arguments */
    enum ArgsIndex
    {
        BrNumber,
        Count,
        // leave this at the end
        NumberOfArgs
    };

    /** ICommand interface implementation */
    void execute(const Arguments& args, NSDebuggingContext::Context& ctx);
};

} // namespace NSCommands

#endif // BREAKPOINT_COMMAND_INCLUDE_H_
