#include "eventpage.h"

InteractionType EventPage::getInteractionType() const
{
    return interact_type;
}

RenderPriority EventPage::getRenderPriority() const
{
    return render_priority;
}

SpriteBase *EventPage::getSprite() const
{
    return sprite;
}

bool EventPage::getDirectionFix() const
{
    return directionFix;
}

EventPage::EventPage(COR_FUNC _action, BOOLEAN_FUNC _active_when, RenderPriority _render_priority, InteractionType _interact_type, SpriteBase *_sprite)
{
    action = _action;
    active_when = _active_when;
    render_priority = _render_priority;
    if ((int)render_priority < 0 || (int)render_priority > 2) {
        render_priority = RenderPriority::BelowCharacters;
    }
    interact_type = _interact_type;
    sprite = _sprite;
}

EventPage::EventPage(COR_FUNC _action, BOOLEAN_FUNC _active_when, RenderPriority _render_priority, InteractionType _interact_type, SpriteBase *_sprite, bool _directionFix)
    : EventPage(_action, _active_when, _render_priority, _interact_type, _sprite)
{
    directionFix = _directionFix;
}

bool EventPage::isActive(InteractableMapObject* _ref)
{
    printf("active_when %p\n", active_when);
    return (active_when == NULL || active_when(_ref));
}

COR_FUNC EventPage::getAction()
{
    return action;
}
