/**
 * Copyright © 2016 Daniel Gutson, Aurelio Remonda, Leonardo Boquillón,
 *                  Francisco Herrero, Emanuel Bringas, Gustavo Ojeda,
 *                  Taller Technologies.
 *
 * @file        printCommand.cpp
 * @author      Gustavo Ojeda
 * @date        2016-05-04
 * @brief       PrintCommand class definition
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

#include "common/exceptions.h"
#include "commands/printCommand.h"

namespace NSCommands
{

void PrintCommand::execute(const Arguments& args, NSDebuggingContext::Context& ctx)
{
    mili::assert_throw<NSCommon::InvalidArgumentNumbers>(args.size() == ArgumentsNumber);

    Message msg;
    const auto cID = ctx.getCurrentInstance();
    const auto instance = ctx.getInstance(cID).lock();
    mili::assert_throw<NSCommon::InstanceNoLongerAlive>(bool(instance));

    instance->evaluateExpression(args[Expression], msg);
    std::cout << args[Expression] << " = " << msg << std::endl;
}

} // namespace NSCommands
