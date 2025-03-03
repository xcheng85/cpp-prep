#pragma once

#include <iostream>
#include <memory>
#include <functional>

#include <common.h>

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

        namespace StaticPoly
        {
            template <typename BoxRenderer>
            class Box : public Stable::Object
            {
            public:
                Box() = delete;
                Box(float x, float y, float z,
                    std::unique_ptr<BoxRenderer> renderer)
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

                std::unique_ptr<BoxRenderer> _renderer;
            };

            template <typename SphereRenderer>
            class Sphere : public Stable::Object
            {
            public:
                Sphere() = delete;
                Sphere(float r, std::unique_ptr<SphereRenderer> renderer)
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
                std::unique_ptr<SphereRenderer> _renderer;
            };
        };

        namespace ValueSemantic
        {
            class Box : public Stable::Object
            {
            public:
                using BoxRenderer = std::function<void(const Box &)>;

                Box() = delete;
                Box(float x, float y, float z,
                    BoxRenderer renderer)
                    : _renderer(std::move(renderer)),
                      _x(x), _y(y), _z(z)
                {
                }

                virtual void render() override
                {
                    _renderer(*this);
                }

            private:
                float _x;
                float _y;
                float _z;

                BoxRenderer _renderer;
            };

            class Sphere : public Stable::Object
            {
            public:
                using SphereRenderer = std::function<void(const Sphere &)>;

                Sphere() = delete;
                Sphere(float r, SphereRenderer renderer)
                    : _renderer(std::move(renderer)),
                      _r(r)
                {
                }

                virtual void render() override
                {
                    _renderer(*this);
                }

            private:
                float _r;
                SphereRenderer _renderer;
            };
            // std::function and the functor
            class VulkanBoxRenderer
            {
            public:
                void operator()(const Box &box)
                {
                    LOG_I("VulkanBoxRenderer::operator()");
                }
            };

            class GLBoxRenderer
            {
            public:
                void operator()(const Box &box)
                {
                    LOG_I("GLBoxRenderer::operator()");
                }
            };

            class VulkanSphereRenderer
            {
            public:
                void operator()(const Sphere &box)
                {
                    LOG_I("VulkanSphereRenderer::operator()");
                }
            };
        }
    }

}