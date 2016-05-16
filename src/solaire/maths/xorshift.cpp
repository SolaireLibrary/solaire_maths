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

#include "solaire/maths/xorshift.hpp"

#if SOLAIRE_COMPILE_MODE != SOLAIRE_SHARED_IMPORT_COMPILE

extern "C" SOLAIRE_EXPORT_API uint64_t SOLAIRE_EXPORT_CALL solaire_xorshift_star(uint64_t* aSeed) {
	uint64_t& x = *aSeed;
	x ^= x >> 12L;
	x ^= x << 25L;
	x ^= x >> 27L;
	return x * 2685821657736338717L;
}

extern "C" SOLAIRE_EXPORT_API uint64_t SOLAIRE_EXPORT_CALL solaire_xorshift_plus(uint64_t* aSeed) {
	uint64_t x = aSeed[0];
	uint64_t const y = aSeed[1];
	aSeed[0] = y;
	x ^= x << 23L;
	aSeed[1] = x ^ y ^ (x >> 17L) ^ (y >> 26L);
	return aSeed[1] + y;
}

#endif