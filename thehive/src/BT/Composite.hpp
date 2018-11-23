#ifndef COMPOSITE_HPP
#define COMPOSITE_HPP

#include "Behavior.hpp"
#include <vector>

class Composite : public Behavior {
    public:
        Composite(const Composite &orig);
        Composite();

       virtual void addChild(Behavior* hijo);
       virtual void removeChild(Behavior* hijo);
       virtual void clearChildren();
       virtual ~Composite();

    protected:
       using Behaviors = std::vector<Behavior*>;
       Behaviors m_Children;
};
#endif
