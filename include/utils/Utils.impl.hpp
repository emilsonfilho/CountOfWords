#include "utils/Utils.hpp"

#include <sstream>

namespace Utils {
	template <typename First, typename Second>
	std::string displayPair(const std::pair<First, Second>& pair) {
		std::ostringstream os;
		os << "(" << pair.first << ", " << pair.second << ")";
		return os.str();
	}
}