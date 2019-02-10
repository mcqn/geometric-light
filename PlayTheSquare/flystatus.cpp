// Copyright 2015 Julian Todd <julian@goatchurch.org.uk> freesteel.co.uk
// This work is free, see COPYING.WTFPL for more details.
#include "flystatus.h"
#include <Arduino.h>

#define P(x) 


ABFilter::ABFilter() :
    a(0), b(0), n(0)
{;}

ABFilter::ABFilter(const float* la, const float* lb, int ln, float ltimestep) :
    a(la), b(lb), n(ln), timestep(ltimestep)
{
    xybuff = (float*)malloc(2*n*sizeof(float)); 
    for (int i = 0; i < 2*n; i++)
        xybuff[i] = 0; 
    xybuffpos = 0; 

    t0 = -1.0; 
    prevt = -1.0; 
    prevx = -1.0; 
    sumX = 0.0; 
}

ABFilter::ABFilter(float b0, float ltimestep) :
    a(0), b(0), n(0), timestep(ltimestep)
{
    xybuff = (float*)malloc(3*sizeof(float)); // xybuff[0] is the y, xybuff[1] is the decayfactor, xybuff[2] is prev-y
    xybuff[0] = 0; 
    xybuff[1] = b0; 
    xybuff[2] = 0; 
    xybuffpos = -1; 

    t0 = -1.0; 
    prevt = -1.0; 
    prevx = -1.0; 
    sumX = 0.0; 
}

float ABFilter::expdecayfac(float dt, float decaypersec)
{
    return 1 - exp(-dt*decaypersec); 
} 


bool ABFilter::addvalueT(float t, float x)
{
    //P("addvalueT "); P(t); P(" "); P(x);     
    // assert t0 <= prevt <= t0 + timestep; 
    if (t <= t0) {
        prevx = x; 
    //P(" t<t0\n");         
        return false; 
    }
    if (t < t0 + timestep) {
        sumX += (t - prevt)*(x + prevx)*0.5; 
        prevt = t; 
        prevx = x; 
        //P(" t<t0+timestep\n");         
        return false; 
    }
    float lam = (t0 + timestep - prevt)/(t - prevt); 
    //assert 0 <= lam <= 1; 
    float xlam = prevx*(1 - lam) + x*lam; 
    //P(" lam "); P(lam); P(" xlam "); P(xlam); 
    // float tlam = prevt*(1 - lam) + t*lam == prevt + lam*(t - prevt) == prevt + (t0 + timestep - prevt) == t0 + timestep 
    sumX += (t0 + timestep - prevt)*(xlam + prevx)*0.5; 
    t0 = t0 + timestep; 
    nt0bytimestep++; 
    // TOL_ZERO(t0 - nt0bytimestep*timestep); 
    //P(" t0 "); P(t0); P("\n");     
    prevt = t0; 
    prevx = xlam; 
    return true; 
}

void ABFilter::addvalueF(float x)
{
//P("addvalueF "); P(x); P("\n");     
    if (n == 0) {
        float y = xybuff[0]; 
        xybuff[2] = y; 
        xybuff[0] = x*xybuff[1] + y*(1-xybuff[1]); 
        return; 
    }
    
    xybuff[xybuffpos] = x; 
    int j = xybuffpos; 
    float y = 0; 
    for (int i = 0; i < n; i++) {
        y += xybuff[j]*b[i]; 
        if (i != 0)
            y -= xybuff[j+n]*a[i]; 
        if (j == 0)
            j = n; 
        j -= 1; 
    }
    if (a[0] != 1)
        y /= a[0]; 
    xybuff[xybuffpos+n] = y; 
    xybuffpos += 1;
    if (xybuffpos == n)
        xybuffpos = 0; 
}

void ABFilter::firstvalue(float t, float x)
{
    nt0bytimestep = (int)floor(t/timestep); 
    t0 = nt0bytimestep*timestep; // get the timesteps syncronized!
    t0 = t; 
    prevt = t0; 
    prevx = x; 
    sumX = 0; 

    if (n == 0) {
        xybuff[0] = x; 
        P("Setting exp filter "); P(xybuff[0]); P("  dt "); P(timestep); P("\n"); 
        xybuff[2] = x; 
    } else {
        for (int i = 0; i < 2*n; i++)
            xybuff[i] = x; 
    }
}


void ABFilter::addvalue(float t, float x)
{
    if (t0 == -1) {
        firstvalue(t, x); 
        return; 
    }
    if (abs(t - t0) > timestep*64) {  
        firstvalue(t, x); 
        P(" big timestep, restarting filter\n"); 
        return; 
    }
    
    int i = 64; // protect against infinite loops
    while (addvalueT(t, x) && (i-- > 0)) {
        addvalueF(sumX/timestep); 
        sumX = 0; 
    }
}

float ABFilter::filtval()
{
    if (n == 0) 
        return xybuff[0]; 
    int j = (xybuffpos == 0 ? n-1 : xybuffpos-1); 
    return xybuff[j+n]; 
}

float ABFilter::difffiltval() 
{
    if (n == 0) 
        return (xybuff[0] - xybuff[2])/timestep; 
    int j = (xybuffpos == 0 ? n-1 : xybuffpos-1); 
    int j1 = (j == 0 ? n-1 : j-1); 
    float res = (xybuff[j+n] - xybuff[j1+n])/timestep; 
    return res; 
}

 
