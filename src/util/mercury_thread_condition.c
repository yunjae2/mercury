/*
 * Copyright (C) 2013-2020 Argonne National Laboratory, Department of Energy,
 *                    UChicago Argonne, LLC and The HDF Group.
 * All rights reserved.
 *
 * The full copyright notice, including terms governing use, modification,
 * and redistribution, is contained in the COPYING file that can be
 * found at the root of the source code distribution tree.
 */

#include "mercury_thread_condition.h"

/*---------------------------------------------------------------------------*/
int
hg_thread_cond_init(hg_thread_cond_t *cond)
{
#ifdef _WIN32
    InitializeConditionVariable(cond);
#else
    pthread_condattr_t attr;

    pthread_condattr_init(&attr);
#    if defined(HG_UTIL_HAS_PTHREAD_CONDATTR_SETCLOCK) &&                      \
        defined(HG_UTIL_HAS_CLOCK_MONOTONIC_COARSE)
    /* Must set clock ID if using different clock */
    pthread_condattr_setclock(&attr, CLOCK_MONOTONIC_COARSE);
#    endif
    if (pthread_cond_init(cond, &attr))
        return HG_UTIL_FAIL;
    pthread_condattr_destroy(&attr);
#endif

    return HG_UTIL_SUCCESS;
}

/*---------------------------------------------------------------------------*/
int
hg_thread_cond_destroy(hg_thread_cond_t *cond)
{
#ifndef _WIN32
    if (pthread_cond_destroy(cond))
        return HG_UTIL_FAIL;
#endif

    return HG_UTIL_SUCCESS;
}
