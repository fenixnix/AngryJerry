#ifndef MRB2CONTACTLISTENER_H
#define MRB2CONTACTLISTENER_H

#include <Box2D/Box2D.h>
#include <singleton.h>

class MRb2ContactListener : public b2ContactListener, public NSingleton<MRb2ContactListener>
{
public:
    MRb2ContactListener();
    void BeginContact(b2Contact* contact);
    void EndContact(b2Contact* contact);
};

#endif // MRB2CONTACTLISTENER_H
