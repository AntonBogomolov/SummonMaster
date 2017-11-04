#pragma once

#include <map>

class CResistances
{
public:
    CResistances() : 
                        physical(0), fire(0), cold(0), electro(0),
                        acid(0), poison(0), mental(0)
    {
       
    }
    CResistances(const int physical,const int fire, const int cold,
                        const int electro, const int acid, const int poison, const  int mental) : 
                        physical(physical), fire(fire), cold(cold), electro(electro),
                        acid(acid), poison(poison), mental(mental)
    {
       
    }
    CResistances(const CResistances& resists)
    {
        physical    = resists.getPhysicalResist();
        fire        = resists.getFireResist();
        cold        = resists.getColdResist();
        electro     = resists.getElectroResist();
        acid        = resists.getAcidResist();
        poison      = resists.getPoisonResist();
        mental      = resists.getMentalResist();
    }
    ~CResistances()
    {
    }
    
    int getPhysicalResist() const
    {
        return physical;
    }
    int getFireResist() const
    {
        return fire;
    }
    int getColdResist() const
    {
        return cold;
    }
    int getElectroResist() const
    {
        return electro;
    }
    int getAcidResist() const
    {
        return acid;
    }
    int getPoisonResist() const
    {
        return poison;
    }
    int getMentalResist() const
    {
        return mental;
    }
protected:
    int physical;
    int fire;
    int cold;
    int electro;
    int acid;
    int poison;
    int mental;
};
