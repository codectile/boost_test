#ifndef VECTOR_UNITS_HPP
#define VECTOR_UNITS_HPP

#include <type_traits>
#include <boost/static_assert.hpp>

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
			_vector[0] = Type(0);
			_vector[1] = Type(0);
			_vector[2] = Type(0);
		}

		/*
		 * parameterized constructor
		 * Parameters:
		 * x - for storing value of x - coordinate
		 * y - for storing value of y - coordinate
		 * z - for storing value of z - coordinate
		 */
		vector_units(Type x, Type y, Type z)
		{
			_vector[0] = x;
			_vector[1] = y;
			_vector[2] = z;
		}

		/*
		 * stores the value for x-ccordinate
		 * Template parameters:
		 * N - 0 for x, 1 for y and 2 for z coordinate
		 * Function parameters:
		 * value - value to be stored
		 * Return type: void
		 */
		template<const size_t N>
		inline void set(Type value)
		{
			BOOST_STATIC_ASSERT_MSG(N < 3, "vector_units: invalid dimension");
			_vector[N] = value;
		}

		/*
		 * returns the value for x-ccordinate
		 * Template parameters:
		 * N - 0 for x, 1 for y and 2 for z coordinate
		 * Function parameters:
		 * Return type: Type
		 */
		template<const size_t N>
		inline Type get() const
		{
			BOOST_STATIC_ASSERT_MSG(N < 3, "vector_units: invalid dimension");
			return _vector[N];
		}

		/*
		 * returns the crossproduct of 2 vectors with same units and dimensions
		 * Template parameters:
		 * Function parameters:
		 * v - another vector of type vector units
		 * Return type: vector_units
		 */
		 //template<typename T1, typename T2, typename T3, typename T4>
		inline vector_units cross(const vector_units &v) const
		{

			vector_units  up;
			up._vector[0] = (_vector[1] * v._vector[2] - _vector[2] * v._vector[1]);
			up._vector[1] = (-(_vector[0] * v._vector[2] - _vector[2] * v._vector[0]));
			up._vector[2] = (_vector[0] * v._vector[1] - _vector[1] * v._vector[0]);
			return up;
		}

		/*
		 * returns the dotproduct of 2 vectors with same units and dimensions
		 * Template parameters:
		 * Function parameters:
		 * v - another vector of type vector_units
		 * Return type: Type
		 */
		inline Type dot(const vector_units<Type, U1, U2, U3> &v) const
		{
			return (_vector[0] * v._vector[0] + _vector[1] * v._vector[1] + _vector[2] * v._vector[2]);
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
			sum._vector[0] = v._vector[0];
			sum._vector[1] = v._vector[1];
			sum._vector[2] = v._vector[2];
			return sum;
		}

		/*
		 * multiplies a scalar quantity to this vector_units
		 * Template parameters:
		 * Function parameters:
		 * x - scalar value of datatype Type
		 * Return type: vector_units
		 */
		vector_units<Type, U1, U2, U3> operator* (Type x)
		{
			vector_units product;
			product._vector[0] *= x;
			product._vector[1] *= x;
			product._vector[2] *= x;
			return product;
		}

		/*
		 * divides a scalar quantity to this vector_units
		 * Template parameters:
		 * Function parameters:
		 * x - scalar value of datatype Type
		 * Return type: vector_units
		 */
		vector_units<Type, U1, U2, U3> operator/ (Type x)
		{
			vector_units div;
			div._vector[0] /= x;
			div._vector[1] /= x;
			div._vector[2] /= x;
			return div;
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
				_vector[0] = v._vector[0];
				_vector[1] = v._vector[1];
				_vector[2] = v._vector[2];
			}
			return *this;
		}

		/*
		 * overloaded subscript operator
		 * Template parameters:
		 * Function parameters:
		 * i - index for the vector
		 * Return type: Type refernce
		 */
		inline Type &operator[](const size_t i)
		{
			return _vector[i];
		}

		/*
		 * overloaded subscript operator
		 * Template parameters:
		 * Function parameters:
		 * i - index for the vector
		 * Return type: Type
		 */
		inline Type operator[](const size_t i) const
		{
			return _vector[i];
		}

	private:
		Type _vector[3];
	};





	//expression template for addition of vectors
	template<typename Type, typename U1, typename U2, typename U3>
	inline vector_units<Type, U1, U2, U3> operator+(const vector_units<Type, U1, U2, U3> &u, const vector_units<Type, U1, U2, U3> &v)
	{
		vector_units< Type, U1, U2, U3> sum;
		for (size_t i = 0; i < 3; i++)
			sum[i] = u[i] + v[i];
		return sum;
	}

	template<typename Type, typename U1, typename U2, typename U3>
	inline vector_units<Type, U1, U2, U3> operator-(const vector_units<Type, U1, U2, U3> &u, const vector_units<Type, U1, U2, U3> &v)
	{
		vector_units<Type, U1, U2, U3> diff;
		for (size_t i = 0; i < 3; i++)
			diff[i] = u[i] - v[i];
		return diff;
	}


	template <typename Type, typename E>
	class vector_units_expr
	{
	public:
		inline Type operator[](const size_t i) const
		{
			return static_cast<const E &>(*this)[i];
		}
	};

	template <typename Type, typename E1, typename E2>
	class vector_units_sum : public vector_units_expr<Type, vector_units_sum<Type, E1, E2>>
	{
	private:
		const E1 &_u;
		const E2 &_v;

	public:
		vector_units_sum(const E1 &u, const E2 &v) : _u(u), _v(v)
		{
		}

		inline Type operator[](const size_t i) const
		{
			return _u[i] + _v[i];
		}
	};

	template <typename Type, typename E1, typename E2>
	class vector_units_diff : public vector_units_expr<Type, vector_units_sum<Type, E1, E2>>
	{
	private:
		const E1 &_u;
		const E2 &_v;

	public:
		vector_units_diff(const E1 &u, const E2 &v) : _u(u), _v(v)
		{
		}

		inline Type operator[](const size_t i) const
		{
			return _u[i] - _v[i];
		}
	};

	template <typename Type, typename E1, typename E2>
	inline vector_units_sum<Type, E1, E2> operator+(const E1 &u, const E2 &v)
	{
		return vector_units_sum<Type, E1, E2>(u, v);
	}

	template <typename Type, typename E1, typename E2>
	inline vector_units_diff<Type, E1, E2> operator-(const E1 &u, const E2 &v)
	{
		return vector_units_sum<Type, E1, E2>(u, v);
	}
}
#endif // VECTOR_UNITS_HPP
