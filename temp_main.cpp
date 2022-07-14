#include "ppm_image.h"

#include <iostream>
#include <string_view>

using namespace std;

// реализуйте горизонтальное отражение
void HMirrInplace(img_lib::Image& image) {
    using namespace img_lib;
    using JSAMPLE = unsigned char;
    int w = image.GetWidth();
    int h = image.GetHeight();
    
    JSAMPLE image_buffer[1000000];
   
    int i = 0;
    for (int y = 0; y < h; ++y) {
        const Color* line = image.GetLine(y);
        for (int x = 0; x < w; ++x) {
            image_buffer[i++] = static_cast<unsigned char>(line[x].r);
            image_buffer[i++] = static_cast<unsigned char>(line[x].g);
            image_buffer[i++] = static_cast<unsigned char>(line[x].b);
        }
    }
    JSAMPLE* buffer = image_buffer;
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

    HMirrInplace(image);

    if (!img_lib::SavePPM(argv[2], image)) {
        cerr << "Error saving image"sv << endl;
        return 3;
    }

    cout << "Image saved successfully!"sv << endl;
}