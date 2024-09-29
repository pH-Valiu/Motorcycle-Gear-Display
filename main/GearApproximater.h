#ifndef GEAR_APPROXIMATER_H
#define GEAR_APPROXIMATER_H

#include "Arduino.h"

class GearApproximater {
public:
    struct TireSpecs {
        int tireWidthMM;
        int tireWidthHeightRatio;
        int tireRimDiameterInch;
    };

    struct MotoSpecs {
        float primaryGearReduction;
        float finalGearReduction;
        int numGears;
        float* gearRatiosPtr;
    };

private:
    float m_formulaConstant;
    const struct TireSpecs* m_tireSpecs;
    const struct MotoSpecs* m_motoSpecs;

public:
    /**
    * Constructor for GearApproximater
    *
    * Internally computes to formulaConstant
    * @param tireSpecs Tire specification as const pointer, needs to be pre allocated with malloc
    * @param motoSpecs Motorcycle specification as const pointer, needs to be pre allocated with malloc
    */
    GearApproximater(const TireSpecs* tireSpecs, const MotoSpecs* motoSpecs);

    /**
    * Calculate the approximated gear based on engineRPM and velocity.
    *
    * First, uses the formula described in README.md to calculate the suited gear ratio for given parameters.
    *
    * Then, it compares that value against the actual gear ratios of the specified moto.
    *
    * The gear with the smallest difference to the ratio gets returned.
    * @param engineRPM the engineRPM (in 1/min), most commonly from 0-15000
    * @param velcoity the moto velocity (in km/h), most commonly from 0-400
    * @return the approximated gear starting at 1, 0 is only being returned in error cases (velocity = 0)
    */
    int approximateGear(const unsigned int& engineRPM, const unsigned int& velocity);

private:
    /**
    * Calculate the tire circumference (in m).
    *
    * To get the circumference we need the wheel diameter.
    *
    * The wheel diameter is composed of the rim diamater plus twice the wheel rubber sidewall height.
    *
    * The sidewall height can be computed using the tire width and its widht/height ratio.
    * @param none, but the m_tireSpecs attribute has to be initialized
    * @return the tire circumference (in m)
    */
    float calculateTireCircumferenceM() const;

    /**
    * Calculate the formula constant.
    * 
    * It derivates from the actual formula, see README.md
    * @param none, but the m_tireSpecs and the m_motoSpecs attribute have to be initialized
    * @return the formula constant
    */
    float calculateFormulaConstant() const;
};

/**
* Helper method to create default TireSpecs based on Honda CB500FA (2017) 
*
* Rear tire is 160/60 ZR 17
* @return GearApproximater::TireSpecs* newly on heap allocated TireSpecs pointer
*/
GearApproximater::TireSpecs* createTireSpecs();

/**
* Helper method to create default MotoSpecs based on Honda CB500FA (2017)
* @return GearApproximater::MotoSpecs* newly on heap allocated MotoSpecs pointer
*/
GearApproximater::MotoSpecs* createMotoSpecs();

#endif
