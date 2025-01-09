#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <stdarg.h>


// Built-in
typedef struct Instance {
    void* vtable;
    void* data;
} Instance;

Instance instance_new(void* vtable, void* data) {
    return (Instance) {
        .data = data,
        .vtable = vtable
    };
}

#define instance_call(self, method, ...)                                       \
    {                                                                          \
        typedef void (*Method)();                                              \
        (((Method*)((self)->vtable))[method])((self)->data, ##__VA_ARGS__);    \
    }


// Entity Trait (Singleton) (generated)
typedef struct EntityTrait {
    void (*update)();
    void (*render)();
} EntityTrait;
typedef enum EntityTraitIds {
    update,
    render,
} EntityTraitIds;


// Front-end
// Player struct of EntityTrait
typedef struct PlayerData {
    float x, y;
    float vx, vy;
    int health;
    bool isJumping;
} PlayerData;

void updatePlayer(PlayerData* self, float dt) {
    if (self->isJumping) {
        self->vy += 3.0f;
        self->isJumping = false;
    }
    
    self->x += self->vx * dt;
    self->y += self->vy * dt;

    self->vx *= 0.98f;
    self->vy += 0.918f;
}

void renderPlayer(PlayerData* self) {
    printf(
        "Player: %.1f, %.1f (isJumping: %d) (health: %d)\n",
        self->x,
        self->y,
        self->isJumping,
        self->health
    );
}


// Platform struct of EntityTrait
typedef struct PlatformData {
    float x, y;
    int w, h;
} PlatformData;

void updatePlatform(PlatformData* self, float dt) {
    self->x += 2.0f * dt;
}

void renderPlatform(PlatformData* self) {
    printf(
        "Platform: %.1f, %.1f (%d, %d)\n",
        self->x,
        self->y,
        self->w,
        self->h
    );
}


int main() {
    EntityTrait PlayerMethods = { updatePlayer, renderPlayer };
    EntityTrait PlatformMethods = { updatePlatform, renderPlatform };

    // Array of Player and Platform instances
    Instance entities[] = {
        instance_new(&PlayerMethods, &(PlayerData) { 2.0f, 0.0f, 0.0f, 3.0f, 20, false }),
        instance_new(&PlatformMethods, &(PlatformData) { 20.0f, 0.0f, 60, 20 }),
        instance_new(&PlayerMethods, &(PlayerData) { 0.0f, 0.0f, 1.0f, 0.0f, 20, true }),
        instance_new(&PlayerMethods, &(PlayerData) { -23.0f, 0.0f, 0.0f, -4.5f, 15, false }),
        instance_new(&PlatformMethods, &(PlatformData) { -20.0f, -20.0f, 120, 20 }),
        instance_new(&PlayerMethods, &(PlayerData) { 0.0f, 0.0f, 1.0f, 0.0f, 4, false }),
        instance_new(&PlatformMethods, &(PlatformData) { 0.0f, -80.0f, 60, 20 }),
    };

    // Call methods on each entity
    for (size_t i = 0; i < sizeof(entities) / sizeof(entities[0]); i++) {
        instance_call(&entities[i], update, 1.0f);
        instance_call(&entities[i], render);
    }

    return 0;
}
