#include "svg.h"

#include <fstream>
#include <stdexcept>

void writePatternSVG(const std::string& filename, const std::vector<PatternPiece>& pieces) {
    std::ofstream out(filename);
    if (!out) throw std::runtime_error("Could not open SVG output file.");

    const double pixelsPerInch = 35.0;
    out << "<svg xmlns=\"http://www.w3.org/2000/svg\" width=\"1100\" height=\"850\" viewBox=\"0 0 1100 850\">\n";
    out << "<rect width=\"100%\" height=\"100%\" fill=\"white\"/>\n";
    out << "<g fill=\"none\" stroke=\"black\" stroke-width=\"2\">\n";

    double xOffset = 70.0;
    for (const PatternPiece& piece : pieces) {
        out << "<polyline points=\"";
        for (const Vec2& p : piece.boundary) {
            double x = xOffset + p.x * pixelsPerInch;
            double y = 70.0 + p.y * pixelsPerInch;
            out << x << "," << y << " ";
        }
        out << "\"/>\n";
        out << "<text x=\"" << xOffset << "\" y=\"45\" fill=\"black\" stroke=\"none\" font-family=\"sans-serif\" font-size=\"20\">" << piece.name << "</text>\n";
        xOffset += 480.0;
    }

    out << "</g>\n";
    out << "<text x=\"70\" y=\"820\" font-family=\"sans-serif\" font-size=\"14\">Prototype geometry only - verify measurements and seam geometry before sewing.</text>\n";
    out << "</svg>\n";
}
