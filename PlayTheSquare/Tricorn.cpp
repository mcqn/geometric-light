// Tricorn.cpp
// (c) Copyright 2017 MCQN Ltd.
//
// Code for the Tricorn animated Neopixel baubles
#include "Tricorn.h"
#include "MakeColour.h"

Tricorn::Tricorn(OctoWS2811& aLEDs, bool aInterlaced, uint32_t aFirstPixel)
    : Bauble(aLEDs, aInterlaced, aFirstPixel, aFirstPixel+kFullLength)
{
}

