#ifndef __UTILITIES_HPP__
#define __UTILITIES_HPP__

#include "../headers/game.hpp"

namespace Util {
    template<typename T>
    void switchState(gameDataRef gameData) {
        gameData->stateMachine.addState(std::make_unique<T>(gameData));
    }

    template<typename T>
    constexpr sf::Vector2f scaleVector(
        const sf::Vector2<T>& base,
        const sf::Vector2<T>& offset,
        const sf::Vector2f& scale
    ) {
        return {
            base.x / offset.x / scale.x,
            base.y / offset.y / scale.y
        };
    }

    template<typename T>
    constexpr sf::Vector2<T> centerVector(
        const sf::Vector2<T>& base,
        const sf::Rect<T>& offset,
        const sf::Vector2<T>& scale
    ) {
        return {
            base.x + (offset.width / scale.x),
            base.y + (offset.height / scale.y)
        };
    }

    template<typename T>
    constexpr sf::Vector2<T> centerRect(
        const sf::Rect<T>& base,
        const sf::Vector2<T>& scale
    ) {
        return {
            base.width / scale.x,
            base.height / scale.y
        };
    }

    template<typename T, typename R>
    constexpr sf::Vector2f centerPosition(
        const sf::Vector2<T>& base,
        const sf::Rect<R>& offset,
        const std::size_t total,
        const std::size_t index
    ) {
        const auto factorDec = (1.0f / (total * 2)) + 1;
        const auto decrement = offset.height / 2 * total * factorDec;
        const auto factorInc = (1.0f / total) + 1;
        const auto increment = offset.height * factorInc * index;
        return {
            (base.x / 2) - (offset.width / 2),
            (base.y / 2) - decrement + increment
        };
    }
}

#endif // __UTILITIES_HPP__
