#include <iostream>
#include <json/json.h>

namespace info
{
double defaultOffset { 0.001 };
int goalWr { 40 };
double maxOffset { 0.0015 };
double minOffset { 0.0005 };
}

struct ActualData
{
	double currentOffset { 0.0 };
	int currentWr { 0 };
	double previousOffset { 0.0 };
	int previousWr { 0 };
};

double IncOffset(double currentOffset)
{
	if (currentOffset < info::maxOffset) {
		return currentOffset + 0.00025;
	} else {
		return info::maxOffset;
	}
}

double DecOffset(double currentOffset)
{
	if (currentOffset > info::minOffset) {
		return currentOffset - 0.00025;
	} else {
		return info::minOffset;
	}
}

void CheckHourly(int step, ActualData& data)
{
	if (step == 1) {
		data.currentOffset = info::defaultOffset;
		return;
	}
	if (data.currentWr >= info::goalWr) {
		data.currentOffset = info::minOffset;
		return;
	}
	if (data.currentWr < info::goalWr) {
		if (data.currentWr < data.previousWr) {
			data.currentOffset = IncOffset(data.currentOffset);
		} else if (data.currentWr >= data.previousWr) {
			data.currentOffset = DecOffset(data.currentOffset);
		}
		data.previousOffset = data.currentOffset;

		return;
	}
}

void PrintData(int step, ActualData& data)
{
	std::cout << "Step  = " << step;
	std::cout << " Current offset  = " << data.currentOffset;
	std::cout << " Current win rate  = " << data.currentWr;
	std::cout << " Previous offset  = " << data.previousOffset;
	std::cout << " Previous win rate  = " << data.previousWr << std::endl;

}

int main()
{
	ActualData data;
	int winRate { 0 };
	int step { 1 };
	CheckHourly(1, data);
	PrintData(step, data);
	++step;

	while (true) {
		std::cout << "Input win rate: ";
		while(true)
		{
			std::cin >> winRate;

			{
				data.previousWr = data.currentWr;
				data.currentWr = winRate;
				CheckHourly(step, data);
				PrintData(step, data);
			}
			++step;
			break;
		}
	}
}
