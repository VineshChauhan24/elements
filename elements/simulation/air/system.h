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

#ifndef SIMULATION_SYSTEM_H_INCLUDED
#define SIMULATION_SYSTEM_H_INCLUDED

#include "math/types.h"
#include "synchronization/future.h"
#include "volume.h"

namespace eps {
namespace simulation {
namespace air {

class system
{
public:

    using future  = sync::future<math::vec2>;
    using promise = sync::promise<math::vec2>;

    bool construct(const math::uvec2 & size);

    void touch_down(float x, float y);
    void touch_up(float x, float y);

    future spawn(float dt);

private:

    void update_velocities(float dt);

private:

    volume volume_;

    math::vec2 touch_;
    math::vec2 touch_prev_;
};

} /* air */
} /* simulation */
} /* eps */


#endif // SIMULATION_SYSTEM_H_INCLUDED
