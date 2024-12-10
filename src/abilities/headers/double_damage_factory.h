#ifndef DOUBLE_DAMAGE_FACTORY
#define DOUBLE_DAMAGE_FACTORY
#include "iability_factory.h"
#include "double_damage_ability.h"

class DoubleDamageFactory : public IAbilityFactory
{
    GameBoard& board;
public:
    DoubleDamageFactory(GameBoard& board);
    virtual std::shared_ptr<IAbility> create() override;
    virtual std::string getName() const override;
    virtual ~DoubleDamageFactory() override = default;

    virtual json toJson() override; 
    virtual void fromJson(const json& jsn) override;
};

#endif