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

class default_randomiser : public solaire::randomiser {
private:
	// inherited from randomiser
	double random_normal() throw() override {
		return static_cast<double>(rand()) / static_cast<double>(RAND_MAX);
	}
public:
	default_randomiser() {

	}

	// inherited from randomiser
	uint64_t get_seed() const throw() override {
		//! \todo Implement default_randomiser.get_seed()
		return 0;
	}

	void set_seed(const uint64_t aSeed) throw() override {
		srand(aSeed);
	}

};

#if SOLAIRE_COMPILE_MODE != SOLAIRE_SHARED_IMPORT_COMPILE
solaire::randomiser* CURRENT_RANDOMISER = nullptr;

extern "C" SOLAIRE_EXPORT_API void SOLAIRE_EXPORT_CALL solaire_set_randomiser(solaire::randomiser* aAllocator) {
	CURRENT_RANDOMISER = aAllocator;
}

extern "C" SOLAIRE_EXPORT_API solaire::randomiser* SOLAIRE_EXPORT_CALL solaire_get_randomiser() {
	if (CURRENT_RANDOMISER == nullptr) CURRENT_RANDOMISER = solaire_get_default_randomiser();
	return CURRENT_RANDOMISER;
}

extern "C" SOLAIRE_EXPORT_API solaire::randomiser* SOLAIRE_EXPORT_CALL solaire_get_default_randomiser() {
	static default_randomiser DEFAULT_RANDOMISER;
	return &DEFAULT_RANDOMISER;
}
#endif