#pragma once

#ifdef DO_IMPL
    #define IMPL(body) body
#else
    #define IMPL(body) ;
#endif