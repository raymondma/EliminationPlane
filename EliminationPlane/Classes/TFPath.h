//
//  TFPath.h
//  EliminationPlane
//
//  Created by 马 俊 on 13-6-3.
//
//

#ifndef __EliminationPlane__TFPath__
#define __EliminationPlane__TFPath__

#include "cocos2d.h"

USING_NS_CC;

class TFPath : public CCObject
{
public:
    TFPath();
    virtual ~TFPath();
    
    bool init(CCArray* cp);
    
    CCArray* getSpline() const {return spline_;}
protected:

private:
    CCArray* spline_;
};

#endif /* defined(__EliminationPlane__TFPath__) */
