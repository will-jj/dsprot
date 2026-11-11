#include "copyfile.h"

#define BUFFER_SIZE 1024

int fopen_by_copy(const char* src_path, const char* dst_path) {

    char buffer[BUFFER_SIZE];

    FILE* src = fopen(src_path, "rb");
    if (src == NULL) {
        return 1;
    }

    FILE* dst = fopen(dst_path, "wb+");
    if (dst == NULL) {
        fclose(src);
        return 1;
    }

    while (!feof(src)) {
        int len = fread(buffer, 1, sizeof(buffer), src);
        if (len > 0) {
            fwrite(buffer, 1, len, dst);
        }
    }

    fclose(src);
    fclose(dst);

    return 0;
}


