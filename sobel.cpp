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
          
                int tl = Sum({ line_y_m_1[x - 1].r , line_y_m_1[x - 1].g,line_y_m_1[x - 1].b });
                int tc = Sum({ line_y_m_1[x].r, line_y_m_1[x].g, line_y_m_1[x].b });
                int tr = Sum({ line_y_m_1[x + 1].r,line_y_m_1[x + 1].g,line_y_m_1[x + 1].b });
                int bl = Sum({ line_y_p_1[x - 1].r,line_y_p_1[x - 1].g,line_y_p_1[x - 1].b });
                int bc = Sum({ line_y_p_1[x].r,line_y_p_1[x].g,line_y_p_1[x].b });
                int br = Sum({ line_y_p_1[x + 1].r, line_y_p_1[x + 1].g, line_y_p_1[x + 1].b });
                int cl = Sum({ line_y[x - 1].r,line_y[x - 1].g,line_y[x - 1].b });
                int cr = Sum({ line_y[x + 1].r,line_y[x + 1].g,line_y[x + 1].b });
                int gx = -tl - 2 * tc - tr + bl + 2 * bc + br;
                int gy = -tl - 2 * cl - bl + tr + 2 * cr + br;
                image_new_y[x].r = static_cast<byte>(std::clamp(std::sqrt(gx * gx + gy * gy), 0., 255.));
                image_new_y[x].g = static_cast<byte>(std::clamp(std::sqrt(gx * gx + gy * gy), 0., 255.));
                image_new_y[x].b = static_cast<byte>(std::clamp(std::sqrt(gx * gx + gy * gy), 0., 255.));          
          
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