#include <iostream>
#include <boost/units/base_dimension.hpp>
#include <boost/units/derived_dimension.hpp>
#include <boost/units/io.hpp>
#include <boost/units/quantity.hpp>
#include <boost/units/static_constant.hpp>
#include <boost/units/unit.hpp>
#include <boost/units/base_unit.hpp>
#include <boost/units/make_system.hpp>
#include <boost/units/base_units/us/foot.hpp>
#include <boost/units/base_units/cgs/centimeter.hpp>
#include <boost/units/systems/cgs.hpp>

#include <boost/units/systems/si/length.hpp>
#include <boost/units/systems/si/time.hpp>
#include <boost/units/systems/si/velocity.hpp>
#include <boost/units/systems/si/acceleration.hpp>
#include <boost/units/systems/si/io.hpp>
#include <boost/units/get_dimension.hpp>
#include <boost/units/get_system.hpp>

#include <chrono>
#include "vector_units.hpp"



int main()
{
	using si_length = boost::units::si::length;
	using cgs_length = boost::units::cgs::length;
	using us_length = boost::units::us::foot_base_unit;
	using namespace boost::units::si;
	using namespace boost::units::cgs;
	
	
	
	std::cout << "Enter data points" << std::endl;
	float data[6];
	std::cin >> data[0] >> data[1] >> data[2] >> data[3] >> data[4] >> data[5];


	vector_units<float, si_length, cgs_length, us_length> vu, vu1;
	vu.set<0>(data[0]);
	vu.set<1>(data[1]);
	vu.set<2>(data[2]);

	vu1.set<0>(data[3]);
	vu1.set<1>(data[4]);
	vu1.set<2>(data[5]);

	std::cout << "=====================================================" << std::endl;

	vector_units sum = vu + vu1;
	std::cout << "Testing sum: " << std::endl;
	std::cout << "Result: " << sum.get<0>() << " " << sum.get<1>() << " " << sum.get<2>() << std::endl;
	vector_units cross = vu.cross(vu1);
	std::cout << "Testing cross product: " << std::endl;
	std::cout << "Result: " << cross.get<0>() << " " << cross.get<1>() << " " << cross.get<2>() << std::endl;

	std::cout << "=====================================================" << std::endl;
	std::cout << std::endl << std::endl;

	
	double time[5];

	std::cout << "Timing for 1 million executions" << std::endl << std::endl;
	for (int j = 0; j < 5; j++)
	{
		auto start = std::chrono::high_resolution_clock::now();
		for (int i = 0; i < 1000000; i++)
			vu.sum(vu1);
		auto end = std::chrono::high_resolution_clock::now();
		time[j] = std::chrono::duration<double>(end - start).count();
	}
	std::cout << "Average running time for sum(without expression templates): " << (time[0] + time[1] + time[2] + time[3] + time[4]) / 5 * 1000 << "ms" << std::endl;


	for (int j = 0; j < 5; j++)
	{
		auto start = std::chrono::high_resolution_clock::now();
		for (int i = 0; i < 1000000; i++)
			vu + vu1;
		auto end = std::chrono::high_resolution_clock::now();
		time[j] = std::chrono::duration<double>(end - start).count();
	}
	std::cout << "Average running time for sum(expression templates): " << (time[0] + time[1] + time[2] + time[3] + time[4]) / 5 * 1000 << "ms" << std::endl;

	for (int j = 0; j < 5; j++)
	{
		auto start = std::chrono::high_resolution_clock::now();
		for (int i = 0; i < 1000000; i++)
			vu.cross(vu1);
		auto end = std::chrono::high_resolution_clock::now();
		time[j] = std::chrono::duration<double>(end - start).count();
	}
	std::cout << "Average running time for crossproduct: " << (time[0] + time[1] + time[2] + time[3] + time[4]) / 5 * 1000 << "ms" << std::endl;

	std::cout << "=====================================================" << std::endl;
}
