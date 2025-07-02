
#ifndef UISUPPORT_EXPORT_H
#define UISUPPORT_EXPORT_H

#ifdef UISUPPORT_STATIC_DEFINE
#  define UISUPPORT_EXPORT
#  define UISUPPORT_NO_EXPORT
#else
#  ifndef UISUPPORT_EXPORT
#    ifdef quassel_uisupport_EXPORTS
        /* We are building this library */
#      define UISUPPORT_EXPORT 
#    else
        /* We are using this library */
#      define UISUPPORT_EXPORT 
#    endif
#  endif

#  ifndef UISUPPORT_NO_EXPORT
#    define UISUPPORT_NO_EXPORT 
#  endif
#endif

#ifndef UISUPPORT_DEPRECATED
#  define UISUPPORT_DEPRECATED __attribute__ ((__deprecated__))
#endif

#ifndef UISUPPORT_DEPRECATED_EXPORT
#  define UISUPPORT_DEPRECATED_EXPORT UISUPPORT_EXPORT UISUPPORT_DEPRECATED
#endif

#ifndef UISUPPORT_DEPRECATED_NO_EXPORT
#  define UISUPPORT_DEPRECATED_NO_EXPORT UISUPPORT_NO_EXPORT UISUPPORT_DEPRECATED
#endif

/* NOLINTNEXTLINE(readability-avoid-unconditional-preprocessor-if) */
#if 0 /* DEFINE_NO_DEPRECATED */
#  ifndef UISUPPORT_NO_DEPRECATED
#    define UISUPPORT_NO_DEPRECATED
#  endif
#endif

#endif /* UISUPPORT_EXPORT_H */
