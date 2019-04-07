#ifndef VECTOR_UNITS_HPP
#define VECTOR_UNITS_HPP

#include <type_traits>
#include <boost/static_assert.hpp>
#include <boost/units/systems/si.hpp>
#include <boost/units/quantity.hpp>

namespace boost_test
{

	/*
	 * class: vector_units, a class that provides time efficient computations of 3-dimensional
	 *		  vectors with boost units.
	 * Template parameters:
	 * Type: int, float, double
	 * U1: unit type of x - coordinate
	 * U2: unit type of y - coordinate
	 * U3: unit type of z - coordinate
	 */
	template<typename Type, typename U1, typename U2, typename U3>
	class vector_units
	{
		BOOST_STATIC_ASSERT_MSG(std::is_same_v<typename U1::dimension_type, typename U2::dimension_type>, "vector_units: all units must be of same dimension");
		BOOST_STATIC_ASSERT_MSG(std::is_same_v<typename U2::dimension_type, typename U3::dimension_type>, "vector_units: all units must be of same dimension");
	public:
		/*
		 * default constructor
		 */
		vector_units()
		{
			
		}

		/*
		 * parameterized constructor
		 * Parameters:
		 * x - for storing value of x - coordinate
		 * y - for storing value of y - coordinate
		 * z - for storing value of z - coordinate
		 */
		vector_units(const Type& x1, const Type& y1, const Type& z1)
		{
			x = boost::units::quantity<U1, Type>::from_value(x1);
			y = boost::units::quantity<U2, Type>::from_value(y1);
			z = boost::units::quantity<U3, Type>::from_value(z1);
		}

		/*
		 * parameterized constructor for quantity type
		 * Parameters:
		 * x - for storing value of x - coordinate
		 * y - for storing value of y - coordinate
		 * z - for storing value of z - coordinate
		 */
		vector_units(boost::units::quantity<U1, Type> x1, boost::units::quantity<U2, Type> y1, boost::units::quantity<U3, Type> z1)
		{
			x = x1;
			y = y1;
			z = z1;
		}

		/*
		 * stores the value for x-ccordinate
		 * Function parameters:
		 * value - value to be stored
		 * Return type: void
		 */
		inline void setx(boost::units::quantity<U1, Type> x1)
		{
			x = x1;
		}

		/*
		 * stores the value for y-ccordinate
		 * Function parameters:
		 * value - value to be stored
		 * Return type: void
		 */
		inline void sety(boost::units::quantity<U2, Type> y1)
		{
			y = y1;
		}

		/*
		 * stores the value for x-ccordinate
		 * Function parameters:
		 * value - value to be stored
		 * Return type: void
		 */
		inline void setz(boost::units::quantity<U3, Type> z1)
		{
			z = z1;
		}


		/*
		 * returns the value for x-ccordinate
		 * Function parameters
		 * Return type: quantity<U1, Type>
		 */
		inline boost::units::quantity<U1, Type> getx() const
		{
			return x;
		}

		/*
		 * returns the value for y-ccordinate
		 * Function parameters
		 * Return type: quantity<U2, Type>
		 */
		inline boost::units::quantity<U2, Type> gety() const
		{
			return y;
		}

		/*
		 * returns the value for z-ccordinate
		 * Function parameters
		 * Return type: quantity<U3, Type>
		 */
		inline boost::units::quantity<U3, Type> getz() const
		{
			return z;
		}

		/*
		 * returns the crossproduct of 2 vectors with same units and dimensions
		 * Template parameters:
		 * Function parameters:
		 * v - another vector of type vector units
		 * Return type: vector_units
		 */
		vector_units cross(const vector_units &v) const
		{

			auto x1 = (static_cast<boost::units::quantity<U1, Type>>(y) * static_cast<boost::units::quantity<U1, Type>>(v.getz()) - static_cast<boost::units::quantity<U1, Type>>(z) * static_cast<boost::units::quantity<U1, Type>>(v.gety()));
			auto y1 = (-(static_cast<boost::units::quantity<U2, Type>>(x) * static_cast<boost::units::quantity<U2, Type>>(v.getz()) - static_cast<boost::units::quantity<U2, Type>>(z) * static_cast<boost::units::quantity<U2, Type>>(v.getx())));
			auto z1 = (static_cast<boost::units::quantity<U2, Type>>(x) * static_cast<boost::units::quantity<U2, Type>>(v.gety()) - static_cast<boost::units::quantity<U2, Type>>(y) * static_cast<boost::units::quantity<U2, Type>>(v.getx()));
			return vector_units(x1.value(), y1.value(), z1.value());
		}

		/*
		 * assigns another vector_units to this vector_units
		 * Template parameters:
		 * Function parameters:
		 * v - another vector of type vector_units
		 * Return type: vector_units
		 */
		inline vector_units<Type, U1, U2, U3> sum(const vector_units<Type, U1, U2, U3> &v)
		{
			vector_units sum;
			sum.setx(x + v.getx());
			sum.sety(y + v.gety());
			sum.setz(z + v.getz());
			return sum;
		}


		/*
		 * assigns another vector_units to this vector_units
		 * Template parameters:
		 * Function parameters:
		 * v - another vector of type vector_units
		 * Return type: vector_units
		 */
		vector_units<Type, U1, U2, U3> operator= (const vector_units<Type, U1, U2, U3> &v)
		{
			if (this != &v)
			{
				x = v.getx();
				y = v.gety();
				z = v.getz();
			}
			return *this;
		}


	private:
		boost::units::quantity<U1, Type> x;
		boost::units::quantity<U2, Type> y;
		boost::units::quantity<U3, Type> z;
		
	};
}
#endif // VECTOR_UNITS_HPP
