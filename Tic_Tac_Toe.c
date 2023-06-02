#include <SDL2/SDL.h>

// Constants for the window size and Tic Tac Toe grid
const int WINDOW_WIDTH = 400;
const int WINDOW_HEIGHT = 400;
const int GRID_SIZE = 3;
const int CELL_SIZE = WINDOW_WIDTH / GRID_SIZE;

// Game state and player turn
enum CellState { EMPTY, X, O };
enum Player { PLAYER_X, PLAYER_O };
enum GameState { RUNNING, DRAW, WIN_X, WIN_O };

CellState grid[GRID_SIZE][GRID_SIZE];
Player currentPlayer;
GameState gameState;

// Initialize SDL and create a window
SDL_Window* window = NULL;
SDL_Renderer* renderer = NULL;

bool initializeSDL()
{
    if (SDL_Init(SDL_INIT_VIDEO) < 0)
    {
        printf("SDL initialization failed: %s\n", SDL_GetError());
        return false;
    }

    window = SDL_CreateWindow("Tic Tac Toe", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,
                              WINDOW_WIDTH, WINDOW_HEIGHT, SDL_WINDOW_SHOWN);
    if (window == NULL)
    {
        printf("Window creation failed: %s\n", SDL_GetError());
        return false;
    }

    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    if (renderer == NULL)
    {
        printf("Renderer creation failed: %s\n", SDL_GetError());
        return false;
    }

    return true;
}

void resetGame()
{
    currentPlayer = PLAYER_X;
    gameState = RUNNING;

    // Clear the grid
    for (int i = 0; i < GRID_SIZE; ++i)
    {
        for (int j = 0; j < GRID_SIZE; ++j)
        {
            grid[i][j] = EMPTY;
        }
    }
}

void handleInput(SDL_Event event)
{
    if (event.type == SDL_QUIT)
    {
        gameState = DRAW; // Exit the game
    }
    else if (event.type == SDL_MOUSEBUTTONDOWN)
    {
        if (gameState == RUNNING)
        {
            int mouseX = event.button.x;
            int mouseY = event.button.y;

            // Calculate the clicked cell based on the mouse position
            int clickedRow = mouseY / CELL_SIZE;
            int clickedColumn = mouseX / CELL_SIZE;

            // If the clicked cell is valid and empty, update the game state
            if (clickedRow >= 0 && clickedRow < GRID_SIZE &&
                clickedColumn >= 0 && clickedColumn < GRID_SIZE &&
                grid[clickedRow][clickedColumn] == EMPTY)
            {
                // Set the cell with the current player's symbol
                grid[clickedRow][clickedColumn] = (currentPlayer == PLAYER_X) ? X : O;

                // Check for a win or draw condition
                // ... (Implement the logic for checking win or draw condition)

                // Switch to the next player's turn
                currentPlayer = (currentPlayer == PLAYER_X) ? PLAYER_O : PLAYER_X;
            }
        }
    }
}

void render()
{
    // Clear the window
    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
    SDL_RenderClear(renderer);

    // Draw the Tic Tac Toe grid lines
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);

    for (int i = 1; i < GRID_SIZE; ++i)
    {
        SDL_RenderDrawLine(renderer, i * CELL_SIZE, 0, i * CELL_SIZE, WINDOW_HEIGHT);
        SDL_RenderDrawLine(renderer, 0, i * CELL_SIZE, WINDOW_WIDTH, i * CELL_SIZE);
    }

    // Draw X's and O's
    for (int i = 0; i < GRID_SIZE; ++i)
    {
        for (int j = 0; j < GRID_SIZE; ++j)
        {
            if (grid[i][j] == X)
            {
                // Render X symbol
                // ... (Implement drawing X symbol on the cell)
            }
            else if (grid[i][j] == O)
            {
                // Render O symbol
                // ... (Implement drawing O symbol on the cell)
            }
        }
    }

    // Present the rendered graphics on the screen
    SDL_RenderPresent(renderer);
}

void cleanupSDL()
{
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
}


