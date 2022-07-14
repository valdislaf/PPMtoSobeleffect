#include "ppm_image.h"

#include <algorithm>
#include <array>
#include <cmath>
#include <iostream>
#include <string_view>

using namespace std;

int Sum(img_lib::Color c) {
    return to_integer<int>(c.r) + to_integer<int>(c.g) + to_integer<int>(c.b);
}


// реализуйте оператор Собеля
img_lib::Image Sobel(const img_lib::Image& image) {
    using namespace img_lib;
    int w = image.GetWidth();
    int h = image.GetHeight();
    Image image_new(w, h, Color::Black());
    for (int y = 1; y < h - 1; ++y) {
        const Color* line_y_m_1 = image.GetLine(y - 1);
        const Color* line_y = image.GetLine(y);
        const Color* line_y_p_1 = image.GetLine(y + 1);
        Color* image_new_y = image_new.GetLine(y);
        for (int x = 1; x < w - 1; ++x) {
            //gx=−tl−2tc−tr+bl+2bc+br,
            //gy=−tl−2cl−bl+tr+2cr+br.
            {
                int tl = static_cast<int>(line_y_m_1[x - 1].r);
                int tc = static_cast<int>(line_y_m_1[x].r);
                int tr = static_cast<int>(line_y_m_1[x + 1].r);
                int bl = static_cast<int>(line_y_p_1[x - 1].r);
                int bc = static_cast<int>(line_y_p_1[x].r);
                int br = static_cast<int>(line_y_p_1[x + 1].r);
                int cl = static_cast<int>(line_y[x - 1].r);
                int cr = static_cast<int>(line_y[x + 1].r);
                int gx = -tl - 2 * tc - tr + bl + 2 * bc + br;
                int gy = -tl - 2 * cl - bl + tr + 2 * cr + br;
                image_new_y[x].r = static_cast<byte>(std::clamp(std::sqrt(gx * gx + gy * gy), 0., 255.));
            }
            {
                int tl = static_cast<int>(line_y_m_1[x - 1].g);
                int tc = static_cast<int>(line_y_m_1[x].g);
                int tr = static_cast<int>(line_y_m_1[x + 1].g);
                int bl = static_cast<int>(line_y_p_1[x - 1].g);
                int bc = static_cast<int>(line_y_p_1[x].g);
                int br = static_cast<int>(line_y_p_1[x + 1].g);
                int cl = static_cast<int>(line_y[x - 1].g);
                int cr = static_cast<int>(line_y[x + 1].g);
                int gx = -tl - 2 * tc - tr + bl + 2 * bc + br;
                int gy = -tl - 2 * cl - bl + tr + 2 * cr + br;
                image_new_y[x].g = static_cast<byte>(std::clamp(std::sqrt(gx * gx + gy * gy), 0., 255.));
            }
            {
                int tl = static_cast<int>(line_y_m_1[x - 1].b);
                int tc = static_cast<int>(line_y_m_1[x].b);
                int tr = static_cast<int>(line_y_m_1[x + 1].b);
                int bl = static_cast<int>(line_y_p_1[x - 1].b);
                int bc = static_cast<int>(line_y_p_1[x].b);
                int br = static_cast<int>(line_y_p_1[x + 1].b);
                int cl = static_cast<int>(line_y[x - 1].b);
                int cr = static_cast<int>(line_y[x + 1].b);
                int gx = -tl - 2 * tc - tr + bl + 2 * bc + br;
                int gy = -tl - 2 * cl - bl + tr + 2 * cr + br;
                image_new_y[x].b = static_cast<byte>(std::clamp(std::sqrt(gx * gx + gy * gy), 0., 255.));
            }
           
        }
    }
    return  image_new;
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

    image = Sobel(image);

    if (!img_lib::SavePPM(argv[2], image)) {
        cerr << "Error saving image"sv << endl;
        return 3;
    }

    cout << "Image saved successfully!"sv << endl;
}