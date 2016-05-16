#ifndef SOLAIRE_RANDOMISER_HPP
#define SOLAIRE_RANDOMISER_HPP

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
	SOLAIRE_EXPORT_INTERFACE randomiser{
	protected:
		virtual SOLAIRE_INTERFACE_CALL double random_normal() throw() = 0;
	public:
		virtual SOLAIRE_INTERFACE_CALL ~randomiser() throw() {}

		virtual uint64_t SOLAIRE_INTERFACE_CALL get_seed() const throw() = 0;
		virtual void SOLAIRE_INTERFACE_CALL set_seed(const uint64_t) throw() = 0;

		inline double next_d(const double aMin, const double aMax) throw() {
			const double n = random_normal();
			return (n * aMin) + (n * aMax);
		}

		inline double next_d() throw() {
			return next_d(DBL_MIN, DBL_MAX);
		}

		#define SOLAIRE_GENERATE_RANDOM(T, POSTFIX, MIN, MAX)\
			inline T next_ ## POSTFIX(const T aMin, const T aMax) throw() {\
				return static_cast<T>(next_d(static_cast<double>(aMin), static_cast<double>(aMax)));\
			}\
			inline T next_ ## POSTFIX(const T aMax) throw() {\
				return next_ ## POSTFIX(static_cast<T>(0), aMax);\
			}\
			inline T next_ ## POSTFIX() throw() {\
				return next_ ## POSTFIX(MIN, MAX);\
			}

		SOLAIRE_GENERATE_RANDOM(uint8_t, 8u, 0, UINT8_MAX);
		SOLAIRE_GENERATE_RANDOM(uint16_t, 16u, 0, UINT16_MAX);
		SOLAIRE_GENERATE_RANDOM(uint32_t, 32u, 0, UINT32_MAX);
		SOLAIRE_GENERATE_RANDOM(uint64_t, 64u, 0, UINT64_MAX);
		SOLAIRE_GENERATE_RANDOM(int8_t, 8i, INT8_MIN, INT8_MAX);
		SOLAIRE_GENERATE_RANDOM(int16_t, 16i, INT16_MIN, INT16_MAX);
		SOLAIRE_GENERATE_RANDOM(int32_t, 32i, INT32_MIN, INT32_MAX);
		SOLAIRE_GENERATE_RANDOM(int64_t, 64i, INT64_MIN, INT64_MAX);
		SOLAIRE_GENERATE_RANDOM(float, f, FLT_MIN, FLT_MAX);

		#undef SOLAIRE_GENERATE_RANDOM
	};
}

extern "C" SOLAIRE_EXPORT_API void SOLAIRE_EXPORT_CALL solaire_set_randomiser(solaire::randomiser*);
extern "C" SOLAIRE_EXPORT_API solaire::randomiser* SOLAIRE_EXPORT_CALL solaire_get_randomiser();
extern "C" SOLAIRE_EXPORT_API solaire::randomiser* SOLAIRE_EXPORT_CALL solaire_get_default_randomiser();

namespace solaire {

	inline void set_randomiser(solaire::randomiser& aRandomiser) {
		solaire_set_randomiser(&aRandomiser);
	}

	inline solaire::randomiser& get_randomiser() {
		return *solaire_get_randomiser();
	}

	inline solaire::randomiser& get_default_randomiser() {
		return *solaire_get_default_randomiser();
	}

	template<class T>
	static T generate_random();

	template<class T>
	static T generate_random(const T aMin, const T aMax);

	#define SOLAIRE_GENERATE_RANDOM(T, POSTFIX)\
		template<>\
		static T generate_random<T>() {\
			return get_randomiser().next_ ## POSTFIX();\
		}\
		template<>\
		static T generate_random<T>(const T aMin, const T aMax) {\
			return get_randomiser().next_ ## POSTFIX(aMin, aMax);\
		}

	SOLAIRE_GENERATE_RANDOM(uint8_t, 8u);
	SOLAIRE_GENERATE_RANDOM(uint16_t, 16u);
	SOLAIRE_GENERATE_RANDOM(uint32_t, 32u);
	SOLAIRE_GENERATE_RANDOM(uint64_t, 64u);
	SOLAIRE_GENERATE_RANDOM(int8_t, 8i);
	SOLAIRE_GENERATE_RANDOM(int16_t, 16i);
	SOLAIRE_GENERATE_RANDOM(int32_t, 32i);
	SOLAIRE_GENERATE_RANDOM(int64_t, 64i);
	SOLAIRE_GENERATE_RANDOM(float, f);
	SOLAIRE_GENERATE_RANDOM(double, d);

	#undef SOLAIRE_GENERATE_RANDOM
}

#endif