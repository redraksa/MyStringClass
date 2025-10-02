#ifndef _LINUXCOMPAT_H_
#define _LINUXCOMPAT_H_
#ifdef __linux__

#include <string.h>
#include <errno.h>

typedef int errno_t;

#ifndef _TRUNCATE
#define _TRUNCATE ((size_t)-1)
#endif

#ifndef STRUNCATE
#define STRUNCATE 80
#endif

static inline errno_t strncpy_s(char* dest, size_t dest_size, const char* src, size_t count) {
    if (!dest || !src || dest_size == 0) return EINVAL;

    if (count == _TRUNCATE) {
        count = dest_size - 1;
    }

    if (count >= dest_size) {
        strncpy(dest, src, dest_size - 1);
        dest[dest_size - 1] = '\0';
        return STRUNCATE;
    }
    else {
        strncpy(dest, src, count);
        dest[count] = '\0';
        return 0;
    }
}

static inline errno_t memcpy_s(void* dest, size_t dest_size, const void* src, size_t count) {
    std::cout << "dest = " << dest << "\ndest_size = " << dest_size << "\nsrc = " << src << "\ncount = " << count << "\n";
    if (dest == nullptr || dest_size == 0) {
        return EINVAL;
    }
    if (src == nullptr) {
        // Если src nullptr, заполняем dest нулями
        memset(dest, 0, dest_size);
        return EINVAL;
    }

    // Копируем не больше чем dest_size
    size_t copy_size = std::min(count, dest_size);
    memcpy(dest, src, copy_size);

    // Если count > dest_size, это ошибка, но мы уже скопировали что могли
    return (count > dest_size) ? ERANGE : 0;
}

static inline errno_t memmove_s(void* dest, size_t dest_size, const void* src, size_t count) {
    if (dest == nullptr || dest_size == 0) {
        return EINVAL;
    }
    if (src == nullptr) {
        memset(dest, 0, dest_size);
        return EINVAL;
    }

    size_t move_size = std::min(count, dest_size);
    memmove(dest, src, move_size);

    return (count > dest_size) ? ERANGE : 0;
}

#endif // !__linux__
#endif // !_LINUXCOMPAT_H_

