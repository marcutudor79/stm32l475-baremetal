#include <stddef.h>
#include <stdint.h>

void *memcpy(void *dest, const void *src, size_t n) {
    if (!n || dest == src) return dest;
    unsigned char *d = (unsigned char *)dest;
    const unsigned char *s = (const unsigned char *)src;

    typedef uintptr_t word;
    const size_t w = sizeof(word);

    if ((((uintptr_t)d | (uintptr_t)s) & (w - 1)) == 0) {
        word *dw = (word *)d;
        const word *sw = (const word *)s;
        while (n >= w) {
            *dw++ = *sw++;
            n -= w;
        }
        d = (unsigned char *)dw;
        s = (const unsigned char *)sw;
    }

    while (n--) {
        *d++ = *s++;
    }
    return dest;
}

void *memmove(void *dest, const void *src, size_t n) {
    if (!n || dest == src) return dest;
    unsigned char *d = (unsigned char *)dest;
    const unsigned char *s = (const unsigned char *)src;

    typedef uintptr_t word;
    const size_t w = sizeof(word);

    if (d < s) {
        /* forward copy (can overlap safely when dest < src) */
        if ((((uintptr_t)d | (uintptr_t)s) & (w - 1)) == 0) {
            word *dw = (word *)d;
            const word *sw = (const word *)s;
            while (n >= w) {
                *dw++ = *sw++;
                n -= w;
            }
            d = (unsigned char *)dw;
            s = (const unsigned char *)sw;
        }
        while (n--) *d++ = *s++;
    } else {
        /* backward copy */
        d += n;
        s += n;
        if ((((uintptr_t)d | (uintptr_t)s) & (w - 1)) == 0) {
            word *dw = (word *)d;
            const word *sw = (const word *)s;
            while (n >= w) {
                *(--dw) = *(--sw);
                n -= w;
            }
            d = (unsigned char *)dw;
            s = (const unsigned char *)sw;
        }
        while (n--) *(--d) = *(--s);
    }

    return dest;
}

void *memset(void *s, int c, size_t n) {
    if (!n) return s;
    unsigned char *d = (unsigned char *)s;
    typedef uintptr_t word;
    const size_t w = sizeof(word);

    if ((((uintptr_t)d) & (w - 1)) == 0) {
        /* build word-sized pattern */
        word pattern = (unsigned char)c;
        for (size_t i = 1; i < w; ++i) {
            pattern = (pattern << 8) | (unsigned char)c;
        }
        word *dw = (word *)d;
        while (n >= w) {
            *dw++ = pattern;
            n -= w;
        }
        d = (unsigned char *)dw;
    }

    while (n--) *d++ = (unsigned char)c;
    return s;
}

int memcmp(const void *s1, const void *s2, size_t n) {
    const unsigned char *a = (const unsigned char *)s1;
    const unsigned char *b = (const unsigned char *)s2;
    while (n--) {
        if (*a != *b) return (int)*a - (int)*b;
        ++a; ++b;
    }
    return 0;
}