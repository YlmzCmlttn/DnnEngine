#pragma once
#undef DNN_ENGINE_ASSERT
#ifdef NDEBUG
#define DNN_ENGINE_ASSERT(expression, errormessage) ((void)0)
#else
#if __STDC_VERSION__-199901L >= 0
#define DNN_ENGINE_ASSERT(expr, msg) \
    ((void)( (expr) ? 0 : do_assert(__FILE__, __LINE__, __func__, msg) ))

#elif defined(__GNUC__)
#define DNN_ENGINE_ASSERT(expr, msg) \
    ((void)( (expr) ? 0 : do_assert(__FILE__, __LINE__, __FUNCTION__, msg) ))

#else
#define DNN_ENGINE_ASSERT(expr, msg) \
    ((void)( (expr) ? 0 : do_assert(__FILE__, __LINE__, NULL, msg) ))
#endif

#ifndef HAVE_DO_ASSERT
#define HAVE_DO_ASSERT
static inline int __attribute__((noreturn)) do_assert(const char *const filename,
                            const unsigned long linenum,
                            const char *const funcname,
                            const char *const msg)
{
    if (funcname)
        fprintf(stderr, "%s: Line %lu, function %s(): %s\n", filename, linenum, funcname, msg);
    else
        fprintf(stderr, "%s: Line %lu: %s\n", filename, linenum, msg);
    abort();
}
#endif

#endif