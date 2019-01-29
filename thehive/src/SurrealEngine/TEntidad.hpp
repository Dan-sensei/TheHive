#ifndef TENTIDAD_H
#define TENTIDAD_H

class TEntidad {
    public:
        virtual ~TEntidad()         = 0;
        virtual void beginDraw()    = 0;
        virtual void endDraw()      = 0;
};

#endif
