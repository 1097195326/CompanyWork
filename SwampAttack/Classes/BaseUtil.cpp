//
//  BaseUtil.cpp
//  SwampAttack
//
//  Created by oceantech02 on 15/3/27.
//
//

#include "BaseUtil.h"

ActionInterval * BaseUtil::makeAnimateWithSprite(const std::string & name, int count)
{
    auto animation = Animation::create();
    for (int i = 1; i <= count; ++i)
    {
        std::string fileName = StringUtils::format("image/%s%00004d.png",name.c_str(),i);
        animation->addSpriteFrameWithFile(fileName);
    }
    animation->setDelayPerUnit(0.08);
    return Animate::create(animation);
}
ActionInterval * BaseUtil::makeAnimateWithNameAndIndex(const std::string & name, int count)
{
    auto spriteFrameCache = SpriteFrameCache::getInstance();
    auto animation = Animation::create();
    for (int i = 1; i <= count; ++i)
    {
//            char str[100] = {};
//            sprintf(str, "stone_hurt%002d.png",i);
//        log("str: %s",StringUtils::format("%s%00004d.png",name.c_str(),i).c_str());
        SpriteFrame * frame = spriteFrameCache->getSpriteFrameByName(
                                        StringUtils::format("%s%00004d.png",name.c_str(),i));
        animation->addSpriteFrame(frame);
    }
    animation->setDelayPerUnit(0.08);
    return Animate::create(animation);
}
ActionInterval * BaseUtil::makeAnimateWithNameIndexDelay(const std::string & name, int count, float delay)
{
    auto spriteFrameCache = SpriteFrameCache::getInstance();
    auto animation = Animation::create();
    for (int i = 1; i <= count; ++i)
    {
        SpriteFrame * frame = spriteFrameCache->getSpriteFrameByName(
                                                                     StringUtils::format("%s%00004d.png",name.c_str(),i));
        animation->addSpriteFrame(frame);
    }
    animation->setDelayPerUnit(delay);
    return Animate::create(animation);
}
void BaseUtil::addGray(Sprite* sp)
{
    do
    {
        GLchar* pszFragSource =
        "#ifdef GL_ES \n \
        precision mediump float; \n \
        #endif \n \
        uniform sampler2D u_texture; \n \
        varying vec2 v_texCoord; \n \
        varying vec4 v_fragmentColor; \n \
        void main(void) \n \
        { \n \
        // Convert to greyscale using NTSC weightings \n \
        vec4 col = texture2D(u_texture, v_texCoord); \n \
        float grey = dot(col.rgb, vec3(0.299, 0.587, 0.114)); \n \
        gl_FragColor = vec4(grey, grey, grey, col.a); \n \
        }";
        GLProgram* pProgram = new GLProgram();
        pProgram->initWithByteArrays(ccPositionTextureColor_vert, pszFragSource);
        sp->setGLProgram(pProgram);
        CHECK_GL_ERROR_DEBUG();
        
        sp->getGLProgram()->bindAttribLocation(GLProgram::ATTRIBUTE_NAME_POSITION, GLProgram::VERTEX_ATTRIB_POSITION);
        sp->getGLProgram()->bindAttribLocation(GLProgram::ATTRIBUTE_NAME_COLOR, GLProgram::VERTEX_ATTRIB_COLOR);
        sp->getGLProgram()->bindAttribLocation(GLProgram::ATTRIBUTE_NAME_TEX_COORD, GLProgram::VERTEX_ATTRIB_TEX_COORD);
        
        CHECK_GL_ERROR_DEBUG();
        
        sp->getGLProgram()->link();
        CHECK_GL_ERROR_DEBUG();
        
        sp->getGLProgram()->updateUniforms();
        CHECK_GL_ERROR_DEBUG();
    } while (0);
}
void BaseUtil::removeGray(Sprite* sp)
{
    do
    {
        GLProgram* pProgram = GLProgramCache::getInstance()->getGLProgram(GLProgram::SHADER_NAME_POSITION_TEXTURE_COLOR);
        sp->setGLProgram(pProgram);
        CHECK_GL_ERROR_DEBUG();
        
        
        sp->getGLProgram()->bindAttribLocation(GLProgram::ATTRIBUTE_NAME_POSITION, GLProgram::VERTEX_ATTRIB_POSITION);
        sp->getGLProgram()->bindAttribLocation(GLProgram::ATTRIBUTE_NAME_COLOR, GLProgram::VERTEX_ATTRIB_COLOR);
        sp->getGLProgram()->bindAttribLocation(GLProgram::ATTRIBUTE_NAME_TEX_COORD, GLProgram::VERTEX_ATTRIB_TEX_COORD);
        CHECK_GL_ERROR_DEBUG();
        
        sp->getGLProgram()->link();
        CHECK_GL_ERROR_DEBUG();
        
        sp->getGLProgram()->updateUniforms();
        CHECK_GL_ERROR_DEBUG();
    } while (0);
}