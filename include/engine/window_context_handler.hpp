#pragma once
#include <SFML/Graphics.hpp>
#include "render/viewport_handler.hpp"
#include "common/event_manager.hpp"
#include "common/utils.hpp"


class WindowContextHandler;


class RenderContext
{
public:
    explicit
    RenderContext(sf::RenderWindow& window)
        : m_window(window)
        , m_viewport_handler(toVector2f(window.getSize()))
    {
    }

    void setFocus(sf::Vector2f focus)
    {
        m_viewport_handler.setFocus(focus);
    }

    void setZoom(float zoom)
    {
        m_viewport_handler.setZoom(zoom);
    }
    
    void registerCallbacks(sfev::EventManager& event_manager)
    {
        event_manager.addEventCallback(sf::Event::Closed, [&](sfev::CstEv) { m_window.close(); });
        event_manager.addKeyPressedCallback(sf::Keyboard::Escape, [&](sfev::CstEv) { m_window.close(); });
        event_manager.addMousePressedCallback(sf::Mouse::Left, [&](sfev::CstEv) {
            m_viewport_handler.click(event_manager.getFloatMousePosition());
        });
        event_manager.addMouseReleasedCallback(sf::Mouse::Left, [&](sfev::CstEv) {
            m_viewport_handler.unclick();
        });
        event_manager.addEventCallback(sf::Event::MouseMoved, [&](sfev::CstEv) {
            m_viewport_handler.setMousePosition(event_manager.getFloatMousePosition());
        });
        event_manager.addEventCallback(sf::Event::MouseWheelScrolled, [&](sfev::CstEv e) {
            m_viewport_handler.wheelZoom(e.mouseWheelScroll.delta);
        });
    }
    
    void drawDirect(const sf::Drawable& drawable)
    {
        m_window.draw(drawable);
    }
    
    void draw(const sf::Drawable& drawable, sf::RenderStates render_states = {})
    {
        render_states.transform = m_viewport_handler.getTransform();
        m_window.draw(drawable, render_states);
    }
    
    void clear(sf::Color color = sf::Color::Black)
    {
        m_window.clear(color);
    }
    
    void display()
    {
        m_window.display();
    }
    
private:
    sf::RenderWindow& m_window;
    ViewportHandler m_viewport_handler;
    
    friend class WindowContextHandler;
};


class WindowContextHandler
{
public:
    WindowContextHandler(const std::string& window_name,
                         sf::Vector2u window_size,
                         int32_t window_style = sf::Style::Default)
        : m_window(sf::VideoMode(window_size.x, window_size.y), window_name, window_style)
        , m_event_manager(m_window, true)
        , m_render_context(m_window)
    {
        m_window.setFramerateLimit(60);
        m_render_context.registerCallbacks(m_event_manager);
    }

    [[nodiscard]]
    sf::Vector2u getWindowSize() const
    {
        return m_window.getSize();
    }
    
    void processEvents()
    {
        m_event_manager.processEvents();
    }
    
    bool isRunning() const
    {
        return m_window.isOpen();
    }
    
    bool run()
    {
        processEvents();
        return isRunning();
    }

    sfev::EventManager& getEventManager()
    {
        return m_event_manager;
    }

    RenderContext& getRenderContext()
    {
        return m_render_context;
    }
    
    sf::Vector2f getWorldMousePosition() const
    {
        return m_render_context.m_viewport_handler.getMouseWorldPosition();
    }
    
private:
    sf::RenderWindow m_window;
    sfev::EventManager m_event_manager;
    RenderContext m_render_context;
};
