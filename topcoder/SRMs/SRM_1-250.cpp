//75pts out of 250
#include <vector>

class SpeedRadar{
public:
	SpeedRadar();
	double averageSpeed(int &, int &, std::vector<int> readings);
};


SpeedRadar::SpeedRadar(){

}

double SpeedRadar::averageSpeed(int &minLimit, int &maxLimit, std::vector<int> readings){
	int sum = 0;
	int numOutside = 0;

	int tenpct = readings.size() / 10;	//threshold for 10 percent

	for (unsigned i = 0; i < readings.size(); i++){
		if (readings[i] > maxLimit || readings[i] < minLimit){
			readings.erase(readings.begin() + i);
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