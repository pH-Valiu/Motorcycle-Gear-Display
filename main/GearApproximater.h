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
    */
    float calculateFormulaConstant() const;
};

// Function declarations
GearApproximater::TireSpecs* createTireSpecs();
GearApproximater::MotoSpecs* createMotoSpecs();

#endif
