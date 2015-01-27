#define CALL_NEAR32 0xE8U
#define JMP_NEAR32 0xE9U
#define NOP 0x90U
struct CallHook {
	BYTE bOriginalCode[5];
	PBYTE pPlace;
	void* pOriginal;
	void* hook;

	void initialize(DWORD place, void* hookToInstall = NULL);
	void installHook(void* hookToInstall = NULL);
	void releaseHook();
};

struct StompHook {
        BYTE bOriginalCode[15];
        BYTE bCountBytes;
        PBYTE pPlace;
        void* hook;
        bool jump;

        void initialize(DWORD place, void *hookToInstall = NULL, BYTE countBytes = 5, bool useJump = true);
        void installHook(void* hookToInstall = NULL);
        void releaseHook();
};
