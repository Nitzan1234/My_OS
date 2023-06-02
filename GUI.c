#include <stdio.h>
#include <stdbool.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_mixer.h>

// Constants for window dimensions
const int WINDOW_WIDTH = 800;
const int WINDOW_HEIGHT = 600;

// Background photo file path
const char* BACKGROUND_IMAGE_PATH = "background.jpg";

// Sound file path
const char* POWER_UP_SOUND_PATH = "power_up.wav";

// Button position and size
const int BUTTON_X = 100;
const int BUTTON_Y = 100;
const int BUTTON_WIDTH = 200;
const int BUTTON_HEIGHT = 100;

// SDL variables
SDL_Window* window = NULL;
SDL_Renderer* renderer = NULL;
SDL_Texture* buttonTexture = NULL;
SDL_Texture* backgroundTexture = NULL;
Mix_Chunk* powerUpSound = NULL;

// Function to initialize SDL, SDL_image, and SDL_mixer
bool initSDL() {
    // Initialize SDL
    if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO) < 0) {
        printf("SDL initialization failed: %s\n", SDL_GetError());
        return false;
    }

    // Initialize SDL_image
    int imgFlags = IMG_INIT_JPG | IMG_INIT_PNG;
    if (!(IMG_Init(imgFlags) & imgFlags)) {
        printf("SDL_image initialization failed: %s\n", IMG_GetError());
        return false;
    }

    // Initialize SDL_mixer
    if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) < 0) {
        printf("SDL_mixer initialization failed: %s\n", Mix_GetError());
        return false;
    }

    // Create the window
    window = SDL_CreateWindow("My OS GUI", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, WINDOW_WIDTH, WINDOW_HEIGHT, SDL_WINDOW_SHOWN);
    if (window == NULL) {
        printf("Window creation failed: %s\n", SDL_GetError());
        return false;
    }

    // Create the renderer
    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    if (renderer == NULL) {
        printf("Renderer creation failed: %s\n", SDL_GetError());
        return false;
    }

    return true;
}

// Function to load an image texture from file
SDL_Texture* loadImageTexture(const char* imagePath) {
    // Load the image
    SDL_Surface* surface = IMG_Load(imagePath);
    if (surface == NULL) {
        printf("Failed to load image texture: %s\n", IMG_GetError());
        return NULL;
    }

    // Create a texture from the surface
    SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, surface);
    if (texture == NULL) {
        printf("Failed to create image texture: %s\n", SDL_GetError());
        return NULL;
    }

    // Free the surface
    SDL_FreeSurface(surface);

    return texture;
}

// Function to load the button texture
bool loadTextures() {
    // Load the button texture
    buttonTexture = loadImageTexture("button.bmp");
    if (buttonTexture == NULL) {
        return false;
    }

    // Load the background texture
    backgroundTexture = loadImageTexture(BACKGROUND_IMAGE_PATH);
    if (backgroundTexture == NULL) {
        return false;
    }

    return true;
}

// Function to load the power-up sound
bool loadSound() {
    powerUpSound = Mix_LoadWAV(POWER_UP_SOUND_PATH);
    if (powerUpSound == NULL) {
        printf("Failed to load sound: %s\n", Mix_GetError());
        return false;
    }

    return true;
}

// Function to handle button click events
void handleButtonClick() {
    printf("Button clicked!\n");
    Mix_PlayChannel(-1, powerUpSound, 0);
}

// Function to handle events
void handleEvents() {
    SDL_Event event;
    while (SDL_PollEvent(&event)) {
        switch (event.type) {
            case SDL_QUIT:
                // Handle quit event
                // ...
                break;
            case SDL_MOUSEBUTTONDOWN:
                // Handle mouse button down event
                if (event.button.button == SDL_BUTTON_LEFT) {
                    int mouseX = event.button.x;
                    int mouseY = event.button.y;
                    if (mouseX >= BUTTON_X && mouseX < BUTTON_X + BUTTON_WIDTH &&
                        mouseY >= BUTTON_Y && mouseY < BUTTON_Y + BUTTON_HEIGHT) {
                        handleButtonClick();
                    }
                }
                break;
            default:
                // Handle other events
                // ...
                break;
        }
    }
}

// Function to render the GUI
void render() {
    // Clear the renderer
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
    SDL_RenderClear(renderer);

    // Render the background
    SDL_RenderCopy(renderer, backgroundTexture, NULL, NULL);

    // Render the button
    SDL_Rect buttonRect = { BUTTON_X, BUTTON_Y, BUTTON_WIDTH, BUTTON_HEIGHT };
    SDL_RenderCopy(renderer, buttonTexture, NULL, &buttonRect);

    // Present the renderer
    SDL_RenderPresent(renderer);
}

// Function to clean up SDL and SDL_image resources
void cleanupSDL() {
    SDL_DestroyTexture(buttonTexture);
    SDL_DestroyTexture(backgroundTexture);
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
    IMG_Quit();
}

// Function to clean up SDL_mixer resources
void cleanupSound() {
    Mix_FreeChunk(powerUpSound);
    Mix_CloseAudio();
}

// Main function
int main() {
    // Initialize SDL, SDL_image, and SDL_mixer
    if (!initSDL()) {
        return 1;
    }

    // Load textures
    if (!loadTextures()) {
        cleanupSDL();
        return 1;
    }

    // Load sound
    if (!loadSound()) {
        cleanupSDL();
        cleanupSound();
        return 1;
    }

    // Main loop
    bool quit = false;
    while (!quit) {
        handleEvents();
        render();

        // Check for quit condition
        // ...
    }

    // Clean up resources
    cleanupSDL();
    cleanupSound();

    return 0;
}

