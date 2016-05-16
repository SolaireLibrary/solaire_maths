#ifndef SOLAIRE_VECTOR_HPP
#define SOLAIRE_VECTOR_HPP

//Copyright 2016 Adam G. Smith
//
//Licensed under the Apache License, Version 2.0 (the "License");
//you may not use this file except in compliance with the License.
//You may obtain a copy of the License at
//
//http ://www.apache.org/licenses/LICENSE-2.0
//
//Unless required by applicable law or agreed to in writing, software
//distributed under the License is distributed on an "AS IS" BASIS,
//WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
//See the License for the specific language governing permissions and
//limitations under the License.

#include "solaire/maths/maths.hpp"

namespace solaire {

	//! \todo scalar & vector
	//! \todo scalar | vector
	//! \todo scalar ^ vector

	#if SOLAIRE_CPP_VER < SOLAIRE_CPP_11
		#pragma message("warning: " __FILE__  " Conditional and parameter pack functionality disabled. Requires C++11 or greater")
	#endif

	#if SOLAIRE_CPP_VER < SOLAIRE_CPP_14
		#pragma message("warning: " __FILE__  " Advanced constexpr functionality disabled. Requires C++14 or greater")
	#endif

	template<class T, const uint32_t S>
	class vector {
	public:
		typedef T type;
		enum{LENGTH = S};
	private:
		type mElements[S];
    private:
        #if SOLAIRE_CPP_VER == SOLAIRE_CPP_11
			SOLAIRE_CONSTEXPR_I11 bool _equals(const vector<T,S>& aOther, const uint32_t aIndex = S) const throw() {
				return aIndex == 0 ? mElements[0] == aOther[0] : mElements[aIndex] == aOther[aIndex] && _equals(aOther, aIndex - 1);
			}
        #endif
	public:
		SOLAIRE_CONSTEXPR_11 vector() throw() :
			mElements()
		{}

        template<class T2, typename ENABLE = typename std::enable_if<std::is_arithmetic<T2>::value>::type>
		SOLAIRE_CONSTEXPR_14 explicit vector(const T2 aScalar) throw() {
			for(uint32_t i = 0; i < S; ++i) mElements[i] = static_cast<T>(aScalar);
		}

		SOLAIRE_CONSTEXPR_14 vector(const T (&aOther)[S]) throw() {
			for(uint32_t i = 0; i < S; ++i) mElements[i] = aOther[i];
		}

		SOLAIRE_CONSTEXPR_14 vector(const vector<T,S>& aOther) {
			for(uint32_t i = 0; i < S; ++i) mElements[i] = aOther[i];
		}

		template<class T2>
		SOLAIRE_CONSTEXPR_14 explicit vector(const vector<T2, S>& aOther) throw() {
			for(uint32_t i = 0; i < S; ++i) mElements[i] = static_cast<T>(aOther[i]);
		}

		#if SOLAIRE_CPP_VER >= SOLAIRE_CPP_11
			template<const uint32_t S2, const uint32_t S3, typename ENABLE = typename std::enable_if<S2 + S3 == S>::type>
			SOLAIRE_CONSTEXPR_14 vector(const vector<T,S2>& aFirst, const vector<T,S3>& aSecond) {
				for(uint32_t i = 0; i < S2; ++i) mElements[i] = aFirst[i];
				for(uint32_t i = 0; i < S3; ++i) mElements[i + S2] = aSecond[i];
			}

			template<const uint32_t S2, const uint32_t S3, const uint32_t S4, typename ENABLE = typename std::enable_if<S2 + S3 + S4 == S>::type>
			SOLAIRE_CONSTEXPR_14 vector(const vector<T,S2>& aFirst, const vector<T,S3>& aSecond, const vector<T,S4>& aThird) {
				for(uint32_t i = 0; i < S2; ++i) mElements[i] = aFirst[i];
				for(uint32_t i = 0; i < S3; ++i) mElements[i + S2] = aSecond[i];
				for(uint32_t i = 0; i < S4; ++i) mElements[i + S2 + S3] = aThird[i];
			}

			template<const uint32_t S2, typename ENABLE = typename std::enable_if<S2 + 1 == S>::type>
			SOLAIRE_CONSTEXPR_14 vector(const T aScalar, const vector<T,S2>& aVector) {
				mElements[0] = aScalar;
				for(uint32_t i = 0; i < S2; ++i) mElements[i + 1] = aVector[i];
			}

			template<const uint32_t S2, typename ENABLE = typename std::enable_if<S2 + 1 == S>::type>
			SOLAIRE_CONSTEXPR_14 vector(const vector<T,S2>& aVector, const T aScalar) {
				for(uint32_t i = 0; i < S2; ++i) mElements[i] = aVector[i];
				mElements[S2] = aScalar;
			}

			template<const uint32_t S2, typename ENABLE = typename std::enable_if<S2 + 2 == S>::type>
			SOLAIRE_CONSTEXPR_14 vector(const T aFirst, const vector<T,S2>& aVector, const T aSecond) {
				mElements[0] = aFirst;
				for(uint32_t i = 0; i < S2; ++i) mElements[i + 1] = aVector[i];
				mElements[S2 + 1] = aSecond;
			}

			template<class ...PARAMS>
			SOLAIRE_CONSTEXPR_11 vector(const PARAMS... aParams) :
				mElements{aParams...}
			{
				static_assert(sizeof...(PARAMS) == S, "solaire::vector : Parameter count must be equal to vector length");
			}
		#endif

		SOLAIRE_CONSTEXPR_I11 T operator[](const uint32_t aIndex) const throw() {
			return mElements[aIndex];
		}

		inline T& operator[](const uint32_t aIndex) throw() {
			return mElements[aIndex];
		}

		SOLAIRE_CONSTEXPR_I11 uint32_t size() const throw() {
			return S;
		}

		template<class T2 = T, typename ENABLE = typename std::enable_if<std::is_arithmetic<T2>::value || std::is_same<T,T2>::value>::type>
		vector<bool, S> operator==(const T2 aScalar) const throw() {
			vector<bool, S> tmp;
			for(uint32_t i = 0; i < S; ++i) tmp[i] = mElements[i] == aScalar;
			return tmp;
		}

		template<class T2 = T, typename ENABLE = typename std::enable_if<std::is_arithmetic<T2>::value || std::is_same<T,T2>::value>::type>
		vector<bool, S> operator!=(const T2 aScalar) const throw() {
			vector<bool, S> tmp;
			for(uint32_t i = 0; i < S; ++i) tmp[i] = mElements[i] != aScalar;
			return tmp;
		}

		template<class T2 = T, typename ENABLE = typename std::enable_if<std::is_arithmetic<T2>::value || std::is_same<T,T2>::value>::type>
		vector<bool, S> operator<(const T2 aScalar) const throw() {
			vector<bool, S> tmp;
			for(uint32_t i = 0; i < S; ++i) tmp[i] = mElements[i] < aScalar;
			return tmp;
		}

		template<class T2 = T, typename ENABLE = typename std::enable_if<std::is_arithmetic<T2>::value || std::is_same<T,T2>::value>::type>
		vector<bool, S> operator>(const T2 aScalar) const throw() {
			vector<bool, S> tmp;
			for(uint32_t i = 0; i < S; ++i) tmp[i] = mElements[i] > aScalar;
			return tmp;
		}

		template<class T2 = T, typename ENABLE = typename std::enable_if<std::is_arithmetic<T2>::value || std::is_same<T,T2>::value>::type>
		vector<bool, S> operator<=(const T2 aScalar) const throw() {
			vector<bool, S> tmp;
			for(uint32_t i = 0; i < S; ++i) tmp[i] = mElements[i] <= aScalar;
			return tmp;
		}

		template<class T2 = T, typename ENABLE = typename std::enable_if<std::is_arithmetic<T2>::value || std::is_same<T, T2>::value>::type>
		vector<bool, S> operator>=(const T2 aScalar) const throw() {
			vector<bool, S> tmp;
			for (uint32_t i = 0; i < S; ++i) tmp[i] = mElements[i] >= aScalar;
			return tmp;
		}

		#if SOLAIRE_CPP_VER >= SOLAIRE_CPP_14 || SOLAIRE_CPP_VER < SOLAIRE_CPP_11
			SOLAIRE_CONSTEXPR_I14 T sum() const throw() {
				T sum = static_cast<T>(0);
				for(uint32_t i = 0; i < S; ++i) sum += mElements[i];
				return sum;
			}

			SOLAIRE_CONSTEXPR_I14 T magnitude_sq() const throw() {
				T mag = static_cast<T>(0);
				for(uint32_t i = 0; i < S; ++i) mag += mElements[i] * mElements[i];
				return mag;
			}
			SOLAIRE_CONSTEXPR_I14 bool operator==(const vector<T,S>& aOther) const throw() {
				for(uint32_t i = 0; i < S; ++i) if(mElements[i] != aOther[i]) return false;
				return true;
			}

			SOLAIRE_CONSTEXPR_I14 bool operator!=(const vector<T,S>& aOther) const throw() {
				for(uint32_t i = 0; i < S; ++i) if(mElements[i] != aOther[i]) return true;
				return false;
			}

			SOLAIRE_CONSTEXPR_I14 T dot_product(const vector<T, S>& aOther) const throw() {
				T dot = static_cast<T>(0);
				for(uint32_t i = 0; i < S; ++i) dot += mElements[i] * aOther[i];
				return dot;
			}
		#else
			SOLAIRE_CONSTEXPR_I11 T sum(const uint32_t aIndex = S - 1) const throw() {
				return aIndex == 0 ? mElements[0] : mElements[aIndex] + sum(aIndex - 1);
			}

			SOLAIRE_CONSTEXPR_I11 T magnitude_sq(const uint32_t aIndex = S - 1) const throw() {
				return aIndex == 0 ? mElements[0] * mElements[0] : mElements[aIndex] * mElements[aIndex] + magnitude_sq(aIndex - 1);
			}

			SOLAIRE_CONSTEXPR_I11 bool operator==(const vector<T,S>& aOther) const throw() {
				return _equals(aOther, S - 1);
			}

			SOLAIRE_CONSTEXPR_I11 bool operator!=(const vector<T,S>& aOther) const throw() {
				return ! _equals(aOther, S - 1);
			}

			SOLAIRE_CONSTEXPR_I11 T dot_product(const vector<T, S>& aOther, const uint32_t aIndex = S - 1) const throw() {
				return aIndex == 0 ? mElements[0] * aOther[0] : mElements[aIndex] * aOther[aIndex] + dotProduct(aOther, aIndex - 1);
			}
		#endif

		SOLAIRE_CONSTEXPR_I11 T average() const throw() {
			return sum() / static_cast<T>(S);
		}

		SOLAIRE_CONSTEXPR_I11 T magnitude() const throw() {
			return SOLAIRE_CONSTEXPR_sqrt(magnitude_sq());
		}

		inline vector<T,S> normalise() const throw() {
			return vector<T,S>(*this) /= this->magitude();
		}

		inline vector<T,S> normalise(const T aMagnitude) const throw() {
			return vector<T,S>(*this) /= aMagnitude;
		}

		template<class T2, const uint32_t S2>
		vector<T, S2> swizzle(const vector<T2, S2>& aIndices) const throw() {
			vector<T, S2> tmp;
			for(uint32_t i = 0; i < S2; ++i) tmp[i] = mElements[aIndices[i]];
			return tmp;
		}

		#if SOLAIRE_CPP_VER >= SOLAIRE_CPP_11
			template<class ...PARAMS>
			inline vector<T, sizeof...(PARAMS)> swizzle(const PARAMS... aParams) const throw() {
				return swizzle(vector<uint32_t, sizeof...(PARAMS)>(aParams...));
			}

			template<class T2 = T>
			SOLAIRE_CONSTEXPR_I11 typename std::enable_if<std::is_same<T2, T>::value && S == 3, vector<T,3>>::type
			cross_product(const vector<T,3>& aOther) const throw() {
				return vector<T,3>(
					mElements[1] * aOther[2] - mElements[2] * aOther[1],
					mElements[2] * aOther[0] - mElements[0] * aOther[2],
					mElements[0] * aOther[1] - mElements[1] * aOther[0]
				);
			}
		#endif

		vector<T, S>& operator+=(const T aScalar) throw() {
			for(uint32_t i = 0; i < S; ++i) mElements[i] += aScalar;
			return *this;
		}

		vector<T, S>& operator-=(const T aScalar) throw() {
			for(uint32_t i = 0; i < S; ++i) mElements[i] -= aScalar;
			return *this;
		}

		vector<T, S>& operator*=(const T aScalar) throw() {
			for(uint32_t i = 0; i < S; ++i) mElements[i] *= aScalar;
			return *this;
		}

		vector<T, S>& operator/=(const T aScalar) throw() {
			for(uint32_t i = 0; i < S; ++i) mElements[i] /= aScalar;
			return *this;
		}

		vector<T, S>& operator+=(const vector<T, S>& aOther) throw() {
			for(uint32_t i = 0; i < S; ++i) mElements[i] += aOther[i];
			return *this;
		}

		vector<T, S>& operator-=(const vector<T, S>& aOther) throw() {
			for(uint32_t i = 0; i < S; ++i) mElements[i] -= aOther[i];
			return *this;
		}

		vector<T, S>& operator*=(const vector<T, S>& aOther) throw() {
			for(uint32_t i = 0; i < S; ++i) mElements[i] *= aOther[i];
			return *this;
		}

		vector<T, S>& operator/=(const vector<T, S>& aOther) throw() {
			for(uint32_t i = 0; i < S; ++i) mElements[i] /= aOther[i];
			return *this;
		}

		inline vector<T, S> operator+(const T aScalar) const throw() {
			return vector<T,S>(*this) += aScalar;
		}

		inline vector<T, S> operator-(const T aScalar) const throw() {
			return vector<T,S>(*this) -= aScalar;
		}

		inline vector<T, S> operator*(const T aScalar) const throw() {
			return vector<T,S>(*this) *= aScalar;
		}

		inline vector<T, S> operator/(const T aScalar) const throw() {
			return vector<T,S>(*this) /= aScalar;
		}

		inline vector<T, S> operator+(const vector<T, S>& aOther) const throw() {
			return vector<T,S>(*this) += aOther;
		}

		inline vector<T, S> operator-(const vector<T, S>& aOther) const throw() {
			return vector<T,S>(*this) -= aOther;
		}

		inline vector<T, S> operator*(const vector<T, S>& aOther) const throw() {
			return vector<T,S>(*this) *= aOther;
		}

		inline vector<T, S> operator/(const vector<T, S>& aOther) const throw() {
			return vector<T,S>(*this) /= aOther;
		}

		#if SOLAIRE_CPP_VER >= SOLAIRE_CPP_11
			template<class T2 = T>
			typename std::enable_if<std::is_integral<T2>::value, vector<bool, S>&>::type
			operator &=(const vector<bool, S>& aOther) throw() {
				for(uint32_t i = 0; i < S; ++i) mElements[i] &= aOther[i];
				return *this;
			}

			template<class T2 = T>
			typename std::enable_if<std::is_integral<T2>::value, vector<bool, S>&>::type
			operator |=(const vector<T, S>& aOther) throw() {
				for(uint32_t i = 0; i < S; ++i) mElements[i] |= aOther[i];
				return *this;
			}

			template<class T2 = T>
			typename std::enable_if<std::is_integral<T2>::value, vector<bool, S>&>::type
			operator ^=(const vector<T, S>& aOther) throw() {
				for(uint32_t i = 0; i < S; ++i) mElements[i] ^= aOther[i];
				return *this;
			}

			template<class T2 = T>
			inline typename std::enable_if<std::is_integral<T2>::value, vector<bool, S>>::type
			operator &(const vector<T, S>& aOther) const throw() {
				return vector<T,S>(*this) &= aOther;
			}

			template<class T2 = T>
			inline typename std::enable_if<std::is_integral<T2>::value, vector<bool, S>>::type
			operator |(const vector<T, S>& aOther) const throw() {
				return vector<T,S>(*this) |= aOther;
			}

			template<class T2 = T>
			inline typename std::enable_if<std::is_integral<T2>::value, vector<bool, S>>::type
			operator ^(const vector<T, S>& aOther) const throw() {
				return vector<T,S>(*this) ^= aOther;
			}

			template<class T2 = T>
			typename std::enable_if<std::is_integral<T2>::value, vector<bool, S>&>::type
			operator &=(const T aScalar) throw() {
				for(uint32_t i = 0; i < S; ++i) mElements[i] &= aScalar;
				return *this;
			}

			template<class T2 = T>
			typename std::enable_if<std::is_integral<T2>::value, vector<bool, S>&>::type
			operator |=(const T aScalar) throw() {
				for(uint32_t i = 0; i < S; ++i) mElements[i] |= aScalar;
				return *this;
			}

			template<class T2 = T>
			typename std::enable_if<std::is_integral<T2>::value, vector<bool, S>&>::type
			operator ^=(const T aScalar) throw() {
				for(uint32_t i = 0; i < S; ++i) mElements[i] ^= aScalar;
				return *this;
			}

			template<class T2 = T>
			inline typename std::enable_if<std::is_integral<T2>::value, vector<bool, S>>::type
			operator &=(const T aScalar) const throw() {
				return vector<T,S>(*this) &= aScalar;
			}

			template<class T2 = T>
			inline typename std::enable_if<std::is_integral<T2>::value, vector<bool, S>>::type
			operator |=(const T aScalar) const throw() {
				return vector<T,S>(*this) |= aScalar;
			}

			template<class T2 = T>
			inline typename std::enable_if<std::is_integral<T2>::value, vector<bool, S>>::type
			operator ^=(const T aScalar) const throw() {
				return vector<T,S>(*this) ^= aScalar;
			}
		#endif

        inline T get_x() const {return mElements[0];}
        inline void set_x(const T aValue) const {mElements[0] = aValue;}
        inline T get_y() const {return mElements[1];}
        inline void set_y(const T aValue) const {mElements[1] = aValue;}
        inline T get_z() const {return mElements[2];}
        inline void set_z(const T aValue) const {mElements[2] = aValue;}
        inline T get_w() const {return mElements[3];}
        inline void set_w(const T aValue) const {mElements[3] = aValue;}
        #if SOLAIRE_COMPILER == SOLAIRE_MSVC
            __declspec(property(get=get_x, put=set_x)) T x;
            __declspec(property(get=get_y, put=set_y)) T y;
            __declspec(property(get=get_z, put=set_z)) T x;
            __declspec(property(get=get_w, put=set_w)) T w;
		#endif

	};

	template<class T, const uint32_t S>
	vector<T,S> operator+(const T aScalar, const vector<T,S>& aVector) throw() {
		vector<T,S> tmp;
		for(uint32_t i = 0; i < S; ++i) tmp[i] = aScalar + aVector[i];
		return tmp;
	}

	template<class T, const uint32_t S>
	vector<T,S> operator-(const T aScalar, const vector<T,S>& aVector) throw() {
		vector<T,S> tmp;
		for(uint32_t i = 0; i < S; ++i) tmp[i] = aScalar - aVector[i];
		return tmp;
	}

	template<class T, const uint32_t S>
	vector<T,S> operator*(const T aScalar, const vector<T,S>& aVector) throw() {
		vector<T,S> tmp;
		for(uint32_t i = 0; i < S; ++i) tmp[i] = aScalar * aVector[i];
		return tmp;
	}

	template<class T, const uint32_t S>
	vector<T,S> operator/(const T aScalar, const vector<T,S>& aVector) throw() {
		vector<T,S> tmp;
		for(uint32_t i = 0; i < S; ++i) tmp[i] = aScalar / aVector[i];
		return tmp;
	}

	template<class T, const uint32_t S>
	std::ostream& operator<<(std::ostream& aStream, const vector<T,S>& aVector) {
		aStream << '[';
		for(uint32_t i = 0; i < S; ++i) {
			aStream << aVector[i];
			if(i + 1 < S) aStream << ',';
		}
		return aStream << ']';
	}

	#define SOLAIRE_DEF_VECTORS(aNum)\
        template<class T>\
        using vector_ ## aNum = vector<T,aNum>;\
		typedef vector<char, aNum> vector_ ## aNum ## c;\
		typedef vector<bool, aNum> vector_ ## aNum ## b;\
		typedef vector<uint8_t, aNum> vector_ ## aNum ## u8;\
		typedef vector<uint16_t, aNum> vector_ ## aNum ## u16;\
		typedef vector<uint32_t, aNum> vector_ ## aNum ## u32;\
		typedef vector<uint64_t, aNum> vector_ ## aNum ## u64;\
		typedef vector<int8_t, aNum> vector_ ## aNum ## i8;\
		typedef vector<int16_t, aNum> vector_ ## aNum ## i16;\
		typedef vector<int32_t, aNum> vector_ ## aNum ## i32;\
		typedef vector<int64_t, aNum> vector_ ## aNum ## i64;\
		typedef vector<float, aNum> vector_ ## aNum ## f;\
		typedef vector<double, aNum> vector_ ## aNum ## d;\
		typedef vector<unsigned int, aNum> vector_ ## aNum ##u;\
		typedef vector<int, aNum> vector_ ## aNum ##i;

	SOLAIRE_DEF_VECTORS(2)
	SOLAIRE_DEF_VECTORS(3)
	SOLAIRE_DEF_VECTORS(4)
	SOLAIRE_DEF_VECTORS(5)
	SOLAIRE_DEF_VECTORS(6)
	SOLAIRE_DEF_VECTORS(7)
	SOLAIRE_DEF_VECTORS(8)
	SOLAIRE_DEF_VECTORS(16)
	SOLAIRE_DEF_VECTORS(32)
	SOLAIRE_DEF_VECTORS(64)
	typedef vector_3u8 vector_rgb;
	typedef vector_4u8 vector_rgba;

	#undef SOLAIRE_DEF_VECTORS
}

#define SOLAIRE_VECTORISE_FUNCTION_V(aReturn, aName, aParam)\
    template<const uint32_t S>\
    solaire::vector<aReturn, S> aName(const solaire::vector<aParam, S>& aInput1) {\
        solaire::vector<aReturn, S> output;\
        for(uint32_t i = 0; i < S; ++i) output[i] = aName(aInput1[i]);\
        return output;\
    }

#define SOLAIRE_VECTORISE_FUNCTION_VS(aReturn, aName, aParam)\
    template<const uint32_t S>\
    solaire::vector<aReturn, S> aName(const solaire::vector<aParam, S>& aInput1, const aParam aInput2) {\
        solaire::vector<aReturn, S> output;\
        for(uint32_t i = 0; i < S; ++i) output[i] = aName(aInput1[i], aInput2);\
        return output;\
    }

#define SOLAIRE_VECTORISE_FUNCTION_SV(aReturn, aName, aParam)\
    template<const uint32_t S>\
    solaire::vector<aReturn, S> aName(const aParam aInput1, const solaire::vector<aParam, S>& aInput2) {\
        solaire::vector<aReturn, S> output;\
        for(uint32_t i = 0; i < S; ++i) output[i] = aName(aInput1, aInput2[i]);\
        return output;\
    }

#define SOLAIRE_VECTORISE_FUNCTION_VV(aReturn, aName, aParam)\
    template<const uint32_t S>\
    solaire::vector<aReturn, S> aName(const solaire::vector<aParam, S>& aInput1, const solaire::vector<aParam, S>& aInput2) {\
        solaire::vector<aReturn, S> output;\
        for(uint32_t i = 0; i < S; ++i) output[i] = aName(aInput1[i], aInput2[i]);\
        return output;\
    }

    ////

#define SOLAIRE_VECTORISE_FUNCTION_1(aReturn, aName, aParam)\
    SOLAIRE_VECTORISE_FUNCTION_V(aReturn, aName, aParam)

#define SOLAIRE_VECTORISE_FUNCTION_2(aReturn, aName, aParam, aParam2)\
    SOLAIRE_VECTORISE_FUNCTION_VV(aReturn, aName, aParam)\
    SOLAIRE_VECTORISE_FUNCTION_VS(aReturn, aName, aParam)\
    SOLAIRE_VECTORISE_FUNCTION_SV(aReturn, aName, aParam)

#define SOLAIRE_VECTORISE_FUNCTION_T(aReturn, aName, aParam)\
    template<class Tconst uint32_t S>\
    solaire::vector<aReturn, S> aName(const solaire::vector<aParam, S>& aInput) {\
        solaire::vector<aReturn, S> output;\
        for(uint32_t i = 0; i < S; ++i) output[i] = aName(aInput[i]);\
        return output;\
    }

#define SOLAIRE_VECTORISE_FUNCTION_2T(aReturn, aName, aParam, aParam2)\
    template<class T, const uint32_t S>\
    solaire::vector<aReturn, S> aName(const solaire::vector<aParam, S>& aInput1, const solaire::vector<aParam2, S>& aInput2) {\
         solaire::vector<aReturn, S> output;\
        for(uint32_t i = 0; i < S; ++i) output[i] = aName(aInput1[i], aInput2[i]);\
        return output;\
    }

namespace std {
    SOLAIRE_VECTORISE_FUNCTION_1(float, sqrt, float);
    SOLAIRE_VECTORISE_FUNCTION_1(double, sqrt, double);
    SOLAIRE_VECTORISE_FUNCTION_1(float, cbrt, float);
    SOLAIRE_VECTORISE_FUNCTION_1(double, cbrt, double);
    SOLAIRE_VECTORISE_FUNCTION_1(float, floor, float);
    SOLAIRE_VECTORISE_FUNCTION_1(double, floor, double);
    SOLAIRE_VECTORISE_FUNCTION_1(float, ceil, float);
    SOLAIRE_VECTORISE_FUNCTION_1(double, ceil, double);
    SOLAIRE_VECTORISE_FUNCTION_1(int8_t, abs, int8_t);
    SOLAIRE_VECTORISE_FUNCTION_1(int16_t, abs, int16_t);
    SOLAIRE_VECTORISE_FUNCTION_1(int32_t, abs, int32_t);
    SOLAIRE_VECTORISE_FUNCTION_1(int64_t, abs, int64_t);
    SOLAIRE_VECTORISE_FUNCTION_1(float, abs, float);
    SOLAIRE_VECTORISE_FUNCTION_1(double, abs, double);
    SOLAIRE_VECTORISE_FUNCTION_1(float, cos, float);
    SOLAIRE_VECTORISE_FUNCTION_1(double, cos, double);
    SOLAIRE_VECTORISE_FUNCTION_1(float, sin, float);
    SOLAIRE_VECTORISE_FUNCTION_1(double, sin, double);
    SOLAIRE_VECTORISE_FUNCTION_1(float, tan, float);
    SOLAIRE_VECTORISE_FUNCTION_1(double, tan, double);
    SOLAIRE_VECTORISE_FUNCTION_1(float, acos, float);
    SOLAIRE_VECTORISE_FUNCTION_1(double, acos, double);
    SOLAIRE_VECTORISE_FUNCTION_1(float, asin, float);
    SOLAIRE_VECTORISE_FUNCTION_1(double, asin, double);
    SOLAIRE_VECTORISE_FUNCTION_1(float, atan, float);
    SOLAIRE_VECTORISE_FUNCTION_1(double, atan, double);
    SOLAIRE_VECTORISE_FUNCTION_1(float, exp, float);
    SOLAIRE_VECTORISE_FUNCTION_1(double, exp, double);
    SOLAIRE_VECTORISE_FUNCTION_1(float, log, float);
    SOLAIRE_VECTORISE_FUNCTION_1(double, log, double);
    SOLAIRE_VECTORISE_FUNCTION_1(float, log10, float);
    SOLAIRE_VECTORISE_FUNCTION_1(double, log10, double);
    SOLAIRE_VECTORISE_FUNCTION_1(float, log2, float);
    SOLAIRE_VECTORISE_FUNCTION_1(double, log2, double);
    //SOLAIRE_VECTORISE_FUNCTION_1(int32_t, strlen, const char*);

    SOLAIRE_VECTORISE_FUNCTION_2(float, pow, float, float);
    SOLAIRE_VECTORISE_FUNCTION_2(double, pow, double, double);
    SOLAIRE_VECTORISE_FUNCTION_2(float, remainder, float, float);
    SOLAIRE_VECTORISE_FUNCTION_2(double, remainder, double, double);
    SOLAIRE_VECTORISE_FUNCTION_2(float, fmod, float, float);
    SOLAIRE_VECTORISE_FUNCTION_2(double, fmod, double, double);
    SOLAIRE_VECTORISE_FUNCTION_2(float, atan2, float, float);
    SOLAIRE_VECTORISE_FUNCTION_2(double, atan2, double, double);
    //SOLAIRE_VECTORISE_FUNCTION_2(int32_t, strcmp, const char*, const char*);
    SOLAIRE_VECTORISE_FUNCTION_2T(T, min, T, T);
    SOLAIRE_VECTORISE_FUNCTION_2T(T, max, T, T);
}

#endif