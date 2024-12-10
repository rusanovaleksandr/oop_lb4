#ifndef IABILITY_FACTORY_H
#define IABILITY_FACTORY_H
#include <memory>
#include <string>
#include "iability.h"
#include "nlohmann/json.hpp"
using json = nlohmann::json;

class IAbilityFactory
{
public:
    virtual std::shared_ptr<IAbility> create() = 0;
    virtual std::string getName() const = 0;
    virtual ~IAbilityFactory() = 0;
    virtual json toJson() = 0;
    virtual void fromJson(const json& jsn) = 0;
};

#endif