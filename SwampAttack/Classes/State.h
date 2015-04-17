//
//  State.h
//  SwampAttack
//
//  Created by oceantech02 on 15/4/16.
//
//

#ifndef __SwampAttack__State__
#define __SwampAttack__State__

template <typename _typeName>
class State {
public:
    virtual void Enter(_typeName *) = 0;
    virtual void Execute(_typeName *) = 0;
    virtual void Exit(_typeName *) = 0;
    virtual ~State(){}
};

//class State {
//public:
//    virtual void Enter(Human *) = 0;
//    virtual void Execute(Human *) = 0;
//    virtual void Exit(Human *) = 0;
//    virtual ~State(){}
//};

#endif /* defined(__SwampAttack__State__) */
