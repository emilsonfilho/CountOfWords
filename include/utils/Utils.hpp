#ifndef UTILS_HPP
#define UTILS_HPP

#include <functional>
#include <string>
#include <utility>

namespace Utils {
	template <typename First, typename Second>
	std::string displayPair(const std::pair<First, Second>& pair);
}

#include "utils/Utils.impl.hpp"

#endif