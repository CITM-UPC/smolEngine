#include <vector>
#include <memory>
#include "BoundingBox.h"

class BVHNode {
public:
    BVHNode(const BoundingBox& bounds) : boundingBox(bounds) {}

    void SetLeftChild(std::shared_ptr<BVHNode> left) { leftChild = left; }
    void SetRightChild(std::shared_ptr<BVHNode> right) { rightChild = right; }
    const std::shared_ptr<BVHNode>& GetLeftChild() const { return leftChild; }
    const std::shared_ptr<BVHNode>& GetRightChild() const { return rightChild; }

    const BoundingBox& GetBoundingBox() const { return boundingBox; }

private:
    BoundingBox boundingBox;
    std::shared_ptr<BVHNode> leftChild;
    std::shared_ptr<BVHNode> rightChild;
};
