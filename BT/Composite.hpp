#ifndef COMPOSITE_HPP
#define COMPOSITE_HPP

#include "Behavior.hpp"
#include <vector>

class Composite : public Behavior {
    public:
       virtual void addChild(Behavior* hijo);
       virtual void removeChild(Behavior* hijo);
       virtual void clearChildren();
    protected:
       typedef std::vector<Behavior*> Behaviors;
       Behaviors m_Children;
};
#endif
