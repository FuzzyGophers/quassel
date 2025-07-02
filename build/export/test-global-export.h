
#ifndef TEST_GLOBAL_EXPORT_H
#define TEST_GLOBAL_EXPORT_H

#ifdef TEST_GLOBAL_STATIC_DEFINE
#  define TEST_GLOBAL_EXPORT
#  define TEST_GLOBAL_NO_EXPORT
#else
#  ifndef TEST_GLOBAL_EXPORT
#    ifdef quassel_test_global_EXPORTS
        /* We are building this library */
#      define TEST_GLOBAL_EXPORT 
#    else
        /* We are using this library */
#      define TEST_GLOBAL_EXPORT 
#    endif
#  endif

#  ifndef TEST_GLOBAL_NO_EXPORT
#    define TEST_GLOBAL_NO_EXPORT 
#  endif
#endif

#ifndef TEST_GLOBAL_DEPRECATED
#  define TEST_GLOBAL_DEPRECATED __attribute__ ((__deprecated__))
#endif

#ifndef TEST_GLOBAL_DEPRECATED_EXPORT
#  define TEST_GLOBAL_DEPRECATED_EXPORT TEST_GLOBAL_EXPORT TEST_GLOBAL_DEPRECATED
#endif

#ifndef TEST_GLOBAL_DEPRECATED_NO_EXPORT
#  define TEST_GLOBAL_DEPRECATED_NO_EXPORT TEST_GLOBAL_NO_EXPORT TEST_GLOBAL_DEPRECATED
#endif

/* NOLINTNEXTLINE(readability-avoid-unconditional-preprocessor-if) */
#if 0 /* DEFINE_NO_DEPRECATED */
#  ifndef TEST_GLOBAL_NO_DEPRECATED
#    define TEST_GLOBAL_NO_DEPRECATED
#  endif
#endif

#endif /* TEST_GLOBAL_EXPORT_H */
