#pragma once

#include "MPoint3.h"

class MVector3 {
private:
    MPoint3 P;
public:
    MVector3() : P() {}

    MVector3(const MPoint3& p1, const MPoint3& p2) {
        P = MPoint3(p1.x() - p2.x(), p1.y() - p2.y(), p1.z() - p2.z());
    }
    MVector3(const MPoint3& p1) : P(p1) {}
    MVector3(double x, double y, double z) : P(x, y, z) {}
    MVector3(double v) : P(v, v, v) {}
    MVector3(const double* array) : P(array) {}
    MVector3(const MVector3& v) : P(v.P) {}
    double x(void) const { return P.x(); }
    double y(void) const { return P.y(); }
    double z(void) const { return P.z(); }
    double norm() const { return std::sqrt(this->norm2()); }
    double norm2() const { return P[0] * P[0] + P[1] * P[1] + P[2] * P[2]; }

    void normalize() {
        double n = norm();
        if (n) {
            P[0] /= n;
            P[1] /= n;
            P[2] /= n;
        }
    }
    MVector3 normalized() const {
        MVector3 v(*this);
        v.normalize();
        return v;
    }

    void negate() {
        P[0] = -P[0];
        P[1] = -P[1];
        P[2] = -P[2];
    }

    double& operator[](int i) { return P[i]; }
    double operator[](int i) const { return P[i]; }
    double& operator()(int i) { return P[i]; }
    double operator()(int i) const { return P[i]; }

    MVector3& operator+=(const MVector3& v) {
        P[0] += v[0];
        P[1] += v[1];
        P[2] += v[2];
        return *this;
    }
    MVector3& operator-=(const MVector3& v) {
        P[0] -= v[0];
        P[1] -= v[1];
        P[2] -= v[2];
        return *this;
    }
    MVector3& operator*=(const MVector3& v) {
        P[0] *= v[0];
        P[1] *= v[1];
        P[2] *= v[2];
        return *this;
    }
    MVector3& operator*=(const double a) {
        P[0] *= a;
        P[1] *= a;
        P[2] *= a;
        return *this;
    }
    MVector3& operator/=(const double a) {
        P[0] /= a;
        P[1] /= a;
        P[2] /= a;
        return *this;
    }
    MVector3& operator=(const MVector3& a) {
        P[0] = a[0];
        P[1] = a[1];
        P[2] = a[2];
        return *this;
    }
    MVector3& operator=(double a) {
        P[0] = a;
        P[1] = a;
        P[2] = a;
        return *this;
    }

    operator double* () { return P; }

    MPoint3 point() const { return P; }

    const double* data() const { return P.data(); }
    double* data() { return P.data(); }

    MVector3 cross(const MVector3& a) const {
        return MVector3(y() * a.z() - a.y() * z(), -(x() * a.z() - a.x() * z()), x() * a.y() - a.x() * y());
    }

    double dot(const MVector3& a) const {
        return x() * a.x() + y() * a.y() + z() * a.z();
    }
};

inline double dot(const MVector3& a, const MVector3& b) {
    return a.x() * b.x() + a.y() * b.y() + a.z() * b.z();
}

inline double norm(const MVector3& v) { return sqrt(dot(v, v)); }
inline double norm2(const MVector3& v) { return dot(v, v); }

inline MVector3 cross(const MVector3& a, const MVector3& b) {
    return MVector3(a.y() * b.z() - b.y() * a.z(),
        -(a.x() * b.z() - b.x() * a.z()),
        a.x() * b.y() - b.x() * a.y());
}

inline double angle(const MVector3& a, const MVector3& b) {
    double x = dot(a, b);
    double y = norm(cross(a, b));
    return atan2(y, x);
}
inline double signedAngle(const MVector3& a, const MVector3& b, const MVector3& n) {
    double x = dot(a, b);
    double y = dot(cross(a, b), n);
    return atan2(y, x);
}

inline MVector3 operator*(double m, const MVector3& v) { return MVector3(v[0] * m, v[1] * m, v[2] * m); }
inline MVector3 operator*(const  MVector3& v, double m) { return MVector3(v[0] * m, v[1] * m, v[2] * m); }
inline MVector3 operator*(const MVector3& v1, const MVector3& v2) { return MVector3(v1[0] * v2[0], v1[1] * v2[1], v1[2] * v2[2]); }

inline MVector3 operator+(const MVector3& a, const MVector3& b) { return MVector3(a[0] + b[0], a[1] + b[1], a[2] + b[2]); }
inline MPoint3  operator+(const MPoint3& a, const MVector3& b) { return MPoint3(a[0] + b[0], a[1] + b[1], a[2] + b[2]); }

inline MVector3 operator-(const MVector3& a, const MVector3& b) { return MVector3(a[0] - b[0], a[1] - b[1], a[2] - b[2]); }
inline MPoint3  operator-(const MPoint3& a, const MVector3& b) { return MPoint3(a[0] - b[0], a[1] - b[1], a[2] - b[2]); }
inline MVector3 operator-(const MPoint3& a, const MPoint3& b) { return MVector3(a.x() - b.x(), a.y() - b.y(), a.z() - b.z()); }
inline MVector3 operator-(const MVector3& a) { return MVector3(-a[0], -a[1], -a[2]); }

inline double operator|(const MVector3& a, const MVector3& b) { return a.x() * b.x() + a.y() * b.y() + a.z() * b.z(); }

inline MVector3 operator%(const MVector3& a, const MVector3& b) {
    return MVector3(a.y() * b.z() - b.y() * a.z(),
        -(a.x() * b.z() - b.x() * a.z()),
        a.x() * b.y() - b.x() * a.y());
}

inline void orthoBasis_naive(MVector3& dir, MVector3& dir1, MVector3& dir2)
{
    dir.normalize();
    if (dir[1] != 0.0 && dir[2] != 0.0) {
        dir1 = MVector3(1.0, 0.0, -dir[0] / dir[2]);
        dir2 = MVector3(dir[0] / dir[2],
            -(dir[0] * dir[0] + dir[2] * dir[2]) / (dir[1] * dir[2]), 1.0);
    }
    else if (dir[0] != 0.0 && dir[2] != 0.0) {
        dir1 = MVector3(-dir[1] / dir[0], 1.0, 0.0);
        dir2 = MVector3(1.0, dir[1] / dir[0],
            -(dir[1] * dir[1] + dir[0] * dir[0]) / (dir[0] * dir[2]));
    }
    else if (dir[0] != 0.0 && dir[1] != 0.0) {
        dir1 = MVector3(0.0, -dir[2] / dir[1], 1.0);
        dir2 = MVector3(-(dir[1] * dir[1] + dir[2] * dir[2]) / (dir[0] * dir[1]),
            1.0, dir[2] / dir[1]);
    }
    else if (dir[0] == 0.0 && dir[1] == 0.0) {
        dir1 = MVector3(0.0, 1.0, 0.0);
        dir2 = MVector3(1.0, 0.0, 0.0);
    }
    else if (dir[1] == 0.0 && dir[2] == 0.0) {
        dir1 = MVector3(0.0, 1.0, 0.0);
        dir2 = MVector3(0.0, 0.0, 1.0);
    }
    else if (dir[0] == 0.0 && dir[2] == 0.0) {
        dir1 = MVector3(1.0, 0.0, 0.0);
        dir2 = MVector3(0.0, 0.0, 1.0);
    }
    else {

    }
    dir1.normalize();
    dir2.normalize();
}

inline void orthoBasis(MVector3& normal, MVector3& tangent, MVector3& binormal) {
    normal.normalize();
    if (fabs(normal[0]) > fabs(normal[1]))
        tangent = MVector3(0.0, 1.0, 0.0);
    else
        tangent = MVector3(1.0, 0.0, 0.0);

    binormal = cross(tangent, normal);
    binormal.normalize();

    tangent = cross(normal, binormal);
    tangent.normalize();

    if (binormal.norm() == 0.0 || tangent.norm() == 0.0) orthoBasis_naive(normal, tangent, binormal);
}