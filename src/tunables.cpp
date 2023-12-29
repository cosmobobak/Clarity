#include "globals.h"

Tunable aspBaseDelta("ASP_BaseDelta", 20, 1);
Tunable aspDeltaMultiplier("ASP_DeltaMultiplier", 1.8, 10);
Tunable aspDepthCondition("ASP_DepthCondition", 4, 1);

Tunable rfpDepthCondition("RFP_DepthCondition", 11, 1);
Tunable rfpMultiplier("RFP_Multiplier", 84, 1);

Tunable iirDepthCondition("IIR_DepthCondition", 5, 1);

Tunable fpDepthCondition("FP_DepthCondition", 3, 1);
Tunable fpBase("FP_Base", 278, 1);
Tunable fpMultiplier("FP_Multiplier", 67, 1);

Tunable lmpDepthCondition("LMP_DepthCondition", 8, 1);
Tunable lmpBase("LMP_Base", 0, 1);  // No divisor adjustment

Tunable sprDepthCondition("SPR_DepthCondition", 3, 1);
Tunable sprCaptureThreshold("SPR_CaptureThreshold", -108, -1);
Tunable sprQuietThreshold("SPR_QuietThreshold", -32, -1);

Tunable nmpDivisor("NMP_Divisor", 196, 1);
Tunable nmpSubtractor("NMP_Subtractor", 3, 1);
Tunable nmpDepthCondition("NMP_DepthCondition", 2, 1);

Tunable hmrDivisor("HMR_Divisor", 8074, 1); 
Tunable cmrDivisor("CMR_Divisor", 3000, 1);

Tunable lmrBase("LMR_Base", 0.80, 100);  // Adjusted divisor for lmrBase
Tunable lmrMultiplier("LMR_Multiplier", 0.56, 100);  // Adjusted divisor for lmrMultiplier

Tunable hstMaxBonus("HST_MaxBonus", 1892, 1);
Tunable hstMultiplier("HST_Multiplier", 4, 1);
Tunable hstAdder("HST_Adder", 121, 1);
Tunable hstSubtractor("HST_Subtractor", 120, 1);

Tunable sinDepthCondition("SIN_DepthCondition", 8, 1);
Tunable sinDepthMargin("SIN_DepthMargin", 3, 1);
Tunable sinDepthScale("SIN_DepthScale", 24, 1);

Tunable razDepthMultiplier("RAZ_DepthMultiplier", 395, 1);

Tunable ntmDepthCondition("NTM_DepthCondition", 8, 1);
Tunable ntmSubtractor("NTM_Subtractor", 1.53, 100);
Tunable ntmMultiplier("NTM_Multiplier", 1.39, 100);
Tunable ntmDefault("NTM_Default", 0.98, 100);

Tunable hipDepthCondition("HIP_DepthCondition", 4, 1);
Tunable hipDepthMultiplier("HIP_DepthMultiplier", -1536, -1);

// Declaration of pointers to tunables

std::vector<Tunable *> tunables = {
    &aspBaseDelta,
    &aspDeltaMultiplier,
    &aspDepthCondition,
    &rfpDepthCondition,
    &rfpMultiplier,
    &iirDepthCondition,
    &fpDepthCondition,
    &fpBase,
    &fpMultiplier,
    &lmpDepthCondition,
    &lmpBase,
    &sprDepthCondition,
    &sprCaptureThreshold,
    &sprQuietThreshold,
    &nmpDivisor,
    &nmpSubtractor,
    &nmpDepthCondition,
    &hmrDivisor,
    &cmrDivisor,
    &lmrBase,
    &lmrMultiplier,
    &hstMaxBonus,
    &hstMultiplier,
    &hstAdder,
    &hstSubtractor,
    &sinDepthCondition,
    &sinDepthMargin,
    &sinDepthScale,
    &razDepthMultiplier,
    &ntmDepthCondition,
    &ntmSubtractor,
    &ntmMultiplier,
    &ntmDefault,
    &hipDepthCondition,
    &hipDepthMultiplier
};


void outputTunables() {
    for(Tunable *tunable : tunables) {
        std::cout << "option name " << tunable->name << " type spin default " << std::to_string(static_cast<int>(tunable->value * tunable->divisor)) << " min " << "0" << " max " << tunable->max << std::endl;
    }
}
void outputTunableJSON() {
    std::cout << "{\n";
    for(Tunable *tunable : tunables) {
        std::cout << "   \"" << tunable->name << "\": {\n";
        std::cout << "      \"value\": " << std::to_string(static_cast<int>(tunable->value * tunable->divisor)) << "," << std::endl;
        std::cout << "      \"min_value\": " << "0" << "," << std::endl;
        std::cout << "      \"max_value\": " << tunable->max << "," << std::endl;
        std::cout << "      \"step\": " << tunable->step << std::endl;
        std::cout << "   },\n";
    }
    std::cout << "}\n";
}
void adjustTunable(const std::string &name, const int &value) {
    for(Tunable *tunable : tunables) {
        if(tunable->name == name) {
            tunable->updateValue(value);
            if(name == "LMR_Base" || name == "LMR_Multiplier") {
                calculateReductions();
            }
            return;
        }
    }
    std::cout << "No Such Tunable\n";
}
void readTunable(const std::string &name) {
    for(Tunable *tunable : tunables) {
        if(tunable->name == name) {
            std::cout << "value: " << tunable->value << std::endl;
            return;
        }
    }
    std::cout << "No Such Tunable\n";
}
void readTunables() {
    for(Tunable *tunable : tunables) {
        std::cout << "name: " << tunable->name << std::endl;
        std::cout << "value: " << tunable->value << std::endl;
        std::cout << "min: " << "0" << std::endl;
        std::cout << "max: " << tunable->max << std::endl;
        std::cout << "divisor: " << tunable->divisor << std::endl;
        std::cout << "step: " << tunable->step << std::endl;
        //std::cout << "value at tuning scale: " << static_cast<int>(tunable->value * tunable->divisor) << std::endl;
    }
}