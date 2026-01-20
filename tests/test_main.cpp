#include <WindowSystem.h>
#include <gtest/gtest.h>
#include <memory.h>

namespace oriongl::test {
class Environment : public ::testing::Environment {
    std::unique_ptr<core::WindowSystem> ctx = nullptr;

    void SetUp() override { ctx = std::make_unique<core::WindowSystem>(); };

    void TearDown() override { ctx->closeWindow(); }
};

} // namespace oriongl::test

int main(int argc, char **argv) {
    ::testing::AddGlobalTestEnvironment(new oriongl::test::Environment);
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
