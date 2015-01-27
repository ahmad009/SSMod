const char* va(const char* format, ...);

// flag settings
#define GAME_FLAG_DEDICATED             (1 << 0)

#define GAME_FLAG(x)                    ((_gameFlags & x) == x)

extern unsigned int _gameFlags;
void DetermineGameFlags();