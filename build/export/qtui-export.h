
#ifndef QTUI_EXPORT_H
#define QTUI_EXPORT_H

#ifdef QTUI_STATIC_DEFINE
#  define QTUI_EXPORT
#  define QTUI_NO_EXPORT
#else
#  ifndef QTUI_EXPORT
#    ifdef quassel_qtui_EXPORTS
        /* We are building this library */
#      define QTUI_EXPORT 
#    else
        /* We are using this library */
#      define QTUI_EXPORT 
#    endif
#  endif

#  ifndef QTUI_NO_EXPORT
#    define QTUI_NO_EXPORT 
#  endif
#endif

#ifndef QTUI_DEPRECATED
#  define QTUI_DEPRECATED __attribute__ ((__deprecated__))
#endif

#ifndef QTUI_DEPRECATED_EXPORT
#  define QTUI_DEPRECATED_EXPORT QTUI_EXPORT QTUI_DEPRECATED
#endif

#ifndef QTUI_DEPRECATED_NO_EXPORT
#  define QTUI_DEPRECATED_NO_EXPORT QTUI_NO_EXPORT QTUI_DEPRECATED
#endif

/* NOLINTNEXTLINE(readability-avoid-unconditional-preprocessor-if) */
#if 0 /* DEFINE_NO_DEPRECATED */
#  ifndef QTUI_NO_DEPRECATED
#    define QTUI_NO_DEPRECATED
#  endif
#endif

#endif /* QTUI_EXPORT_H */
