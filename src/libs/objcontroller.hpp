#ifndef OBJCONTROLLER_HPP
#define OBJCONTROLLER_HPP

class ObjController {
    private:
        int _defX;
        int _defY;
        int _defZ;

    public:
        int x;
        int y;
        int z;
        
        ObjController() {
            _defX = 0;
            _defY = 0;
            _defZ = 0;
            
            calibratePositions();
        }

        ObjController(int defX, int defY, int defZ) {
            _defX = defX;
            _defY = defY;
            _defZ = defZ;

            calibratePositions();
        }

        ~ObjController() { };

        void calibratePositions() {
            setPositions(_defX, _defY, _defZ);
        }

        void setPositions(int newX, int newY, int newZ) {
            x = newX;
            y = newY;
            z = newZ;
        }
};

#endif
