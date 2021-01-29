#ifndef __UTILITIES_HPP__
#define __UTILITIES_HPP__

#include <array>
#include <string>
#include "definitions.hpp"
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
    const sf::Vector2f& left,
    float right
) {
    return {left.x / right, left.y / right};
}

inline sf::Vector2f operator/(
    const sf::Vector2u& left,
    const sf::Vector2u& right
) {
    const auto leftX{static_cast<float>(left.x)};
    const auto leftY{static_cast<float>(left.y)};
    return {leftX / right.x, leftY / right.y};
}

inline sf::Vector2f operator*(
    const sf::Vector2f& left,
    const sf::Vector2f& right
) {
    return {left.x * right.x, left.y * right.y};
}

inline sf::Vector2f operator*(
    float left,
    const sf::Vector2f& right
) {
    return {left * right.x, left * right.y};
}

inline sf::Vector2f operator*(
    const sf::Vector2f& left,
    float right
) {
    return {left.x * right, left.y * right};
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

namespace Util {
    template<typename T>
    constexpr void switchState(gameDataRef gameData) {
        gameData->stateMachine.addState(std::make_unique<T>(gameData), false);
    }

    template<typename T>
    constexpr void switchState(gameDataRef gameData, uint_fast8_t playerId) {
        gameData->stateMachine.addState(std::make_unique<T>(gameData, playerId), false);
    }

    template<typename T>
    constexpr void replaceState(gameDataRef gameData) {
        gameData->stateMachine.addState(std::make_unique<T>(gameData), true);
    }

    template<typename T>
    constexpr void replaceState(gameDataRef gameData, uint_fast8_t playerId) {
        gameData->stateMachine.addState(std::make_unique<T>(gameData, playerId), true);
    }

    inline std::string ellipseString(std::string origin, std::size_t limit) {
        if (origin.length() > limit) {
            const auto ellipses = std::string{"..."};
            return origin.substr(0, limit - ellipses.length()) + ellipses;
        }
        return origin;
    }

    template<auto N>
    constexpr void loadTextures(
        gameDataRef gameData,
        const std::array<resourceData, N>& resources
    ) {
        for (const auto& resource : resources) {
            gameData->assetManager.loadTexture(resource);
        }
    }

    template<auto N>
    constexpr void loadTextures(
        gameDataRef gameData,
        const std::array<resourceContainer, N>& resources
    ) {
        for (const auto& resource : resources) {
            const auto& texture = gameData->assetManager.loadTexture(resource.data);

            if (resource.sprite not_eq nullptr) {
                resource.sprite->setTexture(texture);
            }
        }
    }

    constexpr float offsetFromOrigin(float origin, float section, float count) {
        const auto region = section * (count - 1);
        return (origin - region) / 2;
    }

    inline sf::Vector2f scaleHeightCentered(
        const sf::Vector2u& origin,
        float scale
    ) {
        return {origin.x / 2.f, origin.y * scale};
    }

    template<typename T>
    constexpr void centerXscaleY(const sf::Vector2u& origin, T& drawable, float scale) {
        drawable.setPosition(scaleHeightCentered(origin, scale));
    }

    inline sf::Vector2f scaleWidthCentered(
        const sf::Vector2f& origin,
        float scale
    ) {
        return {origin.x * scale, origin.y / 2};
    }

    template<typename T>
    constexpr void centerYscaleX(const sf::Vector2f& origin, T& drawable, float scale) {
        drawable.setPosition(scaleWidthCentered(origin, scale));
    }

    template<typename T>
    constexpr sf::Vector2f getSize(const T& drawable) {
        const auto& bounds = drawable.getGlobalBounds();
        return {bounds.width, bounds.height};
    }

    template<typename T>
    constexpr float getWidth(const T& drawable) {
        const auto& bounds = drawable.getGlobalBounds();
        return bounds.width;
    }

    template<typename T>
    constexpr float getHeight(const T& drawable) {
        const auto& bounds = drawable.getGlobalBounds();
        return bounds.height;
    }

    template<typename T>
    constexpr sf::Vector2f getCenter(const T& drawable) {
        return getSize(drawable) / 2;
    }

    template<typename T>
    constexpr void centerOrigin(T& drawable) {
        drawable.setOrigin(getCenter(drawable));
    }

    inline sf::Vector2f scaleOrigin(
        const sf::Vector2f& origin,
        float ratioX,
        float ratioY
    ) {
        return {origin.x * ratioX, origin.y * ratioY};
    }

    constexpr float scaleFromRatio(float total, float part, float ratio) {
        const auto content = total * ratio;
        return content / part;
    }

    inline sf::Vector2f xScaleFromRatio(float total, float part, float ratio) {
        return {scaleFromRatio(total, part, ratio), 1};
    }

    inline sf::Vector2f yScaleFromRatio(float total, float part, float ratio) {
        return {1, scaleFromRatio(total, part, ratio)};
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
