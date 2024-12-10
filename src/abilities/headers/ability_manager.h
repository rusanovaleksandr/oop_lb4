#ifndef ABILITY_MANAGER_H
#define ABILITY_MANAGER_H

#include <queue>
#include <memory>
#include <random>
#include <algorithm>
#include <typeinfo>
#include "../../game_modules/headers/observer.h"
#include "../../exceptions/headers/no_abilities_exception.h"
#include "iability_factory.h"
#include "double_damage_factory.h"
#include "scanner_factory.h"
#include "bombardment_factory.h"
#include "ability_factory.h"

class AbilityManager : public Observer
{
private:
    AbilityFactory& ability_factory;
    std::queue<std::shared_ptr<IAbilityFactory>> abilities_;
    std::string last_ability_applied = "";

public:
    AbilityManager(AbilityFactory& ability_factory);
    AbilityManager(const AbilityManager &other);
    AbilityManager(AbilityManager&& other);
    ~AbilityManager() = default;

    void setAbilityFactory(AbilityFactory& factory);

    AbilityManager& operator=(const AbilityManager &other);
    AbilityManager& operator=(AbilityManager&& other);

    std::shared_ptr<IAbilityFactory> getFront();
    std::string peekNextAbility();
    std::string lastAbilityApplied();
    void applyAbility();

    void accept() override;
    void addRandomAbility();

    json toJson() const;
    void fromJson(const json& jsn);
};

#endif