
#ifndef TEST_UTIL_EXPORT_H
#define TEST_UTIL_EXPORT_H

#ifdef TEST_UTIL_STATIC_DEFINE
#  define TEST_UTIL_EXPORT
#  define TEST_UTIL_NO_EXPORT
#else
#  ifndef TEST_UTIL_EXPORT
#    ifdef quassel_test_util_EXPORTS
        /* We are building this library */
#      define TEST_UTIL_EXPORT 
#    else
        /* We are using this library */
#      define TEST_UTIL_EXPORT 
#    endif
#  endif

#  ifndef TEST_UTIL_NO_EXPORT
#    define TEST_UTIL_NO_EXPORT 
#  endif
#endif

#ifndef TEST_UTIL_DEPRECATED
#  define TEST_UTIL_DEPRECATED __attribute__ ((__deprecated__))
#endif

#ifndef TEST_UTIL_DEPRECATED_EXPORT
#  define TEST_UTIL_DEPRECATED_EXPORT TEST_UTIL_EXPORT TEST_UTIL_DEPRECATED
#endif

#ifndef TEST_UTIL_DEPRECATED_NO_EXPORT
#  define TEST_UTIL_DEPRECATED_NO_EXPORT TEST_UTIL_NO_EXPORT TEST_UTIL_DEPRECATED
#endif

/* NOLINTNEXTLINE(readability-avoid-unconditional-preprocessor-if) */
#if 0 /* DEFINE_NO_DEPRECATED */
#  ifndef TEST_UTIL_NO_DEPRECATED
#    define TEST_UTIL_NO_DEPRECATED
#  endif
#endif

#endif /* TEST_UTIL_EXPORT_H */
