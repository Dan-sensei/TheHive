
/* ================================================================================================== */
/* Cosas extra para FMOD                                                                              */
/* ================================================================================================== */

#ifndef _FMOD_EXTRA_HPP
#define _FMOD_EXTRA_HPP

#include <iostream>
#include "fmod_studio.hpp"
#include "fmod.hpp"
#include "fmod_errors.h"

inline void ERRCHECK_fn(FMOD_RESULT result, const char *file, int line)
{
    if (result != FMOD_OK)
    {
        std::cerr << file << "(" << line << "): FMOD error " << result << " - " << FMOD_ErrorString(result) << std::endl;
        exit(-1);
    }
}


#define ERRCHECK(_result) ERRCHECK_fn(_result, __FILE__, __LINE__)


#endif
