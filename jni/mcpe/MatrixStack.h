#pragma once

class Vec3;

class Matrix {
public:
	void translate(const Vec3&);
};

class MatrixStack {
public:

	class Ref {
	public:
		MatrixStack* stack;
		Matrix* matrix;
	};


	static MatrixStack World;

	MatrixStack::Ref push();
};