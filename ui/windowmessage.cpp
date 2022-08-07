#include "windowmessage.h"
#include "../gameresources.h"

void WindowMessage::drawContents(sf::RenderTarget &target)
{
    target.draw(contentText);
}

void WindowMessage::displayContents(YIELD_SINK &sink)
{
    for (int i=0; i<fullmessage.length(); i++) {
        message += fullmessage[i];
        contentText.setString(message);
        sink();
    }
}

WindowMessage::WindowMessage(std::string msg)
    : WindowBase((GAME_WINDOW_WIDTH - WINDOW_MESSAGE_WIDTH) / 2, GAME_WINDOW_HEIGHT - WINDOW_MESSAGE_HEIGHT - 32, WINDOW_MESSAGE_WIDTH, WINDOW_MESSAGE_HEIGHT)
{
    contentText.setPosition(getX() + 8, getY() + 8);
    contentText.setFont(GameResources::font);
    contentText.setCharacterSize(16);
    contentText.setFillColor(sf::Color::White);
    fullmessage = msg;
}
