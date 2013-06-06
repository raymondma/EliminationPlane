//
//  CPathMoveComp.cpp
//  EliminationPlane
//
//  Created by 马 俊 on 13-6-5.
//
//

#include "CPathMoveComp.h"
#include "CPathManager.h"
#include "CPath.h"

CPathMoveComp::CPathMoveComp()
{
    
}



CPathMoveComp::~CPathMoveComp()
{
    
}



void CPathMoveComp::setParameter(CComponentParameter* parameter)
{
    CCString* s;
    if (parameter->getObjectParameter(PARAM_PATH_NAME, reinterpret_cast<CCObject**>(&s)))
    {
        path_ = PATH_MANAGER->getPathByName(s->getCString());
    }

}



void CPathMoveComp::onEnterComponent()
{
    elapse_ = 0.f;
    splineIdx_ = 0;
}



void CPathMoveComp::update(float dt)
{
    do
    {
        CC_BREAK_IF(getTarget() == NULL);

        const float INTV = 0.01f;
        elapse_ += dt;
        if (elapse_ >= INTV)
        {
            elapse_ -= INTV;
            if (path_)
            {
                CCArray* spline = path_->getSpline();
                CCPoint* pt = dynamic_cast<CCPoint*>(spline->objectAtIndex(splineIdx_));
                getTarget()->setSpritePosition(*pt);
                splineIdx_++;
                
                if (splineIdx_ >= spline->count())
                {
                    splineIdx_ = 0;
                }
            }
        }
    }while (false);
}


CVisibleObject* CPathMoveComp::getTarget()
{
    return dynamic_cast<CVisibleObject*>(CComponent::getTarget());
}
