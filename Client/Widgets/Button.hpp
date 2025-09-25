#pragma once
#include <SFML/Graphics.hpp>
#include <string>
#include <functional>
#include <memory>

namespace UI {

    class Button {
    public:
        Button(const std::string& text, const std::string& fontPath, unsigned int charSize, const sf::Vector2f& size, const sf::Color& colorBackground, const sf::Color& colorText)
            : m_font(fontPath)
        {
            m_rect.setSize(size);
            m_rect.setFillColor(colorBackground);

            m_label = std::make_unique<sf::Text>(m_font, text, charSize);
            m_label->setFillColor(colorText);
        }

        void setLabel(const std::string& text) {
            m_label->setString(text);

            sf::Vector2f pos = m_rect.getPosition();

            auto lb = m_label->getLocalBounds();
            m_label->setPosition(
                sf::Vector2f(
                    pos.x + (m_rect.getSize().x - lb.size.x) / 2.f - lb.position.x,
                    pos.y + (m_rect.getSize().y - lb.size.y) / 2.f - lb.position.y
                )
            );
        }

        std::string getLabel() const { return m_label->getString(); }

        void setBackgroundColor(const sf::Color& color) { m_rect.setFillColor(color); }

        sf::Color getBackgroundColor() const { return m_rect.getFillColor(); }

        void setLabelColor(const sf::Color& color) { m_label->setFillColor(color); }

        sf::Color getLabelColor() const { return m_label->getFillColor(); }

        void setPosition(const sf::Vector2f& pos) {
            m_rect.setPosition(pos);

            auto lb = m_label->getLocalBounds();
            m_label->setPosition(
                sf::Vector2f(
                    pos.x + (m_rect.getSize().x - lb.size.x) / 2.f - lb.position.x,
                    pos.y + (m_rect.getSize().y - lb.size.y) / 2.f - lb.position.y
                )
            );
        }
        
        sf::Vector2f getPosition() const { return m_rect.getPosition(); }

        void handleEvent(const sf::Event::MouseButtonPressed& ev, sf::RenderWindow& window) {
            if (ev.button == sf::Mouse::Button::Left) {
                sf::Vector2f pos = window.mapPixelToCoords(ev.position);
                if (contains(pos)) m_pressed = true;
            }
        }
        void handleEvent(const sf::Event::MouseButtonReleased& ev, sf::RenderWindow& window) {
            if (m_pressed && ev.button == sf::Mouse::Button::Left) {
                sf::Vector2f pos = window.mapPixelToCoords(ev.position);
                if (contains(pos)) {
                    if (m_callback) m_callback();
                }
            }
            m_pressed = false;
        }
        void draw(sf::RenderWindow& window) {
            window.draw(m_rect);
            window.draw(*m_label);
        }

        bool isPressed() const { return m_pressed; }
        void setCallback(std::function<void()> cb) { m_callback = std::move(cb); }

    private:
        sf::Font m_font;
        sf::RectangleShape m_rect;
        std::unique_ptr<sf::Text> m_label;
        bool m_pressed = false;
        std::function<void()> m_callback;

        bool contains(const sf::Vector2f& p) const {
            return m_rect.getGlobalBounds().contains(p);
        }
    };

}