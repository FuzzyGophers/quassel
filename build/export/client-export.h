
#ifndef CLIENT_EXPORT_H
#define CLIENT_EXPORT_H

#ifdef CLIENT_STATIC_DEFINE
#  define CLIENT_EXPORT
#  define CLIENT_NO_EXPORT
#else
#  ifndef CLIENT_EXPORT
#    ifdef quassel_client_EXPORTS
        /* We are building this library */
#      define CLIENT_EXPORT 
#    else
        /* We are using this library */
#      define CLIENT_EXPORT 
#    endif
#  endif

#  ifndef CLIENT_NO_EXPORT
#    define CLIENT_NO_EXPORT 
#  endif
#endif

#ifndef CLIENT_DEPRECATED
#  define CLIENT_DEPRECATED __attribute__ ((__deprecated__))
#endif

#ifndef CLIENT_DEPRECATED_EXPORT
#  define CLIENT_DEPRECATED_EXPORT CLIENT_EXPORT CLIENT_DEPRECATED
#endif

#ifndef CLIENT_DEPRECATED_NO_EXPORT
#  define CLIENT_DEPRECATED_NO_EXPORT CLIENT_NO_EXPORT CLIENT_DEPRECATED
#endif

/* NOLINTNEXTLINE(readability-avoid-unconditional-preprocessor-if) */
#if 0 /* DEFINE_NO_DEPRECATED */
#  ifndef CLIENT_NO_DEPRECATED
#    define CLIENT_NO_DEPRECATED
#  endif
#endif

#endif /* CLIENT_EXPORT_H */
