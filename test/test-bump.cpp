#include <gtest/gtest.h>

#include <bump/bump.hpp>

class BoxTest : public ::testing::Test
{
public:
    BoxTest()
    {
        rectangle.dim.x = 4.0;
        rectangle.dim.y = 2.0;
    }

    bump::Box2d createTranslatedBox(const bump::Box2d& box, double x, double y)
    {
        bump::Box2d translated = box;
        translated.center.x += x;
        translated.center.y += y;
        return translated;
    }

protected:
    bump::Box2d rectangle;
};

TEST_F(BoxTest, intersectRectangle)
{
    {
        // completely overlap
        bump::Box2d box1 = rectangle;
        bump::Box2d box2 = box1;
        EXPECT_TRUE(box1.intersects(box2));
        EXPECT_TRUE(box2.intersects(box1));
    }

    // along x
    {
        // partially overlap
        bump::Box2d box1 = rectangle;
        bump::Box2d box2 = createTranslatedBox(box1, 2.0, 0.0);
        EXPECT_TRUE(box1.intersects(box2));
        EXPECT_TRUE(box2.intersects(box1));
    }
    {
        // edge overlap
        bump::Box2d box1 = rectangle;
        bump::Box2d box2 = createTranslatedBox(box1, 4.0, 0.0);
        double margin = 0.01;  // add a small margin to ensure the edges overlap
        EXPECT_TRUE(box1.intersects(box2, margin));
        EXPECT_TRUE(box2.intersects(box1, margin));
    }
    {
        // no overlap
        bump::Box2d box1 = rectangle;
        bump::Box2d box2 = createTranslatedBox(box1, 5.0, 0.0);
        EXPECT_FALSE(box1.intersects(box2));
        EXPECT_FALSE(box2.intersects(box1));
    }
    {
        // overlap margin
        bump::Box2d box1 = rectangle;
        bump::Box2d box2 = createTranslatedBox(box1, 5.0, 0.0);
        double margin = 1.01;
        EXPECT_TRUE(box1.intersects(box2, margin));
        EXPECT_TRUE(box2.intersects(box1, margin));
    }

    // along y
    {
        // partially overlap
        bump::Box2d box1 = rectangle;
        bump::Box2d box2 = createTranslatedBox(box1, 0.0, 1.0);
        EXPECT_TRUE(box1.intersects(box2));
        EXPECT_TRUE(box2.intersects(box1));
    }
    {
        // edge overlap
        bump::Box2d box1 = rectangle;
        bump::Box2d box2 = createTranslatedBox(box1, 0.0, 2.0);
        double margin = 0.01;  // add a small margin to ensure the edges overlap
        EXPECT_TRUE(box1.intersects(box2, margin));
        EXPECT_TRUE(box2.intersects(box1, margin));
    }
    {
        // no overlap
        bump::Box2d box1 = rectangle;
        bump::Box2d box2 = createTranslatedBox(box1, 0.0, 3.0);
        EXPECT_FALSE(box1.intersects(box2));
        EXPECT_FALSE(box2.intersects(box1));
    }
    {
        // overlap margin
        bump::Box2d box1 = rectangle;
        bump::Box2d box2 = createTranslatedBox(box1, 0.0, 3.0);
        double margin = 1.01;
        EXPECT_TRUE(box1.intersects(box2, margin));
        EXPECT_TRUE(box2.intersects(box1, margin));
    }
}
