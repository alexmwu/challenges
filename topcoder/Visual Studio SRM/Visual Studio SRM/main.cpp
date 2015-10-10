/*
0)

1
50
{45, 40, 50}
Returns: 45.0
With all drivers within the speed limits, the return value is just the average speed.

1)

    
1
50
{42,43,44,45,46,47,48,49,50,51}
Returns: 46.0
There is only one driver infringing the limit, and it represents 10% of the total readings.
The average speed of the other readings is 46.0.

2)

	    
1
50
{42,46,48,50,52}
Returns: 0.0
Only one reading is outside the given limits, but it represents 20% of the total number of readings.
We therefore assume that the radar is not working and return 0.0.

3)

		    
20
60
{25,45,45,43,24,9,51,55,60,34,61,23,40,40,47,49,33,23,47,54,54}
Returns: 41.68421052631579

*/

#include "speedradar.h"
#include <iostream>
#include <vector>

int main(){
	char q='a';
	int a0[3] = { 45, 40, 50 };
	int a1[10] = { 42, 43, 44, 45, 46, 47, 48, 49, 50, 51 };
	int a2[5] = { 42, 46, 48, 50, 52 };
	int a3[21] = { 25, 45, 45, 43, 24, 9, 51, 55, 60, 34, 61, 23, 40, 40, 47, 49, 33, 23, 47, 54, 54 };

	std::vector<int> v0(a0, a0 + sizeof(a0)/sizeof(a0[0]));
	std::vector<int> v1(a1, a1 + sizeof(a1) / sizeof(a0[1]));
	std::vector<int> v2(a2, a2 + sizeof(a2) / sizeof(a0[2]));
	std::vector<int> v3(a3, a3 + sizeof(a3) / sizeof(a0[3]));


	SpeedRadar sp0(1, 50, v0);
	SpeedRadar sp1(1,50,v1);
	SpeedRadar sp2(1, 50, v2);
	SpeedRadar sp3(20,60,v3);

	std::cout << sp0.averageSpeed() << std::endl;
	std::cout << sp1.averageSpeed() << std::endl;
	std::cout << sp2.averageSpeed()<<std::endl;
	std::cout << sp3.averageSpeed()<<std::endl;
	while (q != 'q') std::cin >> q;
}