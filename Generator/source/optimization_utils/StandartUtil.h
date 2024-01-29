#ifndef STANDART_UTIL_H
#define STANDART_UTIL_H

#include <map>
#include <tuple>
#include <string>
#include <sstream>

// so, this struct is used for sending info about multi-line commands
// for abc, yosys etc
struct StandartCommandInfo
{
    // длина команды
    int sumLen;
    // информация о том, какая команда вызвала ошибку
    std::string info;
};

// result of work
struct CommandWorkResult
{
    bool correct;
    std::map<std::string, std::string> commandsOutput;
};

// link on used code - https://gist.github.com/en4bz/f07ef13706c3ae3a4fb2
template<class Tuple, std::size_t N>
struct TuplePrinter {
    static void print(const std::string& fmt, std::ostream& os, const Tuple& t) {
        const size_t idx = fmt.find_last_of('%');
        TuplePrinter<Tuple, N - 1>::print( std::string( fmt, 0, idx ), os, t );
        os << std::get<N - 1>(t) << std::string( fmt, idx + 1 );
    }
};

template<class Tuple>
struct TuplePrinter<Tuple, 1>{
    static void print(const std::string& fmt, std::ostream& os, const Tuple& t) {
        const size_t idx = fmt.find_first_of('%');
        os << std::string( fmt, 0, idx ) << std::get<0>(t) << std::string( fmt, idx + 1 );
    }
};

template<class... Args>
std::string format(const std::string& fmt, Args&&... args) {
    std::stringstream ss;

    const auto t = std::make_tuple(std::forward<Args>(args)...);

    TuplePrinter<decltype(t), sizeof...(Args)>::print(fmt, ss, t);
    return ss.str();
}

#endif
