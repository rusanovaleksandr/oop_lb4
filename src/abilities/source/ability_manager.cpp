#include "../headers/ability_manager.h"

AbilityManager::AbilityManager(AbilityFactory &ability_factory) : ability_factory(ability_factory)
{
    std::vector<std::shared_ptr<IAbilityFactory>> abilities_vec;
    abilities_vec.push_back(ability_factory.getBombardmentFactory());
    abilities_vec.push_back(ability_factory.getDoubleDamageFactory());
    abilities_vec.push_back(ability_factory.getDoubleScannerFactory());

    std::random_device rd;
    std::mt19937 g(rd());
    std::shuffle(abilities_vec.begin(), abilities_vec.end(), g);

    for (const auto &ability : abilities_vec)
    {
        abilities_.push(ability);
    }
}

AbilityManager::AbilityManager(const AbilityManager &other) : ability_factory(other.ability_factory)
{
    abilities_ = other.abilities_;
}

AbilityManager::AbilityManager(AbilityManager &&other) : ability_factory(other.ability_factory)
{
    abilities_ = std::move(other.abilities_);
}

AbilityManager &AbilityManager::operator=(const AbilityManager &other)
{
    if (this != &other)
    {
        this->ability_factory = other.ability_factory;
        this->abilities_ = other.abilities_;
    }
    return *this;
}

AbilityManager &AbilityManager::operator=(AbilityManager &&other)
{
    if (this != &other)
    {
        this->ability_factory = other.ability_factory;
        this->abilities_ = std::move(other.abilities_);
    }
    return *this;
}

void AbilityManager::addRandomAbility()
{
    std::vector<std::shared_ptr<IAbilityFactory>> abilities_vec;
    abilities_vec.push_back(ability_factory.getBombardmentFactory());
    abilities_vec.push_back(ability_factory.getDoubleDamageFactory());
    abilities_vec.push_back(ability_factory.getDoubleScannerFactory());

    std::random_device rd;
    std::mt19937 g(rd());
    std::uniform_int_distribution<> dis(0, 2);
    abilities_.push(abilities_vec[dis(g)]);
}

void AbilityManager::accept()
{
    this->addRandomAbility();
}

std::shared_ptr<IAbilityFactory> AbilityManager::getFront()
{
    if (abilities_.empty())
    {
        throw NoAbilitiesException("No abilities available");
    }
    std::shared_ptr<IAbilityFactory> ability = abilities_.front();
    abilities_.pop();
    return ability;
}

std::string AbilityManager::peekNextAbility()
{
    std::string result;
    if (!abilities_.empty())
    {
        result = abilities_.front()->getName();
    }
    else
    {
        result = "No abilities available";
    }
    return result;
}

std::string AbilityManager::lastAbilityApplied()
{
    return last_ability_applied;
}


json AbilityManager::toJson() const
{
    json json_object;

    json abilities_array = json::array();
    std::queue<std::shared_ptr<IAbilityFactory>> temp_queue = abilities_;
    while (!temp_queue.empty())
    {
        abilities_array.push_back(temp_queue.front()->toJson());
        temp_queue.pop();
    }

    json_object["abilities"] = abilities_array;

    return json_object;
}

void AbilityManager::fromJson(const json &jsn)
{
    abilities_ = std::queue<std::shared_ptr<IAbilityFactory>>();
    for (const auto &ability_json : jsn.at("abilities"))
    {
        std::string abilityType = ability_json.at("type");

        if (abilityType == "DoubleDamageFactory")
        {
            abilities_.push(ability_factory.getDoubleDamageFactory());
        }
        else if (abilityType == "BombardmentFactory")
        {
            abilities_.push(ability_factory.getBombardmentFactory());
        }
        else if (abilityType == "ScannerFactory")
        {
            abilities_.push(ability_factory.getDoubleScannerFactory());
        }
    }
}

void AbilityManager::setAbilityFactory(AbilityFactory &factory)
{
    ability_factory = factory;
}

void AbilityManager::applyAbility()
{
    auto ability_name = peekNextAbility();
    last_ability_applied = ability_name;

    auto ability = getFront()->create();
    ability->apply();

}