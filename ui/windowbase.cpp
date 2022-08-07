#include "windowbase.h"
#include "../utils/utils.h"

bool WindowBase::isOpen()
{
    return opened;
}

bool WindowBase::shouldClose()
{
    return should_close;
}

float WindowBase::getX()
{
    return X;
}

float WindowBase::getY()
{
    return Y;
}

unsigned int WindowBase::getWidth()
{
    return width;
}

unsigned int WindowBase::getHeight()
{
    return height;
}

void WindowBase::update(YIELD_SINK &sink)
{
    open(sink);
    opened = true;
    displayContents(sink);
    ready = true;
    while (!should_close) {
        sink();
    }
    opened = false;
    close(sink);
}

void WindowBase::draw(sf::RenderTarget &target)
{
    target.draw(*windowShape);
    if (opened) {
        drawContents(target);
    }
}

void WindowBase::drawContents(sf::RenderTarget &target) {}

void WindowBase::handleInput(sf::Keyboard::Key key)
{
    if (!should_close && ready && key == sf::Keyboard::Escape) {
        should_close = true;
        return;
    }
}

void WindowBase::open(YIELD_SINK &sink)
{
    utils::animate_rectangle_shape(sink, windowShape, X, Y, width, height, WINDOW_OPEN_FRAME_SPEED);
}

void WindowBase::displayContents(YIELD_SINK &sink) {}

void WindowBase::close(YIELD_SINK &sink)
{
    printf("Close %f %f %i %i\n", initX, initY, initWidth, initHeight);
    utils::animate_rectangle_shape(sink, windowShape, initX, initY, initWidth, initHeight, WINDOW_CLOSE_FRAME_SPEED);
}

WindowBase::WindowBase(int _X, int _Y, unsigned int W, unsigned int H)
{
    X = _X;
    Y = _Y;
    width = W;
    height = H;

    initX = X + (float)width / 2;
    initY = Y + (float)height / 2;
    initWidth = 0;
    initHeight = 0;

    // Replace with something else if needed
    windowShape = new sf::RectangleShape();
    windowShape->setPosition(initX, initY);
    windowShape->setSize(sf::Vector2f(initWidth, initHeight));
    windowShape->setFillColor(sf::Color::Black);
    windowShape->setOutlineColor(sf::Color::White);
    windowShape->setOutlineThickness(1.0F);
}

WindowBase::~WindowBase()
{
    delete windowShape;
}
