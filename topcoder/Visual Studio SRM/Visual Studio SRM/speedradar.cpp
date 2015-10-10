/*speedradar.cpp*/

#include "speedradar.h"
#include <vector>

SpeedRadar::SpeedRadar(){

}

SpeedRadar::SpeedRadar(int minLimit, int maxLimit, std::vector<int> readings){
	this->minLimit = minLimit;
	this->maxLimit = maxLimit;
	this->readings = readings;
}

void SpeedRadar::readSpeed(int reading){
	readings.push_back(reading);
}

double SpeedRadar::averageSpeed(){
	int sum = 0;
	int numOutside=0;

	int tenpct = readings.size() / 10;	//threshold for 10 percent

	for (unsigned i = 0; i < readings.size(); i++){
		if (readings[i] > this->maxLimit || readings[i] < this->minLimit){
			readings.erase(readings.begin()+i);
			numOutside++;
		}
	}

	if (numOutside > tenpct)return 0.0;

	for (std::vector<int>::const_iterator i = readings.begin(); i != readings.end(); i++){
		sum += *i;
	}
	double average = (double)sum / readings.size();

	return average;
}