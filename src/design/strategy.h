#pragma once

#include <iostream>
#include <memory>

// object/entity: Mesh
// function on entity: render
// function variation: solid/wireframe/point

namespace Strategy
{
    namespace Stable
    {
        class Object
        {
        public:
            Object() = default;
            virtual ~Object() = default;
            virtual void render() = 0;
        };

        template <typename T>
        class ObjectRenderer
        {
        public:
            virtual ~ObjectRenderer() = default;
            virtual void render(const T &) = 0;
        };
    }
    namespace Unstable
    {
        class Box;
        class Sphere;
        class VulkanBoxRenderer : public Stable::ObjectRenderer<Box>
        {
        public:
            virtual void render(const Box &) override
            {
                std::cout << "VulkanBoxRenderer::render" << std::endl;
            }
        };

        class VulkanSphereRenderer : public Stable::ObjectRenderer<Sphere>
        {
        public:
            virtual void render(const Sphere &) override
            {
                std::cout << "VulkanSphereRenderer::render" << std::endl;
            }
        };
        class Box : public Stable::Object
        {
        public:
            Box() = delete;
            Box(float x, float y, float z,
                std::unique_ptr<VulkanBoxRenderer> renderer)
                : _renderer(std::move(renderer)),
                  _x(x), _y(y), _z(z)
            {
            }

            virtual void render() override
            {
                _renderer->render(*this);
            }

        private:
            float _x;
            float _y;
            float _z;

            std::unique_ptr<VulkanBoxRenderer> _renderer;
        };

        class Sphere : public Stable::Object
        {
        public:
            Sphere() = delete;
            Sphere(float r, std::unique_ptr<VulkanSphereRenderer> renderer)
                : _renderer(std::move(renderer)),
                  _r(r)
            {
            }

            virtual void render() override
            {
                _renderer->render(*this);
            }

        private:
            float _r;
            std::unique_ptr<VulkanSphereRenderer> _renderer;
        };

    }
}