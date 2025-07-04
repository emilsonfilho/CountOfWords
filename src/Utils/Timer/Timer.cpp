#include "Utils/Timer/Timer.hpp"

#include <clocale>
#include <sstream>
#include <iomanip>

#include "Configs/Locale.hpp"
#include "Exceptions/FileProcessorExceptions.hpp"

std::chrono::high_resolution_clock::time_point Timer::now() const {
    return std::chrono::high_resolution_clock::now();
}

void Timer::start() {
    begin = now();
}

void Timer::stop() {
    end = now();
}

std::chrono::milliseconds Timer::duration() const {
    return std::chrono::duration_cast<std::chrono::milliseconds>(end - begin);
}

std::string Timer::getCurrentDateTime() {
    auto now = std::chrono::system_clock::now();
    std::time_t time = std::chrono::system_clock::to_time_t(now);

    if (!std::setlocale(LC_ALL, lang))
        throw LocaleNotFoundException();

    std::locale loc("pt_BR.utf8");

    std::ostringstream oss;
    oss.imbue(loc);
    oss << std::put_time(std::localtime(&time), "%A, %d de %B de %Y - %H:%M:%S");
    return oss.str();
}