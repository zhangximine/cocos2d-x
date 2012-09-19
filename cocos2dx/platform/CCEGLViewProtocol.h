#ifndef __CCEGLVIEWPROTOCOL_H__
#define __CCEGLVIEWPROTOCOL_H__

#include "ccTypes.h"

enum ResolutionPolicy
{
    // The entire application is visible in the specified area without trying to preserve the original aspect ratio. 
    // Distortion can occur, and the application may appear stretched or compressed.
    kResolutionExactFit,
    // The entire application fills the specified area, without distortion but possibly with some cropping, 
    // while maintaining the original aspect ratio of the application.
    kResolutionNoBorder,
    // The entire application is visible in the specified area without distortion while maintaining the original 
    // aspect ratio of the application. Borders can appear on two sides of the application.
    kResolutionShowAll,
    
    kResolutionUnKnown,
};

NS_CC_BEGIN

#define CC_MAX_TOUCHES  5

class EGLTouchDelegate;
class CCSet;

/**
 * @addtogroup platform
 * @{
 */

class CC_DLL CCEGLViewProtocol
{
public:
    CCEGLViewProtocol();
    virtual ~CCEGLViewProtocol();

    /** Force destorying EGL view, subclass must implement this method. */
    virtual void    end() = 0;
    
    /** Get whether opengl render system is ready, subclass must implement this method. */
    virtual bool    isOpenGLReady() = 0;
    
    /** Exchanges the front and back buffers, subclass must implement this method. */
    virtual void    swapBuffers() = 0;
    
    /** Open or close IME keyboard , subclass must implement this method. */
    virtual void    setIMEKeyboardState(bool bOpen) = 0;

    /** 
     * Get design resolution size.
     * If setDesignResolutionSize wasn't invoked, the result of this function return is the same as 'getFrameSize'
     */

    virtual const CCSize&  getSize() const;
    
    /**
     * Get the frame size of EGL view.
     * In general, it returns the screen size since the EGL view is a fullscreen view.
     */
    virtual const CCSize& getFrameSize() const;
    
    /**
     * Set the frame size of EGL view.
     */
    virtual bool setFrameSize(float width, float height);
    
    /**
     * Get the visible area size of opengl viewport.
     */
    virtual CCSize getVisibleSize() const;
    
    /**
     * Get the visible origin point of opengl viewport.
     */
    virtual CCPoint getVisibleOrigin() const;
    
    /** 
     * Set the design resolutin size.
     * You can't use it with enableRetina together.
     * @param width Design resolution width.
     * @param height Design resolution height.
     * @param resolutionPolicy The resolution policy you need, there are:
     *                         [1] kCCResolutionExactFit Fill screen, if the design resolution ratio of width and height is different from the screen resolution ratio, your game view will be stretched.
     *                         [2] kCCResolutionNoBorder Full screen without black border, if the design resolution ratio of width and height is different from the screen resolution ratio, two areas of your game view will be cut.
     *                         [3] kCCResolutionShowAll  Full screen with black border, if the design resolution ratio of width and height is different from the screen resolution ratio, two black border will be shown on the screen;
     */
    virtual void setDesignResolutionSize(float width, float height, ResolutionPolicy resolutionPolicy);
    
    /** Set touch delegate */
    virtual void setTouchDelegate(EGLTouchDelegate * pDelegate);
    
    /**
     * Set content scale factor.
     * @return If return true, it means the plaform supports retina display.
     */
    virtual bool setContentScaleFactor(float contentScaleFactor);
    
    /**
     * Set opengl view port rectangle with points.
     */
    virtual void setViewPortInPoints(float x , float y , float w , float h);
    
    /**
     * Set Scissor rectangle with points.
     */
    virtual void setScissorInPoints(float x , float y , float w , float h);
    
    /** 
     * Enable retina mode.
     * You can't use it with setDesignResolutionSize
     */
    virtual bool enableRetina();

    /** handle touch events by default, if you want to custom your handles, please override these functions */
    virtual void handleTouchesBegin(int num, int ids[], float xs[], float ys[]);
    virtual void handleTouchesMove(int num, int ids[], float xs[], float ys[]);
    virtual void handleTouchesEnd(int num, int ids[], float xs[], float ys[]);
    virtual void handleTouchesCancel(int num, int ids[], float xs[], float ys[]);

    /**
     * Get opengl view port rectangle.
     */
    const CCRect& getViewPortRect() const;
    
    /**
     * Get the scale factor of horizontal direction.
     * 
     */
    float getScaleX() const;
    
    /**
     * Get the scale factor of vertical direction.
     */
    float getScaleY() const;
    
    /**
     * Get whether the retina mode is enabled.
     */
    bool isRetinaEnabled() const;
private:
    void getSetOfTouchesEndOrCancel(CCSet& set, int num, int ids[], float xs[], float ys[]);
    
protected:
    EGLTouchDelegate* m_pDelegate;

    // real size of screen
    CCSize m_obScreenSize;
    // resolution size, it is the size the app resources designed for
    CCSize m_obDesignResolutionSize;
    // the view port size
    CCRect m_obViewPortRect;
    // the view name
    char   m_szViewName[50];
    
    float  m_fScaleX;
    float  m_fScaleY;
    ResolutionPolicy m_eResolutionPolicy;
    bool   m_bIsRetinaEnabled;
};

// end of platform group
/// @}

NS_CC_END

#endif /* __CCEGLVIEWPROTOCOL_H__ */
