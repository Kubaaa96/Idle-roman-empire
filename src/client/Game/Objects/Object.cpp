#include "Object.h"

namespace ire::client::objects
{
    void Object::setName(std::string& name)
    {
        if (m_name != name)
        {
            m_name = name;
        }
    }

    const std::string Object::getName() const
    {
        return m_name;
    }

    void Object::setPosition(sf::Vector2i pos)
    {
        if (m_currentPosition != pos)
        {
            m_currentPosition = pos;
        }
    }

    const sf::Vector2i Object::getPosition() const
    {
        return m_currentPosition;
    }
}