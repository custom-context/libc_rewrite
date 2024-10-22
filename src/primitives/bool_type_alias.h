#pragma once

// C2x integrates these keywords: bool, true, false
#if __STDC_VERSION__ < 202311L

#ifndef bool
typedef unsigned char bool;
#endif

#ifndef true
#define true ((bool)1u)
#endif

#ifndef false
#define false ((bool)0u)
#endif

#endif
