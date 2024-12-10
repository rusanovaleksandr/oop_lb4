#include "../headers/bombardment_factory.h"

BombardmentFactory::BombardmentFactory(ShipManager& manager) : ship_manager(manager) {}


std::shared_ptr<IAbility> BombardmentFactory::create()
{
    return std::make_shared<BombardmentAbility>(ship_manager);
}

std::string BombardmentFactory::getName() const
{
    return "Bombardment";
}

json BombardmentFactory::toJson()
{
    json json_object;
    json_object["type"] = "BombardmentFactory";
    json_object["name"] = getName();
    return json_object;
}

void BombardmentFactory::fromJson(const json& jsn) {};