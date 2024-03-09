#include "include/events.h"

using namespace Odyssey;

static Events* _instance = nullptr;

Events::Events(): m_keys{false}, mouse_changes{0},
    current_coords{0}, last_coords{0}, mouse_init(false) {
}

Events* Events::getInstance(){
    if(_instance == nullptr){
        _instance =  new Events();
    }
    return _instance;
}

Events::~Events(){
    delete _instance;
}
