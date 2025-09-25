#pragma once
#include <SFML/Graphics.hpp>
#include <string>

namespace UI {

    class TextInput {
    public:
        TextInput(const std::string& method, const std::string& fontPath, const sf::Vector2f& position, unsigned int charSize, const sf::Vector2f& size, const sf::Color& colorBackground, const sf::Color& colorText)
        : m_font(fontPath), m_method(method)
        {
            box.setSize(size);
            box.setFillColor(colorBackground);
            box.setOutlineColor(colorBackground);
            box.setOutlineThickness(2.f);
            box.setPosition(position);

            text = std::make_unique<sf::Text>(m_font, "", charSize);
            text->setFillColor(colorText);
            text->setPosition(position + sf::Vector2f(5.f, 5.f));

            caret.setSize({ 2.f, static_cast<float>(charSize) });
            caret.setFillColor(colorText);
            caret.setPosition(position + sf::Vector2f(5.f, 5.f));

            blinkClock.restart();
        }

        void handleEvent(const sf::Event::MouseButtonPressed& ev, sf::RenderWindow& window) {
            sf::Vector2f mousePos(sf::Vector2f(ev.position.x, ev.position.y));
            focused = box.getGlobalBounds().contains(mousePos);
        }

        void handleEvent(const sf::Event::MouseButtonReleased& ev, sf::RenderWindow& window) {
            // Currently empty; could add visual feedback
        }

        void handleEvent(const sf::Event::TextEntered& ev) {
            if (!focused) return;

            if (ev.unicode == 8) {
                if (!str.empty()) str.pop_back();
                text->setString(str);
                return;
            }

            char c = static_cast<char>(ev.unicode);

            if (m_method == "FULLNAME") {
                const std::string allowedSymbols = " ";
                if (str.size() < 30 &&
                    ((c >= 'a' && c <= 'z') ||
                        (c >= 'A' && c <= 'Z') ||
                        allowedSymbols.find(c) != std::string::npos))
                {
                    str += c;
                    text->setString(str);
                }
            }
            else if (m_method == "MAIL") {
                const std::string allowedSymbols = "@.";
                if (str.size() < 30 &&
                    ((c >= 'a' && c <= 'z') ||
                        (c >= 'A' && c <= 'Z') ||
                        (c >= '0' && c <= '9') ||
                        allowedSymbols.find(c) != std::string::npos))
                {
                    str += c;
                    text->setString(str);
                }
            }
            else if (m_method == "PASSWORD") {
                const std::string allowedSymbols = ".,?!@#$%&*-_=+";
                if (str.size() < 30 &&
                    ((c >= 'a' && c <= 'z') ||
                        (c >= 'A' && c <= 'Z') ||
                        (c >= '0' && c <= '9') ||
                        allowedSymbols.find(c) != std::string::npos))
                {
                    str += c;
                    text->setString(str);
                }
            }
            else if (m_method == "CODE") {
                const std::string allowedSymbols = "";
                if (str.size() < 4 && ((c >= '0' && c <= '9') ||
                    allowedSymbols.find(c) != std::string::npos))
                {
                    str += c;
                    text->setString(str);
                }
            }
            else {
                const std::string allowedSymbols = ".,?!@#$%&*-_=+ ";
                if ((c >= 'a' && c <= 'z') ||
                    (c >= 'A' && c <= 'Z') ||
                    (c >= '0' && c <= '9') ||
                    allowedSymbols.find(c) != std::string::npos)
                {
                    str += c;
                    text->setString(str);
                }
            }
        }

        void draw(sf::RenderWindow& window) {
            window.draw(box);
            window.draw(*text);

            if (focused) {
                if (blinkClock.getElapsedTime().asSeconds() > 0.5f) {
                    caretVisible = !caretVisible;
                    blinkClock.restart();
                }

                sf::Vector2f pos;
                if (!str.empty()) {
                    pos = text->findCharacterPos(str.size());
                }
                else {
                    pos = text->getPosition();
                }
                caret.setPosition({ pos.x + 1.f, text->getPosition().y + 5.f });

                if (caretVisible) {
                    window.draw(caret);
                }
            }
        }

        sf::Vector2f getPosition() const { return box.getPosition(); }
        const std::string& getText() const { return str; }
        void setText(const std::string& s) { str = s; text->setString(str); }

    private:
        sf::Font m_font;
        sf::RectangleShape box;
        std::unique_ptr<sf::Text> text;
        std::string str;
        std::string m_method;

        bool focused = false;

        sf::RectangleShape caret;
        sf::Clock blinkClock;
        bool caretVisible = true;
    };

}