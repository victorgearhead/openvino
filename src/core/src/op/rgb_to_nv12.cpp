// Copyright (C) 2018-2025 Intel Corporation
// SPDX-License-Identifier: Apache-2.0
//

#include "openvino/op/rgb_to_nv12.hpp"
#include "itt.hpp"

using namespace ov;
using namespace ov::op::v8;

RGBtoNV12::RGBtoNV12(const Output<Node>& arg)
    : util::ConvertColorRGBBase(arg, util::ConvertColorRGBBase::ColorConversion::RGB_TO_NV12) {
    constructor_validate_and_infer_types();
}

RGBtoNV12::RGBtoNV12(const Output<Node>& arg_y, const Output<Node>& arg_uv)
    : util::ConvertColorRGBBase(arg_y, arg_uv, util::ConvertColorRGBBase::ColorConversion::RGB_TO_NV12) {
    constructor_validate_and_infer_types();
}

std::shared_ptr<Node> RGBtoNV12::clone_with_new_inputs(const OutputVector& new_args) const {
    OV_OP_SCOPE(v8_RGBtoNV12_clone_with_new_inputs);
    OPENVINO_ASSERT(new_args.size() == 1 || new_args.size() == 2, "RGBtoNV12 shall have one or two input nodes");
    if (new_args.size() == 1) {
        return std::make_shared<RGBtoNV12>(new_args.at(0));
    } else {
        return std::make_shared<RGBtoNV12>(new_args.at(0), new_args.at(1));
    }
}
