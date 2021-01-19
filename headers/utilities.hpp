#ifndef __UTILITIES_HPP__
#define __UTILITIES_HPP__

#include "../headers/game.hpp"

template<typename T>
inline sf::Vector2f operator/(
    const sf::Vector2<T>& left,
    const sf::Vector2f& right
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

namespace Util {
    template<typename T>
    void switchState(gameDataRef gameData) {
        gameData->stateMachine.addState(std::make_unique<T>(gameData), false);
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
        const auto factorDec = (1.0f / (total * 2)) + 1;
        const auto decrement = rect.height / 2 * total * factorDec;
        const auto factorInc = (1.0f / total) + 1;
        const auto increment = rect.height * factorInc * index;
        return {
            (canvas.x / 2) - (rect.width / 2),
            (canvas.y / 2) - decrement + increment
        };
    }
}

#endif // __UTILITIES_HPP__
