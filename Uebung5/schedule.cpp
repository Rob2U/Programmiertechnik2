#include <algorithm>
#include <ctime>
#include <iostream>
#include <random>
#include <vector>

struct Interval
{
	size_t index;
	size_t start;
	size_t end;
};

constexpr size_t MaxEnd = 74;
constexpr size_t MaxDuration = 10;

std::ostream& operator<<(std::ostream& os, const std::vector<Interval>& intervals)
{
	// TODO 5.3: Implement a nice print function

	std::for_each(intervals.begin(), intervals.end(), [&os](Interval elem){
		std::string output = "#" + std::string((elem.index/10 == 0) ? " " : "") + std::to_string(elem.index) + " |";
		for (int i = 0; i < MaxEnd; i++){
			output += (i >= elem.start && i <= elem.end) ? "#" : "-";
		}
		os << output << "|" << std::endl;
	});
	return os;
}

// creates random data
std::vector<Interval> createRandomIntervals(size_t item_count)
{
	std::vector<Interval> intervals;
	intervals.resize(item_count);

	std::random_device rd;
	std::mt19937 gen(rd());
	std::uniform_int_distribution<size_t> durationDistrib(1, MaxDuration);

	for (size_t i = 0; i < intervals.size(); ++i)
	{
		auto duration = durationDistrib(gen);
		std::uniform_int_distribution<size_t> startDistrib(0, MaxEnd - duration + 1);

		auto& interval = intervals[i];
		interval.index = i;
		interval.start = startDistrib(gen);
		interval.end = interval.start + duration - 1;
	}

	return intervals;
}

void schedule(const std::vector<Interval>& intervals)
{
	std::cout << std::endl << "Intervals (randomized):\n" << intervals;

	// TODO 5.3: Sort intervals
	std::vector<Interval> sorted = intervals;
	std::sort(sorted.begin(), sorted.end(), [](const Interval& a, const Interval& b) {
		if (a.start != b.start)
			return a.start < b.start;
		else 
			return a.end < b.end;
	});

	std::cout << std::endl << "Intervals (sorted):\n" << sorted;

	// TODO 5.3: Implement greedy scheduling
	std::vector<Interval> scheduled;

	Interval previousElem = sorted.at(0);
	scheduled.push_back(previousElem);
	std::copy_if(std::next(sorted.begin()), sorted.end(), std::back_inserter(scheduled), [&](Interval elem) {
		if (previousElem.end < elem.start){
			previousElem = elem;
			return true;
		}
		return false;
	});

	std::cout << "\nIntervals (scheduled, " << scheduled.size() << " of " << sorted.size() << " possible)\n"
			  << scheduled;
}

int main()
{
	constexpr size_t item_count = 20;
	auto intervals = createRandomIntervals(item_count);
	schedule(intervals);

	return 0;
}
