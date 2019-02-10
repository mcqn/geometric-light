// Icicle.cpp
// (c) Copyright 2017 MCQN Ltd.
//
// Code for the Icicle animated Neopixel baubles
#include "Icicle.h"
#include "MakeColour.h"

Icicle::Icicle(OctoWS2811& aLEDs, bool aInterlaced, uint32_t aFirstPixel)
    : Bauble(aLEDs, aInterlaced, aFirstPixel, aFirstPixel+kFullLength)
{
}

