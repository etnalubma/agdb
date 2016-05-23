/**
 * Copyright © 2016 Daniel Gutson, Aurelio Remonda, Leonardo Boquillón,
 *                  Francisco Herrero, Emanuel Bringas, Gustavo Ojeda,
 *                  Taller Technologies.
 *
 * @file        ContextInstanceAspect.h
 * @author      Leonardo Boquillón
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

#ifndef _CONTEXT_INSTANCE_ASPECT_INCLUDE_H_
#define _CONTEXT_INSTANCE_ASPECT_INCLUDE_H_

#include <vector>
#include <memory>
#include <cassert>
#include "common/exceptions.h"
#include "gdbProxy/GdbProxy.h"

namespace NSDebuggingContext
{

// TODO: Create an interator class rather than make the proxy iterable
template<class NextAspect>
class ContextInstanceAspect : public NextAspect
{

private:
    //TODO: emplace instead of pointers, and implement move assignation and constructor in proxy
    using InstancesVector = typename std::vector<std::unique_ptr<NSGdbProxy::GdbProxy>>;

public:
    using NextAspect::NextAspect;

    using InstancesIterator = typename InstancesVector::const_iterator;

    static constexpr NSCommon::InstanceId NoInstance = 0u;

    NSCommon::InstanceId addGdbInstance(NSGdbProxy::GdbProxy* const instance);

    NSCommon::InstanceId addGdbInstance(std::unique_ptr<NSGdbProxy::GdbProxy>&& instance);

    NSGdbProxy::GdbProxy& getInstance(NSCommon::InstanceId id) const;

    NSCommon::InstanceId getCurrentInstance() const;

    void setCurrentInstance(NSCommon::InstanceId id);

    InstancesIterator begin() const;

    InstancesIterator end() const;

protected:

    InstancesVector gdbInstances;

    NSCommon::InstanceId      currentInstance = NoInstance;
};

template<class NextAspect>
NSCommon::InstanceId ContextInstanceAspect<NextAspect>::addGdbInstance(NSGdbProxy::GdbProxy* const instance)
{
    gdbInstances.emplace_back(instance);
    currentInstance = gdbInstances.size();
    return currentInstance;
}

template<class NextAspect>
NSCommon::InstanceId ContextInstanceAspect<NextAspect>::addGdbInstance(std::unique_ptr<NSGdbProxy::GdbProxy>&& instance)
{
    gdbInstances.emplace_back(std::move(instance));
    currentInstance = gdbInstances.size();
    return currentInstance;
}

template<class NextAspect>
NSGdbProxy::GdbProxy& ContextInstanceAspect<NextAspect>::getInstance(NSCommon::InstanceId id) const
{
    mili::assert_throw<NSCommon::WrongInstanceNumber>(id >= NoInstance and id <= gdbInstances.size());
    return *gdbInstances.at(id - 1u);
}

template<class NextAspect>
NSCommon::InstanceId ContextInstanceAspect<NextAspect>::getCurrentInstance() const
{
    return currentInstance;
}

template<class NextAspect>
void ContextInstanceAspect<NextAspect>::setCurrentInstance(NSCommon::InstanceId id)
{
    if (id > gdbInstances.size())
    {
        throw NSCommon::WrongInstanceNumber(std::to_string(id));
    }
    currentInstance = id;
}

template<class NextAspect>
typename ContextInstanceAspect<NextAspect>::InstancesIterator
ContextInstanceAspect<NextAspect>::begin() const
{
    return gdbInstances.cbegin();
}

template<class NextAspect>
typename ContextInstanceAspect<NextAspect>::InstancesIterator
ContextInstanceAspect<NextAspect>::end() const
{
    return gdbInstances.cend();
}

} // end namespace NSDebuggingContext

#endif /* _CONTEXT_INSTANCE_ASPECT_INCLUDE_H_ */