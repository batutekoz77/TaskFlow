#pragma once
#include <SFML/Graphics.hpp>
#include <string>
#include <functional>

namespace UI {

    class Label {
    private:
        sf::Text m_text;
        sf::Font m_font;
        std::function<void()> m_onClick;

    public:
        Label(const std::string& str, const std::string& fontPath, unsigned int charSize, const sf::Color& color)
            : m_font(fontPath), m_text(m_font, str, charSize)
        {
            m_text.setFillColor(color);
        }

        void setText(const std::string& str) {
            m_text.setString(str);
        }

        std::string getText() const& {
            return m_text.getString();
        }

        void setColor(const sf::Color& color) {
            m_text.setFillColor(color);
        }

        void setPosition(const sf::Vector2f& position) {
            m_text.setPosition(position);
        }

        void setOnClick(std::function<void()> callback) {
            m_onClick = std::move(callback);
        }

        void draw(sf::RenderWindow& window) const {
            window.draw(m_text);
        }

        void handleEvent(const sf::Event::MouseButtonPressed& ev, sf::RenderWindow& window) {
            if (ev.button == sf::Mouse::Button::Left) {
                sf::Vector2f pos = window.mapPixelToCoords({ ev.position.x, ev.position.y });
                if (m_text.getGlobalBounds().contains(pos)) {
                    if (m_onClick) {
                        m_onClick();
                    }
                }
            }
        }
    };

}
