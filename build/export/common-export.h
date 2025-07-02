
#ifndef COMMON_EXPORT_H
#define COMMON_EXPORT_H

#ifdef COMMON_STATIC_DEFINE
#  define COMMON_EXPORT
#  define COMMON_NO_EXPORT
#else
#  ifndef COMMON_EXPORT
#    ifdef quassel_common_EXPORTS
        /* We are building this library */
#      define COMMON_EXPORT 
#    else
        /* We are using this library */
#      define COMMON_EXPORT 
#    endif
#  endif

#  ifndef COMMON_NO_EXPORT
#    define COMMON_NO_EXPORT 
#  endif
#endif

#ifndef COMMON_DEPRECATED
#  define COMMON_DEPRECATED __attribute__ ((__deprecated__))
#endif

#ifndef COMMON_DEPRECATED_EXPORT
#  define COMMON_DEPRECATED_EXPORT COMMON_EXPORT COMMON_DEPRECATED
#endif

#ifndef COMMON_DEPRECATED_NO_EXPORT
#  define COMMON_DEPRECATED_NO_EXPORT COMMON_NO_EXPORT COMMON_DEPRECATED
#endif

/* NOLINTNEXTLINE(readability-avoid-unconditional-preprocessor-if) */
#if 0 /* DEFINE_NO_DEPRECATED */
#  ifndef COMMON_NO_DEPRECATED
#    define COMMON_NO_DEPRECATED
#  endif
#endif

#endif /* COMMON_EXPORT_H */
