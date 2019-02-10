// Slant.cpp
// (c) Copyright 2017 MCQN Ltd.
//
// Code for the Slant animated Neopixel baubles
#include "Slant.h"
#include "MakeColour.h"

Slant::Slant(OctoWS2811& aLEDs, bool aInterlaced, uint32_t aFirstPixel)
    : Bauble(aLEDs, aInterlaced, aFirstPixel, aFirstPixel+kFullLength)
{
}

