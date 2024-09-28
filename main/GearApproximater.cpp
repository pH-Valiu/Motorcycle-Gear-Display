#include "Arduino.h"
#include "float.h"
#include "GearApproximater.h"


GearApproximater::GearApproximater( const TireSpecs* tireSpecs, const MotoSpecs* motoSpecs )
    : m_tireSpecs(tireSpecs), m_motoSpecs(motoSpecs) {
      m_formulaConstant = calculateFormulaConstant();
}
 
int GearApproximater::approximateGear(const unsigned int& engineRPM, const unsigned int& velocity){
  // Divide by 0 handler
  if (velocity == 0){
    return 0;
  }

  // Calculate the gear ratio
  float gearRatio = (engineRPM / float(velocity)) * m_formulaConstant;

  // Approximate the calculated value to the actual values
  int gear = 0;
  float minDistance = FLT_MAX;

  // Check each present gear ratio and compare it to computed one
  for(int i=0; i < m_motoSpecs->numGears; i++){
    float distance = abs(gearRatio - m_motoSpecs->gearRatiosPtr[i]);
    if (distance < minDistance){
      gear = i+1;
      minDistance = distance;
    }
  }

  // Return the approximated calculated gear
  return gear;
}

    
float GearApproximater::calculateTireCircumferenceM() const{
  float sideWallHeightMM = m_tireSpecs->tireWidthMM * (m_tireSpecs->tireWidthHeightRatio / 100.0f);
  float tireRimDiameterMM = m_tireSpecs->tireRimDiameterInch * 25.4f;
  float tireDiameterMM = tireRimDiameterMM + 2 * sideWallHeightMM;
  float tireCircumferenceMM = PI * tireDiameterMM;

  return tireCircumferenceMM / 1000.0f;
}

    
float GearApproximater::calculateFormulaConstant() const{
  float tireCircumferenceM = calculateTireCircumferenceM();
  return (tireCircumferenceM * 60.0f) / (m_motoSpecs->primaryGearReduction * m_motoSpecs->finalGearReduction * 1000.0f);

}

GearApproximater::TireSpecs* createTireSpecs(){
  struct GearApproximater::TireSpecs* tireSpecs = new GearApproximater::TireSpecs();
  tireSpecs->tireWidthMM = 160;
  tireSpecs->tireWidthHeightRatio = 60;
  tireSpecs->tireRimDiameterInch = 17;

  return tireSpecs;
}

GearApproximater::MotoSpecs* createMotoSpecs(){
  struct GearApproximater::MotoSpecs* motoSpecs = new GearApproximater::MotoSpecs();
  motoSpecs->primaryGearReduction = 2.029f;
  motoSpecs->finalGearReduction = 2.733f;
  motoSpecs->numGears = 6;
  motoSpecs->gearRatiosPtr = (float*) malloc(sizeof(float) * motoSpecs->numGears);
  motoSpecs->gearRatiosPtr[0] = 3.285f;
  motoSpecs->gearRatiosPtr[1] = 2.105f;
  motoSpecs->gearRatiosPtr[2] = 1.600f;
  motoSpecs->gearRatiosPtr[3] = 1.300f;
  motoSpecs->gearRatiosPtr[4] = 1.150f;
  motoSpecs->gearRatiosPtr[5] = 1.043f;

  return motoSpecs;
}