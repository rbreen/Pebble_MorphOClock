#pragma once

#define ANIMATION_DURATION 2500

/**** globals declaration ****/  
static bool s_animating = false;
  
/**** function declarations ****/
static void animate(int duration, int delay, AnimationImplementation *implementation, bool handlers);
static void animation_stopped(Animation *anim, bool stopped, void *context);
static void animation_started(Animation *anim, void *context);
