#include "BrowserBackend.h"
#include "DesktopBackend.h"
#include "IBackend.h"

int main() {
    IBackend* b;
    #ifdef __EMSCRIPTEN__
    BrowserBackend bb;
    b= &bb;
    #else
    DesktopBackend db;
    b = &db;
    #endif
    b->init();
    b->do_main_loop();
    b->cleanup();
    return 0;
}
