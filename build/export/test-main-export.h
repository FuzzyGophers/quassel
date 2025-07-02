
#ifndef TEST_MAIN_EXPORT_H
#define TEST_MAIN_EXPORT_H

#ifdef TEST_MAIN_STATIC_DEFINE
#  define TEST_MAIN_EXPORT
#  define TEST_MAIN_NO_EXPORT
#else
#  ifndef TEST_MAIN_EXPORT
#    ifdef quassel_test_main_EXPORTS
        /* We are building this library */
#      define TEST_MAIN_EXPORT 
#    else
        /* We are using this library */
#      define TEST_MAIN_EXPORT 
#    endif
#  endif

#  ifndef TEST_MAIN_NO_EXPORT
#    define TEST_MAIN_NO_EXPORT 
#  endif
#endif

#ifndef TEST_MAIN_DEPRECATED
#  define TEST_MAIN_DEPRECATED __attribute__ ((__deprecated__))
#endif

#ifndef TEST_MAIN_DEPRECATED_EXPORT
#  define TEST_MAIN_DEPRECATED_EXPORT TEST_MAIN_EXPORT TEST_MAIN_DEPRECATED
#endif

#ifndef TEST_MAIN_DEPRECATED_NO_EXPORT
#  define TEST_MAIN_DEPRECATED_NO_EXPORT TEST_MAIN_NO_EXPORT TEST_MAIN_DEPRECATED
#endif

/* NOLINTNEXTLINE(readability-avoid-unconditional-preprocessor-if) */
#if 0 /* DEFINE_NO_DEPRECATED */
#  ifndef TEST_MAIN_NO_DEPRECATED
#    define TEST_MAIN_NO_DEPRECATED
#  endif
#endif

#endif /* TEST_MAIN_EXPORT_H */
