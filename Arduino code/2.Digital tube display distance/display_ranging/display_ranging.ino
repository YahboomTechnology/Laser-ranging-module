#include "Seeed_vl53l0x.h"
#include "LEDdisp.h"
LEDdisp LEDdisp;

Seeed_vl53l0x VL53L0X;
int rangunm = 0;

void setup()
{ 
  VL53L0X_Error Status = VL53L0X_ERROR_NONE;
  Serial.begin(115200);
  Status=VL53L0X.VL53L0X_common_init();
  if(VL53L0X_ERROR_NONE!=Status)
  {
    Serial.println("start vl53l0x mesurement failed!");
    VL53L0X.print_pal_error(Status);
    while(1);
  }
  
  VL53L0X.VL53L0X_long_distance_ranging_init();
  
  if(VL53L0X_ERROR_NONE!=Status)
  {
    Serial.println("start vl53l0x mesurement failed!");
    VL53L0X.print_pal_error(Status);
    while(1);
  }
  delay(1000);
  LEDdisp.port(2,3);
  LEDdisp.bright(1);
}


void loop()
{
  VL53L0X_RangingMeasurementData_t RangingMeasurementData;
  VL53L0X_Error Status = VL53L0X_ERROR_NONE;

  memset(&RangingMeasurementData,0,sizeof(VL53L0X_RangingMeasurementData_t));
  Status=VL53L0X.PerformSingleRangingMeasurement(&RangingMeasurementData);
  if(VL53L0X_ERROR_NONE==Status)
  {
    rangunm = RangingMeasurementData.RangeMilliMeter-25;
    if(rangunm>=2000)
    {
      Serial.println("out of range!!");
    }
    else
    {
      Serial.print("Measured distance:");
      Serial.print(rangunm);
      Serial.println(" mm");
      LEDdisp.all(int(rangunm/10));
    }
  }
  else
  {
    Serial.print("mesurement failed !! Status code =");
    Serial.println(Status);
  }
  
  delay(300);
}
