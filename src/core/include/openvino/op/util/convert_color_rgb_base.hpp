// Copyright (C) 2018-2025 Intel Corporation
// SPDX-License-Identifier: Apache-2.0
//

#pragma once

#include "openvino/op/op.hpp"
#include "openvino/op/util/attr_types.hpp"

namespace ov {
namespace op {
namespace util {

/// \brief Base class for color conversion operation from RGB to NV12 format.
///    Input:
///        - Operation expects input shape in NHWC layout for RGB images.
///        - Output NV12 image can be represented in two ways:
///            a) Single plane: NV12 height dimension is 1.5x the image height. 'C' dimension shall be 1.
///            b) Two separate planes: Y and UV. In this case:
///               b1) Y plane has the same height as the image, with 'C' dimension equal to 1.
///               b2) UV plane has dimensions: 'H' = image_h / 2; 'W' = image_w / 2; 'C' dimension equals 2.
///        - Supported element types: u8 or any supported floating-point type.
///    Output:
///        - The output will be in NV12 format. For single plane, the tensor shape is adjusted accordingly;
///          for two-plane representation, two tensors (Y and UV) are produced.
/// \details Conversion from RGB to NV12 typically involves transforming RGB values into YUV space
///          using the appropriate coefficients, and then reordering the Y, U, and V channels into
///          NV12 format. This base class provides the necessary structure and attributes for implementing
///          such conversion operations.
class OPENVINO_API ConvertColorRGBBase : public Op {
public:
    /// \brief Exact conversion format details
    /// Currently supports conversion from RGB to NV12 (or similar variants such as NV21 if extended in the future).
    enum class ColorConversion : int { RGB_TO_NV12 = 0, RGB_TO_NV21 = 1 };

protected:
    ConvertColorRGBBase() = default;

    /// \brief Constructs a conversion operation from an input RGB image.
    /// \param arg          Node that produces the input tensor in RGB format (NHWC layout).
    /// \param format       Conversion format (e.g., RGB_TO_NV12).
    explicit ConvertColorRGBBase(const Output<Node>& arg, ColorConversion format);

    /// \brief Constructs a conversion operation from an RGB image represented with two nodes.
    ///        This constructor is useful if additional inputs are required (e.g., for separate processing
    ///        of image channels or extra auxiliary information).
    /// \param arg_rgb      Node that produces the primary RGB input tensor.
    /// \param arg_extra    Node for any auxiliary data required for conversion.
    /// \param format       Conversion format.
    ConvertColorRGBBase(const Output<Node>& arg_rgb, const Output<Node>& arg_extra, ColorConversion format);

public:
    OPENVINO_OP("ConvertColorRGBBase", "util");

    void validate_and_infer_types() override;

    bool visit_attributes(AttributeVisitor& visitor) override;

protected:
    /// \brief Checks if the provided element type is supported for conversion.
    bool is_type_supported(const ov::element::Type& type) const;

    /// \brief Specifies the conversion format (default is RGB_TO_NV12).
    ColorConversion m_format = ColorConversion::RGB_TO_NV12;
};

}  // namespace util
}  // namespace op
}  // namespace ov
