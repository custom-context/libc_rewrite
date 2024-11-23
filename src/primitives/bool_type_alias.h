#pragma once

// C2x integrates these keywords: bool, true, false
#if __STDC_VERSION__ > 201710L
    #include "version/c2x_bool_type_alias.h"
#else
    #include "version/c17_bool_type_alias.h"
#endif
