#pragma once
#include <SFML/Graphics.hpp>

namespace UI {

    class Checkbox {
    public:
        Checkbox(const sf::Vector2f& position,
            float size,
            const sf::Color& fillColor,
            const sf::Color& outlineColor,
            float outlineThickness)
        {
            m_box.setSize({ size, size });
            m_box.setFillColor(fillColor);
            m_box.setOutlineColor(outlineColor);
            m_box.setOutlineThickness(outlineThickness);
            m_box.setPosition(position);

            float thickness = 3.f;
            m_thickness = thickness;

            updateTick();
        }

        void draw(sf::RenderWindow& window) {
            window.draw(m_box);
            if (m_checked) {
                window.draw(m_line1);
                window.draw(m_line2);
            }
        }

        void handleEvent(const sf::Event::MouseButtonPressed& ev, sf::RenderWindow& window) {
            if (ev.button == sf::Mouse::Button::Left) {
                sf::Vector2f pos = window.mapPixelToCoords({ ev.position.x, ev.position.y });

                if (m_box.getGlobalBounds().contains(pos)) {
                    toggle();
                }
            }
        }

        void toggle() {
            m_checked = !m_checked;
        }

        bool isChecked() const { return m_checked; }

        void setPosition(const sf::Vector2f& pos) {
            m_box.setPosition(pos);
            updateTick();
        }

        sf::Vector2f getPosition() const { return m_box.getPosition(); }

    private:
        sf::RectangleShape m_box;
        sf::RectangleShape m_line1;
        sf::RectangleShape m_line2;
        float m_thickness;
        bool m_checked = false;

        void updateTick() {
            sf::Vector2f pos = m_box.getPosition();
            float s = m_box.getSize().x;
            float t = m_thickness;

            m_line1.setSize({ s * 0.35f, t });
            m_line1.setFillColor(sf::Color::Black);
            m_line1.setOrigin({ 0, t / 2.f });
            m_line1.setRotation(sf::degrees(45.f));
            m_line1.setPosition({ pos.x + 4.f, pos.y + s * 0.55f });

            m_line2.setSize({ s * 0.6f, t });
            m_line2.setFillColor(sf::Color::Black);
            m_line2.setOrigin({ 0, t / 2.f });
            m_line2.setRotation(sf::degrees(-45.f));
            m_line2.setPosition({ pos.x + s * 0.3f, pos.y + s - 4.f });
        }
    };

}