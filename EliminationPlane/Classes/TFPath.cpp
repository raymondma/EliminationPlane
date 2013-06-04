//
//  TFPath.cpp
//  EliminationPlane
//
//  Created by 马 俊 on 13-6-3.
//
//

#include "TFPath.h"

#define B_SPLINE(u, u_2, u_3, cntrl0, cntrl1, cntrl2, cntrl3) \
( \
( \
(-1*u_3 + 3*u_2 - 3*u + 1) * (cntrl0) + \
( 3*u_3 - 6*u_2 + 0*u + 4) * (cntrl1) + \
(-3*u_3 + 3*u_2 + 3*u + 1) * (cntrl2) + \
( 1*u_3 + 0*u_2 + 0*u + 0) * (cntrl3)   \
) / 6 \
)

#define CATMULL_ROM_SPLINE(u, u_2, u_3, cntrl0, cntrl1, cntrl2, cntrl3) \
( \
( \
(-1*u_3 + 2*u_2 - 1*u + 0) * (cntrl0) + \
( 3*u_3 - 5*u_2 + 0*u + 2) * (cntrl1) + \
(-3*u_3 + 4*u_2 + 1*u + 0) * (cntrl2) + \
( 1*u_3 - 1*u_2 + 0*u + 0) * (cntrl3)   \
) / 2 \
)

#define SPLINE  B_SPLINE


TFPath::TFPath()
: spline_(NULL)
{
    
}



TFPath::~TFPath()
{
    CC_SAFE_RELEASE(spline_);
}



bool TFPath::init(CCArray* cp)
{
    int division;
    int maxDivision = 0;
    float u, u_2, u_3;
    int cpCount = (int)cp->count();
    if (cpCount < 4) return false;
    
    CC_SAFE_RELEASE(spline_);
    spline_ = CCArray::create();
    CC_SAFE_RETAIN(spline_);
    
    cpCount -= 3;
    CCPoint cps[4];
    
    for (int i = 0; i < cpCount; ++i)
    {
        cps[0] = *dynamic_cast<CCPoint*>(cp->objectAtIndex(i));
        cps[1] = *dynamic_cast<CCPoint*>(cp->objectAtIndex(i+1));
        cps[2] = *dynamic_cast<CCPoint*>(cp->objectAtIndex(i+2));
        cps[3] = *dynamic_cast<CCPoint*>(cp->objectAtIndex(i+3));
        
        CCPoint startPoint;
        CCPoint endPoint;
        startPoint.x = SPLINE(0.f, 0.f, 0.f,
                              cps[0].x,
                              cps[1].x,
                              cps[2].x,
                              cps[3].x);
        startPoint.y = SPLINE(0.f, 0.f, 0.f,
                              cps[0].y,
                              cps[1].y,
                              cps[2].y,
                              cps[3].y);
        
        
        endPoint.x = SPLINE(1.f, 1.f, 1.f,
                            cps[0].x,
                            cps[1].x,
                            cps[2].x,
                            cps[3].x);
        endPoint.y = SPLINE(1.f, 1.f, 1.f,
                            cps[0].y,
                            cps[1].y,
                            cps[2].y,
                            cps[3].y);
        
        division = MAX(abs(startPoint.x-endPoint.x), abs(startPoint.y-endPoint.y));
        if (division > maxDivision)
        {
            maxDivision = division;
        }
        for(int j = 0; j < division; j++)
        {
            
			u = (float)j / division;
			u_2 = u * u;
			u_3 = u_2 * u;
            
            CCPoint* curveData = new CCPoint;
            curveData->autorelease();
            // Position
            curveData->x = SPLINE(u, u_2, u_3,
                                  cps[0].x,
                                  cps[1].x,
                                  cps[2].x,
                                  cps[3].x);
            
            curveData->y = SPLINE(u, u_2, u_3,
                                  cps[0].y,
                                  cps[1].y,
                                  cps[2].y,
                                  cps[3].y);
            
            spline_->addObject(curveData);
        }
    }
    
    return true;
}
