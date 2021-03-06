/**
 * Copyright © 2016 Daniel Gutson, Aurelio Remonda, Leonardo Boquillón,
 *                  Francisco Herrero, Emanuel Bringas, Gustavo Ojeda,
 *                  Taller Technologies.
 *
 * @file        breakpointCommand.cpp
 * @author      Emanuel Bringas
 * @author      Francisco Herrero
 * @date        2016-05-04
 * @brief       Breakpoint commands definition.
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

#include "mili/mili.h"
#include "common/exceptions.h"
#include "common/Breakpoint.h"
#include "commands/breakpointCommand.h"

namespace NSCommands
{

using NSDebuggingContext::BreakpointId;

const char BreakpointCommand::IF_WORD[] = "if";

void BreakpointCommand::execute(const Arguments& args, NSDebuggingContext::Context& ctx)
{
    mili::assert_throw<NSCommon::InvalidArgumentNumbers>(args.size() == 1u || args.size() == NumberOfArgs);

    const auto instanceId = ctx.getCurrentInstance();
    auto instance = ctx.getInstance(instanceId).lock();
    mili::assert_throw<NSCommon::InstanceNoLongerAlive>(bool(instance));

    auto location = BreakpointLocation::fromArgument(args[Location]);
    if (args.size() == NumberOfArgs)
    {
        if (args[IfWord] != IF_WORD)
        {
            throw NSCommon::ArgumentMissing(IF_WORD);
        }
        location.condition = args[Condition];
    }
    // else there is no condition on breakpoint.

    auto breakpoint = instance->addBreakpoint(location, [instanceId](IUserBreakpoint* /*breakpoint*/, moirai::PostIterationAction & nextAction)
    {
        std::cout << "Breakpoint in instance " << instanceId << std::endl;
        nextAction = moirai::SuspendLooping;
    });

    const auto breakpointId = ctx.addBreakpoint(breakpoint);
    instance->registerTerminationCallback([&ctx, breakpointId]()
    {
        ctx.removeBreakpoint(breakpointId);
    });

    std::cout << "Breakpoint " << breakpointId << " created." << std::endl;
}

void EnableBreakpointCommand::execute(const Arguments& args, NSDebuggingContext::Context& ctx)
{
    mili::assert_throw<NSCommon::InvalidArgumentNumbers>(args.size() == NumberOfArgs);
    const auto mbrId = mili::from_string<BreakpointId>(args[BrNumber]);
    auto br = ctx.getBreakpoint(mbrId);
    br->enable();
}

void DisableBreakpointCommand::execute(const Arguments& args, NSDebuggingContext::Context& ctx)
{
    mili::assert_throw<NSCommon::InvalidArgumentNumbers>(args.size() == NumberOfArgs);
    const auto mbrId = mili::from_string<BreakpointId>(args[BrNumber]);
    auto br = ctx.getBreakpoint(mbrId);
    br->disable();
}

void IgnoreBreakpointCommand::execute(const Arguments& args, NSDebuggingContext::Context& ctx)
{
    mili::assert_throw<NSCommon::InvalidArgumentNumbers>(args.size() == NumberOfArgs);
    const auto mbrId = mili::from_string<BreakpointId>(args[BrNumber]);
    const auto count = mili::from_string<BreakpointId>(args[Count]);
    auto br = ctx.getBreakpoint(mbrId);
    br->ignore(count);
}

} // namespace NSCommands
