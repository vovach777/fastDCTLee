#pragma once
/*
 * Fast discrete cosine transform algorithms (C++)
 *
 * Copyright (c) 2019 Project Nayuki. (MIT License)
 * https://www.nayuki.io/page/fast-discrete-cosine-transform-algorithms
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy of
 * this software and associated documentation files (the "Software"), to deal in
 * the Software without restriction, including without limitation the rights to
 * use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of
 * the Software, and to permit persons to whom the Software is furnished to do so,
 * subject to the following conditions:
 * - The above copyright notice and this permission notice shall be included in
 *   all copies or substantial portions of the Software.
 * - The Software is provided "as is", without warranty of any kind, express or
 *   implied, including but not limited to the warranties of merchantability,
 *   fitness for a particular purpose and noninfringement. In no event shall the
 *   authors or copyright holders be liable for any claim, damages or other
 *   liability, whether in an action of contract, tort or otherwise, arising from,
 *   out of or in connection with the Software or the use or other dealings in the
 *   Software.
 */

#include <cstddef>
#include <cmath>
#include <stdexcept>
#include <vector>



inline void forwardTransform_normalization(float vec[], std::size_t len) {
    vec[0] *= float(1.0/len);
    float scale = float(2.0/len);
    for (int i = 1; i < len; ++i)
    {
        vec[i] *= scale;
    }
}

inline void forwardTransform(float * vec, float * temp,  size_t len) {
	if (len == 1)
		return;

	size_t halfLen = len / 2;
	for (size_t i = 0; i < halfLen; i++) {
		float x = vec[i];
		float y = vec[len - 1 - i];
		temp[i] = x + y;
		temp[i + halfLen] = (x - y) / (std::cos((i + 0.5) * M_PI / len) * 2);
	}
	forwardTransform(temp, vec, halfLen);
	forwardTransform(&temp[halfLen], vec, halfLen);
	for (size_t i = 0; i < halfLen - 1; i++) {
		vec[i * 2 + 0] = temp[i];
		vec[i * 2 + 1] = temp[i + halfLen] + temp[i + halfLen + 1];
	}
	vec[len - 2] = temp[halfLen - 1];
	vec[len - 1] = temp[len - 1];
}


inline void inverseTransform(float * vec, float * temp, size_t len) {
	if (len == 1)
		return;
	size_t halfLen = len / 2;
	temp[0] = vec[0];
	temp[halfLen] = vec[1];
	for (size_t i = 1; i < halfLen; i++) {
		temp[i] = vec[i * 2];
		temp[i + halfLen] = vec[i * 2 - 1] + vec[i * 2 + 1];
	}
	inverseTransform(temp, vec, halfLen);
	inverseTransform(&temp[halfLen], vec, halfLen);
	for (size_t i = 0; i < halfLen; i++) {
		float x = temp[i];
		float y = temp[i + halfLen] / (std::cos((i + 0.5) * M_PI / len) * 2);
		vec[i] = x + y;
		vec[len - 1 - i] = x - y;
	}
}

inline auto g_temp_1 =  std::vector<float>();
inline auto g_temp_2 =  std::vector<float>();

template <typename Array2D>
inline void DCT2D(Array2D && vecvec, size_t width, size_t height) {

    if (g_temp_1.size() < std::max(width,height) )
    {
        g_temp_1.resize(std::max(width,height));
        g_temp_2.resize(std::max(width,height));
    }

    for (size_t h=0; h<height; ++h)
    {
        for (size_t i = 0; i < width; ++i)
            g_temp_1[i] = vecvec[h][i];
        forwardTransform(&g_temp_1[0],&g_temp_2[0],width);
        forwardTransform_normalization(&g_temp_1[0],width);
        for (size_t i = 0; i < width; ++i)
            vecvec[h][i] = g_temp_1[i];
    }


    for (size_t w=0; w<width; ++w)
    {
        for (size_t i = 0; i < height; ++i)
            g_temp_1[i] = vecvec[i][w];
        forwardTransform(&g_temp_1[0],&g_temp_2[0],height);
        forwardTransform_normalization(&g_temp_1[0],height);
        for (size_t i = 0; i < height; ++i)
            vecvec[i][w] = g_temp_1[i];
    }

}


template <typename Array2D>
inline void iDCT2D(Array2D && vecvec, size_t width, size_t height) {

    if (g_temp_1.size() < std::max(width,height) )
    {
        g_temp_1.resize(std::max(width,height));
        g_temp_2.resize(std::max(width,height));
    }

    for (size_t w=0; w<width; ++w)
    {
        for (size_t i = 0; i < height; ++i)
            g_temp_1[i] = vecvec[i][w];
        inverseTransform(&g_temp_1[0],&g_temp_2[0],height);
        for (size_t i = 0; i < height; ++i)
            vecvec[i][w] = g_temp_1[i];
    }

    for (size_t h=0; h<height; ++h)
    {
        for (size_t i = 0; i < width; ++i)
            g_temp_1[i] = vecvec[h][i];
        inverseTransform(&g_temp_1[0],&g_temp_2[0],width);
        for (size_t i = 0; i < width; ++i)
            vecvec[h][i] = g_temp_1[i];
    }

}

