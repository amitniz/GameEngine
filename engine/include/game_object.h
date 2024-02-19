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

    /* @brief
    *  add the gameobject to the game engine's list and update its id. 
    */
    //friend void GameEngine::addGameObject(GameObject &game_object);
    /* @brief
    * add the game object to the scene's gameobjects list and update it's scene_id 
    */
protected:
    unsigned m_object_id;
    unsigned m_scene_id;

    friend class Scene;
    friend class GameEngine;
};
};
