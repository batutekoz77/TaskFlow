#pragma once
#include <SFML/Graphics.hpp>
#include <string>
#include <functional>
#include <memory>
#include <filesystem>

namespace UI {

    class ButtonWithImage {
    public:
        ButtonWithImage(const std::string& text,
            const std::string& fontPath,
            unsigned int charSize,
            const sf::Vector2f& size,
            const std::string& imagePath,
            const sf::Color& colorText)
            : m_font(fontPath), m_imagePath(imagePath)
        {

            if (!m_texture.loadFromFile(imagePath)) {
                throw std::runtime_error("Failed to load button image: " + imagePath);
            }
            m_texture.setSmooth(true);

            // Setup sprite as background
            m_sprite = std::make_unique<sf::Sprite>(m_texture);
            m_sprite->setScale({
                size.x / static_cast<float>(m_texture.getSize().x),
                size.y / static_cast<float>(m_texture.getSize().y)
            });

            // Setup label
            m_label = std::make_unique<sf::Text>(m_font, text, charSize);
            m_label->setFillColor(colorText);

            updateLabelPosition();
        }

        void setLabel(const std::string& text) {
            m_label->setString(text);
            updateLabelPosition();
        }

        std::string getLabel() const { return m_label->getString(); }

        void setLabelColor(const sf::Color& color) { m_label->setFillColor(color); }
        sf::Color getLabelColor() const { return m_label->getFillColor(); }

        void setPosition(const sf::Vector2f& pos) {
            m_sprite->setPosition(pos);
            updateLabelPosition();
        }

        sf::Vector2f getPosition() const { return m_sprite->getPosition(); }

        void setImage(const std::string& imagePath) {
            if (!m_texture.loadFromFile(imagePath)) {
                throw std::runtime_error("Failed to load button image: " + imagePath);
            }
            m_texture.setSmooth(true);

            m_sprite->setTexture(m_texture, true);

            m_imagePath = imagePath;

            updateLabelPosition();
        }

        std::string getImage() const { return std::filesystem::path(m_imagePath).filename().string(); }

        void handleEvent(const sf::Event::MouseButtonPressed& ev, sf::RenderWindow& window) {
            if (ev.button == sf::Mouse::Button::Left) {
                sf::Vector2f pos = window.mapPixelToCoords({ ev.position.x, ev.position.y });
                if (contains(pos)) m_pressed = true;
            }
        }

        void handleEvent(const sf::Event::MouseButtonReleased& ev, sf::RenderWindow& window) {
            if (m_pressed && ev.button == sf::Mouse::Button::Left) {
                sf::Vector2f pos = window.mapPixelToCoords({ ev.position.x, ev.position.y });
                if (contains(pos)) {
                    if (m_callback) m_callback();
                }
            }
            m_pressed = false;
        }

        void draw(sf::RenderWindow& window) {
            window.draw(*m_sprite);
            window.draw(*m_label);
        }

        bool isPressed() const { return m_pressed; }
        void setCallback(std::function<void()> cb) { m_callback = std::move(cb); }

    private:
        sf::Font m_font;
        std::string m_imagePath;
        sf::Texture m_texture;
        std::unique_ptr<sf::Sprite> m_sprite;
        std::unique_ptr<sf::Text> m_label;
        bool m_pressed = false;
        std::function<void()> m_callback;

        bool contains(const sf::Vector2f& p) const {
            auto bounds = m_sprite->getGlobalBounds();
            return p.x >= bounds.position.x && p.x <= bounds.position.x + bounds.size.x &&
                p.y >= bounds.position.y && p.y <= bounds.position.y + bounds.size.y;
        }

        void updateLabelPosition() {
            auto lb = m_label->getLocalBounds();
            auto bounds = m_sprite->getGlobalBounds();

            m_label->setPosition({
                bounds.position.x + (bounds.size.x - lb.size.x) / 2.f - lb.position.x,
                bounds.position.y + (bounds.size.y - lb.size.y) / 2.f - lb.position.y
            });
        }
    };

}
