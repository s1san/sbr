#ifndef SBR_SCENE_H
#define SBR_SCENE_H

#include "geometry.h"

struct Light {
    Light(const Vec3f& p, const float &i): position(p),intensity(i) {}
    Vec3f position;
    float intensity;
};

struct Material {
    Material(const Vec3f &color):diffuse_color(color) {}
    Material():diffuse_color() {}

    Vec3f diffuse_color;
};

struct Sphere
{
    Vec3f center;
    float radius;

    Material material;

    Sphere(const Vec3f& c, const float& r, const Material& m) : center(c), radius(r), material(m) {}

    bool ray_intersect( const Vec3f& orig, const Vec3f& dir, float& t0 ) const
    {
        Vec3f L   = center - orig;
        float tca = L * dir;
        float d2  = L * L - tca * tca;
        if ( d2 > radius * radius )
            return false;
        float thc = sqrtf( radius * radius - d2 );
        t0        = tca - thc;
        float t1  = tca + thc;
        if ( t0 < 0 )
            t0 = t1;
        if ( t0 < 0 )
            return false;
        return true;
    }
};

Vec3f cast_ray(const Vec3f& orig, const Vec3f& dir, const std::vector<Sphere>& spheres, const std::vector<Light>& lights);

bool scene_intersect(const Vec3f& orig, const Vec3f& dir, const std::vector<Sphere>& spheres, Vec3f& hit, Vec3f& N, Material& material);

#endif  // !SBR_SCENE_H