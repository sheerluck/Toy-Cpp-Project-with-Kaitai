template<typename T>
struct reverse
{
    reverse(T& acontainer)
        : container{acontainer}
    {}

    decltype(auto) begin()
    {
        return container.rbegin();
    }

    decltype(auto) end()
    {
        return container.rend();
    }
    T& container;
};
