//
// Created by gfiorini on 11/8/24.
//

#ifndef BASETEST_H
#define BASETEST_H
#include <functional>
#include <iostream>
#include <memory>
#include <vector>

#include "Renderer.h"
#include "CameraController.h"

namespace Test {
    class BaseTest {
    public:
        BaseTest(Renderer& r) : m_Renderer(r) {
            m_Width = m_Renderer.GetWinWidth();
            m_Height = m_Renderer.GetWinHeigth();
            m_CameraController = CameraController(m_Width, m_Height);

        }
        virtual ~BaseTest() = default;

        virtual void OnUpdate(double deltaTime){}

        virtual void OnRender(){}

        virtual void OnImGuiRender(){}

        virtual void OnScroll(int xoffset, int yoffset){}

        void OnResize(int width, int height) {
            const auto aspectRatio = static_cast<float>(width) / static_cast<float>(height);
            std::cout << "Aspect ratio: " << aspectRatio << std::endl;
            m_Width = width;//m_Renderer.GetWinWidth();
            m_Height = height;//m_Renderer.GetWinHeigth();
        }

    protected:
        Renderer& m_Renderer;
        float m_Width;
        float m_Height;
        CameraController m_CameraController;
    };



    class TestMenu : public BaseTest {
    public:
        TestMenu(BaseTest *&currentTestPointer, Renderer &renderer);
        virtual ~TestMenu() = default;
        void OnRender() override;
        void OnImGuiRender() override;

        // https://isocpp.org/wiki/faq/templates#templates-defn-vs-decl
        template<typename  T>
        void registerTest(const std::string& testName, Renderer& renderer) {
            auto lambda = [&renderer]() { return new T(renderer); };
            m_Tests.push_back(std::make_pair(testName, lambda));
        }

    private:
        BaseTest*& m_CurrentTest;
        std::vector<std::pair<std::string, std::function<BaseTest*()>>> m_Tests;
    protected:

        //std::vector<std::pair<std::string, std::function<BaseTest*(Renderer&)>>> v;

    };


}
#endif //GLTEST_H
