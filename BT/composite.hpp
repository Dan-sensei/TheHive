#ifndef COMPOSITE_HPP
#define COMPOSITE_HPP

#include "behavior.h"

class composite : public behavior {
protected:
   virtual void addChild(behavior*)    = 0;
   virtual void removeChild(behavior*) = 0;
   virtual void clearChildren()        = 0;
public:
   typedef std::vector<behavior*> behaviors;
   behaviors m_Children;
};


#endif /* end of include guard: COMPOSITE_HPP */
