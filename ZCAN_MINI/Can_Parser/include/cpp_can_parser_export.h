
#ifndef CPP_CAN_PARSER_EXPORT_H
#define CPP_CAN_PARSER_EXPORT_H

#ifdef CPP_CAN_PARSER_STATIC_DEFINE
#  define CPP_CAN_PARSER_EXPORT
#  define CPP_CAN_PARSER_NO_EXPORT
#else
#  ifndef CPP_CAN_PARSER_EXPORT
#    ifdef cpp_can_parser_EXPORTS
        /* We are building this library */
#      define CPP_CAN_PARSER_EXPORT 
#    else
        /* We are using this library */
#      define CPP_CAN_PARSER_EXPORT 
#    endif
#  endif

#  ifndef CPP_CAN_PARSER_NO_EXPORT
#    define CPP_CAN_PARSER_NO_EXPORT 
#  endif
#endif

#ifndef CPP_CAN_PARSER_DEPRECATED
#  define CPP_CAN_PARSER_DEPRECATED __declspec(deprecated)
#endif

#ifndef CPP_CAN_PARSER_DEPRECATED_EXPORT
#  define CPP_CAN_PARSER_DEPRECATED_EXPORT CPP_CAN_PARSER_EXPORT CPP_CAN_PARSER_DEPRECATED
#endif

#ifndef CPP_CAN_PARSER_DEPRECATED_NO_EXPORT
#  define CPP_CAN_PARSER_DEPRECATED_NO_EXPORT CPP_CAN_PARSER_NO_EXPORT CPP_CAN_PARSER_DEPRECATED
#endif

#if 0 /* DEFINE_NO_DEPRECATED */
#  ifndef CPP_CAN_PARSER_NO_DEPRECATED
#    define CPP_CAN_PARSER_NO_DEPRECATED
#  endif
#endif

#endif /* CPP_CAN_PARSER_EXPORT_H */
