#include "uv_gui.h"
int main (int argc, char *argv[])
{
    uv_window test (800, 600);
    uv_window sef (200, 100, 300, 300, &test);
    uv_window ssef (50, 50, 20, 20, &sef);
    run ();

    return 0;
};
