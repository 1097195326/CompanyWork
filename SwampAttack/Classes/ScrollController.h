//
//  ScrollController.h
//  SwampAttack
//
//  Created by oceantech02 on 15/5/4.
//
//

#ifndef __SwampAttack__ScrollController__
#define __SwampAttack__ScrollController__


enum CenterPoint
{
    leftTop,
//    center,
    leftBottom,
};
struct M_Vec2f
{
    float x;
    float y;
    // function
    M_Vec2f():x(0.0),y(0.0){}
    M_Vec2f(float _x,float _y):x(_x),y(_y){}
    void    add(M_Vec2f vec){
        x += vec.x;
        y += vec.y;
    }
    void    add(float _x,float _y){
        x += _x;
        y += _y;
    }
    void    mult(float d)
    {
        x *= d;
        y *= d;
    }
    
};
class ScrollController {
private:
    M_Vec2f     m_offSet;
    M_Vec2f     m_velocity;
    M_Vec2f     m_force;
    M_Vec2f     m_toOffSet;
    
    CenterPoint m_centerPoint;      // 坐标原点
    bool        m_horizontal;       // 水平
    bool        m_vertical;         // 垂直
    bool        m_undulate;         // 波动
    bool        m_isMoving;
    bool        m_isMoveToing;
    float       m_viewWidth;
    float       m_viewHeight;
    float       m_contentWidth;
    float       m_contentHeight;
    
public:
    ScrollController();
    ~ScrollController();
public:
    M_Vec2f getOffSet();
//    bool    get
    
    void    setCenterPoint(CenterPoint point);
    void    setHorizontal(bool canH);
    void    setVertical(bool canV);
    void    setUndulate(bool undulate);
    void    setViewWidth(float width);
    void    setViewHeight(float height);
    void    setContentWidth(float width);
    void    setContentHeight(float height);
    
    void    update(float data);
    void    updateVelocity(float ox, float oy);
    void    updateOffSet(float ox, float oy);
    void    moveToOffSet(float ox, float oy);
    
private:
    inline  M_Vec2f addMV(M_Vec2f a, M_Vec2f b)
    {
        return M_Vec2f(a.x + b.y, a.y + b.y);
    }
    inline  M_Vec2f minusMv(M_Vec2f a, M_Vec2f b)
    {
        return M_Vec2f(a.x - b.y, a.y - b.y);
    }
    inline  M_Vec2f multMV(M_Vec2f a, float d)
    {
        return M_Vec2f(a.x * d, a.y * d);
    }
};

#endif /* defined(__SwampAttack__ScrollController__) */
