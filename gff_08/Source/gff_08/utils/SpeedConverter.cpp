// Fill out your copyright notice in the Description page of Project Settings.

#include "SpeedConverter.h"

float USpeedConverter::ToSpeedKilometerPerHour(float SpeedCentimeterPerSecond) {
	float res = SpeedCentimeterPerSecond;	 // cm/s
	res = res * 3600.0f;					 // cm/h
	res = res / 100.0f;						 // m/h
	res = res / 1000.0f;					 // km/h
	return res;
}

float USpeedConverter::ToSpeedCentimeterPerSecond(float KilometerPerHour) {
	float res = KilometerPerHour;	 // km/h
	res = res * 1000.0f;			 // m/h
	res = res * 100.0f;				 // cm/h
	res = res / 3600.0f;			 // cm/s
	return res;
}
