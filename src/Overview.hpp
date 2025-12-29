#pragma once
#include <helpers/AnimatedVariable.hpp> 
#include <Compositor.hpp>
#include <desktop/view/LayerSurface.hpp>
#include <hyprutils/animation/AnimationConfig.hpp>
#include <vector>
#include <tuple>
#include <chrono>

class CHyprspaceWidget {

    bool active = false;

    int64_t ownerID;

    // animation override stuff
    Hyprutils::Animation::SAnimationPropertyConfig curAnimationConfig;
    Hyprutils::Animation::SAnimationPropertyConfig curAnimation;

    // for checking mouse hover for workspace drag and move
    // modified on draw call, accessed on mouse click and release
    std::vector<std::tuple<int, CBox>> workspaceBoxes;

    // for storing the fullscreen state of windows prior to overview activation (which unfullscreens all windows)
    std::vector<std::tuple<uint32_t, eFullscreenMode>> prevFullscreen;

    // for storing the layer alpha values prior to overview activation (which sets all panel to transparent when configured)
    std::vector<std::tuple<PHLLS, float>> oLayerAlpha;

    // for click-to-exit
    std::chrono::system_clock::time_point lastPressedTime = std::chrono::high_resolution_clock::now();

    bool swiping = false;
    // whether if the panel is active before the current swiping event
    bool activeBeforeSwipe = false;
    double avgSwipeSpeed = 0.;
    // number of swiping speed frames recorded
    int swipePoints = 0;
    
    double curSwipeOffset = 10.;

    // MIGRATION v0.52 : PHLANIMVAR est maintenant défini via <helpers/AnimatedVariable.hpp>
    // C'est un std::unique_ptr<CAnimatedVariable<T>>
    PHLANIMVAR<float> workspaceScrollOffset;

public:

    // for slide-in animation and swiping
    PHLANIMVAR<float> curYOffset;

    CHyprspaceWidget(uint64_t);
    ~CHyprspaceWidget();

    PHLMONITOR getOwner();
    bool isActive();

    void show();
    void hide();

    void updateConfig();

    // should be called active or not
    void draw();

    // reserves area on owner monitor
    void updateLayout();

    bool buttonEvent(bool, Vector2D coords);
    bool axisEvent(double, Vector2D coords);

    bool isSwiping();

    bool beginSwipe(IPointer::SSwipeBeginEvent);
    bool updateSwipe(IPointer::SSwipeUpdateEvent);
    bool endSwipe(IPointer::SSwipeEndEvent);

};