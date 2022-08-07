#ifndef EVENTPAGE_H
#define EVENTPAGE_H

#include "../engine.h"

class InteractableMapObject;
class SpriteBase;

typedef bool (*BOOLEAN_FUNC)(InteractableMapObject*);

class EventPage
{
private:
    COR_FUNC action = NULL;
    BOOLEAN_FUNC active_when = NULL;
    RenderPriority render_priority = RenderPriority::BelowCharacters;
    InteractionType interact_type = InteractionType::ActionButton;
    SpriteBase* sprite = NULL;

    // checkboxes
    bool directionFix = false;

public:
    EventPage(COR_FUNC _action, BOOLEAN_FUNC _active_when, RenderPriority _render_priority, InteractionType _interact_type, SpriteBase* _sprite);
    EventPage(COR_FUNC _action, BOOLEAN_FUNC _active_when, RenderPriority _render_priority, InteractionType _interact_type, SpriteBase* _sprite, bool _directionFix);
    bool isActive(InteractableMapObject* _ref);

    // getters
    COR_FUNC getAction();
    InteractionType getInteractionType() const;
    RenderPriority getRenderPriority() const;
    SpriteBase *getSprite() const;
    bool getDirectionFix() const;
};

#endif // EVENTPAGE_H
