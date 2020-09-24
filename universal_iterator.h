#include <filesystem>

namespace fs = std::filesystem;

class universal_iterator
{
public:
    universal_iterator();
    universal_iterator(const std::string& path,
                       bool flag);
    universal_iterator& operator++();
    const fs::directory_entry& operator*() const noexcept;

private:
    bool req;
    fs::recursive_directory_iterator rdi;
    fs::directory_iterator            di;

    friend bool
    operator==(const universal_iterator& lhs,
               const universal_iterator& rhs) noexcept
    {
        if (lhs.req) return lhs.rdi == rhs.rdi;
        else         return lhs. di == rhs. di;
    }

    friend bool
    operator!=(const universal_iterator& lhs,
               const universal_iterator& rhs) noexcept
    { return !(lhs == rhs); }
};

inline universal_iterator
begin(universal_iterator __iter) noexcept
{ return __iter; }

inline universal_iterator
end(universal_iterator) noexcept
{ return universal_iterator(); }
