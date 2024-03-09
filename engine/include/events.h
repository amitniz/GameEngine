
#define MAX_KEYS 1024

namespace Odyssey{
/**
* Events 
* A singleton of the engine's events system. 
* Contains keyboard, mouse events.
*
*/
class Events{
public:
    static Events* getInstance();
    Events(Events const&) = delete; 
    void operator =(Events const&) = delete;

    inline const bool* getKeysState() const {return m_keys;}
    inline const int *getMouseChanges() const { return this->mouse_changes; }
    ~Events();

private:
    Events();
    // keyboard
    bool m_keys[MAX_KEYS];
    // mouse
    int current_coords[2];
    int mouse_changes[2];
    int last_coords[2];
    bool mouse_init; // prevents inital read before user moved the mouse

    friend class Window;
};
}
