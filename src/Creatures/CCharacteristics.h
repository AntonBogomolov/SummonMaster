#pragma once

#include <vector>

enum class ENCondition{ NORMAL, DEAD };

class CCharacteristics
{
public:
    CCharacteristics()
    {
        condition = ENCondition::NORMAL;
        maxHP       = 10;
        hp          = 10;
        maxStamina  = 10;
        stamina     = 10;
        maxMagica   = 10;
        magica      = 10;
    }
    CCharacteristics(const int maxHP, const int maxStamina, const int maxMagica)
    {
        this->maxHP   = maxHP;
        this->hp      = maxHP;
        this->maxStamina  = maxStamina;
        this->stamina     = maxStamina;
        this->maxMagica   = maxMagica;
        this->magica      = maxMagica;
        this->condition = ENCondition::NORMAL;
    }
    CCharacteristics(const CCharacteristics& bodyCondition)
    {
        this->maxHP      = bodyCondition.getMaxHP();
        this->hp         = bodyCondition.getHP();
        this->maxStamina = bodyCondition.getMaxStamina();
        this->stamina    = bodyCondition.getStamina();
        this->maxMagica  = bodyCondition.getMaxMagica();
        this->magica     = bodyCondition.getMagica();
        this->condition  = bodyCondition.getCondition();
    }
    ~CCharacteristics(){};
    
    bool getIsDead() const
    {
        return condition == ENCondition::DEAD;
    }
    const ENCondition getCondition() const
    {
        return condition;
    }
    int getHP() const
    {
        return hp;
    }
    int getStamina() const
    {
        return stamina;
    }
    int getMagica() const
    {
        return magica;
    }
    int getMaxHP() const
    {
        return maxHP;
    }
    int getMaxStamina() const
    {
        return maxStamina;
    }
    int getMaxMagica() const
    {
        return maxMagica;
    }    
    void setCondition(const ENCondition newCondition)
    {
        this->condition = newCondition;
    }
    
    void setHP(const int newHP)
    {
        hp = newHP;
        if(hp < 0) condition = ENCondition::DEAD;
        if(hp > maxHP) hp = maxHP;
    }
    void changeHP(const int deltaHP)
    {
        hp += deltaHP;
        if(hp < 0) condition = ENCondition::DEAD;
        if(hp > maxHP) hp = maxHP;
    }
    void setStamina(const int newStamina)
    {
        stamina = newStamina;
        if(stamina > maxStamina) stamina = maxStamina;
    }
    void changeStamina(const int deltaStamina)
    {
        stamina += deltaStamina;
        if(stamina > maxStamina) stamina = maxStamina;
    }
    void setMagica(const int newMagica)
    {
        magica = newMagica;
        if(magica > maxMagica) magica = maxMagica;
    }
    void changeMagica(const int deltaMagica)
    {
        magica += deltaMagica;
        if(magica > maxMagica) magica = maxMagica;
    }
protected:
    ENCondition condition;
    int hp;
    int maxHP;
    int stamina;
    int maxStamina;
    int magica;
    int maxMagica;
};