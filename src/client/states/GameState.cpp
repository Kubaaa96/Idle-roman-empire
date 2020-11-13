#include "GameState.h"

#include <iostream>

namespace ire::client::state
{
    GameState::GameState(const sf::Vector2u sizeOfWindow)
        : State(sizeOfWindow)
    {
    }
    core::gui::Group* GameState::drawGUI()
    {
        verticalLayout = ire::core::gui::VerticalLayout::create({ 500, 400 });
        //verticalLayout->setPosition({ 100, 100 });
        verticalLayout->setSpaces(5);
        verticalLayout->setMargins({ 0, 0, 15, 15 });
        auto btn5Ptr = ire::core::gui::Button::create("test");
        auto btn6Ptr = ire::core::gui::Button::create("test1");
        auto label7Ptr = ire::core::gui::Label::create("test");
        auto editBox8Ptr = ire::core::gui::EditBox::create("test1");

        btn5Ptr->addEventListener<ire::core::gui::MouseClickEvent>(
            [](ire::core::gui::MouseClickEvent& ev) { std::cout << "Clicked btn5Ptr button\n"; });

        btn6Ptr->addEventListener<ire::core::gui::MouseClickEvent>(
            [](ire::core::gui::MouseClickEvent& ev) { std::cout << "Clicked btn6Ptr button " << ev.position.x << "\n"; });

        verticalLayout->add(std::move(btn5Ptr), "Button5");
        verticalLayout->add(std::move(btn6Ptr), "Button6");
        verticalLayout->add(std::move(label7Ptr), "Label1");
        verticalLayout->add(std::move(editBox8Ptr), "EditBox1");

        verticalLayout->setLayoutStretch({ 1, 3, 6, 2 });

        horizontalLayout = ire::core::gui::HorizontalLayout::create({ 500,400 });
        horizontalLayout->setSpaces(10);
        horizontalLayout->setMargins({ 10, 10, 10, 10 });
        auto editBox1Ptr = ire::core::gui::EditBox::create("test");
        auto btn2Ptr = ire::core::gui::Button::create("test1");
        auto label3Ptr = ire::core::gui::Label::create("test");
        auto btn4Ptr = ire::core::gui::Button::create("test1");

        btn2Ptr->addEventListener<ire::core::gui::MouseClickEvent>(
            [](ire::core::gui::MouseClickEvent& ev) { std::cout << "Clicked btn2Ptr button\n"; });

        btn4Ptr->addEventListener<ire::core::gui::MouseClickEvent>(
            [](ire::core::gui::MouseClickEvent& ev) { std::cout << "Clicked btn4Ptr button\n"; });

        horizontalLayout->add(std::move(editBox1Ptr), "EditBox2");
        horizontalLayout->add(std::move(btn2Ptr), "Button2");
        horizontalLayout->add(std::move(verticalLayout), "VerticalLayout");
        horizontalLayout->add(std::move(label3Ptr), "Label2");
        horizontalLayout->add(std::move(btn4Ptr), "Button4");

        horizontalLayout->setLayoutStretch({ 3, 6, 12, 2, 1 });

        panel = ire::core::gui::Panel::create({ 700, 400 }, std::move(horizontalLayout), "HorizontalLayout");
        panel->setPosition({ 300,300 });
        panel->setOpacity(200);
        panel->setOutlineColor(sf::Color::Magenta);
        panel->setOutlineThickness(7);

        auto verticalLayout2 = ire::core::gui::VerticalLayout::create({ 100, 200 });
        verticalLayout2->setSpaces(5);
        verticalLayout2->setMargins({ 5, 5, 5, 5 });

        auto btn10Ptr = ire::core::gui::Button::create("elo");
        btn10Ptr->addEventListener<ire::core::gui::MouseClickEvent>(
            [](ire::core::gui::MouseClickEvent& ev) { std::cout << "Clicked btn10Ptr button\n"; });
        verticalLayout2->add(std::move(btn10Ptr), "Button10");

        auto btn11Ptr = ire::core::gui::Button::create("elo2");
        btn11Ptr->addEventListener<ire::core::gui::MouseClickEvent>(
            [](ire::core::gui::MouseClickEvent& ev) { std::cout << "Clicked btn11Ptr button\n"; });

        verticalLayout2->add(std::move(btn11Ptr), "Button11");

        panel2 = ire::core::gui::Panel::create({ 100, 200 }, std::move(verticalLayout2), "VerticalLayout2");
        panel2->setPosition({ 100, 100 });
        panel2->setOutlineColor(sf::Color::Red);
        panel2->setOutlineThickness(7);

        group = ire::core::gui::Group::create(m_sizeOfWindow);
        group->add(std::move(panel), "panel1");
        group->add(std::move(panel2), "panel2");
        
        return group.release();
    }
}