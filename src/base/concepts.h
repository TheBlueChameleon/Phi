#ifndef CONCEPTS_H
#define CONCEPTS_H

#include <concepts>

namespace Base
{
    template<typename T, typename E, typename O>
    concept EitherOr = std::is_convertible_v<T, E> || std::is_convertible_v<T, O>;
}

#endif // CONCEPTS_H
