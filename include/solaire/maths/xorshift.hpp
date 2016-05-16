#ifndef SOLAIRE_XORSHIFT_HPP
#define SOLAIRE_XORSHIFT_HPP

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

#include "solaire/maths/randomiser.hpp"

extern "C" SOLAIRE_EXPORT_API uint64_t SOLAIRE_EXPORT_CALL solaire_xorshift_star(uint64_t*);
extern "C" SOLAIRE_EXPORT_API uint64_t SOLAIRE_EXPORT_CALL solaire_xorshift_plus(uint64_t*);

namespace solaire {

	inline uint64_t xorshift_star(uint64_t& aSeed) {
		solaire_xorshift_star(&aSeed);
	}

	inline uint64_t xorshift_plus(uint64_t* const aSeed) {
		solaire_xorshift_plus(aSeed);
	}

	SOLAIRE_EXPORT_CLASS xorshift_star_randomiser : public randomiser{
	private:
		uint64_t mSeed;
	protected:
		// inherited from randomiser
		SOLAIRE_INTERFACE_CALL double random_normal() throw() override {
			return xorshift_star(mSeed);
		}
	public:
		xorshift_star_randomiser() :
			mSeed(rand())
		{}

		xorshift_star_randomiser(const uint64_t aSeed) :
			mSeed(aSeed)
		{}

		// inherited from randomiser
		uint64_t SOLAIRE_INTERFACE_CALL get_seed() const throw() override {
			return mSeed;
		}

		void SOLAIRE_INTERFACE_CALL set_seed(const uint64_t aSeed) throw() override {
			mSeed = aSeed;
		}
	};

	SOLAIRE_EXPORT_CLASS xorshift_plus_randomiser : public randomiser{
	private:
		uint64_t mSeed[2];
	protected:
		// inherited from randomiser
		SOLAIRE_INTERFACE_CALL double random_normal() throw() override {
			return xorshift_plus(mSeed);
		}
	public:
		xorshift_plus_randomiser() {
			mSeed[0] = rand();
			mSeed[1] = ~mSeed[0];
		}

		xorshift_plus_randomiser(const uint64_t aSeed) {
			mSeed[0] = aSeed;
			mSeed[1] = ~aSeed;
		}

		// inherited from randomiser
		uint64_t SOLAIRE_INTERFACE_CALL get_seed() const throw() override {
			return mSeed[0];
		}

		void SOLAIRE_INTERFACE_CALL set_seed(const uint64_t aSeed) throw() override {
			mSeed[0] = aSeed;
			mSeed[1] = ~aSeed;
		}
	};
}

#endif