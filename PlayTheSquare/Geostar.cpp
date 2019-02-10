// Geostar.cpp
// (c) Copyright 2017 MCQN Ltd.
//
// Code for the Geostar animated Neopixel baubles
#include "Geostar.h"
#include "MakeColour.h"

Geostar::Geostar(OctoWS2811& aLEDs, bool aInterlaced, uint32_t aFirstPixel)
    : Bauble(aLEDs, aInterlaced, aFirstPixel, aFirstPixel+kFullLength)
{
}

