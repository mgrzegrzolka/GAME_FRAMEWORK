#include "GameObjectFactory.h"

GameObjectFactory *GameObjectFactory::s_pInstance = 0;

bool GameObjectFactory::registerType(std::string typeID, BaseCreator *pCreator) 
{
    std::map<std::string, BaseCreator*>::iterator it = m_creators.find(typeID);
    /* if after doing a .find, "it" is not in the .end position, it means it found an ID */
    /* and the function is stopped because there is already such an element in "m_creators" */
    if(it != m_creators.end()) {
        delete pCreator;
        return false;
    }

    m_creators[typeID] = pCreator;

    return true;
}

GameObject* GameObjectFactory::create(std::string typeID) 
{
    std::map<std::string, BaseCreator*>::iterator it = m_creators.find(typeID);

    if(it == m_creators.end()) {
        printf("could not find type: %s", typeID);
        return NULL;
    }
        
    BaseCreator *pCreator = (*it).second;
    return pCreator->createGameObject();
}