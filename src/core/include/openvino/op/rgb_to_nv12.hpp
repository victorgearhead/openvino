#ifndef OPENVINO_OP_RGB_TO_NV12_HPP
#define OPENVINO_OP_RGB_TO_NV12_HPP

#include "openvino/op/util/convert_color_rgb_base.hpp"

namespace ov {
namespace op {
namespace v8 {

class RGBtoNV12 : public util::ConvertColorRGBBase {
public:
    OPENVINO_OP("RGBtoNV12", "opset8");

    RGBtoNV12(const Output<Node>& arg);

    RGBtoNV12(const Output<Node>& arg_y, const Output<Node>& arg_uv);

    std::shared_ptr<Node> clone_with_new_inputs(const OutputVector& new_args) const override;
};

} // namespace v8
} // namespace op
} // namespace ov

#endif // OPENVINO_OP_RGB_TO_NV12_HPP
