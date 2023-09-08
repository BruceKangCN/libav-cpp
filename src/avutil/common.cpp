#include <ios>
#include <stdexcept>

#include <av-cpp/avutil/common.hpp>

namespace av {

void throwOnError(int code)
{
    switch (code) {
    case 0:
        break;
    case AVERROR(EPERM):
        throw std::system_error({ EPERM, std::system_category() }, "Operation not permitted");
    case AVERROR(ENOENT):
        throw std::ios_base::failure("No such file or directory");
    case AVERROR(ESRCH):
        throw std::system_error({ ESRCH, std::system_category() }, "No such process");
    case AVERROR(EINTR):
        throw std::system_error({ EINTR, std::system_category() }, "Interrupted system call");
    case AVERROR(EIO):
        throw std::ios_base::failure("I/O error");
    case AVERROR(ENXIO):
        throw std::ios_base::failure("No such device or address");
    case AVERROR(E2BIG):
        throw std::length_error("Argument list too long");
    case AVERROR(ENOEXEC):
        throw std::system_error({ ENOEXEC, std::system_category() }, "Exec format error");
    case AVERROR(EBADF):
        throw std::ios_base::failure("Bad file number");
    case AVERROR(ECHILD):
        throw std::system_error({ ESRCH, std::system_category() }, "No child processes");
    case AVERROR(EAGAIN):
        throw std::system_error({ EAGAIN, std::system_category() }, "Try Again");
    case AVERROR(ENOMEM):
        throw std::bad_alloc();
    case AVERROR(EACCES):
        throw std::system_error({ EACCES, std::system_category() }, "Permission denied");
    case AVERROR(EFAULT):
        throw std::system_error({ EFAULT, std::system_category() }, "Bad address");
    case AVERROR(ENOTBLK):
        throw std::ios_base::failure("Block device required");
    case AVERROR(EBUSY):
        throw std::ios_base::failure("Device or resource busy");
    case AVERROR(EEXIST):
        throw std::ios_base::failure("File exists");
    case AVERROR(EXDEV):
        throw std::ios_base::failure("Cross-device link");
    case AVERROR(ENODEV):
        throw std::ios_base::failure("No such device");
    case AVERROR(ENOTDIR):
        throw std::ios_base::failure("Not a directory");
    case AVERROR(EISDIR):
        throw std::ios_base::failure("Is a director");
    case AVERROR(EINVAL):
        throw std::invalid_argument("Invalid argument");
    case AVERROR(ENFILE):
        throw std::ios_base::failure("File table overflow");
    case AVERROR(EMFILE):
        throw std::ios_base::failure("Too many open files");
    case AVERROR(ENOTTY):
        throw std::ios_base::failure("Not a typewritter");
    case AVERROR(ETXTBSY):
        throw std::ios_base::failure("Text file busy");
    case AVERROR(EFBIG):
        throw std::ios_base::failure("File too large");
    case AVERROR(ENOSPC):
        throw std::ios_base::failure("No space left on device");
    case AVERROR(ESPIPE):
        throw std::ios_base::failure("Illegal seek");
    case AVERROR(EROFS):
        throw std::ios_base::failure("Read-only file system");
    case AVERROR(EMLINK):
        throw std::ios_base::failure("Too many links");
    case AVERROR(EPIPE):
        throw std::ios_base::failure("Broken pipe");
    case AVERROR(EDOM):
        throw std::domain_error("Math argument out of domain of func");
    case AVERROR(ERANGE):
        throw std::out_of_range("Math result not representable");
    default:
        throw std::runtime_error("Unknown error");
    }
}

} // namespace av
