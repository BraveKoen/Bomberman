#ifndef __BUTTONFACTORY__
#define __BUTTONFACTORY__

#include <vector>
#include <string>
#include <SFML/Graphics.hpp>

#include "definitions.hpp"
#include "menuButton.hpp"

// using TransformFunc = sf::Vector2f (*)(sf::Vector2f left, sf::Vector2f right);

typedef sf::Vector2f (*TransformFunc)(sf::Vector2f left, sf::Vector2f right) ;

class ButtonFactory {
private:
    const resourceData& texture;
    const resourceData& font;
    float textScale;
    sf::Vector2f textOffset;
    sf::Color textColor;
    template<typename T, typename D>
    std::vector<T> createButtons(
        gameDataRef gameData,
        std::vector<D> buttonData,
        TransformFunc transformAxis,
        float placementRatio,
        float spacingScale,
        sf::Vector2f buttonScale
    ) const;
public:
    ButtonFactory();
    ButtonFactory(
        const resourceData& texture,
        const resourceData& font
    );
    ButtonFactory(
        const resourceData& texture,
        const resourceData& font,
        float textScale,
        sf::Vector2f textOffset,
        sf::Color textColor
    );
    void loadResources(gameDataRef gameData) const;
    template<typename T, typename D>
    std::vector<T> createButtonsHorizontal(
        gameDataRef gameData,
        std::vector<D> buttons,
        float placementRatio,
        float spacingScale = Resource::Button::defaultSpacingScale,
        sf::Vector2f buttonScale = Resource::Button::defaultButtonScale
    ) const;
    template<typename T, typename D>
    std::vector<T> createButtonsVertical(
        gameDataRef gameData,
        std::vector<D> buttons,
        float placementRatio,
        float spacingScale = Resource::Button::defaultSpacingScale,
        sf::Vector2f buttonScale = Resource::Button::defaultButtonScale
    ) const;
    float getTextScale() const;
    const sf::Vector2f& getTextOffset() const;
    const sf::Color& getTextColor() const;
    void setTextScale(float textScale);
    void setTextOffset(sf::Vector2f textOffset);
    void setTextColor(sf::Color textColor);
};

#endif // __BUTTONFACTORY__
