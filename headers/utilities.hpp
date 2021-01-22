#ifndef __UTILITIES_HPP__
#define __UTILITIES_HPP__

#include "game.hpp"

template<typename T>
inline sf::Vector2f operator/(
    const sf::Vector2<T>& left,
    const sf::Vector2f& right
) {
    return {left.x / right.x, left.y / right.y};
}

template<typename T>
inline sf::Vector2f operator/(
    const sf::Vector2f& left,
    const sf::Vector2<T>& right
) {
    return {left.x / right.x, left.y / right.y};
}

inline sf::Vector2f operator/(
    const sf::Vector2f& left,
    const sf::Vector2f& right
) {
    return {left.x / right.x, left.y / right.y};
}

inline sf::Vector2f operator/(
    const sf::Vector2u& left,
    const sf::Vector2u& right
) {
    const auto leftX{static_cast<float>(left.x)};
    const auto leftY{static_cast<float>(left.y)};
    return {leftX / right.x, leftY / right.y};
}

inline sf::Vector2f operator+(
    const sf::Vector2f& left,
    const sf::Vector2f& right
) {
    return {left.x + right.x, left.y + right.y};
}

inline sf::Vector2i operator+(
    const sf::Vector2i& left,
    const sf::Vector2i& right
) {
    return {left.x + right.x, left.y + right.y};
}

inline sf::Vector2f operator-(
    const sf::Vector2f& left,
    const sf::Vector2f& right
) {
    return {left.x - right.x, left.y - right.y};
}

namespace Sprite {
    inline sf::Vector2f getSize(const sf::Sprite& sprite) {
        const auto& bounds = sprite.getGlobalBounds();
        return {bounds.width, bounds.height};
    }

    inline float getWidth(const sf::Sprite& sprite) {
        const auto& bounds = sprite.getGlobalBounds();
        return bounds.width;
    }

    inline float getHeight(const sf::Sprite& sprite) {
        const auto& bounds = sprite.getGlobalBounds();
        return bounds.height;
    }
}

namespace Util {
    template<typename T>
    void switchState(gameDataRef gameData) {
        gameData->stateMachine.addState(std::make_unique<T>(gameData), false);
    }

    constexpr float scaleFromRatio(float total, float part, float ratio) {
        const auto content = total * ratio;
        return content / part;
    }

    constexpr float offsetFromContent(float total, float content) {
        const auto padding = total - content;
        return padding / 2;
    }

    constexpr float offsetFromRatio(float total, float ratio) {
        return offsetFromContent(total, total * ratio);
    }

    template<typename T>
    constexpr sf::Vector2<T> scaleRect(
        const sf::Rect<T>& base,
        const sf::Vector2<T>& scale
    ) {
        return {
            base.width / scale.x,
            base.height / scale.y
        };
    }

    template<typename T>
    constexpr sf::Vector2<T> centerVector(
        const sf::Vector2<T>& base,
        const sf::Rect<T>& offset,
        const sf::Vector2<T>& scale
    ) {
        return base + scaleRect(offset, scale);
    }

    template<typename T, typename R>
    constexpr sf::Vector2f centerRect(
        const sf::Vector2<T>& canvas,
        const sf::Rect<R>& rect,
        const std::size_t index,
        const std::size_t total
    ) {
        const auto decrement = rect.height / 2 * total;
        const auto increment = rect.height * index;
        return {
            (canvas.x / 2) - (rect.width / 2),
            (canvas.y / 2) - decrement + increment
        };
    }

    template<typename T>
    constexpr sf::Vector2f centerRect(
        const sf::Sprite& canvas,
        const sf::Rect<T>& rect,
        const std::size_t index,
        const std::size_t total
    ) {
        const auto decrement = rect.height / 2 * total;
        const auto increment = rect.height * index;
        const auto& bounds = canvas.getGlobalBounds();
        return {
            (bounds.width / 2) - (rect.width / 2),
            (bounds.height / 2) - decrement + increment
        };
    }

    template<typename T, typename R>
    constexpr sf::Vector2f centerRectMargin(
        const sf::Vector2<T>& canvas,
        const sf::Rect<R>& rect,
        const std::size_t index,
        const std::size_t total
    ) {
        const auto marginDec = (1.0f / (total * 2)) + 1;
        const auto decrement = rect.height / 2 * total * marginDec;
        const auto marginInc = (1.0f / total) + 1;
        const auto increment = rect.height * marginInc * index;
        return {
            (canvas.x / 2) - (rect.width / 2),
            (canvas.y / 2) - decrement + increment
        };
    }
}

#endif // __UTILITIES_HPP__
