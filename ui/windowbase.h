#ifndef WINDOWBASE_H
#define WINDOWBASE_H

#include "../engine.h"
#include "updateable.h"

#define WINDOW_OPEN_FRAME_SPEED 15
#define WINDOW_CLOSE_FRAME_SPEED 15

class WindowBase : public Updateable
{
private:
    float X;
    float Y;
    unsigned int width;
    unsigned int height;

    float initX;
    float initY;
    unsigned int initWidth;
    unsigned int initHeight;

protected:
    // Pointer due to possible override (NinePatchRect instead of simple window)
    sf::RectangleShape* windowShape = NULL;

    bool opened = false; // When open animation finished
    bool ready = false; // When ready to be closed
    bool should_close = false; // When is should be closed

public:

    bool isOpen();
    bool shouldClose();

    float getX();
    float getY();
    unsigned int getWidth();
    unsigned int getHeight();

    virtual void update(YIELD_SINK &sink);

    virtual void draw(sf::RenderTarget& target) override;
    virtual void drawContents(sf::RenderTarget& target);
    virtual void handleInput(sf::Keyboard::Key key);

    // Use for opening animation
    virtual void open(YIELD_SINK &sink);

    // Use for animating the contents when displayed
    virtual void displayContents(YIELD_SINK &sink);

    // Use for closing animation
    virtual void close(YIELD_SINK &sink);


    WindowBase(int _X, int _Y, unsigned int W, unsigned int H);
    virtual ~WindowBase();
};

#endif // WINDOWBASE_H
