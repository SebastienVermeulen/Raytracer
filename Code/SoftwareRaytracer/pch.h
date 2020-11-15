#pragma once
#define _USE_MATH_DEFINES
#define MIN_OFFSET 0.001f

#include <iostream>
#include <time.h> 
#include <chrono>
#include <SDL.h>
#undef main

#include "MathLib.h"
//Materials
#include "Material.h"
#include "LambertDiffuse.h"
#include "Metal.h"
#include "Dielectric.h"


// Utility Functions
inline float DegreesToRadians(const float degrees)
{
    return degrees * (float)M_PI / 180.0f;
}
inline float RadiansToDegrees(const float radians)
{
    return radians * 180.0f / (float)M_PI;
}

inline float Clamp(const float value, const float min, const float max)
{
    return std::min(std::max(value, min), max);
}
inline vec3 Clamp(const vec3& value, const float min, const float max)
{
    vec3 temp{};
    temp[0] = Clamp(value[0], min, max);
    temp[1] = Clamp(value[1], min, max);
    temp[2] = Clamp(value[2], min, max);
    return temp;
}

//Random
inline float RandomFloat()
{
    return rand() / ((float)RAND_MAX + 1.0f);
}
inline float RandomInRange(const float min, const float max)
{
    float random = rand() / ((float)RAND_MAX + 1.0f);
    return random * (max - min) + min;
}

//Random
inline vec3 RandomVec3()
{
    return { RandomFloat(), RandomFloat(), RandomFloat() };
}
inline vec3 RandomVec3InRange(const float min, const float max)
{
    return { RandomInRange(min, max), RandomInRange(min, max), RandomInRange(min, max) };
}

/// <summary>
/// Returns a point in the unit sphere using a simple method.
/// Not all function calls will take the same amount of time.
/// </summary>
/// <returns>A Random Point In a Unit Sphere</returns>
inline vec3 RandomPointInSphere()
{
    vec3 point{};
    while (true) 
    {
        point = RandomVec3();
        if (point.SquareMagnitude() <= 1.f)
        {
            return point;
        }
    }
}
inline vec3 RandomPointInUnitSphere()
{
    return RandomPointInSphere().Normalised();
}
inline vec3 RandomPointInDisk() 
{
    while (true)
    {
        vec3 point = vec3(RandomInRange(-1.f, 1.f), RandomInRange(-1.f, 1.f), 0.f);
        if (point.SquareMagnitude() >= 1)
        {
            continue;
        }
        return point;
    }
}
inline vec3 RandomPointInUnitDisk()
{
    return RandomPointInDisk().Normalised();
}
