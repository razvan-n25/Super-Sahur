#include "Terrain.h"

Terrain::Terrain(float in_x, float in_y, CyberBlock in_type)
    : x(in_x), y(in_y), type(in_type),
      width(0.f), height(0.f) {}

Terrain::Terrain(const Terrain& other)
    : x(other.x), y(other.y), type(other.type),
      width(other.width), height(other.height) {}

Terrain& Terrain::operator=(const Terrain& other) {
    if (this != &other) {
        x      = other.x;
        y      = other.y;
        type   = other.type;
        width  = other.width;
        height = other.height;
    }
    return *this;
}

Terrain::~Terrain() = default;



std::ostream& operator<<(std::ostream& os, const Terrain& t) {
    os << "Terrain(type=";
    switch (t.type) {
        case CEMENT:        os << "CEMENT"; break;
        case LAVA:          os << "LAVA"; break;
        case PLATFORM:      os << "PLATFORM"; break;
        case JUMP_BOX_LOW:  os << "JUMP_BOX_LOW"; break;
        case JUMP_BOX_HIGH: os << "JUMP_BOX_HIGH"; break;
    }
    os << ", x=" << t.x << ", y=" << t.y
       << ", w=" << t.width << ", h=" << t.height << ")";
    return os;
}
