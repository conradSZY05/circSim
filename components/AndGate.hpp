#pragma once

#include "Component.hpp"


class AndGate : public Component
{
    public:
        AndGate(sf::Vector2f mousePos);
        void update() override;
        void initButtons() override;

    protected:
        void setType(sf::Vector2f mousePos) override;
};