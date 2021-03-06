/**
 * Copyright © 2016 Daniel Gutson, Aurelio Remonda, Leonardo Boquillón,
 *                  Francisco Herrero, Emanuel Bringas, Gustavo Ojeda,
 *                  Taller Technologies.
 *
 * @file        MultiContinueCommand.cpp
 * @author      Leonardo Boquillon
 * @date        2016-05-10
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

#include "commands/MultiContinueCommand.h"

namespace NSCommands
{

void MultiContinueCommand::execute(const Arguments& args, NSDebuggingContext::Context& ctx)
{
    if (args.empty())
    {
        for (auto& proxy : ctx)
        {
            proxy.second->continueExecution();
        }
    }
    else
    {
        for (const auto& arg : args)
        {
            const auto proxy = ctx.getInstance(mili::from_string<NSCommon::InstanceId>(arg)).lock();
            mili::assert_throw<NSCommon::InstanceNoLongerAlive>(bool(proxy));
            proxy->continueExecution();
        }
    }
}

} // namespace NSCommands
