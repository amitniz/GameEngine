#pragma once

namespace Odyssey{

/*
* GameObject
* An abstract class for the engine objects such as lights, models and camera..
*
* Each GameObject must have an object_id and a scene_id.
* The object_id will be updated by the GameEngine and the scene_id by its Scene.
*/
class GameObject{
public: 
    GameObject() = default;
    virtual ~GameObject() = default;
    inline unsigned getSceneId() const {return m_scene_id;}
    inline unsigned getObjectId() const {return m_object_id;}

protected:
    inline void setSceneID(unsigned id) {m_scene_id = id;}
    inline void setObjectID(unsigned id) {m_object_id = id;}
    friend class GameEngine;

private:
    unsigned m_object_id;
    unsigned m_scene_id;
};
};
