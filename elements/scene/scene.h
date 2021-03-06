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

#ifndef SCENE_H_INCLUDED
#define SCENE_H_INCLUDED

#include "camera/camera.h"
#include "graph/node.h"
#include "entity/entity.h"
#include "modifier/modifier.h"
#include "light/light.h"
#include <cassert>
#include <list>
#include <unordered_map>

namespace eps {
namespace scene {

class scene
{
public:

    scene();

    utils::link<node> add_node(const std::string & name) { return root_->add_node(name); }
    utils::link<node> get_root() const { return root_; }

    template<typename _Modifier, typename... _Args>
    utils::link<_Modifier> add_node_modifier(const utils::link<node> & sn, _Args&& ...args);

    template<typename _Entity, typename... _Args>
    utils::link<_Entity> add_node_entity(const utils::link<node> & sn, _Args&& ...args);

    template<typename _Camera, typename... _Args>
    utils::link<_Camera> add_node_camera(const utils::link<node> & sn, _Args&& ...args);

    template<typename _Light, typename... _Args>
    utils::link<_Light> add_node_light(const utils::link<node> & sn, _Args&& ...args);

    void update(float dt);

    template<typename _Visitor, typename... _Args>
    void process_entities(_Visitor & visitor, _Args&&... args)
    {
        for(auto & entry : entities_)
            visitor(*entry, std::forward<_Args>(args)...);
    }

    template<typename _Visitor, typename... _Args>
    void process_lights(_Visitor & visitor, _Args&&... args)
    {
        for(auto & entry : lights_)
            if(entry.second->get_enabled())
                visitor(*entry.second, std::forward<_Args>(args)...);
    }

    template<typename _Visitor, typename... _Args>
    void process_light(const std::string & name, _Visitor & visitor, _Args&&... args)
    {
        auto it = lights_.find(name);
        if(it != lights_.end())
            visitor(*it->second, std::forward<_Args>(args)...);
    }

    utils::link<camera> get_camera() const;
    utils::link<camera> get_camera(const std::string & name) const;

private:

    std::list<utils::pointer<modifier>> modifiers_;
    std::list<utils::pointer<entity>> entities_;

    std::unordered_map<std::string, utils::pointer<camera>> cameras_;
    std::unordered_map<std::string, utils::pointer<light>> lights_;

    utils::pointer<node> root_;
};

template<typename _Entity, typename... _Args>
utils::link<_Entity> scene::add_node_entity(const utils::link<node> & sn, _Args&& ...args)
{
    auto se = utils::make_shared<_Entity>(sn, std::forward<_Args>(args)...);
    entities_.push_back(se);
    return se;
}

template<typename _Modifier, typename... _Args>
utils::link<_Modifier> scene::add_node_modifier(const utils::link<node> & sn, _Args&& ...args)
{
    auto sm = utils::make_shared<_Modifier>(sn, std::forward<_Args>(args)...);
    modifiers_.push_back(sm);
    return sm;
}

template<typename _Camera, typename... _Args>
utils::link<_Camera> scene::add_node_camera(const utils::link<node> & sn, _Args&& ...args)
{
    auto pnode = sn.lock();
    assert(pnode);

    auto sc = utils::make_shared<_Camera>(sn, std::forward<_Args>(args)...);
    cameras_[pnode->get_name()] = sc;

    return sc;
}

template<typename _Light, typename... _Args>
utils::link<_Light> scene::add_node_light(const utils::link<node> & sn, _Args&& ...args)
{
    auto pnode = sn.lock();
    assert(pnode);

    auto sl = utils::make_shared<_Light>(sn, std::forward<_Args>(args)...);
    lights_[pnode->get_name()] = sl;

    return sl;
}

} /* scene */
} /* eps */

#endif // SCENE_H_INCLUDED
