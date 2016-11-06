/*
 * Definitions.h
 * RVO2-3D Library
 *
 * Copyright 2008 University of North Carolina at Chapel Hill
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 *
 * Please send all bug reports to <geom@cs.unc.edu>.
 *
 * The authors may be contacted via:
 *
 * Jur van den Berg, Stephen J. Guy, Jamie Snape, Ming C. Lin, Dinesh Manocha
 * Dept. of Computer Science
 * 201 S. Columbia St.
 * Frederick P. Brooks, Jr. Computer Science Bldg.
 * Chapel Hill, N.C. 27599-3175
 * United States of America
 *
 * <http://gamma.cs.unc.edu/RVO2/>
 */

/**
 * \file   Definitions.h
 * \brief  Contains functions and constants used in multiple classes.
 */

#ifndef RVO_DEFINITIONS_H_
#define RVO_DEFINITIONS_H_

#include <assert.h>
#include <malloc.h>

#include "API.h"

namespace RVO {
	/**
	 * \brief   Computes the square of a float.
	 * \param   scalar  The float to be squared.
	 * \return  The square of the float.
	 */
	inline float sqr(float scalar)
	{
		return scalar * scalar;
	}

	template<typename T>
	inline T max(T a, T b) {
		return a >= b ? a : b;
	}

	template<typename T>
	inline T min(T a, T b) {
		return a <= b ? a : b;
	}

	template<typename T>
	inline void swap(T &a, T &b) {
		T temp = a;
		a = b;
		b = temp;
	}

	template<typename A, typename B>
	struct Pair {
		A first;
		B second;
	};

	template<typename A, typename B>
	inline Pair<A, B> make_pair(A a, B b) {
		Pair<A, B> p;
		p.first = a;
		p.second = b;
		return p;
	}

	template<typename T>
	class Vector {
            Vector(const Vector &);
            Vector &operator=(const Vector &);
            
		size_t count;
		size_t capacity;
		T *data;

	public:
		Vector() : count(0), capacity(0), data(NULL) {
		}

		~Vector() {
			free(data);
		}

		size_t size() const {
			return count;
		}

		bool empty() {
			return count == 0;
		}

		T back() const {
			assert(count > 0);
			return data[count - 1];
		}

		T operator[](size_t i) const {
			assert(i < count);
			return data[i];
		}

		T &operator[](size_t i) {
			assert(i < count);
			return data[i];
		}

		void clear() {
			count = 0;
		}

		void resize(size_t new_count) {
			count = new_count;
			while (new_count > capacity) {
				capacity = capacity ? capacity * 2 : 16;
			}
			data = (T *)realloc(data, sizeof(T) * capacity);
		}

		void push_back(T value) {
			if (count == capacity) {
				capacity = capacity ? capacity * 2 : 16;
				data = (T *)realloc(data, sizeof(T) * capacity);
			}
			data[count++] = value;
		}

		void pop_back() {
			assert(count > 0);
			--count;
		}
	};
}

#endif /* RVO_DEFINITIONS_H_ */
