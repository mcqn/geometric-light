// Copyright 2015 Julian Todd <julian@goatchurch.org.uk> freesteel.co.uk
// This work is free, see COPYING.WTFPL for more details.

#ifndef FLYSTATUS_h
#define FLYSTATUS_h


class ABFilter
{
    const float* a; 
    const float* b; 
    const int n; 
    float* xybuff; 
    int xybuffpos; 
    
    float timestep; 
    float t0; 
    int nt0bytimestep; 
    float prevt; 
    float prevx; 
    float sumX; 
public:
    void firstvalue(float t, float x); 
    bool addvalueT(float t, float x); 
    void addvalueF(float x); 
    
public:
    ABFilter(const float* la, const float* lb, int ln, float ltimestep); 
    ABFilter(float b0, float ltimestep); 
    ABFilter();  
    void addvalue(float t, float x); 
    float filtval(); 
    float difffiltval(); 
    
    static float expdecayfac(float dt, float decaypersec); 
};



#endif
