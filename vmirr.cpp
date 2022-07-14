#include "ppm_image.h"

#include <algorithm>
#include <iostream>
#include <string_view>

using namespace std;

// реализуйте вертикальное отражение
void VMirrInplace(img_lib::Image& image) {
    using namespace img_lib;
    int w = image.GetWidth();
    int h = image.GetHeight();
    int hh = h;
    if (h % 2 != 0) { hh = h - 1; }
    for (int y = 0; y < hh / 2; ++y) {
        std::vector<Color> buff1(0);
        std::vector<Color> buff2(0);
        Color* line1 = image.GetLine(y);
        Color* line2 = image.GetLine(hh - y - 1);
        for (int x = 0; x < w; ++x) {
            buff1.push_back(line1[x]);
            buff2.push_back(line2[x]);
        }
        for (int x = 0; x < w; ++x) {
            line1[x] = buff2[x];
            line2[x] = buff1[x];
        }
        // swap_ranges(buff1.begin(), buff1.end(), buff2.begin()); 
    }

}

int main(int argc, const char** argv) {
    if (argc != 3) {
        cerr << "Usage: "sv << argv[0] << " <input image> <output image>"sv << endl;
        return 1;
    }

    auto image = img_lib::LoadPPM(argv[1]);
    if (!image) {
        cerr << "Error loading image"sv << endl;
        return 2;
    }

    VMirrInplace(image);

    if (!img_lib::SavePPM(argv[2], image)) {
        cerr << "Error saving image"sv << endl;
        return 3;
    }

    cout << "Image saved successfully!"sv << endl;
}