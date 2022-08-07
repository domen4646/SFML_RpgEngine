#ifndef WINDOWMESSAGE_H
#define WINDOWMESSAGE_H

#include "windowbase.h"

#define WINDOW_MESSAGE_HEIGHT 96
#define WINDOW_MESSAGE_WIDTH 480

class WindowMessage : public WindowBase
{
private:
    std::string fullmessage;
    std::string message = "";
    sf::Text contentText;

public:
    virtual void drawContents(sf::RenderTarget& target) override;
    virtual void displayContents(YIELD_SINK &sink) override;
    WindowMessage(std::string msg);
};

#endif // WINDOWMESSAGE_H
