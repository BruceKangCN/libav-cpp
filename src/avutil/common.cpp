#include <av-cpp/avutil/common.hpp>

namespace av {

Exception::Exception(int no) noexcept
    : m_no(no)
{
    // nothing
}

const char* Exception::what() const noexcept
{
    switch (m_no) {
    case 0:
        return  "No error";
    case AVERROR(EPERM):
        return "Operation not permitted";
    case AVERROR(ENOENT):
        return "No such file or directory";
    case AVERROR(ESRCH):
        return "No such process";
    case AVERROR(EINTR):
        return " Interrupted system call";
    case AVERROR(EIO):
        return "I/O error";
    case AVERROR(ENXIO):
        return "No such device or address";
    case AVERROR(E2BIG):
        return "Argument list too long";
    case AVERROR(ENOEXEC):
        return "Exec format error";
    case AVERROR(EBADF):
        return "Bad file number";
    case AVERROR(ECHILD):
        return "No child processes";
    case AVERROR(EAGAIN):
        return "Try again";
    case AVERROR(ENOMEM):
        return "Out of memory";
    case AVERROR(EACCES):
        return "Permission denied";
    case AVERROR(EFAULT):
        return "Bad address";
    case AVERROR(ENOTBLK):
        return "Block device required";
    case AVERROR(EBUSY):
        return "Device or resource busy";
    case AVERROR(EEXIST):
        return "File exists";
    case AVERROR(EXDEV):
        return "Cross-device link";
    case AVERROR(ENODEV):
        return "No such device";
    case AVERROR(ENOTDIR):
        return "Not a directory";
    case AVERROR(EISDIR):
        return "Is a directory";
    case AVERROR(EINVAL):
        return "Invalid argument";
    case AVERROR(ENFILE):
        return "File table overflow";
    case AVERROR(EMFILE):
        return "Too many open files";
    case AVERROR(ENOTTY):
        return "Not a typewritter";
    case AVERROR(ETXTBSY):
        return "Text file busy";
    case AVERROR(EFBIG):
        return "File too large";
    case AVERROR(ENOSPC):
        return "No space left on device";
    case AVERROR(ESPIPE):
        return "Illegal seek";
    case AVERROR(EROFS):
        return "Read-only file system";
    case AVERROR(EMLINK):
        return "Too many links";
    case AVERROR(EPIPE):
        return "Broken pipe";
    case AVERROR(EDOM):
        return "Math argument out of domain of func";
    case AVERROR(ERANGE):
        return "Math result not representable";
    default:
        return "Unknown error";
    }
}

} // namespace av
