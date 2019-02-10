// Star.cpp
// (c) Copyright 2017 MCQN Ltd.
//
// Code for the Star animated Neopixel baubles
#include "Star.h"
#include "MakeColour.h"

Star::Star(OctoWS2811& aLEDs, bool aInterlaced, uint32_t aFirstPixel)
    : Bauble(aLEDs, aInterlaced, aFirstPixel, aFirstPixel+kFullLength)
{
}

