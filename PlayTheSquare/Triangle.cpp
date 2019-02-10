// Triangle.cpp
// (c) Copyright 2017 MCQN Ltd.
//
// Code for the Triangle animated Neopixel baubles
#include "Triangle.h"
#include "MakeColour.h"

Triangle::Triangle(OctoWS2811& aLEDs, bool aInterlaced, uint32_t aFirstPixel)
    : Bauble(aLEDs, aInterlaced, aFirstPixel, aFirstPixel+kFullLength)
{
}

