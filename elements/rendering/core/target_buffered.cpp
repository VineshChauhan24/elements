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

#include "target_buffered.h"

namespace eps {
namespace rendering {

target_buffered::target_buffered(target front, target back)
    : write_(0)
{
    targets_[0] = std::move(front);
    targets_[1] = std::move(back);
}

void target_buffered::swap()
{
    write_ = 1 - write_;
}

const product_type & target_buffered::get_target() const
{
    return targets_[write_].get_target();
}

const product_type & target_buffered::get_product() const
{
    return targets_[1 - write_].get_product();
}

const product_type & target_buffered::get_product(attachment id) const
{
    return targets_[1 - write_].get_product(id);
}

const math::uvec2 & target_buffered::get_size() const
{
    return targets_[1 - write_].get_size();
}

const math::uvec2 & target_buffered::get_size(attachment id) const
{
    return targets_[1 - write_].get_size(id);
}

} /* rendering */
} /* eps */
