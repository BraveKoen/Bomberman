#include "../headers/buttonFactory.hpp"
#include "../headers/definitions.hpp"
#include "../headers/utilities.hpp"
#include "../headers/menuButton.hpp"
#include "../headers/menuButtonExt.hpp"

ButtonFactory::ButtonFactory():
    ButtonFactory{
        Resource::Button::defaultTexture,
        Resource::Button::defaultFont
    }
{}

ButtonFactory::ButtonFactory(
    const resourceData& texture,
    const resourceData& font
):
    ButtonFactory{
        texture,
        font,
        Resource::Button::defaultTextScale,
        std::move(Resource::Button::defaultTextOffset),
        Resource::Button::defaultTextColor
    }
{}

ButtonFactory::ButtonFactory(
    const resourceData& texture,
    const resourceData& font,
    float textScale,
    sf::Vector2f textOffset,
    sf::Color textColor
):
    texture{texture},
    font{font},
    textScale{textScale},
    textOffset{std::move(textOffset)},
    textColor{textColor}
{}

void ButtonFactory::loadResources(gameDataRef gameData) const {
    gameData->assetManager.loadTexture(texture);
    gameData->assetManager.loadFont(font);
}

template<typename T, typename D> std::vector<T>
ButtonFactory::createButtonsHorizontal(
    gameDataRef gameData,
    std::vector<D> buttonData,
    float placementRatio,
    float spacingScale,
    sf::Vector2f buttonScale
) const {
    return createButtons<T, D>(
        gameData,
        std::move(buttonData),
        [](sf::Vector2f left, sf::Vector2f right){
            return sf::Vector2f{left.x, right.y};
        },
        placementRatio,
        spacingScale,
        buttonScale
    );
}

template std::vector<MenuButton>
ButtonFactory::createButtonsHorizontal(
    gameDataRef gameData,
    std::vector<ButtonData> buttonData,
    float placementRatio,
    float spacingScale,
    sf::Vector2f buttonScale
) const;

template std::vector<MenuButtonExt>
ButtonFactory::createButtonsHorizontal(
    gameDataRef gameData,
    std::vector<ButtonDataExt> buttonData,
    float placementRatio,
    float spacingScale,
    sf::Vector2f buttonScale
) const;

template<typename T, typename D>
std::vector<T> ButtonFactory::createButtonsVertical(
    gameDataRef gameData,
    std::vector<D> buttonData,
    float placementRatio,
    float spacingScale,
    sf::Vector2f buttonScale
) const {
    return createButtons<T, D>(
        gameData,
        std::move(buttonData),
        [](sf::Vector2f left, sf::Vector2f right){
            return sf::Vector2f{right.x, left.y};
        },
        placementRatio,
        spacingScale,
        buttonScale
    );
}

template std::vector<MenuButton>
ButtonFactory::createButtonsVertical(
    gameDataRef gameData,
    std::vector<ButtonData> buttonData,
    float placementRatio,
    float spacingScale,
    sf::Vector2f buttonScale
) const;

template std::vector<MenuButtonExt>
ButtonFactory::createButtonsVertical(
    gameDataRef gameData,
    std::vector<ButtonDataExt> buttonData,
    float placementRatio,
    float spacingScale,
    sf::Vector2f buttonScale
) const;

template<typename T, typename D>
std::vector<T> ButtonFactory::createButtons(
    gameDataRef gameData,
    std::vector<D> buttonData,
    TransformFunc transformAxis,
    float placementRatio,
    float spacingScale,
    sf::Vector2f buttonScale
) const {
    std::vector<T> buttonObjects;

    for (auto index = 0u; index < buttonData.size(); ++index) {
        static const auto& buttonTexture = gameData->assetManager.getTexture(this->texture);
        static const auto windowSize = gameData->window.getSize();
        static const auto spriteScale = windowSize / buttonTexture.getSize() / buttonScale;
        auto sprite = sf::Sprite{buttonTexture};
        Util::centerOrigin(sprite);
        sprite.setScale(spriteScale);

        static const auto interval = Util::getSize(sprite) * spacingScale;
        static const auto offset = Util::offsetFromOrigin(windowSize, interval, buttonData.size());
        static const auto placement = windowSize * placementRatio;
        const auto position = transformAxis(offset + (interval * index), placement);
        sprite.setPosition(position);

        static const auto& buttonFont = gameData->assetManager.getFont(this->font);
        auto text = sf::Text{buttonData[index].title, buttonFont};
        Util::centerOrigin(text);
        static const auto fontScale = spriteScale * this->textScale;
        text.setScale(fontScale);
        text.setPosition(position - this->textOffset);
        text.setFillColor(this->textColor);

        buttonObjects.emplace_back(std::move(sprite), std::move(text), buttonData[index].action);
    }
    return buttonObjects;
}

template std::vector<MenuButton> ButtonFactory::createButtons(
    gameDataRef gameData,
    std::vector<ButtonData> buttonData,
    TransformFunc transformAxis,
    float placementRatio,
    float spacingScale,
    sf::Vector2f buttonScale
) const;

template std::vector<MenuButtonExt> ButtonFactory::createButtons(
    gameDataRef gameData,
    std::vector<ButtonDataExt> buttonData,
    TransformFunc transformAxis,
    float placementRatio,
    float spacingScale,
    sf::Vector2f buttonScale
) const;

float ButtonFactory::getTextScale() const {
    return textScale;
}

const sf::Vector2f& ButtonFactory::getTextOffset() const {
    return textOffset;
}

const sf::Color& ButtonFactory::getTextColor() const {
    return textColor;
}

void ButtonFactory::setTextOffset(sf::Vector2f textOffset) {
    textOffset = std::move(textOffset);
}

void ButtonFactory::setTextScale(float textScale) {
    textScale = textScale;
}

void ButtonFactory::setTextColor(sf::Color textColor) {
    textColor = textColor;
}
