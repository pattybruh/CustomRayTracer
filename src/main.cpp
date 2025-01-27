
#include "Bvh.h"
#include "Camera.h"
#include "Material.h"
#include "Sphere.h"
#include "Quad.h"

/*
#include "utility.h"
#include "Hittable.h"
#include "HittableList.h"
#include "Sphere.h"
*/

const double ASPECT_RATIO = 16.0/9.0;
void spheres() {
	//camera 256
	Camera camera(512, ASPECT_RATIO, 50);
	camera.vFOV = 70.0;
	camera.maxBounce = 10;
	camera.bgColor = color(0.4,0.46,1.0);

	//world
	HittableList objList;

	std::shared_ptr<Material> ground = std::make_shared<Lambertian>(color(0.756, 0.604, 0.419));//193, 154, 107
	objList.add(std::make_shared<Sphere>(point3(0, -1000, 0), 1000, ground));

	std::shared_ptr<CheckerTexture> checkerGround = std::make_shared<CheckerTexture>(0.3, color(0.1, 0.1, 0.1), color(.9,.9,.9));
	objList.add(std::make_shared<Sphere>(point3(0, -1000, 0), 1000, std::make_shared<Lambertian>(checkerGround)));

	std::shared_ptr<Material> yellowDiff = std::make_shared<Lambertian>(color(1.0, 0.81, 0.2));//255, 207, 51
	std::shared_ptr<Material> purpleDiff= std::make_shared<Lambertian>(color(0.557, 0.141, 0.667));//142, 36, 170
	std::shared_ptr<Material> metalBall1 = std::make_shared<Metal>(color(0.6, 0.6, 0.6), 0);
	std::shared_ptr<Material> glassBall = std::make_shared<Dielectric>(1.5);
	camera.eye = point3(2,1.3,3);
	camera.lookAt = point3(0,0,-10);
	camera.up = vec3(0,1,0);
	camera.focusAngle = 0.0;
	camera.focusDist = 1.0;
	for(int i=0; i<2; i++) {
		for(int j=-1; j<1; j++) {
			double radius = random_double(0, 0.5);
			point3 center(i+random_double(), radius, j+random_double());
			if((center-point3(4, radius, 0)).length() > 0.9) {
				color c = color::random()*color::random();
				std::shared_ptr<Material> material = std::make_shared<Lambertian>(c);
				point3 center2 = center+vec3(0,random_double(0,0.5), 0);
				objList.add(std::make_shared<Sphere>(center, center2, radius, material));
			}
		}
	}
	//objList.add(std::make_shared<Sphere>(point3(-10, -3, -25), 8, yellowDiff));
	objList.add(std::make_shared<Sphere>(point3(3, 1.5, -3), 1.5, purpleDiff));
	objList.add(std::make_shared<Sphere>(point3(-1, 1, -1), 1, metalBall1));
	objList.add(std::make_shared<Sphere>(point3(-3, 0.7, -3), 0.7, glassBall));
	objList = HittableList(std::make_shared<BvhNode>(objList));
	camera.render(objList);
}
void bouncingSpheres() {
	//camera 256
	Camera camera(1280, ASPECT_RATIO, 50);
	camera.vFOV = 70.0;
	camera.maxBounce = 10;
	camera.bgColor = color(0.4,0.46,1.0);

	//world
	HittableList objList;

	std::shared_ptr<Material> ground = std::make_shared<Lambertian>(color(0.756, 0.604, 0.419));//193, 154, 107
	objList.add(std::make_shared<Sphere>(point3(0, -1000, 0), 1000, ground));

	std::shared_ptr<Material> yellowDiff = std::make_shared<Lambertian>(color(1.0, 0.81, 0.2));//255, 207, 51
	std::shared_ptr<Material> purpleDiff= std::make_shared<Lambertian>(color(0.557, 0.141, 0.667));//142, 36, 170
	std::shared_ptr<Material> metalBall1 = std::make_shared<Metal>(color(0.6, 0.6, 0.6), 0);
	std::shared_ptr<Material> glassBall = std::make_shared<Dielectric>(1.5);
	camera.eye = point3(2,1.3,5);
	camera.lookAt = point3(0,0,0);
	camera.up = vec3(0,1,0);
	camera.focusAngle = 0.0;
	camera.focusDist = 1.0;

	for(int i=-5; i<5; i++) {
		for(int j=-5; j<5; j++) {
			double matType = random_double();
			double radius = random_double(0, 0.5);
			point3 center(i+random_double(), radius, j+random_double());
			if((center-point3(4, radius, 0)).length() > 0.9) {
				std::shared_ptr<Material> material;
				if(matType < 0.6) {
					color c = color::random()*color::random();
					material = std::make_shared<Lambertian>(c);
					point3 center2(0,0,0);
					if(random_int(0, 1)) {
						center2 = center + vec3(0, random_double(0,0.5), 0);
					}
					objList.add(std::make_shared<Sphere>(center, center2, radius, material));
				}
				if(matType < 0.9) {
					color c = color::random(0.5, 1.0);
					material = std::make_shared<Metal>(c, random_double());
					objList.add(std::make_shared<Sphere>(center, radius, material));
				}
				else {
					material = std::make_shared<Dielectric>(1.5);
					objList.add(std::make_shared<Sphere>(center, radius, material));
				}
			}
		}
	}
	objList.add(std::make_shared<Sphere>(point3(-1, 1, 0), 1, purpleDiff));
	objList.add(std::make_shared<Sphere>(point3(3, 1.5, -4), 1.5, metalBall1));
	objList.add(std::make_shared<Sphere>(point3(-3, 0.7, -3), 0.7, glassBall));
	objList = HittableList(std::make_shared<BvhNode>(objList));
	camera.render(objList);
}
void squares() {
	//camera 256
	Camera camera(512, ASPECT_RATIO, 50);
	camera.vFOV = 70.0;
	camera.maxBounce = 10;
	camera.eye = point3(2,1.3,5);
	camera.lookAt = point3(0,0,0);
	camera.up = vec3(0,1,0);
	camera.focusAngle = 0.0;
	camera.focusDist = 1.0;
	camera.bgColor = color(0.4,0.46,1.0);

	//world
	HittableList objList;

	std::shared_ptr<Material> ground = std::make_shared<Lambertian>(color(0.756, 0.604, 0.419));//193, 154, 107
	objList.add(std::make_shared<Sphere>(point3(0, -1000, 0), 1000, ground));

	std::shared_ptr<Material> yellowDiff = std::make_shared<Lambertian>(color(1.0, 0.81, 0.2));//255, 207, 51
	objList.add(std::make_shared<Quad>(point3(0,1,-5), vec3(1,0,0), vec3(0,1,0), yellowDiff));


	objList = HittableList(std::make_shared<BvhNode>(objList));
	camera.render(objList);
}
void textureSphere() {
	//camera 256
	Camera camera(512, ASPECT_RATIO, 50);
	camera.vFOV = 70.0;
	camera.maxBounce = 10;
	camera.eye = point3(10,0,3);
	camera.lookAt = point3(0,0,0);
	camera.up = vec3(0,1,0);
	camera.focusAngle = 0.0;
	camera.focusDist = 1.0;
	camera.bgColor = color(0.4,0.46,1.0);

	//world
	HittableList objList;


	std::shared_ptr<CheckerTexture> checkerGround = std::make_shared<CheckerTexture>(0.3, color(0.1, 0.1, 0.1), color(.9,.9,.9));
	//objList.add(std::make_shared<Sphere>(point3(0, -1000, 0), 1000, std::make_shared<Lambertian>(checkerGround)));

	objList.add(std::make_shared<Sphere>(point3(0,10, 0), 10, std::make_shared<Lambertian>(checkerGround)));
	objList.add(std::make_shared<Sphere>(point3(0, -10, 0), 10, std::make_shared<Lambertian>(checkerGround)));



	//objList.add(std::make_shared<Sphere>(point3(-10, -3, -25), 8, yellowDiff));
	objList = HittableList(std::make_shared<BvhNode>(objList));
	camera.render(objList);
}
void light() {
	//camera 256
	Camera camera(512, ASPECT_RATIO, 50);
	camera.vFOV = 70.0;
	camera.maxBounce = 10;
	camera.eye = point3(0,2,4);
	camera.lookAt = point3(0,2,0);
	camera.up = vec3(0,1,0);
	camera.focusAngle = 0.0;
	camera.focusDist = 1.0;
	camera.bgColor = color(0,0,0);

	//world
	HittableList objList;


	std::shared_ptr<CheckerTexture> checkerGround = std::make_shared<CheckerTexture>(0.3, color(0.1, 0.1, 0.1), color(.9,.9,.9));
	std::shared_ptr<Material> purpleDiff= std::make_shared<Lambertian>(color(0.557, 0.141, 0.667));

	objList.add(std::make_shared<Sphere>(point3(0,-1000, 0), 1000, std::make_shared<Lambertian>(checkerGround)));
	objList.add(std::make_shared<Sphere>(point3(0, 2, -5), 2, purpleDiff));

	std::shared_ptr<DiffuseLight> light = std::make_shared<DiffuseLight>(color(3, 3, 3));
	objList.add(std::make_shared<Sphere>(point3(0, 7, -5), 1, light));

	objList = HittableList(std::make_shared<BvhNode>(objList));
	camera.render(objList);
}
int main() {
	int scene = 5;
	switch(scene) {
	case 1:
		spheres();
		break;
	case 2:
		bouncingSpheres();
		break;
	case 3:
		squares();
		break;
	case 4:
		textureSphere();
		break;
	case 5:
		light();
		break;
	default:
		break;
	}


}
