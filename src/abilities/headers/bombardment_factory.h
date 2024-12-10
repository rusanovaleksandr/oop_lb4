#ifndef BOMBARDMENT_FACTORY_H
#define BOMBARDMENT_FACTORY_H
#include "bombardment_ability.h"
#include "iability_factory.h"

class BombardmentFactory : public IAbilityFactory
{
    ShipManager& ship_manager;
public:
    BombardmentFactory(ShipManager& manager);
    std::shared_ptr<IAbility> create() override;
    std::string getName() const override;
    ~BombardmentFactory() override = default;

    virtual json toJson() override; 
    virtual void fromJson(const json& jsn) override;
};

#endif