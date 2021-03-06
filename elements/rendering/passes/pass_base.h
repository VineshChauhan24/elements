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

#ifndef RENDERING_PASSES_PASS_BASE_H_INCLUDED
#define RENDERING_PASSES_PASS_BASE_H_INCLUDED

#include "utils/std/pointer.h"
#include "math/types.h"
#include "pass_target_input.h"

namespace eps {
namespace rendering {

class pass_target;

class pass_base
{
public:

    pass_base(size_t place, const pass_target_input & inputs)
        : inputs_(inputs)
        , place_(place)
    {}

    virtual ~pass_base()
    {}

    const pass_target_input & get_inputs() const { return inputs_; }
    size_t get_place() const { return place_; }

public:

    virtual bool initialize() = 0;
    virtual void process(float dt) = 0;

    virtual utils::unique<pass_target> construct(const math::uvec2 &)
    {
        return nullptr;
    }

private:

    pass_target_input inputs_;
    size_t place_;
};

} /* rendering */
} /* eps */

#endif // RENDERING_PASSES_PASS_BASE_H_INCLUDED
