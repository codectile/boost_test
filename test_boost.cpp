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

#include "vector_units.hpp"

template<typename Unit, typename Type>
using quantity = boost::units::quantity<Unit, Type>;

int main()
{
	using si_length = boost::units::si::length;
	using cgs_length = boost::units::cgs::length;
	using us_length = boost::units::us::foot_base_unit;
	using namespace boost::units::si;
	using namespace boost::units::cgs;
	using namespace boost_test;
	
	

	vector_units<float, si_length, cgs_length, si_length> vu(1, 2, 3), vu1(4, 5, 6);



	std::cout << "=====================================================" << std::endl;

	std::cout << "Vector 1: (" << vu.getx() << ", " << vu.gety() << ", " << vu.getz() << ")" << std::endl;
	std::cout << "Vector 2: (" << vu1.getx() << ", " << vu1.gety() << ", " << vu1.getz() << ")" << std::endl;
	vector_units sum = vu.sum(vu1);
	std::cout << "Testing sum: " << std::endl;
	std::cout << "Result: " << sum.getx() << " " << sum.gety() << " " << sum.getz() << std::endl;
	vector_units cross = vu.cross(vu1);
	std::cout << "Testing cross product (All values are properly converted): " << std::endl;
	std::cout << "Result: " << cross.getx() << " " << cross.gety() << " " << cross.getz() << std::endl;

	std::cout << "=====================================================" << std::endl;
	std::cout << std::endl << std::endl;

	return 0;
}
