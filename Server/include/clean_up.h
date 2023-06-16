/*
** EPITECH PROJECT, 2023
** B-YEP-400-REN-4-1-zappy-tristan.bros
** File description:
** clean_up.h
*/
#ifndef CLEAN_UP_H
    #define CLEAN_UP_H
    #include <stdlib.h>
    #include <unistd.h>
    #define ATTR(key) __attribute__((key))
    #define ON_CLEANUP(func) ATTR(cleanup(func))
    #define AUTO_FREE ON_CLEANUP(free_stack)
    #define ALWAYS_INLINE ATTR(always_inline)
    #define $$ ({ $$ })
    #define IS_USED_BY_AUTO_CLEANUP(var) (void)(var)
    #define NEED_COMMA struct _
    #define STA_INL static inline ALWAYS_INLINE
    #define CLF_HEAD(name, ptr) STA_INL void name(void *ptr)
    #define CLF_BODY(type, func, ptr) if (*(type *)(ptr)) func(*(type *)ptr);
    #define CL_INTERN(n, t, f) CLF_HEAD(n, ptr) { CLF_BODY(t, f, ptr) }
    #define CLEANUP_FUNC(n, t, f) CL_INTERN(n, t, f) NEED_COMMA
    //#define AUTO_FREE_ARRAY ON_CLEANUP(free_array)
    //CLEANUP_FUNC(array_free, char **, free_array);

    CLEANUP_FUNC(free_stack, void *, free);
#endif /* !CLEAN_UP_H */