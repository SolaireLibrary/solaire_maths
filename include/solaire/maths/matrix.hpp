#ifndef SOLAIRE_MATRIX_HPP
#define SOLAIRE_MATRIX_HPP

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

#include "solaire/maths/vector.hpp"

namespace solaire {

	template<class T, const uint32_t W, const uint32_t H>
	class matrix {
	public:
		typedef T type;
		enum{
			WIDTH = W,
			HEIGHT = H
		};
		typedef vector<T,W> row_t;
		typedef vector<T,H> column_t;
	private:
		type mElements[W * H];
	public:
		template<class ...PARAMS>
		matrix(const PARAMS... aParams) :
			mElements{aParams...}
		{
			static_assert(sizeof...(PARAMS) == 0 || sizeof...(PARAMS) == W * H, "solaire::matrix : Parameter count must be equal to matrix dimensions");
			if(sizeof...(PARAMS) == 0) {
				for(uint32_t i = 0; i < W; ++i) {
					for(uint32_t j = 0; j < H; ++j) {
						mElements[i * W + j] = static_cast<T>(i == j ? 1 : 0);
					}
				}
			}
		}

		inline T* operator[](const uint32_t aIndex) throw() {
			return mElements + aIndex * W;
		}

		inline const T* operator[](const uint32_t aIndex) const throw() {
			return mElements + aIndex * W;
		}

		row_t get_row(const uint32_t aIndex) const throw() {
			return *reinterpret_cast<const row_t*>(mElements + aIndex * W);
		}

		column_t get_column(const uint32_t aIndex) const throw() {
			column_t tmp;
			for(uint32_t i = 0; i < H; ++i) tmp[i] = mElements[i * W + aIndex];
			return tmp;
		}

		matrix<T,H,W> transpose() const throw() {
			matrix<T,H,W> tmp;
			for(uint32_t i = 0; i < W; ++i) {
				for(uint32_t j = 0; j < H; ++j) {
					tmp[j][i] = mElements[i * W + j];
				}
			}
			return tmp;
		}

		matrix<T,W,H>& operator+=(const matrix<T,W,H>& aOther) {
			for(uint32_t i = 0; i < W*H; ++i) mElements[i] += aOther.mElements[i];
			return *this;
		}

		matrix<T,W,H>& operator-=(const matrix<T,W,H>& aOther) {
			for(uint32_t i = 0; i < W*H; ++i) mElements[i] -= aOther.mElements[i];
			return *this;
		}

		template<const uint32_t W2, const uint32_t H2>
		matrix<T,W,H>& operator*=(const matrix<T,W2,H2>& aOther) {
			static_assert(W == H2, "solaire::matrix::operator* : Matrix dimension mismatch");
			row_t rows[H];
			column_t columns[W2];

			for(uint32_t i = 0; i < H; ++i) rows[i] = get_row(i);
			for(uint32_t i = 0; i < W2; ++i) columns[i] = aOther.get_column(i);

			for(uint32_t i = 0; i < H; ++i) {
				for(uint32_t j = 0; j < W2; ++j) {
					mElements[i * W + j] = rows[i].dot_product(columns[j]);
				}
			}
			return *this;
		}

		matrix<T,W,H>& operator+=(const T aScalar) {
			for(uint32_t i = 0; i < W*H; ++i) mElements[i] += aScalar;
			return *this;
		}

		matrix<T,W,H>& operator-=(const T aScalar) {
			for(uint32_t i = 0; i < W*H; ++i) mElements[i] -= aScalar;
			return *this;
		}

		matrix<T,W,H>& operator*=(const T aScalar) {
			for(uint32_t i = 0; i < W*H; ++i) mElements[i] *= aScalar;
			return *this;
		}

		matrix<T,W,H>& operator/=(const T aScalar) {
			for(uint32_t i = 0; i < W*H; ++i) mElements[i] /= aScalar;
			return *this;
		}

		inline matrix<T,W,H> operator+(const matrix<T,W,H>& aOther) const throw() {
			return matrix<T,W,H>(*this) += aOther;
		}

		inline matrix<T,W,H> operator-(const matrix<T,W,H>& aOther) const throw() {
			return matrix<T,W,H>(*this) -= aOther;
		}

		inline matrix<T,W,H> operator*(const matrix<T,W,H>& aOther) const throw() {
			return matrix<T,W,H>(*this) *= aOther;
		}

		inline matrix<T,W,H> operator+(const T aScalar) const throw() {
			return matrix<T,W,H>(*this) += aScalar;
		}

		inline matrix<T,W,H> operator-(const T aScalar) const throw() {
			return matrix<T,W,H>(*this) -= aScalar;
		}

		inline matrix<T,W,H> operator*(const T aScalar) const throw() {
			return matrix<T,W,H>(*this) *= aScalar;
		}

		inline matrix<T,W,H> operator/(const T aScalar) const throw() {
			return matrix<T,W,H>(*this) /= aScalar;
		}
	};

	//#define SOLAIRE_DEF_MATRICES2(aWidth, aHeight)\
  //      template<class T>\
  //      using matrix_ ## aWidth ## x ## aHeight = matrix<T, aWidth, aHeight>;\
		//typedef matrix<char, aWidth, aHeight> matrix_ ## aWidth ## x ## aHeight ## c;\
		//typedef matrix<bool, aWidth, aHeight> matrix_ ## aWidth ## x ## aHeight ## b;\
		//typedef matrix<uint8_t, aWidth, aHeight> matrix_ ## aWidth ## x ## aHeight ## u8;\
		//typedef matrix<uint16_t, aWidth, aHeight> matrix_ ## aWidth ## x ## aHeight ## u16;\
		//typedef matrix<uint32_t, aWidth, aHeight> matrix_ ## aWidth ## x ## aHeight ## u32;\
		//typedef matrix<uint64_t, aWidth, aHeight> matrix_ ## aWidth ## x ## aHeight ## u64;\
		//typedef matrix<int8_t, aWidth, aHeight> matrix_ ## aWidth ## x ## aHeight ## i8;\
		//typedef matrix<int16_t, aWidth, aHeight> matrix_ ## aWidth ## x ## aHeight ## i16;\
		//typedef matrix<int32_t, aWidth, aHeight> matrix_ ## aWidth ## x ## aHeight ## i32;\
		//typedef matrix<int64_t, aWidth, aHeight> matrix_ ## aWidth ## x ## aHeight ## i64;\
		//typedef matrix<float, aWidth, aHeight> matrix_ ## aWidth ## x ## aHeight ## f;\
		//typedef matrix<double, aWidth, aHeight> matrix_ ## aWidth ## x ## aHeight ## d;\
		//typedef matrix<unsigned int, aWidth, aHeight> matrix_ ## aWidth ## x ## aHeight ##u;\
		//typedef matrix<int, aWidth, aHeight> matrix_ ## aWidth ## x ## aHeight ##i;

	//#define SOLAIRE_DEF_MATRICES(aHeight)
	//	SOLAIRE_DEF_MATRICES2(2, aHeight)
	//	SOLAIRE_DEF_MATRICES2(3, aHeight)
	//	SOLAIRE_DEF_MATRICES2(4, aHeight)
	//	SOLAIRE_DEF_MATRICES2(5, aHeight)
	//	SOLAIRE_DEF_MATRICES2(6, aHeight)
	//	SOLAIRE_DEF_MATRICES2(7, aHeight)
	//	SOLAIRE_DEF_MATRICES2(8, aHeight)
	//	SOLAIRE_DEF_MATRICES2(16, aHeight)
	//	SOLAIRE_DEF_MATRICES2(32, aHeight)
	//	SOLAIRE_DEF_MATRICES2(64, aHeight)

	//SOLAIRE_DEF_MATRICES(2)
	//SOLAIRE_DEF_MATRICES(3)
	//SOLAIRE_DEF_MATRICES(4)
	//SOLAIRE_DEF_MATRICES(5)
	//SOLAIRE_DEF_MATRICES(6)
	//SOLAIRE_DEF_MATRICES(7)
	//SOLAIRE_DEF_MATRICES(8)
	//SOLAIRE_DEF_MATRICES(16)
	//SOLAIRE_DEF_MATRICES(32)
	//SOLAIRE_DEF_MATRICES(64)

	//#undef SOLAIRE_DEF_MATRICES2
	//#undef SOLAIRE_DEF_MATRICES
}

#endif