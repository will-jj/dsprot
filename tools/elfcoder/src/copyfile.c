#include <fcntl.h>
#include <unistd.h>
#if defined(__APPLE__)
#include <copyfile.h>
#elif defined(__FreeBSD__)
#include <limits.h>
#include <sys/stat.h>
#include <sys/types.h>
#else // Linux and others
#include <limits.h>
#include <sys/sendfile.h>
#include <sys/stat.h>
#endif

int OSCopyFile(const char* source, const char* destination)
{
    int result = 0;
    int input, output;
    if ((input = open(source, O_RDONLY)) == -1)
    {
        return -1;
    }
    // Create new or truncate existing at destination
    if ((output = creat(destination, 0660)) == -1)
    {
        close(input);
        return -1;
    }

    // Use platform-specific APIs to perform a kernel-mode file copy
#if defined(__APPLE__)
    // fcopyfile(3) is supported on OS X 10.5+
    result = fcopyfile(input, output, 0, COPYFILE_ALL);
#elif defined(__FreeBSD__)
    // FreeBSD used to have fcopyfile(3) but that API was dropped and now we
    // need to use copy_file_range(2) manually. Note that we are still not
    // buffering in userspace.
    struct stat file_stat = {0};
    result = fstat(input, &file_stat);
    off_t copied = 0;
    while (result == 0 && copied < file_stat.st_size) {
        ssize_t written = copy_file_range(input, 0, output, NULL, SSIZE_MAX, 0);
        copied += written;
        if (written == -1) {
            result = -1;
        }
    }
#else
    // sendfile will work with non-socket output (i.e. regular file) under
    // Linux 2.6.33+ and some other unixy systems.
    struct stat file_stat = {0};
    result = fstat(input, &file_stat);
    off_t copied = 0;
    while (result == 0 && copied < file_stat.st_size) {
        ssize_t written = sendfile(output, input, &copied, SSIZE_MAX);
        copied += written;
        if (written == -1) {
            result = -1;
        }
    }
#endif

    close(input);
    close(output);

    return result;
}

// https://stackoverflow.com/questions/2180079/how-can-i-copy-a-file-on-unix-using-c
