#include "json_logic.h"

#include <algorithm>

#include "json.hpp"

using namespace nlohmann;

namespace json_logic
{
    json JsonLogic::operation_logic_or(const json& values, const json& data)
    {
        return std::any_of(
            values.begin(),
            values.end(),
            [data, this](const json& value)
            {
                return Truthy(Apply(value, data));
            }
        );
    }
}
