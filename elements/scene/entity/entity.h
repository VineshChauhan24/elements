/*
The MIT License (MIT)
Copyright (c) 2016 Alexey Yegorov

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in
all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY,
WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS
IN THE SOFTWARE.
*/

#ifndef SCENE_ENTITY_H_INCLUDED
#define SCENE_ENTITY_H_INCLUDED

#include "scene/graph/node.h"
#include <snape/visitor.h>

namespace eps {
namespace scene {

class entity : public snape::visitable<entity>
{
public:

    SNAPE_VISITABLE(entity);

public:

    explicit entity(const utils::link<node> & parent)
        : node_(parent)
    {}

    virtual ~entity()
    {}

    entity(entity &&) = default;
    entity & operator=(entity &&) = default;

    const utils::link<node> & get_node() const { return node_; }

private:

    utils::link<node> node_;
};

template<typename _Visitor>
using visitor = snape::visitor<_Visitor, snape::visitor_traits<entity>>;

} /* scene */
} /* eps */

#endif // SCENE_ENTITY_H_INCLUDED
