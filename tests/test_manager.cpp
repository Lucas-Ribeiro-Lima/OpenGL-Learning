#include <Manager.h>
#include <gtest/gtest.h>

namespace oriongl::core::storage {

static int constructions = 0;
class StubClass {
    int id;
    char ascii = '\0';

  public:
    StubClass(int id) : id(++constructions) {};
    StubClass(int id, char c) : id(id), ascii(c) {}
    int getId() { return id; };
    char getChar() { return ascii; };
};

class ManagerTest : public testing::Test {
  protected:
    static std::shared_ptr<Manager<StubClass>> mock_manager;

    void SetUp() override { mock_manager = std::make_shared<Manager<StubClass>>(); };
    void TearDown() override { mock_manager = nullptr; };
};

std::shared_ptr<storage::Manager<StubClass>> ManagerTest::mock_manager = nullptr;

TEST_F(ManagerTest, same_key_must_return_same_object) {
    auto stub1 = mock_manager->createResource(1);
    auto stub2 = mock_manager->createResource(1);

    EXPECT_EQ(stub1, stub2);
};

TEST_F(ManagerTest, odd_keys_must_return_different_objects) {
    auto stub1 = mock_manager->createResource(1);
    auto stub2 = mock_manager->createResource(2);

    EXPECT_NE(stub1, stub2);
}

TEST_F(ManagerTest, died_objects_must_be_recreated) {
    int first_construction = 0;
    {
        auto stub_scoped = mock_manager->createResource(1);
        first_construction = stub_scoped->getId();
    }

    auto stub_recreated = mock_manager->createResource(1);

    EXPECT_NE(first_construction, stub_recreated->getId());
}

TEST_F(ManagerTest, invalid_constructor_arguments_must_use_first_as_key) {
    auto stub1 = mock_manager->createResource("stub1", 2);
    auto stub2 = mock_manager->createResource("stub1", 3);

    // Actually ignores the argument and returns the cached key
    EXPECT_EQ(stub1, stub2);
    EXPECT_EQ(stub1->getId(), stub2->getId());
}

TEST_F(ManagerTest, must_forward_all_arguments_to_constructor) {
    auto stub = mock_manager->createResource(2, 's');
    EXPECT_EQ(stub->getId(), 2);
    EXPECT_EQ(stub->getChar(), 's');
}

} // namespace oriongl::core::storage
