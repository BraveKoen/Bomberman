#ifndef __UTILITIES_HPP__
#define __UTILITIES_HPP__

#include <array>
#include <string>
#include "definitions.hpp"
#include "game.hpp"

/// \brief
/// Overloaded functions for vector operations
/// \details
/// These overloaded operators provide easy usage for performing vector
/// calculations. Since their implementation is pretty self-explanatory,
/// no additional documentation is provided. While these overloaded
/// operators have their uses, things can become messy when throwing
/// them anywhere and eveywhere.

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

/// \brief
/// Utilities namespace
/// \details
/// A collection of useful functions that can be used throughout the entire
/// code base, not bound to any specific class.
namespace Util {
    /// \brief
    /// Switches to another state
    /// \details
    /// Adds another state to the given state machine without replacing the
    /// state that is currently on top.
    template<typename T>
    constexpr void switchState(gameDataRef gameData) {
        gameData->stateMachine.addState(std::make_unique<T>(gameData), false);
    }

    /// \brief
    /// Switches to another state
    /// \details
    /// Adds another state to the given state machine without replacing the
    /// state that is currently on top. Allows for providing an playerId to the
    /// object being constructed.
    template<typename T>
    constexpr void switchState(gameDataRef gameData, uint_fast8_t playerId) {
        gameData->stateMachine.addState(std::make_unique<T>(gameData, playerId), false);
    }

    /// \brief
    /// Replaces the current state
    /// \details
    /// Adds another state to the given state machine while replacing the state
    /// that is currently on top.
    template<typename T>
    constexpr void replaceState(gameDataRef gameData) {
        gameData->stateMachine.addState(std::make_unique<T>(gameData), true);
    }

    /// \brief
    /// Switches to another state
    /// \details
    /// Adds another state to the given state machine while replacing the
    /// state that is currently on top. Also passes a playerId to the object
    /// being constructed.
    template<typename T>
    constexpr void replaceState(gameDataRef gameData, uint_fast8_t playerId) {
        gameData->stateMachine.addState(std::make_unique<T>(gameData, playerId), true);
    }

    /// \brief
    /// Truncates a string with ellipses
    /// \details
    /// Truncates a string with trailing ellipses. Limit specifies the maximum
    /// amount of characters that the resulting string can contain.
    inline std::string ellipseString(std::string origin, std::size_t limit) {
        if (origin.length() > limit) {
            const auto ellipses = std::string{"..."};
            return origin.substr(0, limit - ellipses.length()) + ellipses;
        }
        return origin;
    }

    /// \brief
    /// Loads an array of textures
    /// \details
    /// Loads multiple textures at once, specified by an array of Resource Data
    /// items. Resource Data items consist of an identifier and a file name.
    template<auto N>
    constexpr void loadTextures(
        gameDataRef gameData,
        const std::array<resourceData, N>& resources
    ) {
        for (const auto& resource : resources) {
            gameData->assetManager.loadTexture(resource);
        }
    }

    /// \brief
    /// Loads an array of textures
    /// \details
    /// Loads multiple textures at once, specified by an array of Resource
    /// Container items. The result is stored within the Resource Container
    /// whenever its sprite member points to an actual sprite.
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

    /// \brief
    /// Gets the offset from a related origin
    /// \details
    /// Calculates the offset from a related origin.
    constexpr float offsetFromOrigin(float origin, float section, float count) {
        const auto region = section * (count - 1);
        return (origin - region) / 2;
    }

    /// \brief
    /// Scales a vector in a centered position
    /// \details
    /// Scales the Y-value of a vector while centering the X-value.
    inline sf::Vector2f scaleHeightCentered(
        const sf::Vector2u& origin,
        float scale
    ) {
        return {origin.x / 2.f, origin.y * scale};
    }

    /// \brief
    /// Positions a scaled drawable in a centered position
    /// \details
    /// Centers the X-value and scales Y-value.
    template<typename T>
    constexpr void centerXscaleY(const sf::Vector2u& origin, T& drawable, float scale) {
        drawable.setPosition(scaleHeightCentered(origin, scale));
    }

    /// \brief
    /// Scales a vector in a centered position
    /// \details
    /// Scales the X-value of a vector while centering the Y-value.
    inline sf::Vector2f scaleWidthCentered(
        const sf::Vector2f& origin,
        float scale
    ) {
        return {origin.x * scale, origin.y / 2};
    }

    /// \brief
    /// Positions a scaled drawable in a centered position
    /// \details
    /// Centers the Y-value and scales X-value.
    template<typename T>
    constexpr void centerYscaleX(const sf::Vector2f& origin, T& drawable, float scale) {
        drawable.setPosition(scaleWidthCentered(origin, scale));
    }

    /// \brief
    /// Drawable's size
    /// \details
    /// Gets the size of a drawable object as a floating point vector.
    template<typename T>
    constexpr sf::Vector2f getSize(const T& drawable) {
        const auto& bounds = drawable.getGlobalBounds();
        return {bounds.width, bounds.height};
    }

    /// \brief
    /// Drawable's width
    /// \details
    /// Gets the width of a drawable object as a floating point value.
    template<typename T>
    constexpr float getWidth(const T& drawable) {
        const auto& bounds = drawable.getGlobalBounds();
        return bounds.width;
    }

    /// \brief
    /// Drawable's height
    /// \details
    /// Gets the height of a drawable object as a floating point value.
    template<typename T>
    constexpr float getHeight(const T& drawable) {
        const auto& bounds = drawable.getGlobalBounds();
        return bounds.height;
    }

    /// \brief
    /// Drawable's center
    /// \details
    /// Gets the center of a drawable object as a floating point vector.
    template<typename T>
    constexpr sf::Vector2f getCenter(const T& drawable) {
        return getSize(drawable) / 2;
    }

    /// \brief
    /// Centers drawable's origin
    /// \details
    /// Sets the origin of a drawable to its center.
    template<typename T>
    constexpr void centerOrigin(T& drawable) {
        drawable.setOrigin(getCenter(drawable));
    }

    /// \brief
    /// Scale origin vector
    /// \details
    /// Scales the origin of a vector.
    inline sf::Vector2f scaleOrigin(
        const sf::Vector2f& origin,
        float ratioX,
        float ratioY
    ) {
        return {origin.x * ratioX, origin.y * ratioY};
    }

    /// \brief
    /// Scale from a ratio
    /// \details
    /// Calculates the scale from a ratio.
    constexpr float scaleFromRatio(float total, float part, float ratio) {
        const auto content = total * ratio;
        return content / part;
    }

    /// \brief
    /// Scale from a ratio
    /// \details
    /// Calculates the x-value of a scale from a ratio. Uses 1 for the y-value.
    inline sf::Vector2f xScaleFromRatio(float total, float part, float ratio) {
        return {scaleFromRatio(total, part, ratio), 1};
    }

    /// \brief
    /// Scale from a ratio
    /// \details
    /// Calculates the y-value of a scale from a ratio. Uses 1 for the x-value.
    inline sf::Vector2f yScaleFromRatio(float total, float part, float ratio) {
        return {1, scaleFromRatio(total, part, ratio)};
    }

    /// \brief
    /// Offset from content
    /// \details
    /// Calculates the offset related to some contents.
    constexpr float offsetFromContent(float total, float content) {
        const auto padding = total - content;
        return padding / 2;
    }

    /// \brief
    /// Offset from ratio
    /// \details
    /// Calculates the offset related to some contents based on a ratio.
    constexpr float offsetFromRatio(float total, float ratio) {
        return offsetFromContent(total, total * ratio);
    }

    /// \brief
    /// Scales a rectangle object
    /// \details
    /// Scales a rectangle object bases on a floating point vector value.
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

    /// \brief
    /// Centers a vector value
    /// \details
    /// Centers a floating point vector value using a base and offset.
    template<typename T>
    constexpr sf::Vector2<T> centerVector(
        const sf::Vector2<T>& base,
        const sf::Rect<T>& offset,
        const sf::Vector2<T>& scale
    ) {
        return base + scaleRect(offset, scale);
    }

    /// \brief
    /// Centers a rectangle shape
    /// \details
    /// Centers a rectangle shape related to a vector value as canvas
    /// proportionally to given index value and total.
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

    /// \brief
    /// Centers a rectangle shape
    /// \details
    /// Centers a rectangle shape related to the rectangle bounds of a canvas
    /// proportionally to given index value and total.
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

    /// \brief
    /// Centers a rectangle shape margin
    /// \details
    /// Centers a rectangle shape related to the rectangle bounds of a canvas
    /// proportionally to a given index value and total with a margin.
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
