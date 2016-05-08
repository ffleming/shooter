#pragma once
class Board {
    private:
    public:
        static float gravity;
        Board() : Board(1.4, 1.8, 0.05) {}
        Board(float cubeSize) : Board( cubeSize * 31, cubeSize * 35, cubeSize * 2) {}
        Board(float width, float height) : Board(width, height, 0.05) {}
        Board(float, float, float);
        void render(float);
        void update();
        float height;
        float width;
        float thickness;
        float bottomSurfaceY();
        float topSurfaceY();
        float leftSurfaceX();
        float rightSurfaceX();
};
