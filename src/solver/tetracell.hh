#pragma once

struct tetra_cell
{
    tetra_cell() {}
    tetra_cell(int up, int down, int right, int left)
    {
        this->up = up;
        this->down = down;
        this->right = right;
        this->left = left;
    }
    int up;
    int down;
    int right;
    int left;
};
