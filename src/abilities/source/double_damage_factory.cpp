#include "../headers/double_damage_factory.h"

DoubleDamageFactory::DoubleDamageFactory(GameBoard& board) : board(board) {}

std::shared_ptr<IAbility> DoubleDamageFactory::create()
{
    return std::make_shared<DoubleDamageAbility>(board);
}

std::string DoubleDamageFactory::getName() const
{
    return "DoubleDamage";
}

json DoubleDamageFactory::toJson()
{
    json json_object;
    json_object["type"] = "DoubleDamageFactory";
    json_object["name"] = getName();
    return json_object;
}

void DoubleDamageFactory::fromJson(const json& jsn) {};