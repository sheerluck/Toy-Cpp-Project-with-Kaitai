#include "universal_iterator.h"

universal_iterator::universal_iterator() {}
universal_iterator::universal_iterator(const std::string& path,
                                       bool flag)
{
    req = not flag;
    const auto o = fs::directory_options::skip_permission_denied;
    if (req)
        rdi = fs::recursive_directory_iterator(fs::path{path}, o);
    else
        di = fs::directory_iterator(fs::path{path}, o);
}

universal_iterator&
universal_iterator::operator++()
{
    if (req) rdi.operator++();
    else      di.operator++();
    return *this;
}

const fs::directory_entry& 
universal_iterator::operator*() const noexcept
{
    if (req) return rdi.operator*();
    else     return  di.operator*();
}
