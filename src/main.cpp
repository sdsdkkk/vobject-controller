#include <objcontroller.hpp>
#include <appwindow.hpp>

int main(int argc, char** argv) {
    ObjController *oc = new ObjController(10, 10, 10);

    appWindowStart(oc);

    return 0;
}
