const float primaryGearRatio = 2.029f;
const float finalGearRatio = 2.733f;

const int numGears = 6;
const float gearRatios[numGears] = {3.285f, 2.105f, 1.6f, 1.3f, 1.15f, 1.043f};

const int tireWidthMM = 160;
const int tireWidthHeightRatio = 60;
const int tireRimDiameterInch = 17;


const float tireCircumferenceM = calculateTireCircumferenceM();
const float formulaConstant = calculateFormulaConstant();


// For Honda CB500FA (2017) rear wheel is 160/60 ZR 17
// so circmference is around 1.96m
float calculateTireCircumferenceM(){
  float sideWallHeightMM = tireWidthMM * (tireWidthHeightRatio / 100.0f);
  float tireRimDiameterMM = tireRimDiameterInch * 25.4f;
  float tireDiameterMM = tireRimDiameterMM + 2 * sideWallHeightMM;
  float tireCircumferenceMM = PI * tireDiameterMM;

  return tireCircumferenceMM / 1000.0f;
}


// calculate the derived formula constant
// for my Honda CB500FA (2017) this is around 0.0212
float calculateFormulaConstant(){
  float constant = (tireCircumferenceM * 60.0f) / (primaryGearRatio * finalGearRatio * 1000.0f);
  return constant;
}

// rpm is (1/min) and vel is (km/h)
float calculateGearRatio(float rpm, float vel){
  float ratio = formulaConstant * (rpm / vel);

  return ratio;
}

int approximateGear(float calculatedGearRatio){
    int closestGear = -1;
    float smallestDifference = 1e+38;

    for(int i=0; i<numGears; i++){
      float abs = abs(calculatedGearRatio - gearRatios[i]);
      if (abs < smallestDifference){
        smallestDifference = abs;
        closestGear = i+1;
      }
    }

    return closestGear;
}

