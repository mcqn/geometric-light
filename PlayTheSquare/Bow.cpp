// Bow.cpp
// (c) Copyright 2017 MCQN Ltd.
//
// Code for the Bow animated Neopixel baubles
#include "Bow.h"
#include "MakeColour.h"

Bow::Bow(OctoWS2811& aLEDs, bool aInterlaced, uint32_t aFirstPixel)
    : Bauble(aLEDs, aInterlaced, aFirstPixel, aFirstPixel+kFullLength)
{
}

