#include <exception>

class IllegalMoveException : public std::exception
{
public:
    const char* what() const noexcept override
    {
        return "Illegal move";
    }
};