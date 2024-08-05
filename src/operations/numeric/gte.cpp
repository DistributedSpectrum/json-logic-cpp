#include "json_logic.h"

#include "json.hpp"

using namespace nlohmann;

namespace json_logic
{
    json JsonLogic::operation_numeric_gte(const json& values, const json& data)
    {
        if (values.size() != 2)
            throw JsonLogicException(
                __FUNCTION__,
                "Expected 2 arguments, but received " + std::to_string(values.size())
            );

        const auto a = Apply(values[0], data);
        const auto b = Apply(values[1], data);

        if (!a.is_number() || !b.is_number())
            throw JsonLogicException(__FUNCTION__, "All arguments must be numbers");

        return a >= b;
    }
}
